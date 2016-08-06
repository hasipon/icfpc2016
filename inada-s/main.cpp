#include <boost/assign/list_of.hpp>
#include <iostream>
#include "common.hpp"

using namespace std;

void gvBox(const box& b, GV_RGB rgb) {
  const auto p1 = b.min_corner();
  const auto p2 = b.max_corner() - b.min_corner();
  const auto x = p1.x().convert_to<double>();
  const auto y = p1.y().convert_to<double>();
  const auto w = p2.x().convert_to<double>();
  const auto h = p2.y().convert_to<double>();
  gvRect(x, y, w, h, rgb);
}

void gvPolygon(const polygon& pol, GV_RGB rgb) {
  gvPolygon(rgb, [&pol]() {
    bg::for_each_point(pol, [&](const point& p) {
      const auto x = p.x().convert_to<double>();
      const auto y = p.y().convert_to<double>();
      gvPolygonAdd(x, y);
    });
  });
}

void gvSegment(const segment& s, double r, GV_RGB rgb) {
  const auto p1 = s.first;
  const auto p2 = s.second;
  const auto x1 = p1.x().convert_to<double>();
  const auto y1 = p1.y().convert_to<double>();
  const auto x2 = p2.x().convert_to<double>();
  const auto y2 = p2.y().convert_to<double>();
  gvLine(x1, y1, x2, y2, r, rgb);
}
void gvSegment(const segment& s, GV_RGB rgb) { gvSegment(s, 0.5, rgb); }

int main() {
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
}
