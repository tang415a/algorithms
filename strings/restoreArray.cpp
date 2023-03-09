/*
A program was supposed to print an array of integers. The program forgot to
print whitespaces and the array is printed as a string of digits s and all we
know is that all integers in the array were in the range [1, k] and there are no
leading zeros in the array.

Given the string s and the integer k, return the number of the possible arrays
that can be printed as s using the mentioned program. Since the answer may be
very large, return it modulo 10^9 + 7.

Example 1:

Input: s = "1000", k = 10000
Output: 1
Explanation: The only possible array is [1000]

Example 2:

Input: s = "1000", k = 10
Output: 0
Explanation: There cannot be an array that was printed this way and has all
integer >= 1 and <= 10.

Example 3:

Input: s = "1317", k = 2000
Output: 8
Explanation: Possible arrays are
[1317],[131,7],[13,17],[1,317],[13,1,7],[1,31,7],[1,3,17],[1,3,1,7]

Constraints:

1 <= s.length <= 10^5
s consists of only digits and does not contain leading zeros.
1 <= k <= 10^9
*/
#include <iostream>
#include <string>

using namespace std;

long long solve(const string &s, int p, int l, int h, const string &z) {
  if (p == l) {
    return 1;
  }
  long long res = 0;
  int m = min(h, l - p);
  for (int i = 1; i <= m; i++) {
    while (i < l - p && s[p + i] == '0') {
      i++;
    }
    if (h < i) {
      return res;
    }
    if (i < h || s.substr(p, i) <= z) {
      res += solve(s, p + i, l, h, z);
    }
  }
  return res;
}

int numberOfArrays(const string &s, int k) {
  string z;
  while (k > 0) {
    int r = k / 10;
    z.push_back('0' + k - 10 * r);
    k = r;
  }
  reverse(z.begin(), z.end());
  return solve(s, 0, s.length(), z.length(), z) % 1'000'000'007;
}

#include <stack>

int numberOfArrays2(const string &s, int k) {
  string z;
  while (k > 0) {
    int r = k / 10;
    z.push_back('0' + k - 10 * r);
    k = r;
  }
  reverse(z.begin(), z.end());
  const int l = s.length(), h = z.length();
  long long res = 0;
  stack<int> st;
  st.push(0);
  while (!st.empty()) {
    int p = st.top();
    st.pop();
    int m = min(l - p, h);
    for (int i = 1; i <= m; i++) {
      while (i < l - p && s[p + i] == '0') {
        i++;
      }
      if (h < i) {
        break;
      }
      if (i < h || s.substr(p, i) <= z) {
        if (p + i < l) {
          st.push(p + i);
        } else {
          res++;
        }
      }
    }
  }
  return res % 1'000'000'007;
}

long long solve2(const string &s, const string &z, int i, int j, int h) {
  long long res = 0;
  stack<int> st;
  st.push(i);
  while (!st.empty()) {
    int p = st.top();
    st.pop();
    int m = min(j - p, h);
    for (int x = 1; x <= m; x++) {
      while (x < j - p && s[p + x] == '0') {
        x++;
      }
      if (h < x) {
        break;
      }
      if (x < h || s.substr(p, x) <= z) {
        if (p + x < j) {
          st.push(p + x);
        } else {
          res++;
        }
      }
    }
  }
  return res;
}

#include <vector>

int numberOfArrays3(const string &s, int k) {
  string z;
  while (k > 0) {
    int r = k / 10;
    z.push_back('0' + k - 10 * r);
    k = r;
  }
  reverse(z.begin(), z.end());
  const int l = s.length(), h = z.length();
  vector<int> vec;
  for (int i = 0, x = 0; i < l; i++) {
    if (s[i] != '0' && x > 0) {
      if (x == h - 1) {
        vec.emplace_back(i);
      }
      x = 0;
    } else if (s[i] == '0') {
      if (++x >= h) {
        return 0;
      }
    }
  }
  if (vec.empty()) {
    return solve2(s, z, 0, l, h) % 1'000'000'007;
  }
  long long res = 1;
  int i = 0;
  for (int j : vec) {
    res *= solve2(s, z, i, j - h, h);
    i = j;
  }
  res *= solve2(s, z, i, l, h);
  return res % 1'000'000'007;
}

long long solve3(const string &s, const string &z, int i, int j, int h) {
  vector<long long> dp(j - i);
  for (int y = j - 1; y >= i; y--) {
    if (s[y] == '0') {
      continue;
    }
    int m = min(j - y, h);
    for (int x = 1; x <= m; x++) {
      while (x < j - y && s[y + x] == '0') {
        x++;
      }
      if (h < x) {
        break;
      }
      if (x < h || s.substr(y, x) <= z) {
        dp[y - i] += y + x < j ? dp[y + x - i] : 1;
      }
    }
  }
  return dp[0];
}

