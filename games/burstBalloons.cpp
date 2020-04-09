/*
Given n balloons, indexed from 0 to n-1. Each balloon is painted with a number on it represented by array nums. You are asked to burst all the balloons. If the you burst balloon i you will get nums[left] * nums[i] * nums[right] coins. Here left and right are adjacent indices of i. After the burst, the left and right then becomes adjacent.

Find the maximum coins you can collect by bursting the balloons wisely.

Note:

You may imagine nums[-1] = nums[n] = 1. They are not real therefore you can not burst them.
0 ≤ n ≤ 500, 0 ≤ nums[i] ≤ 100
Example:

Input: [3,1,5,8]
Output: 167 
Explanation: nums = [3,1,5,8] --> [3,5,8] -->   [3,8]   -->  [8]  --> []
             coins =  3*1*5      +  3*5*8    +  1*3*8      + 1*8*1   = 167
*/

#include <stdio.h>
#include <vector>
using namespace std;

int max(int i, int j) {
  return i < j ? j : i;
}

int maxCoins(vector<int>& nums) {
  int N = nums.size();
  int * balloons = new int [N + 2];
  balloons[0] = 1;
  balloons[N + 1] = 1;

  for(int i = 1; i <= N; i++)
    balloons[i] = nums[i - 1];

  int** dp = new int*[N + 2];
  for(int i = 0; i < N + 2; i++) {
    dp[i] = new int[N + 2];
    memset(dp[i], 0, sizeof(int) * (N + 2));
  }

  for(int i = 1; i <= N; i++) {
    for(int l = 1; l <= N + 1 - i; l++) {
      int r = l + i - 1;
      for(int k = l; k <= r; k++) {
        dp[l][r] = max(dp[l][r], dp[l][k - 1] + balloons[l - 1] * balloons[k] * balloons[r + 1] + dp[k + 1][r]);
      }
    }
  }

  int res = dp[1][N];

  for(int i = 0; i < N + 2; i++)
    delete dp[i];
  delete[] dp;
  delete[] balloons;

  return res;
}

int main() {
  vector<int> balloons = {3,1,5,8};
  printf("%d", maxCoins(balloons));
  getchar();
  return 0;
}
