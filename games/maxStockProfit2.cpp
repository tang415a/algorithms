/*
You are given an array prices where prices[i] is the price of a given stock on
the ith day.

Find the maximum profit you can achieve. You may complete at most two
transactions.

Note: You may not engage in multiple transactions simultaneously (i.e., you must
sell the stock before you buy again).

Example 1:

Input: prices = [3,3,5,0,0,3,1,4]
Output: 6
Explanation: Buy on day 4 (price = 0) and sell on day 6 (price = 3), profit =
3-0 = 3. Then buy on day 7 (price = 1) and sell on day 8 (price = 4), profit =
4-1 = 3.

Example 2:

Input: prices = [1,2,3,4,5]
Output: 4
Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit =
5-1 = 4. Note that you cannot buy on day 1, buy on day 2 and sell them later, as
you are engaging multiple transactions at the same time. You must sell before
buying again.

Example 3:

Input: prices = [7,6,4,3,1]
Output: 0
Explanation: In this case, no transaction is done, i.e. max profit = 0.

Constraints:

1 <= prices.length <= 10^5
0 <= prices[i] <= 10^5
*/

#include <iostream>
#include <vector>

using namespace std;

int maxProfit(const vector<int> &prices) {
  int n = prices.size();
  vector<int> forward(n), backward(n);
  int l = prices[0], h = l;
  for (int i = 1; i < n; i++) {
    if (prices[i] > h) {
      h = prices[i];
    }
    forward[i] = max(forward[i - 1], h - l);
    if (prices[i] < l) {
      l = h = prices[i];
    }
  }
  l = prices[n - 1];
  h = l;
  for (int i = n - 2; i >= 0; i--) {
    if (prices[i] < l) {
      l = prices[i];
    }
    backward[i] = max(backward[i + 1], h - l);
    if (prices[i] > h) {
      h = l = prices[i];
    }
  }
  int ans = max(forward[n - 1], backward[0]);
  for (int i = 1; i < n - 1; i++) {
    ans = max(ans, forward[i] + backward[i]);
  }
  return ans;
}

// a better approach
// hints:
// max profit of one transaction: Max - Min, i.e. must be the largest price
// difference in the entire range
// max profit of two transactions: Max1 - Min1, Max2 - Min2, i.e. must be the
// largest price difference in the respective two sub-ranges
int maxProfit2(const vector<int> &prices) {
  int sold[2] = {}, bought[2] = {INT_MIN, INT_MIN};
  for (int x : prices) {
    // max profit of one transaction: the largest price diff in the entire range
    // when we iterate over the prices
    bought[0] = max(bought[0], -x);
    sold[0] = max(sold[0], bought[0] + x);
    // max profit of two transactions: use bought[0]/sold[0] as the largest
    // price diff in the first sub-range, then find the largest price diff in
    // the second
    bought[1] = max(bought[1], sold[0] - x);
    sold[1] = max(sold[1], bought[1] + x);
  }
  return max(sold[0], sold[1]);
}

int main() {
  cout << maxProfit({3, 3, 5, 0, 0, 3, 1, 4}) << endl;
  cout << maxProfit({1, 2, 3, 4, 5}) << endl;
  cout << maxProfit({7, 6, 4, 3, 1}) << endl;
  cout << maxProfit({1, 2, 4, 2, 5, 7, 2, 4, 9, 0}) << endl;
  cout << maxProfit2({3, 3, 5, 0, 0, 3, 1, 4}) << endl;
  cout << maxProfit2({1, 2, 3, 4, 5}) << endl;
  cout << maxProfit2({7, 6, 4, 3, 1}) << endl;
  cout << maxProfit2({1, 2, 4, 2, 5, 7, 2, 4, 9, 0}) << endl;
  return 0;
}
