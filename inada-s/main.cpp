#include <algorithm>
#include <boost/assign/list_of.hpp>
#include <fstream>
#include <iostream>
#include <vector>
#include "common.hpp"
using namespace std;

struct Problem2 {
  vector<point> points;
  vector<vector<int>> polygon_index;

  void init(istream& is) {
    int n;
    is >> n;
    points.resize(n);
    for (size_t i = 0; i < points.size(); ++i) {
      is >> points[i];
      // ps[i].ID = i;
    }

    int m;
    is >> m;
    polygon_index.resize(m);
    string s;
    getline(is, s);
    for (int i = 0; i < m; ++i) {
      getline(is, s);
      istringstream iss(s);
      for (int z; iss >> z; polygon_index[i].push_back(z))
        ;
    }
  }
};

// 穴あきは考えてない
// p1, p2はpolの交点でなければならない
vector<polygon> cut(const polygon& pol, point p1, point p2) {
  vector<polygon> res(2);
  // assert(bg::touches(polygon, p1), bg::touches(polygon, p2));

  vector<vector<point>> points(2);
  int prev_ccw = -10;
  for (int i = 0; i < pol.outer().size(); ++i) {
    auto p = pol.outer()[i];
    auto c = ccw(p1, p2, p);
    bool change = prev_ccw != -10 && prev_ccw != c;

    if (c == CCW::COUNTER_CLOCKWISE) {
      if (change) {
        bg::append(res[0], p1);
        bg::append(res[1], p1);
      }
      bg::append(res[0], p);
    } else if (c == CCW::CLOCKWISE) {
      if (change) {
        bg::append(res[0], p2);
        bg::append(res[1], p2);
      }
      bg::append(res[1], p);
    } else if (c == CCW::ONLINE_BACK) {
      assert(false);
    } else if (c == CCW::ONLINE_FRONT) {
      assert(false);
    } else if (c == CCW::ONSEGMENT) {
      bg::append(res[0], p);
      bg::append(res[1], p);
    }
    prev_ccw = c;
  }
  bg::correct(res[0]);
  bg::correct(res[1]);
  return res;
}

// p1, p2は targetの交点
polygon flip(const polygon& target, point p1, point p2) {
  auto ret = target;
  for (int i = 0; i < target.outer().size(); ++i) {
    if (bg::equals(target.outer()[i], p1)) {
    } else if (bg::equals(target.outer()[i], p2)) {
    } else {
      ret.outer()[i] = reflect(p1, p2, target.outer()[i]);
    }
  }
  bg::reverse(ret);
  return ret;
}

struct Answer {
  vector<point> from, to;
  vector<vector<int>> index;
  string output_format() {
    stringstream ss;

    ss << from.size() << endl;
    for (int i = 0; i < from.size(); ++i) {
      ss << from[i] << endl;
    }

    ss << index.size() << endl;
    for (int i = 0; i < index.size(); ++i) {
      ss << index[i].size();
      for (int j = 0; j < index[i].size(); ++j) {
        ss << " " << index[i][j];
      }
      ss << endl;
    }

    for (int i = 0; i < to.size(); ++i) {
      ss << to[i] << endl;
    }

    return ss.str();
  }
};

polygon convex_hull(Problem2 prob) {
  // 頂点集合から凸包求める
  polygon hull;
  auto points = prob.points;
  sort(begin(points), end(points), [](const point& a, const point& b) {
    if (a.y() == b.y()) return a.x() < b.x();
    return a.y() < b.y();
  });
  bg::append(hull, points[0]);
  int last_index = 0;

  while (true) {
    point vec;
    int best_index = -1;
    for (int i = 0; i < points.size(); ++i) {
      if (i == last_index) continue;
      auto v = points[i] - points[last_index];
      if (best_index == -1 || cross(vec, v) > 0) {
        best_index = i;
        vec = v;
      }
    }
    bg::append(hull, points[best_index]);
    if (best_index == 0) break;
    last_index = best_index;
  }
  return hull;
}

