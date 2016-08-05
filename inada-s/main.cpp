//#define GV_JS
//#include "gv.hpp"

#include <boost/assign/list_of.hpp>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
using namespace std;
using namespace boost::multiprecision;

namespace bg = boost::geometry;
using point = bg::model::d2::point_xy<cpp_rational>;
using box = bg::model::box<point>;
using polygon = bg::model::polygon<point>;

int main() {
  // box
  {
    const box x(point(0, 0), point(3, 3));
    const auto result = bg::area(x);
    std::cout << result << std::endl;
  }
  // polygon
  {
    polygon x;
    bg::exterior_ring(x) =
        boost::assign::list_of<point>(0, 0)(0, 3)(3, 3)(0, 0);

    const auto result = bg::area(x);
    std::cout << result << std::endl;
  }
}
