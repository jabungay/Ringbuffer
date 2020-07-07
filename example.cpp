#include <iostream>
using namespace std;

#include "ringbuffer.h"

int main()
{

  Ringbuffer<int> a(100);

  int w = 100;
  a.write(&w);
  w = 10;
  a.write(&w);

  int r;
  a.read(&r);
  cout << r << endl;
  a.read(&r);
  cout << r << endl;
  a.read(&r);
  cout << r << endl;
  
  return 0;
}