Answer solve_convex_hull(Problem2 prob) {
  vector<polygon> pols(prob.polygon_index.size());
  for (int i = 0; i < prob.polygon_index.size(); ++i) {
    polygon& pol = pols[i];
    for (int j = 0; j < prob.polygon_index[i].size(); ++j) {
      bg::append(pol, prob.points[prob.polygon_index[i][j]]);
    }
  }

  for (int i = 0; i < pols.size(); ++i) {
    gvPolygon(pols[i], gvColor(i));
  }

  gvNewTime();

  const auto hull = convex_hull(prob);
  const point hull_center = bg::return_centroid<point>(hull);

  vector<segment> tocut;
  auto& outer = hull.outer();
  for (int j = 1; j < outer.size(); ++j) {
    auto v = outer[j] - outer[j - 1];
    v /= norm(v);
    segment seg(outer[j - 1] + v * 2, outer[j - 1] - v * 2);
    tocut.push_back(seg);
  }

  struct polygon2 {
    int id = -1;
    int parent_id = -1;
    polygon pol;
  };

  struct Cut {
    segment seg;
    int step;
    int polygon_parent;
    int polygon_child1;
    int polygon_child2;
  };

  struct Node {
    vector<polygon2> pols;
  };

  Node node;
  node.pols.resize(1);
  node.pols[0].id = 1;
  int polygon_cnt = 2;
  bg::exterior_ring(node.pols[0].pol) =
      boost::assign::list_of<point>(0, 0)(0, 1)(1, 1)(1, 0)(0, 0);

  vector<Cut> history;
  vector<Node> nodes;
  nodes.push_back(node);

  for (int step = 0; step < 500; ++step) {
    const auto& cur = nodes[step];
    Node next = cur;

    gvNewTime();
    gvPolygon(hull, gvColor(0));
    for (int i = 0; i < cur.pols.size(); ++i) {
      gvPolygon(cur.pols[i].pol, gvColor(i + 1));
    }

    // 切りたい辺と交わってる交点をみつけて折る
    // 一つみつかったらつぎのステップへ
    bool found = false;
    for (int t = 0; t < tocut.size() && !found; ++t) {
      const auto& target = tocut[(step + t) % tocut.size()];

      for (auto& pol : cur.pols) {
        vector<point> out, tmp;
        const auto& outer = pol.pol.outer();
        for (int i = 1; i < outer.size(); ++i) {
          segment seg(outer[i], outer[i - 1]);
          auto v1 = outer[i] - outer[i - 1];
          auto v2 = target.first - target.second;
          if (cross(v1, v2) == 0) {
            continue;  // 平行
          }
          tmp.clear();
          bg::intersection(target, seg, tmp);
          if (tmp.size()) {
            out.insert(end(out), begin(tmp), end(tmp));
          }
        }

        if (out.size()) {
          sort(out.begin(), out.end(), [](const point& a, const point& b) {
            if (a.y() == b.y())
              return a.x() < b.x();
            else
              return a.y() < b.y();
          });
          out.erase(unique(out.begin(), out.end(),
                           [](const point& a, const point& b) {
                             return a.x() == b.x() && a.y() == b.y();
                           }),
                    out.end());

          if (out.size() != 2) {
            continue;
          }

          bool ok = true;
          for (int i = 1; i < outer.size(); ++i) {
            segment s1(outer[i], outer[i - 1]);
            segment s2(out[0], out[1]);
            if (bg::equals(s1, s2)) {
              ok = false;
              break;
            }
          }
          if (!ok) continue;

          found = true;

          auto separeted = cut(pol.pol, out[0], out[1]);
          for (int j = 0; j < separeted.size(); ++j) {
            gvPolygon(separeted[j], gvColor(j + 4));
          }

          auto area_hull = [&hull](const polygon& p) {
            std::vector<polygon> out;
            bg::intersection(hull, p, out);
            rational a = 0;
            for (const auto& o : out) {
              a += bg::area(o);
            }
            return a;
          };

          if (area_hull(separeted[1]) < area_hull(separeted[0])) {
            swap(separeted[0], separeted[1]);
          }
          auto flipped = flip(separeted[0], out[0], out[1]);
          next.pols.erase(
              remove_if(next.pols.begin(), next.pols.end(),
                        [&](const polygon2& a) { return a.id == pol.id; }),
              next.pols.end());

          polygon2 a;
          a.pol = std::move(flipped);
          a.id = polygon_cnt++;
          a.parent_id = pol.id;
          const int child1 = a.id;
          next.pols.push_back(a);

          a.pol = std::move(separeted[1]);
          a.id = polygon_cnt++;
          const int child2 = a.id;
          a.parent_id = pol.id;
          next.pols.push_back(a);

          Cut cut;
          cut.step = step;
          cut.seg = segment(out[0], out[1]);
          cut.polygon_parent = pol.id;
          cut.polygon_child1 = child1;
          cut.polygon_child2 = child2;
          history.push_back(cut);
        }
      }
    }

    if (found) {
      nodes.push_back(next);
    } else {
      break;
    }
  }

  reverse(begin(history), end(history));

  vector<polygon2> reversing;
  for (auto& p : nodes.back().pols) {
    reversing.push_back(p);
  }

  for (int h = 0; h < history.size(); ++h) {
    const auto& cut = history[h];
    gvNewTime();
    gvPolygon(hull, gvColor(0));
    gvSegment(history[h].seg, 0.1, gvColor(1));

    for (int i = 0; i < reversing.size(); ++i) {
      if (cut.polygon_child1 == reversing[i].id) {
        reversing[i].pol =
            flip(reversing[i].pol, cut.seg.first, cut.seg.second);
        reversing[i].id = cut.polygon_parent;
      } else if (cut.polygon_child2 == reversing[i].id) {
        reversing[i].id = cut.polygon_parent;
      }
    }
    for (int i = 0; i < reversing.size(); ++i) {
      bg::unique(reversing[i].pol);
    }
    for (int i = 0; i < reversing.size(); ++i) {
      gvPolygon(reversing[i].pol, gvColor(i));
    }
  }

  vector<point> all_points;
  for (int i = 0; i < reversing.size(); ++i) {
    for (auto& p : reversing[i].pol.outer()) {
      all_points.push_back(p);
    }
  }

  sort(all_points.begin(), all_points.end(),
       [](const point& a, const point& b) {
         if (a.y() == b.y())
           return a.x() < b.x();
         else
           return a.y() < b.y();
       });
  all_points.erase(unique(all_points.begin(), all_points.end(),
                          [](const point& a, const point& b) {
                            return a.x() == b.x() && a.y() == b.y();
                          }),
                   all_points.end());

  for (int i = 0; i < all_points.size(); ++i) {
    auto p1 = all_points[i];
    gvCircle(p1.x().convert_to<double>(), p1.y().convert_to<double>(), 0.01,
             gvColor(i));
  }

  map<int, vector<pair<int, point>>> mapping;
  vector<pair<int, point>> vppi;
  for (int i = 0; i < all_points.size(); ++i) {
    vppi.emplace_back(i, all_points[i]);
  }
  mapping[1] = vppi;

  reverse(begin(history), end(history));

  for (int h = 0; h < history.size(); ++h) {
    gvNewTime();
    gvSegment(history[h].seg, 0.1, gvColor(1));
    const auto& cut = history[h];
    const auto& m = mapping[cut.polygon_parent];
    const auto& cur = nodes[cut.step];

    for (int i = 0; i < cur.pols.size(); ++i) {
      gvPolygon(cur.pols[i].pol, gvColor(i));
    }

    for (auto& p : m) {
      auto& p1 = p.second;
      gvCircle(p1.x().convert_to<double>(), p1.y().convert_to<double>(), 0.01,
               gvColor(p.first));
    }

    const auto& nex = nodes[cut.step + 1];
    auto it = find_if(begin(nex.pols), end(nex.pols), [&](const polygon2& pol) {
      return pol.id == cut.polygon_child2;
    });
    assert(it != end(nex.pols));
    const auto& child2 = *it;
    for (const auto& p : m) {
      if (bg::intersects(child2.pol, p.second)) {
        mapping[cut.polygon_child2].push_back(p);
      } else {
        mapping[cut.polygon_child1].push_back(p);
        mapping[cut.polygon_child1].back().second =
            reflect(cut.seg.first, cut.seg.second, p.second);
      }
    }
  }

  vppi.clear();
  for (auto& p : nodes.back().pols) {
    vppi.insert(vppi.end(), mapping[p.id].begin(), mapping[p.id].end());
  }
  sort(begin(vppi), end(vppi),
       [](const pair<int, point>& a, const pair<int, point>& b) {
         return a.first < b.first;
       });
  assert(vppi.size() == all_points.size());

  Answer ans;
  ans.from = all_points;

  ans.index.resize(reversing.size());
  for (int i = 0; i < reversing.size(); ++i) {
    auto n = reversing[i].pol.outer().size() - 1;
    ans.index[i].resize(n);
    for (int j = 0; j < n; ++j) {
      const auto& p = reversing[i].pol.outer()[j];
      ans.index[i][j] =
          static_cast<int>(lower_bound(all_points.begin(), all_points.end(), p,
                                       [](const point& a, const point& b) {
                                         if (a.y() == b.y())
                                           return a.x() < b.x();
                                         else
                                           return a.y() < b.y();
                                       }) -
                           all_points.begin());
    }
  }

  for (const auto& p : vppi) {
    ans.to.push_back(p.second);
  }

  return ans;
}

