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
  a %= 1337;
  int ans = 1;
  for (int i = 0, n = b.size(); i < n;) {
    bool carry = false;
    for (int k = i; k < n; k++) {
      if (carry)
        b[k] += 10;
      carry = (b[k] & 0x1) != 0;
      b[k] >>= 1;
    }
    if (carry) {
      ans *= a;
      ans %= 1337;
    }
    a = (a * a) % 1337;
    while (i < n && b[i] == 0) {
      i++;
    }
  }
  return ans;
}

/*
This is a simple approach to the problem Super Pow. This requires few concepts
of mathematics which are Euler's theorem and ETF(Euler Totient Function).

Now, what is ETF?

ETF of a number n can be defined as: ETF(n) = n * product_of(1 - 1 / p), where
p=prime factors.

Euler's Theorem States that: a^b % M = a ^ (b % ETF(n)) % M. In this question
ETF(1337)=1140.

Once we implement Euler's theorem, the question becomes really easy.Then we need
to use simple binary exponentiation to solve rest of the question.
*/
// a better solution
int binpow(int a, int b) {
  int res = 1;
  while (b > 0) {
    if (b & 1)
      res = (res * a) % 1337;
    a = (a * a) % (1337);
    b >>= 1;
  }
  return res;
}
// https://brilliant.org/wiki/eulers-totient-function/
// Euler's totient function (also called the Phi function) counts the number of
// positive integers less than n that are coprime to n. That is, ϕ(n) is the
// number of m ∈ N such that 1 ≤ m < n and gcd(m, n) = 1.
// To calculate ETF(Euler's Totient Function) i.e., phi(n), n must be prime but
// here n is not prime so we have to calculate phi(n) also. phi(n) = n * (1 - 1
// / p1) * (1 - 1 / p2), where p1 and p2 are prime factors of a. Here n is 1337
// and for this n p1 = 191 and p2 = 7. phi(1337) = 1337 * (1 - 1 / 191) * (1 - 1
// / 7) = 190 * 6 = 1140.
int superPow2(int a, const vector<int> &b) {
  int n = b.size();

  long long int num = 0;

  for (int i = 0; i < n; i++) {
    num = ((num * 10) % 1140 + b[i]) % 1140;
  }
  return binpow(a % 1337, num);
}

int main() {
  vector<int> b = {3};
  cout << superPow(2, b) << endl;    // 8
  cout << superPow2(2, {3}) << endl; // 8

  b = {1, 0};
  cout << superPow(2, b) << endl;       // 1024
  cout << superPow2(2, {1, 0}) << endl; // 1024

  b = {4, 3, 3, 8, 5, 2};
  cout << superPow(1, b) << endl;                   // 1
  cout << superPow2(1, {4, 3, 3, 8, 5, 2}) << endl; // 1

  b = {5, 0};
  cout << superPow(1339, b) << endl;       // 536
  cout << superPow2(1339, {5, 0}) << endl; // 536

  b = {3, 2};
  cout << superPow(3, b) << endl;       // 1003
  cout << superPow2(3, {3, 2}) << endl; // 1003

  b = {0};
  cout << superPow(3, b) << endl;    // 1
  cout << superPow2(3, {0}) << endl; // 1

  b = {1, 0, 0};
  cout << superPow(2, b) << endl;          // 1178
  cout << superPow2(2, {1, 0, 0}) << endl; // 1178

  b = {1, 0, 0, 0};
  cout << superPow(2, b) << endl;             // 345
  cout << superPow2(2, {1, 0, 0, 0}) << endl; // 345
  return 0;
}