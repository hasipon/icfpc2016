#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>

#define each(i, c) for (auto& i : c)
#define unless(cond) if (!(cond))

using namespace std;
using namespace boost::multiprecision;

typedef long long int lli;
typedef unsigned long long ull;
typedef complex<double> point;
typedef cpp_rational rational;

template<typename P, typename Q>
ostream& operator << (ostream& os, pair<P, Q> p)
{
  os << "(" << p.first << "," << p.second << ")";
  return os;
}

const vector<string> cs = {
  "grey",
  "red",
  "blue",
  "navy",
  "cyan",
  "magenta",
  "turquoise",
  "pink",
  "coral",
  "orange-red",
  "salmon",
  "aquamarine",
  "khaki",
  "goldenrod",
  "gold",
  "beige",
  "brown",
  "orange",
  "violet",
  "plum",
  "purple",
  "yellow",
  "green"};

istream& operator >> (istream& is, pair<rational, rational>& p)
{
  string s;
  is >> s;
  replace(s.begin(), s.end(), ',', ' ');
  stringstream ss(s);
  ss >> p.first >> p.second;
  return is;
}

void f(int id)
{
  char buff[1000];

  sprintf(buff, "../../problems/%d.txt", id);
  ifstream fin(buff, ifstream::in);

  vector<vector<pair<rational, rational>>> silhouette;
  typedef pair<rational, rational> point;
  vector<pair<point, point>> skeleton;

  {
    int p;
    unless (fin >> p) return ;

    silhouette.resize(p);
    for (int j = 0; j < p; ++j) {
      int n;
      fin >> n;
      for (int i = 0; i < n; ++i) {
        pair<rational, rational> point;
        fin >> point;
        silhouette[j].push_back(point);
      }
    }

    int line;
    fin >> line;
    for (int i = 0; i < line; ++i) {
      pair<rational,rational> p, q;
      fin >> p >> q;
      skeleton.push_back(make_pair(p, q));
    }
  }

  const double eps = 1e-3;
  rational mn_x = silhouette[0][0].first;
  rational mn_y = silhouette[0][0].second;
  rational mx_x = silhouette[0][0].first;
  rational mx_y = silhouette[0][0].second;
  each (i, silhouette) {
    each (p, i) {
      mn_x = min(mn_x, p.first);
      mx_x = max(mx_x, p.first);
      mn_y = min(mn_y, p.second);
      mx_y = max(mx_y, p.second);
    }
  }

  {
    sprintf(buff, "./tmp/%d.gpi", id);
    ofstream fout(buff);
    rational a = mx_x - mn_x;
    rational b = mx_y - mn_y;
    rational c = max(a, b);
    fout << "set size ratio 1" << endl;
    fout << "set grid" << endl;
    fout << "set xrange[" << -eps << ":" << c.convert_to<double>()+eps << "]" << endl;
    fout << "set yrange[" << -eps << ":" << c.convert_to<double>()+eps << "]" << endl;
    fout << "set xtics 0.1" <<endl;
    fout << "set ytics 0.1" <<endl;
    fout << "set terminal png" << endl;
    fout << "set multiplot"<< endl;
    fout << "plot ";
    for (size_t i = 0; i < silhouette.size() + 1; ++i) {
      sprintf(buff, "./tmp/%d.dat", id);
      fout << "\\\n" << "  \"" << buff << "\" index " << i << " w l lw 3 lc rgb \"" + cs[i% cs.size()] + "\"";
      fout << (i<silhouette.size()?',':'\n');
    }
  }

  {
    sprintf(buff, "./tmp/%d.dat", id);
    ofstream fout(buff);
    each (i, skeleton) {
      point a = i.first;
      point b = i.second;

      rational p = a.first  - mn_x;
      rational q = a.second - mn_y;

      rational s = b.first  - mn_x;
      rational t = b.second - mn_y;

      fout << p.convert_to<double>() << ' ' << q.convert_to<double>() << endl;
      fout << s.convert_to<double>() << ' ' << t.convert_to<double>() << endl;
      fout << endl;
    }

    for (int i = 0; i < silhouette.size(); ++i) {
      fout << endl << endl;
      auto& v = silhouette[i];
      for (int j = 0; j < v.size(); ++j) {
        int k = (j + 1) % v.size();

        rational p = v[j].first  - mn_x;
        rational q = v[j].second - mn_y;

        rational s = v[k].first  - mn_x;
        rational t = v[k].second - mn_y;

        fout << p.convert_to<double>() << ' ' << q.convert_to<double>() << endl;
        fout << s.convert_to<double>() << ' ' << t.convert_to<double>() << endl;
        fout << endl;
      }
    }
  }

  cout << "gnuplot < " << "./tmp/" << id << ".gpi > ./img/" << id << ".png" << endl;
  return ;
}

int main(int argc, char** argv)
{
  if(argc > 1){
    for(int i = 1; i < argc; ++i)
      f(stoi(argv[i]));
  }
  else{
    for (int i = 0; i < 10000; ++i)
      f(i);
  }
}
