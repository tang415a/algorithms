/*
Given a non-negative integer num represented as a string, remove k digits from
the number so that the new number is the smallest possible.

Note:
The length of num is less than 10002 and will be ≥ k.
The given num does not contain any leading zero.
Example 1:

Input: num = "1432219", k = 3
Output: "1219"
Explanation: Remove the three digits 4, 3, and 2 to form the new number 1219
which is the smallest. Example 2:

Input: num = "10200", k = 1
Output: "200"
Explanation: Remove the leading 1 and the number is 200. Note that the output
must not contain leading zeroes. Example 3:

Input: num = "10", k = 2
Output: "0"
Explanation: Remove all the digits from the number and it is left with nothing
which is 0.

Constraints:

1 <= k <= num.length <= 10^5
num consists of only digits.
num does not have any leading zeros except for the zero itself.
*/

#include <iostream>
#include <string>

using namespace std;

string doRemove(string num, int k, int st, bool leading) {
  int all = num.size() - st;
  if (k >= all)
    return leading ? "0" : "";
  int min = st;
  for (int i = 1; i <= k; i++) {
    if (num[min] > num[st + i])
      min = st + i;
  }
  if (k == min - st) {
    if (leading)
      while (num[min] == '0' && ++min < num.size() - 1)
        ;
    return num.substr(min);
  }
  if (leading)
    leading = num[min] == '0';
  return (leading ? "" : num.substr(min, 1)) +
         doRemove(num, k - min + st, min + 1, leading);
}

string removeKDigits(string num, int k) { return doRemove(num, k, 0, true); }

string doRemove2(string &num, int k) {
  if (k == 0)
    return num;
  int len = num.length();
  if (len <= k)
    return "";
  int min = 0;
  for (int i = 1; i <= k; i++) {
    if (num[i] < num[min])
      min = i;
  }
  return num.substr(min, 1) + doRemove2(num.substr(min + 1), k - min);
}

string removeKDigits2(string num, int k) {
  string res = doRemove2(num, k);
  int i = 0, len = res.length();
  while (i < len && res[i] == '0')
    i++;
  return i < len ? res.substr(i) : "0";
}

string removeKDigits3(const string &num, int k) {
  string st;
  int i = 0, n = num.length();
  for (; i < n; i++) {
    while (k > 0 && !st.empty() && (i == n || num[i] < st.back())) {
      st.pop_back();
      k--;
    }
    if ((st.empty() && num[i] != '0') || !st.empty()) {
      st.push_back(num[i]);
    }
  }
  n = st.length();
  if (n <= k) return "0";
  return st.substr(0, n - k);
}

int main() {
  cout << removeKDigits("78956", 2) << endl;
  cout << removeKDigits2("78956", 2) << endl;
  cout << removeKDigits3("78956", 2) << endl;

  cout << removeKDigits("13579", 3) << endl;
  cout << removeKDigits2("13579", 3) << endl;
  cout << removeKDigits3("13579", 3) << endl;

  cout << removeKDigits("1432219", 3) << endl;
  cout << removeKDigits2("1432219", 3) << endl;
  cout << removeKDigits3("1432219", 3) << endl;

  cout << removeKDigits("10200", 1) << endl;
  cout << removeKDigits2("10200", 1) << endl;
  cout << removeKDigits3("10200", 1) << endl;

  cout << removeKDigits("11200", 1) << endl;
  cout << removeKDigits2("11200", 1) << endl;
  cout << removeKDigits3("11200", 1) << endl;

  cout << removeKDigits("10", 2) << endl;
  cout << removeKDigits2("10", 2) << endl;
  cout << removeKDigits3("10", 2) << endl;

  cout << removeKDigits("129200", 2) << endl;
  cout << removeKDigits2("129200", 2) << endl;
  cout << removeKDigits3("129200", 2) << endl;

  cout << removeKDigits("109000", 2) << endl;
  cout << removeKDigits2("109000", 2) << endl;
  cout << removeKDigits3("109000", 2) << endl;

  cout << removeKDigits("000", 2) << endl;
  cout << removeKDigits2("000", 2) << endl;
  cout << removeKDigits3("000", 2) << endl;

  return 0;
}