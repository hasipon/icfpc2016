#include <bits/stdc++.h>

#define each(i, c) for (auto& i : c)
#define unless(cond) if (!(cond))

using namespace std;

typedef long long int lli;
typedef unsigned long long ull;
typedef complex<double> point;

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

double mn;
double mx;
string h(string s)
{
  if (count(s.begin(), s.end(), '/') == 0) {
    istringstream iss(s);
    double a, b;
    iss >> a >> b;
    mn = min(mn, a);
    mx = max(mx, a);
    return s;
  }
  replace(s.begin(), s.end(), '/', ' ');
  istringstream iss(s);
  double a, b;
  iss >> a >> b;
  char buff[1000];
  sprintf(buff, "%lf", a/b);
  mn = min(mn, a/b);
  mx = max(mx, a/b);
  return string(buff);
}

string g(string s)
{
  replace(s.begin(), s.end(), ',', ' ');
  istringstream iss(s);
  string a;
  string b;
  iss >> a >> b;
  return h(a) + " "+ h(b);
}

void f(int id)
{
  mn = 0;
  mx = 0.5;
  char buff[1000];

  sprintf(buff, "../../problems/%d.txt", id);
  ifstream fin(buff, ifstream::in);

  int p;
  unless (fin >> p) return ;

  ostringstream oss;

  vector<vector<string>> v;
  
  for (int j = 0; j < p; ++j) {
    int n;
    fin >> n;
    v.push_back(vector<string>());
    for (int i = 0; i < n; ++i) {
      string s;
      fin >> s;
      v.back().push_back(s);
    }
  }

  int line;
  fin >> line;

  oss << "set terminal png" << endl;
  oss << "set multiplot"<< endl;

  {
    sprintf(buff, "./problem/%d.%d.dat", id, 0);
    ofstream fout(buff);
    oss << "plot \"" << buff << "\" w l lw 3 lc rgb \"" + cs[0] + "\"" << endl;

    for (int i = 0; i < line; ++i) {
      string s;
      fin >> s; fout << g(s) << endl;
      fin >> s; fout << g(s) << endl;
      fout << endl;
    }
  }

  for (int i = 0; i < v.size(); ++i) {
    sprintf(buff, "./problem/%d.%d.dat", id, i + 1);
    ofstream fout(buff);
    oss << "plot \"" << buff << "\" w l lw 3 lc rgb \"" + cs[(i + 1) % cs.size()] + "\"" << endl;
    for (int j = 0; j < v[i].size(); ++j) {
      fout << g(v[i][j]) << endl;
      fout << g(v[i][(j + 1) % v[i].size()]) << endl;
      fout << endl;
    }
  }
  
  sprintf(buff, "./problem/%d.dat", id);
  ofstream fout(buff);
  fout << "set xrange[" << mn << ":" << mx << "]" << endl;
  fout << "set yrange[" << mn << ":" << mx << "]" << endl;
  fout << oss.str();

  sprintf(buff, "./problem/%d.png", id);
  cout << "gnuplot < " << "./problem/" << id << ".dat" << "> " << buff << endl;
  
  return ;
}

int main(int argc, char *argv[])
{
  for (int i = 0; i < 1000; ++i) {
    f(i + 1);
  }
  return 0;
}
