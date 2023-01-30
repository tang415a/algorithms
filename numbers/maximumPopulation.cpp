/*
You are given a 2D integer array logs where each logs[i] = [birthi, deathi]
indicates the birth and death years of the ith person.

The population of some year x is the number of people alive during that year.
The ith person is counted in year x's population if x is in the inclusive range
[birthi, deathi - 1]. Note that the person is not counted in the year that they
die.

Return the earliest year with the maximum population.



Example 1:

Input: logs = [[1993,1999],[2000,2010]]
Output: 1993
Explanation: The maximum population is 1, and 1993 is the earliest year with
this population.

Example 2:

Input: logs = [[1950,1961],[1960,1971],[1970,1981]]
Output: 1960
Explanation:
The maximum population is 2, and it had happened in years 1960 and 1970.
The earlier year between them is 1960.


Constraints:

1 <= logs.length <= 100
1950 <= birthi < deathi <= 2050
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int maximumPopulation(const vector<vector<int>> &logs) {
  auto v = logs;
  sort(v.begin(), v.end());
  int m = 0, r = 0;
  for (int i = 0, n = logs.size(); i < n; ++i) {
    int k = 0;
    for (int j = 0; j < n && v[j][0] <= v[i][0]; ++j) {
      if (v[j][1] > v[i][0])
        ++k;
    }
    if (m < k) {
      m = k;
      r = v[i][0];
    }
  }
  return r;
}

int maximumPopulation2(const vector<vector<int>> &logs) {
  int count[101] = {0}, current = 0, maximum = 0, res = 1950;

  for (auto &log : logs) {
    ++count[log[0] - 1950];
    --count[log[1] - 1950];
  }

  for (int i = 0; i <= 100; ++i) {
    current += count[i];

    if (current > maximum) {
      res = 1950 + i;
      maximum = current;
    }
  }
  return res;
}

int main() {
  cout << maximumPopulation({{1993, 1999}, {2000, 2010}}) << endl;
  cout << maximumPopulation2({{1993, 1999}, {2000, 2010}}) << endl;
  cout << maximumPopulation({{1950, 1961}, {1960, 1971}, {1970, 1981}}) << endl;
  cout << maximumPopulation2({{1950, 1961}, {1960, 1971}, {1970, 1981}}) << endl;
  return 0;
}