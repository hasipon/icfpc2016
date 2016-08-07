#include <ostream>
#include <sstream>

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

const rational eps = rational("1/1000000000");
const rational PI = rational(M_PI);
const point ORIGIN(0, 0);

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
  bg::multiply_value(a, t);
  return a;
}

template<typename T>
point operator /= (point& a, T t)
{
  bg::divide_value(a, t);
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

std::ostream& operator << (std::ostream& os, const point& a)
{
  os << a.x() << "," << a.y();
  return os;
}

std::istream& operator >> (std::istream& is, point& a)
{
  
  std::string s;
  is >> s;
  replace(s.begin(), s.end(), ',', ' ');
  std::stringstream ss(s);
  rational x, y;
  ss >> x >> y;
  a.x(x);
  a.y(y);
  return is;
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

// rational abs (point a)
// {
//   return sqrt(norm(a));
// }

point project(point s1, point s2, point p) {
  point base = s2 - s1;
  rational t = dot(p - s1, base) / norm(base);
  return s1 + base * t;
}

point reflect(point s1, point s2, point p)
{
  return p + (project(s1, s2, p) - p)*2.0;
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

// double getAngle(point a, point b)
// {
//   return acos(dot(a, b) / (abs(a) * abs(b)));
// }

// double getAngle(point a)
// {
//   return atan2(a.real(), a.imag());
// }

// vector<polygon> convex_cut() {}


// -----------------------------------------------------------------------------------------

#define each(i, c) for (auto& i : c)
#define unless(cond) if (!(cond))

using namespace std;

typedef long long int lli;
typedef unsigned long long ull;

template<typename P, typename Q>
ostream& operator << (ostream& os, pair<P, Q> p)
{
  os << "<" << p.first << "," << p.second << ">";
  return os;
}

void f(istream& is, ostream& os)
{
  // silhouette
  int ps;
  unless (is >> ps) return ;
  
  polygon p, q;
  for (int i = 0; i < ps; ++i) {
    int n;
    is >> n;
    for (int j = 0; j < n; ++j) {
      point x;
      is >> x;
      p.outer().push_back(x);
    }
  }

  // skeleton
  is >> ps;
  for (int i = 0; i < ps; ++i) {
    point x;
    is >> x >> x;
  }

  bg::convex_hull(p, q);
  os << 1 << endl;
  os << q.outer().size() - 1 << endl;
  for (int i = 0; i + 1 < q.outer().size(); ++i) {
    os << q.outer().at(i) << endl;
  }
  os << 0 << endl;

  return ;
}

int main(int argc, char *argv[])
{
  f(cin, cout);
  return 0;
}