pair<trans::translate_transformer<rational, 2, 2>,
     trans::translate_transformer<rational, 2, 2>>
get_trans_pair(const Problem2& base_prob, int i) {
  auto prob = base_prob;
  rational minx, miny, maxx, maxy;
  maxx = minx = base_prob.points[0].x();
  maxy = miny = base_prob.points[0].y();

  for (int i = 0; i < base_prob.points.size(); ++i) {
    minx = min(minx, base_prob.points[i].x());
    miny = min(miny, base_prob.points[i].y());
    maxx = max(maxx, base_prob.points[i].x());
    maxy = max(maxy, base_prob.points[i].y());
  }

  if (i % 4 == 0) {
    return make_pair(trans::translate_transformer<rational, 2, 2>(-minx, -miny),
                     trans::translate_transformer<rational, 2, 2>(minx, miny));
  } else if (i % 4 == 1) {
    return make_pair(
        trans::translate_transformer<rational, 2, 2>(-maxx + 1, -miny),
        trans::translate_transformer<rational, 2, 2>(maxx - 1, miny));
  } else if (i % 4 == 2) {
    return make_pair(
        trans::translate_transformer<rational, 2, 2>(-minx, -maxy + 1),
        trans::translate_transformer<rational, 2, 2>(minx, maxy - 1));
  } else {
    return make_pair(
        trans::translate_transformer<rational, 2, 2>(-maxx + 1, -maxy + 1),
        trans::translate_transformer<rational, 2, 2>(maxx - 1, maxy - 1));
  }
}

