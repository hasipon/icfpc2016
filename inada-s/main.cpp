#include <iostream>
#define GV_JS
#include "gv.hpp"
using namespace std;

int main() {
  /*
for (int i = 0; i < 10; ++i) {
  gvNewTime();
  gvOutput(("Hello world" + to_string(i)).c_str());
  gvLine(0, 0, 100, 100, gvColor(i));
  gvCircle(i * 10, i * 10, i, gvColor(i));
}
   */

  gvMoveTo(0, 0);
  for (int i = 1; i < 10; ++i) {
    gvLineTo(g_gvLastLineX + i, g_gvLastLineY + i);
    gvLineTo(g_gvLastLineX, g_gvLastLineY + i);
    gvLineTo(g_gvLastLineX - i, g_gvLastLineY);
    gvArrowTo(g_gvLastLineX, g_gvLastLineY - 1);
  }
  cout << "Hello" << endl;
  return 0;
}
