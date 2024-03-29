/*
You are given a 2D integer array intervals, where intervals[i] = [lefti, righti]
describes the ith interval starting at lefti and ending at righti (inclusive).
The size of an interval is defined as the number of integers it contains, or
more formally righti - lefti + 1.

You are also given an integer array queries. The answer to the jth query is the
size of the smallest interval i such that lefti <= queries[j] <= righti. If no
such interval exists, the answer is -1.

Return an array containing the answers to the queries.



Example 1:

Input: intervals = [[1,4],[2,4],[3,6],[4,4]], queries = [2,3,4,5]
Output: [3,3,1,4]
Explanation: The queries are processed as follows:
- Query = 2: The interval [2,4] is the smallest interval containing 2. The
answer is 4 - 2 + 1 = 3.
- Query = 3: The interval [2,4] is the smallest interval containing 3. The
answer is 4 - 2 + 1 = 3.
- Query = 4: The interval [4,4] is the smallest interval containing 4. The
answer is 4 - 4 + 1 = 1.
- Query = 5: The interval [3,6] is the smallest interval containing 5. The
answer is 6 - 3 + 1 = 4.

Example 2:

Input: intervals = [[2,3],[2,5],[1,8],[20,25]], queries = [2,19,5,22]
Output: [2,-1,4,6]
Explanation: The queries are processed as follows:
- Query = 2: The interval [2,3] is the smallest interval containing 2. The
answer is 3 - 2 + 1 = 2.
- Query = 19: None of the intervals contain 19. The answer is -1.
- Query = 5: The interval [2,5] is the smallest interval containing 5. The
answer is 5 - 2 + 1 = 4.
- Query = 22: The interval [20,25] is the smallest interval containing 22. The
answer is 25 - 20 + 1 = 6.


Constraints:

1 <= intervals.length <= 10^5
1 <= queries.length <= 10^5
intervals[i].length == 2
1 <= lefti <= righti <= 10^7
1 <= queries[j] <= 10^7
*/

// you may refer to skyline which is similar to this problem

#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

// hints

// sort both interval lower bounds and queries
// when forming the set for each query, if the lower bound of interval begins to
// exceed the query, break; the interval filtered out by the last query (because
// its higher bound is too small) in the following step remains filtered out by
// this query (its higher bound is even smaller).

// utilize the set to sort the interval according to the length of range
// iterate the set:
// if the higher bound of interval is lower then the query, filter it out;
// if the interval begins to cover the query, i.e. higher bound exceeds the
// query, bingo.
vector<int> minInterval(vector<vector<int>> &intervals, vector<int> &queries) {
  set<pair<int, int>> s;

  vector<pair<int, int>> iQueries;
  for (int i = 0; i < queries.size(); i++) {
    iQueries.push_back({queries[i], i});
  }

  sort(intervals.begin(), intervals.end());
  sort(iQueries.begin(), iQueries.end());

  vector<int> result(queries.size(), -1);

  int i = 0, len = intervals.size();

  for (auto &iq : iQueries) {
    while (i < len && intervals[i][0] <= iq.first) {
      s.insert({intervals[i][1] - intervals[i][0] + 1, intervals[i][1]});
      i++;
    }
    while (!s.empty()) {
      auto it = s.begin();
      if (it->second >= iq.first)
        break;
      // the interval is entirely smaller than query and therefore is useless
      // from now on
      s.erase(s.begin());
    }
    if (!s.empty()) {
      result[iq.second] = s.begin()->first;
    }
  }
  return result;
}

// use priority_queue instead; seems a better approach
#include <queue>
vector<int> minInterval2(vector<vector<int>> &intervals, vector<int> &queries) {
  vector<pair<int, int>> iQueries;
  for (int i = 0; i < queries.size(); i++) {
    iQueries.push_back({queries[i], i});
  }

  sort(intervals.begin(), intervals.end());
  sort(iQueries.begin(), iQueries.end());

  vector<int> result(queries.size(), -1);

  int i = 0, len = intervals.size();
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
  for (auto &iq : iQueries) {
    while (i < len && intervals[i][0] <= iq.first) {
      pq.push({intervals[i][1] - intervals[i][0] + 1, intervals[i][1]});
      i++;
    }
    while (!pq.empty()) {
      auto it = pq.top();
      if (it.second >= iq.first) {
        result[iq.second] = it.first;
        break;
      }
      // the interval is entirely smaller than query and therefore is useless
      // from now on
      pq.pop();
    }
  }
  return result;
}

int main() {
  vector<vector<int>> intervals = {{1, 4}, {2, 4}, {3, 6}, {4, 4}};
  vector<int> queries = {2, 3, 4, 5};
  auto res = minInterval(intervals, queries);
  for (int i : res)
    cout << i << " ";
  cout << endl;

  intervals = {{2, 3}, {2, 5}, {1, 8}, {20, 25}};
  queries = {2, 19, 5, 22};
  res = minInterval(intervals, queries);
  for (int i : res)
    cout << i << " ";
  cout << endl;
  
  // use the second approach
  intervals = {{1, 4}, {2, 4}, {3, 6}, {4, 4}};
  queries = {2, 3, 4, 5};
  res = minInterval2(intervals, queries);
  for (int i : res)
    cout << i << " ";
  cout << endl;

  intervals = {{2, 3}, {2, 5}, {1, 8}, {20, 25}};
  queries = {2, 19, 5, 22};
  res = minInterval2(intervals, queries);
  for (int i : res)
    cout << i << " ";
  cout << endl;
  return 0;
}