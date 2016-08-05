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

struct P {
  string x, y;
  int ID;
};

struct L : pair<P, P> {};

struct Sawaput {
  vector<P> ps;
  vector<vector<int>> pid;
  void init(istream& is)
  {
    int n;
    is >> n;
    ps.resize(n);
    for (size_t i = 0; i < ps.size(); ++i) {
      string s;
      is >> s >> ps[i].ID;
      replace(s.begin(), s.end(), ',', ' ');
      stringstream ss(s);      
      ss >> ps[i].x >> ps[i].y;
    }

    int m;
    is >> m;
    pid.resize(m);
    for (int i = 0; i < m; ++i) {
      int x;
      is >> x;
      for (int j = 0; j < x; ++j) {
        int y;
        is >> y;
        pid[i].push_back(y);
      }
    }

    return ;
  }
};

struct Hasiput {
  vector<P> ps;
  vector<vector<int>> pol;
  void init(istream& is)
  {
    int n;
    is >> n;
    ps.resize(n);
    for (size_t i = 0; i < ps.size(); ++i) {
      string s;
      is >> s;
      replace(s.begin(), s.end(), ',', ' ');
      stringstream ss(s);
      ss >> ps[i].x >> ps[i].y;
      ps[i].ID = i;
    }

    int m;
    is >> m;
    pol.resize(m);
    string s;
    getline(is, s);
    for (int i = 0; i < m; ++i) {
      getline(is, s);
      istringstream iss(s);
      for (int z; iss >> z; pol[i].push_back(z)) ;
    }
  }
  P& operator [] (int idx)
  {
    return ps[idx];
  }
};

int main(int argc, char *argv[])
{
  Hasiput h;
  Sawaput s;

  h.init(cin);
  s.init(cin);

  cout << s.ps.size() << endl;
  each (i, s.ps) {
    cout << i.x << ',' << i.y << endl;
  }
  
  cout << s.pid.size() << endl;
  each (i, s.pid) {
    cout << i.size() ;
    each (j, i) cout << ' ' << j;
    cout << endl;
  }

  cout << s.ps.size() << endl;
  each (i, s.ps) {
    cout << h[i.ID].x << ',' << h[i.ID].y << endl;
  }
  
  return 0;
}
