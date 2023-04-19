/*
You are given a large integer represented as an integer array digits, where each
digits[i] is the ith digit of the integer. The digits are ordered from most
significant to least significant in left-to-right order. The large integer does
not contain any leading 0's.

Increment the large integer by one and return the resulting array of digits.

Example 1:

Input: digits = [1,2,3]
Output: [1,2,4]
Explanation: The array represents the integer 123.
Incrementing by one gives 123 + 1 = 124.
Thus, the result should be [1,2,4].
Example 2:

Input: digits = [4,3,2,1]
Output: [4,3,2,2]
Explanation: The array represents the integer 4321.
Incrementing by one gives 4321 + 1 = 4322.
Thus, the result should be [4,3,2,2].
Example 3:

Input: digits = [9]
Output: [1,0]
Explanation: The array represents the integer 9.
Incrementing by one gives 9 + 1 = 10.
Thus, the result should be [1,0].

Constraints:

1 <= digits.length <= 100
0 <= digits[i] <= 9
digits does not contain any leading 0's.
*/

#include <iostream>
#include <vector>

using namespace std;

vector<int> plusOne(const vector<int> &digits) {
  const int n = digits.size();
  bool overflow = true;
  for (int i = 0; i < n; i++) {
    if (digits[i] < 9) {
      overflow = false;
      break;
    }
  }
  if (overflow) {
    vector<int> ans(n + 1);
    ans[0] = 1;
    return ans;
  }
  vector<int> ans(n);
  bool carry = true;
  for (int i = n - 1; i >= 0; i--) {
    if (carry) {
      ans[i] = digits[i] + 1;
      if (ans[i] > 9) {
        ans[i] = 0;
      } else {
        carry = false;
      }
    } else {
      ans[i] = digits[i];
    }
  }
  return ans;
}

vector<int> plusOne2(const vector<int> &digits) {
  int size = digits.size();
  vector<int> vect = {};
  int count = 0;
  for (int i = size - 1; i >= 0; i--) {
    if ((digits[i] + 1 == 10) && (count == 0)) {
      vect.push_back(0);
      if (i == 0)
        vect.push_back(1);
    } else {
      if (++count == 1) {
        vect.push_back(digits[i] + 1);
      } else {
        vect.push_back(digits[i]);
      }
    }
    // if ((digits[i] + 1 == 10) && (i == 0) && (count == 0)) {
    //   vect.push_back(1);
    // }
    // if (!(digits[i] + 1 == 10) || !(count == 0)) {
    //   count += 1;
    //   if (count == 1) {
    //     vect.push_back(digits[i] + 1);
    //   } else {
    //     vect.push_back(digits[i]);
    //   }
    // }
  }
  vector<int> real_vect = {};
  int vect_size = vect.size();
  for (int i = vect_size - 1; i >= 0; i--) {
    real_vect.push_back(vect[i]);
  }
  return real_vect;
}

vector<int> plusOne3(const vector<int> &digits) {
  const int n = digits.size();
  int j = n;
  while (--j >= 0 && digits[j] == 9) {
    ;
  }
  if (j < 0) {
    vector<int> ans(n + 1);
    ans[0] = 1;
    return ans;
  }
  vector<int> ans(n);
  ans[j] = digits[j] + 1;
  for (int i = 0; i < j; i++) {
    ans[i] = digits[i];
  }
  return ans;
}

vector<int> plusOne4(vector<int> &v) {
  const int n = v.size();
  v[n - 1]++;
  for (int i = n - 1; i >= 0; i--) {
    if (v[i] == 10) {
      v[i] = 0;
      if (i != 0) {
        v[i - 1]++;
      } else {
        v.push_back(0);
        v[i] = 1;
      }
    }
    else
      break;
  }
  return v;
}

int main() {
  auto r = plusOne({1, 2, 3});
  const char *comma = "";
  for (int i = 0; i < r.size(); i++) {
    cout << comma << r[i];
    comma = ",";
  }
  cout << endl;
  r = plusOne({4, 3, 2, 1});
  comma = "";
  for (int i = 0; i < r.size(); i++) {
    cout << comma << r[i];
    comma = ",";
  }
  cout << endl;
  r = plusOne({9});
  comma = "";
  for (int i = 0; i < r.size(); i++) {
    cout << comma << r[i];
    comma = ",";
  }
  cout << endl;
  r = plusOne({9, 9, 9});
  comma = "";
  for (int i = 0; i < r.size(); i++) {
    cout << comma << r[i];
    comma = ",";
  }
  cout << endl;
  r = plusOne2({1, 2, 3});
  comma = "";
  for (int i = 0; i < r.size(); i++) {
    cout << comma << r[i];
    comma = ",";
  }
  cout << endl;
  r = plusOne2({4, 3, 2, 1});
  comma = "";
  for (int i = 0; i < r.size(); i++) {
    cout << comma << r[i];
    comma = ",";
  }
  cout << endl;
  r = plusOne2({9});
  comma = "";
  for (int i = 0; i < r.size(); i++) {
    cout << comma << r[i];
    comma = ",";
  }
  cout << endl;
  r = plusOne2({9, 9, 9});
  comma = "";
  for (int i = 0; i < r.size(); i++) {
    cout << comma << r[i];
    comma = ",";
  }
  cout << endl;
  r = plusOne3({1, 2, 3});
  comma = "";
  for (int i = 0; i < r.size(); i++) {
    cout << comma << r[i];
    comma = ",";
  }
  cout << endl;
  r = plusOne3({4, 3, 2, 1});
  comma = "";
  for (int i = 0; i < r.size(); i++) {
    cout << comma << r[i];
    comma = ",";
  }
  cout << endl;
  r = plusOne3({9});
  comma = "";
  for (int i = 0; i < r.size(); i++) {
    cout << comma << r[i];
    comma = ",";
  }
  cout << endl;
  r = plusOne3({9, 9, 9});
  comma = "";
  for (int i = 0; i < r.size(); i++) {
    cout << comma << r[i];
    comma = ",";
  }
  cout << endl;
  return 0;
}