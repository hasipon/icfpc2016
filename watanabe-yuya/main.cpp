#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp> 
#include <boost/geometry/geometries/segment.hpp>
#include <boost/geometry/algorithms/intersection.hpp>

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/gmp.hpp>
#include <boost/multiprecision/number.hpp>

namespace bg = boost::geometry;
namespace bm = boost::multiprecision;

typedef bm::number<bm::gmp_rational, bm::et_off> rational;
// typedef bm::cpp_rational rational;
typedef bg::model::d2::point_xy<rational> point;
typedef bg::model::segment<point> segment;
typedef bg::model::polygon<point> polygon;
typedef bg::model::box<point> box;

const rational eps = rational("1e-10");
const rational PI = rational(M_PI);

point operator -= (point& a, point b)
{
  bg::subtract_point(a, b);
  return a;
}

point operator += (point& a, point b)
{
  bg::add_point(a, b);
  return a;
}

template<typename T>
point operator *= (point& a, T t)
{
  multiply_value(a, t);
  return a;
}

template<typename T>
point operator /= (point& a, T t)
{
  divide_value(a, t);
  return a;
}

point operator - (point a, point b)
{
  point c = a;
  c -= b;
  return c;
}

point operator + (point a, point b)
{
  point c = a;
  c += b;
  return c;
}

template<typename T>
point operator * (point a, T t)
{
  point b = a;
  b *= t;
  return b;
}

template<typename T>
point operator / (point a, T t)
{
  point b = a;
  b /= t;
  return b;
}

rational score(const polygon& submition, const polygon& solution)
{
  std::vector<polygon> or_;
  std::vector<polygon> and_;

  bg::union_(submition, solution, or_);
  bg::intersection(submition, solution, and_);

  rational o(0, 1);
  rational a(0, 1);

  for (std::vector<polygon>::iterator i = or_.begin(); i != or_.end(); ++i) {
    o += bg::area(*i);
  }

  for (std::vector<polygon>::iterator i = and_.begin(); i != and_.end(); ++i) {
    a += bg::area(*i);
  }

  return a / o;
}

rational norm(point a)
{
  return a.x() * a.x() + a.y() * a.y();
}
rational dot(point a, point b)
{
  return a.x() * b.x() + a.y() * b.y();
}
rational cross(point a, point b)
{
  return a.x() * b.y() - a.y() * b.x();
}

point project(point s1, point s2, point p) {
  point base = s2 - s1;
  rational t = dot(p - s1, base) / norm(base);
  return s1 + base * t;
}

enum CCW {
  COUNTER_CLOCKWISE = 1,
  CLOCKWISE = -1,
  ONLINE_BACK = 2,
  ONLINE_FRONT = -2,
  ONSEGMENT = 0
};

CCW ccw(point p0, point a, point b) {
  a -= p0;
  b -= p0;
  if(cross(a, b) > eps) return CCW::COUNTER_CLOCKWISE;
  if(cross(a, b) < -eps) return CCW::CLOCKWISE;
  if(dot(a, b) < -eps) return CCW::ONLINE_BACK;
  if(norm(b)-norm(a) > eps) return CCW::ONLINE_FRONT;
  return CCW::ONSEGMENT;
}


#define each(i, c) for (auto& i : c)
#define unless(cond) if (!(cond))

using namespace std;

typedef long long int lli;
typedef unsigned long long ull;

template<typename P, typename Q>
ostream& operator << (ostream& os, pair<P, Q> p)
{
  os << "(" << p.first << "," << p.second << ")";
  return os;
}

int main(int argc, char *argv[])
{
  stringstream ss("10/3");
  rational r;
  ss >> r;
  cout << r << endl;
  return 0;
}