int main(int argc, char** argv) {
  // g_gvEnableFlag = false;
  g_gvDefaultAlpha = 64;
  if (argc == 1) return 1;
  string problem_path = argv[1];
  ifstream ifs(argv[1]);

  Problem2 base_prob;
  base_prob.init(ifs);

  for (int i = 0; i < 4; ++i) {
    auto trans = get_trans_pair(base_prob, i);
    auto prob = base_prob;
    for (int j = 0; j < base_prob.points.size(); ++j) {
      bg::transform(base_prob.points[j], prob.points[j], trans.first);
    }
    gvNewTime();
    gvOutput("%d", i);
    auto pol = convex_hull(prob);
    gvPolygon(pol, gvColor(i));
  }

  for (int i = 0; i < 4; ++i) {
    auto trans = get_trans_pair(base_prob, i);
    auto prob = base_prob;
    for (int j = 0; j < base_prob.points.size(); ++j) {
      bg::transform(base_prob.points[j], prob.points[j], trans.first);
    }
    auto ans = solve_convex_hull(prob);
    for (int j = 0; j < ans.to.size(); ++j) {
      auto tmp = ans.to[j];
      bg::transform(tmp, ans.to[j], trans.second);
    }
    auto str = ans.output_format();
    cerr << str.length() << endl;
    if (str.length() <= 5000) {
      cout << str;
      break;
    }
  }
}
