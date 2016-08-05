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

string h(string s)
{
  if (count(s.begin(), s.end(), '/') == 0) return s;
  replace(s.begin(), s.end(), '/', ' ');
  istringstream iss(s);
  double a, b;
  iss >> a >> b;
  char buff[1000];
  sprintf(buff, "%lf", a/b);
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
  char buff[1000];

  sprintf(buff, "./problem/%d.in", id);
  ifstream fin(buff, ifstream::in);

  int p;
  unless (fin >> p) return ;

  ostringstream oss;
  
  for (int j = 0; j < p; ++j) {
    int v;
    fin >> v;

    for (int i = 0; i < v; ++i) {
      string s;
      fin >> s;
    }
  }

  int line;
  fin >> line;

  oss << "set terminal png" << endl;
  oss << "set output \'./problem/"<< id << ".png\'" << endl;

  oss << "plot \"-\" w l lw 3" << endl;
  oss << endl;
  
  for (int i = 0; i < line; ++i) {
    string s;
    
    fin >> s; oss << g(s) << endl;

    fin >> s; oss << g(s) << endl;

    oss << endl;
  }
  
  sprintf(buff, "./problem/%d.dat", id);
  ofstream fout(buff);
  fout << oss.str();

  cout << "gnuplot < " << "./problem/" << id << ".dat" << endl;
  
  return ;
}

int main(int argc, char *argv[])
{
  for (int i = 0; i < 1000; ++i) {
    f(i + 1);
  }
  
  return 0;
}
