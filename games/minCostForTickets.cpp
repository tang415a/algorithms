// In a country popular for train travel, you have planned some train travelling one year in advance.  The days of the year that you will travel is given as an array days.  Each day is an integer from 1 to 365.

// Train tickets are sold in 3 different ways:

// a 1-day pass is sold for costs[0] dollars;
// a 7-day pass is sold for costs[1] dollars;
// a 30-day pass is sold for costs[2] dollars.
// The passes allow that many days of consecutive travel.  For example, if we get a 7-day pass on day 2, then we can travel for 7 days: day 2, 3, 4, 5, 6, 7, and 8.

// Return the minimum number of dollars you need to travel every day in the given list of days.

// Example 1:

// Input: days = [1,4,6,7,8,20], costs = [2,7,15]
// Output: 11
// Explanation: 
// For example, here is one way to buy passes that lets you travel your travel plan:
// On day 1, you bought a 1-day pass for costs[0] = $2, which covered day 1.
// On day 3, you bought a 7-day pass for costs[1] = $7, which covered days 3, 4, ..., 9.
// On day 20, you bought a 1-day pass for costs[0] = $2, which covered day 20.
// In total you spent $11 and covered all the days of your travel.

// Example 2:

// Input: days = [1,2,3,4,5,6,7,8,9,10,30,31], costs = [2,7,15]
// Output: 17
// Explanation: 
// For example, here is one way to buy passes that lets you travel your travel plan:
// On day 1, you bought a 30-day pass for costs[2] = $15 which covered days 1, 2, ..., 30.
// On day 31, you bought a 1-day pass for costs[0] = $2 which covered day 31.
// In total you spent $17 and covered all the days of your travel.
 
// Note:

// 1 <= days.length <= 365
// 1 <= days[i] <= 365
// days is in strictly increasing order.
// costs.length == 3
// 1 <= costs[i] <= 1000

#include <vector>
using namespace std;

int durations[] = {1,7,30};
int buyTicket(const vector<int>& days, int start, int option) {
  int next = start + 1;
  while(next < days.size()) {
    if (days[next] >= durations[option] + days[start])
      break;
    next++;
  }
  return next;
}

int doCalc(const vector<int>& days, const vector<int>& costs, int start, int cost) {
  if (start >= days.size())
    return cost;
  int candidates[3];
  for(int i = 0; i < 3; i++) {
    candidates[i] = doCalc(days, costs, buyTicket(days, start, i), cost + costs[i]);
  }
  int min = candidates[0];
  if (min > candidates[1]) min = candidates[1];
  if (min > candidates[2]) min = candidates[2];
  return min;
}

int minCostTickets(const vector<int>& days, const vector<int>& costs) {
  return doCalc(days, costs, 0, 0);
}

int minCostTickets2(const vector<int>& days, const vector<int>& costs) {
  int N = days.size();
  int ** dp = new int*[N];
  for(int i = 0; i < N; i++)
    dp[i] = new int[N];

  for(int i = 0; i < N; i++) {
    for(int j = i; j < N; j++) {
      int n = days[j] - days[i];
      int k = 0;
      for(; k < 3; k++) {
        if (n < durations[k]) {
          dp[i][j] = costs[k];
          break;
        }
      }
      if (k == 3)
        dp[i][j] = -1;
    }
  }

  for(int n = 1; n < N; n++) {
    for(int l = 0; l < N - n; l++) {
      int r = l + n;
      for(int k = l; k < r; k++) {
        int costs = dp[l][k] + dp[k+1][r];
        if (dp[l][r] < 0 || dp[l][r] > costs)
          dp[l][r] = costs;
      }
    }
  }

  int res = dp[0][N - 1];
  for(int i = 0; i < N; i++)
    delete[] dp[i];
  delete[] dp;
  return res;
}

#include <set>
int smaller(int i, int j) {
  return i < j ? i : j;
}

int dp(int i, int max, int* memo, const vector<int>& costs, const set<int>& daySet) {
  if (i >= max)
    return 0;
  if (memo[i] > 0)
    return memo[i];

  int ans;
  if (daySet.find(i + 1) == daySet.end())
    ans = dp(i + 1, max, memo, costs, daySet);
  else {
    ans = smaller(costs[0] + dp(i + durations[0], max, memo, costs, daySet), costs[1] + dp(i + durations[1], max, memo, costs, daySet));
    ans = smaller(ans, costs[2] + dp(i + durations[2], max, memo, costs, daySet));
  }

  memo[i] = ans;
  return ans;
}


int minCostTickets3(const vector<int>& days, const vector<int>& costs) {
  int max = days[days.size() - 1];

  int *memo = new int[max];
  memset(memo, 0, sizeof(int) * max);

  set<int> daySet;
  for(auto&d : days) daySet.insert(d);
  int r = dp(0, max, memo, costs, daySet);
  delete[] memo;
  return r;
}

#include <stdlib.h>
#include <time.h>
#include <ctime>

void initialize(vector<int>& days, int siz) {
  int maxSpan = 10;
  srand(time(NULL));
  for (int i = 0; i < siz; i++) {
    int d = (i == 0 ? 0 : days[i - 1]) + (rand() % maxSpan);
    days.push_back(d);
  }
}

int main() {
  // vector<int> days = {1,3,4,5,6,7,8,9,30,31}, costs = {2,7,15};
  // printf("%d\n", minCostTickets(days, costs));
  // printf("%d\n", minCostTickets2(days, costs));

  // days = {1,4,6,7,8,20};
  // printf("%d\n", minCostTickets(days, costs));
  // printf("%d\n", minCostTickets2(days, costs));

  // days = {1,2,3,4,5,6,7,8,9,10,30,31};
  // printf("%d\n", minCostTickets(days, costs));
  // printf("%d\n", minCostTickets2(days, costs));

  int siz = 365;
  vector<int> days, costs = {2,7,15};
  initialize(days, siz);
  
  clock_t startTime, endTime;
  // startTime = clock();
  // printf("%d\n", minCostTickets(days, costs));
  // endTime = clock();
  // printf("The run time is %fs\n", (double)(endTime - startTime) / CLOCKS_PER_SEC);

  // printf("\n");

  startTime = clock();
  printf("%d\n", minCostTickets2(days, costs));
  endTime = clock();
  printf("The run time is %fs\n", (double)(endTime - startTime) / CLOCKS_PER_SEC);

  startTime = clock();
  printf("%d\n", minCostTickets3(days, costs));
  endTime = clock();
  printf("The run time is %fs\n", (double)(endTime - startTime) / CLOCKS_PER_SEC);
  return 0;
}