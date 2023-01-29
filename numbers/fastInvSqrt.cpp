/*
The fast inverse square root is a clever algorithm that approximates 1/sqrt(x).
It became famous when the Quake III source code was made public around 2005.
While it was initially attributed to Carmack, he denied having written it. Its
origins aren’t completely clear and they can be traced back way before Quake III
was launched in 1999.
*/

#include <iostream>
using namespace std;

// https://www.bilibili.com/video/av289226859/
// https://betterexplained.com/articles/understanding-quakes-fast-inverse-square-root/
float fastInvSqrt(float x) {
  float xhalf = 0.5f * x;
  int i = *(int *)&x;        // evil floating point bit level hacking
  i = 0x5f3759df - (i >> 1); // what the fuck?
  x = *(float *)&i;
  x = x * (1.5f - (xhalf * x * x)); // first iteration of Newton's Method of Approximation
  // x = x * (1.5f - (xhalf * x * x)); // second iteration, can be removed
  return x;
}

int main() {
  cout << fastInvSqrt(4) << endl;
  cout << fastInvSqrt(9) << endl;
  cout << fastInvSqrt(0.04) << endl;
  cout << fastInvSqrt(3) << endl;
  return 0;
}