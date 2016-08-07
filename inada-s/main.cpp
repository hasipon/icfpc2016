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

int main(int argc, char** argv) {
  if (argc == 1) return 1;
  string problem_path = argv[1];
  ifstream ifs(argv[1]);

  Problem2 prob;
  prob.init(ifs);

  vector<vector<point>> vps;
  for (int i = 0; i < prob.polygon_index.size(); ++i) {
    vector<point> vp;
    for (int j = 0; j < prob.polygon_index[i].size(); ++j) {
      vp.push_back(prob.points[prob.polygon_index[i][j]]);
    }
    vps.push_back(vp);
  }

  for (int i = 0; i < vps.size(); ++i) {
    const auto& vp = vps[i];
    polygon pol;
    for (int j = 0; j < vp.size(); ++j) {
      bg::append(pol, vp[j]);
    }
    // bg::assign(pol, vp);
    gvPolygon(pol, gvColor(i));
  }
  /*
    // box
    {
      g_gvDefaultAlpha = 128;
      const box x(point(0, 0), point(3, 3));
      const auto result = bg::area(x);
      std::cout << result << std::endl;
      gvBox(x, gvColor(0));
      const box y(point(1, 1), point(4, 4));
      gvBox(y, gvColor(2));
    }
    // polygon
    {
      gvNewTime();
      polygon x;
      bg::exterior_ring(x) =
          boost::assign::list_of<point>(0, 0)(0, 3)(3, 3)(0, 0);

      const auto result = bg::area(x);
      gvPolygon(x, gvColor(9));
      std::cout << result << std::endl;
    }
    {
      const box a(point(0, 0), point(3, 3));
      const box b(point(4, 4), point(7, 7));
      cout << bg::disjoint(a, b) << endl;
    }

    {
      gvNewTime();
      segment s(point(1, 1), point(3, 3));
      gvSegment(s, 0.1, gvColor(4));
    }
   */
}