int numberOfArrays4(const string &s, int k) {
  string z;
  while (k > 0) {
    int r = k / 10;
    z.push_back('0' + k - 10 * r);
    k = r;
  }
  reverse(z.begin(), z.end());
  const int l = s.length(), h = z.length();
  vector<int> vec;
  for (int i = 0, x = 0; i < l; i++) {
    if (s[i] != '0' && x > 0) {
      if (x == h - 1) {
        vec.emplace_back(i);
      }
      x = 0;
    } else if (s[i] == '0') {
      if (++x >= h) {
        return 0;
      }
    }
  }
  if (vec.empty()) {
    return solve3(s, z, 0, l, h) % 1'000'000'007;
  }
  long long res = 1;
  int i = 0;
  for (int j : vec) {
    res *= solve3(s, z, i, j - h, h);
    i = j;
  }
  res *= solve3(s, z, i, l, h);
  return res % 1'000'000'007;
}

int numberOfArrays5(const string &s, int k) {
  string z;
  while (k > 0) {
    int r = k / 10;
    z.push_back('0' + k - 10 * r);
    k = r;
  }
  reverse(z.begin(), z.end());
  const int l = s.length(), h = z.length();
  vector<int> dp(l);
  int o = 0;
  for (int i = l - 1; i >= 0 && o < h; i--) {
    if (s[i] == '0') {
      o++;
      continue;
    }
    int m = min(l - i, h);
    for (int x = 1; x <= m; x++) {
      while (x < l - i && s[i + x] == '0') {
        x++;
      }
      if (h < x) {
        break;
      }
      if (x < h || s.substr(i, x) <= z) {
        dp[i] += i + x < l ? dp[i + x] : 1;
        dp[i] %= 1'000'000'007;
      }
    }
    if (dp[i] == 0) {
      o++;
    } else if (o > 0) {
      o = 0;
    }
  }
  if (o >= h)
    return 0;
  return dp[0];
}

// a better approach
int numberOfArrays6(string s, int k) {
  int n = s.length(), *tb = new int[n + 1]{};
  long tmp;

  tb[n] = 1;
  for (int i = n - 1; i != -1; --i) {
    if (s[i] == '0')
      continue;

    tmp = 0;
    auto &r = tb[i];
    for (int j = i; j != n; ++j) {
      tmp = tmp * 10 + (s[j] - '0');
      if (tmp > k)
        break;
      r = (r + tb[j + 1]) % 1000000007;
    }
  }

  return tb[0];
}

int main() {
  cout << numberOfArrays("1000", 10000) << endl;   // 1
  cout << numberOfArrays("1000", 10) << endl;      // 0
  cout << numberOfArrays("1317", 2000) << endl;    // 8
  cout << numberOfArrays2("1000", 10000) << endl;  // 1
  cout << numberOfArrays2("1000", 10) << endl;     // 0
  cout << numberOfArrays2("1317", 2000) << endl;   // 8
  cout << numberOfArrays2("11000", 100) << endl;   // 0
  cout << numberOfArrays2("115708", 9) << endl;    // 0
  cout << numberOfArrays3("1000", 10000) << endl;  // 1
  cout << numberOfArrays3("1000", 10) << endl;     // 0
  cout << numberOfArrays3("1317", 2000) << endl;   // 8
  cout << numberOfArrays3("11000", 100) << endl;   // 0
  cout << numberOfArrays3("115708", 9) << endl;    // 0
  cout << numberOfArrays4("1000", 10000) << endl;  // 1
  cout << numberOfArrays4("1000", 10) << endl;     // 0
  cout << numberOfArrays4("1317", 2000) << endl;   // 8
  cout << numberOfArrays4("11000", 100) << endl;   // 0
  cout << numberOfArrays4("115708", 9) << endl;    // 0
  cout << numberOfArrays5("1000", 10000) << endl;  // 1
  cout << numberOfArrays5("1000", 10) << endl;     // 0
  cout << numberOfArrays5("1317", 2000) << endl;   // 8
  cout << numberOfArrays5("11000", 100) << endl;   // 0
  cout << numberOfArrays5("115708", 9) << endl;    // 0
  cout << numberOfArrays("11570872", 92) << endl;  // 9
  cout << numberOfArrays2("11570872", 92) << endl; // 9
  cout << numberOfArrays3("11570872", 92) << endl; // 9
  cout << numberOfArrays4("11570872", 92) << endl; // 9
  cout << numberOfArrays5("11570872", 92) << endl; // 9
  return 0;
}