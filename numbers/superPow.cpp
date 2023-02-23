/*
Your task is to calculate a^b mod 1337 where a is a positive integer and b is an
extremely large positive integer given in the form of an array.

Example 1:

Input: a = 2, b = [3]
Output: 8

Example 2:

Input: a = 2, b = [1,0]
Output: 1024

Example 3:

Input: a = 1, b = [4,3,3,8,5,2]
Output: 1

Constraints:

1 <= a <= 2^31 - 1
1 <= b.length <= 2000
0 <= b[i] <= 9
b does not contain leading zeros.
*/

#include <iostream>
#include <vector>

using namespace std;

int superPow(int a, vector<int> &b) {
  vector<bool> d(6670);
  int j = 0;
  for (int i = 0, n = b.size(); i < n;) {
    d[j++] = (b[n - 1] & 0x1) == 0 ? false : true;
    bool carry = false;
    for (int k = i; k < n; k++) {
      if (carry)
        b[k] += 10;
      carry = (b[k] & 0x1) != 0;
      b[k] >>= 1;
    }
    while (b[i] == 0) {
      i++;
    }
  }
  int ans = 1;
  for (int i = 0; i < j; i++) {
    if (d[i]) {
      ans *= a;
      ans %= 1337;
    }
    a = (a * a) % 1337;
  }
  return ans;
}

int main() {
  vector<int> b = {3};
  cout << superPow(2, b) << endl;
  b = {1, 0};
  cout << superPow(2, b) << endl;
  b = {4, 3, 3, 8, 5, 2};
  cout << superPow(1, b) << endl;
  b = {5, 0};
  cout << superPow(1339, b) << endl;
  b = {3, 2};
  cout << superPow(3, b) << endl;
  b = {0};
  cout << superPow(3, b) << endl;
  b = {1, 0, 0};
  cout << superPow(2, b) << endl;
  return 0;
}