/*
You are given an array of integers prices, for which the i-th element is the
price of a given stock on day i; and a non-negative integer fee representing a
transaction fee.

You may complete as many transactions as you like, but you need to pay the
transaction fee for each transaction. You may not buy more than 1 share of a
stock at a time (ie. you must sell the stock share before you buy again.)

Return the maximum profit you can make.

Example 1:
Input: prices = [1, 3, 2, 8, 4, 9], fee = 2
Output: 8
Explanation: The maximum profit can be achieved by:
Buying at prices[0] = 1
Selling at prices[3] = 8
Buying at prices[4] = 4
Selling at prices[5] = 9
The total profit is ((8 - 1) - 2) + ((9 - 4) - 2) = 8.
Note:

0 < prices.length <= 50000.
0 < prices[i] < 50000.
0 <= fee < 50000.
*/

#include <stdio.h>
#include <vector>
using namespace std;

int maxProfit(vector<int> &prices, int fee) {
  int N = prices.size();
  int *dp = new int[N];
  dp[0] = 0;

  for (int i = 1; i < N; i++) {
    dp[i] = dp[i - 1];
    for (int j = 0; j < i; j++) {
      int profit = (j > 0 ? dp[j - 1] : 0) + prices[i] - prices[j] - fee;
      if (profit > dp[i])
        dp[i] = profit;
    }
  }
  int res = dp[N - 1];
  delete[] dp;
  return res;
}

int main() {
  vector<int> prices = {1, 3, 2, 8, 4, 9};
  const int fee = 2;
  printf("%d", maxProfit(prices, fee));
  return 0;
}
