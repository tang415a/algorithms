/*
There are 100 different types of caps each having a unique id from 1 to 100.
Also, there are n persons each having a collection of a variable number of caps.
One day all of these persons decide to go in a party wearing a cap but to look
unique they decided that none of them will wear the same type of cap. So, count
the total number of arrangements or ways such that none of them is wearing the
same type of cap.

Since, number of ways could be large, so output modulo 1000000007.

Constraints: 1 <= n <= 10

Example:

The first line contains the value of n, next n lines contain collections
of all the n persons.
Input:
3
5 100 1     // Collection of the first person.
2           // Collection of the second person.
5 100       // Collection of the third person.

Output:
4
Explanation: All valid possible ways are (5, 2, 100), (100, 2, 5),
            (1, 2, 5) and (1, 2, 100)
*/

#include <iostream>
#include <vector>

using namespace std;

/*
https://www.geeksforgeeks.org/bitmasking-and-dynamic-programming-set-1-count-ways-to-assign-unique-cap-to-every-person/

consider the case when ith cap is not included in the arrangement
countWays(mask, i) = countWays(mask, i+1) +
                    when ith cap is included in the arrangement
                    so, assign this cap to all possible persons
                    one by one and recur for remaining persons.
                    ∑ countWays(mask | (1 << j), i+1)
                       for every person j that can wear cap i
*/

long long int doCap(int (&masks)[4], int r, vector<vector<int>> const &v) {
  if (r-- == 0)
    return 1;
  long long int ret = 0;
  for (int i = 0, n = v[r].size(); i < n; ++i) {
    int j = v[r][i] / 32;
    int k = 1 << (v[r][i] - j * 32);
    if ((masks[j] & k) == 0) {
      masks[j] |= k;
      ret += doCap(masks, r, v);
      masks[j] ^= k;
    }
  }
  return ret;
}

int wearingCap(int n, vector<vector<int>> const &v) {
  const int kMax = 1e9 + 7;
  int masks[4];
  memset(masks, 0, sizeof(int) * 4);
  long long int r = doCap(masks, n, v);
  return r % kMax;
}

int main() {
  cout << wearingCap(3, {{5, 100, 1}, {2}, {5, 100}}) << endl;
  return 0;
}