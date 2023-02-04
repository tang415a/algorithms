/*
You are given n​​​​​​ tasks labeled from 0 to n - 1 represented by a
2D integer array tasks, where tasks[i] = [enqueueTimei, processingTimei] means
that the i​​​​​​th​​​​ task will be available to process at
enqueueTimei and will take processingTimei to finish processing.

You have a single-threaded CPU that can process at most one task at a time and
will act in the following way:

If the CPU is idle and there are no available tasks to process, the CPU remains
idle. If the CPU is idle and there are available tasks, the CPU will choose the
one with the shortest processing time. If multiple tasks have the same shortest
processing time, it will choose the task with the smallest index. Once a task is
started, the CPU will process the entire task without stopping. The CPU can
finish a task then start a new one instantly. Return the order in which the CPU
will process the tasks.



Example 1:

Input: tasks = [[1,2],[2,4],[3,2],[4,1]]
Output: [0,2,3,1]
Explanation: The events go as follows:
- At time = 1, task 0 is available to process. Available tasks = {0}.
- Also at time = 1, the idle CPU starts processing task 0. Available tasks = {}.
- At time = 2, task 1 is available to process. Available tasks = {1}.
- At time = 3, task 2 is available to process. Available tasks = {1, 2}.
- Also at time = 3, the CPU finishes task 0 and starts processing task 2 as it
is the shortest. Available tasks = {1}.
- At time = 4, task 3 is available to process. Available tasks = {1, 3}.
- At time = 5, the CPU finishes task 2 and starts processing task 3 as it is the
shortest. Available tasks = {1}.
- At time = 6, the CPU finishes task 3 and starts processing task 1. Available
tasks = {}.
- At time = 10, the CPU finishes task 1 and becomes idle.
Example 2:

Input: tasks = [[7,10],[7,12],[7,5],[7,4],[7,2]]
Output: [4,3,2,0,1]
Explanation: The events go as follows:
- At time = 7, all the tasks become available. Available tasks = {0,1,2,3,4}.
- Also at time = 7, the idle CPU starts processing task 4. Available tasks =
{0,1,2,3}.
- At time = 9, the CPU finishes task 4 and starts processing task 3. Available
tasks = {0,1,2}.
- At time = 13, the CPU finishes task 3 and starts processing task 2. Available
tasks = {0,1}.
- At time = 18, the CPU finishes task 2 and starts processing task 0. Available
tasks = {1}.
- At time = 28, the CPU finishes task 0 and starts processing task 1. Available
tasks = {}.
- At time = 40, the CPU finishes task 1 and becomes idle.


Constraints:

tasks.length == n
1 <= n <= 10^5
1 <= enqueueTimei, processingTimei <= 10^9
*/

#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using namespace std;
vector<int> getOrder(vector<vector<int>> &tasks) {
  int n = tasks.size();
  for (int i = 0; i < n; ++i) {
    tasks[i].push_back(i);
  }
  sort(begin(tasks), end(tasks));
  set<vector<int>> p;
  vector<int> ans(n);
  for (int i = 0, s = 0, step = tasks[0][0]; i < n; ++i) {
    while (s < n && tasks[s][0] <= step) {
      vector<int> a = {tasks[s][1], tasks[s][2]};
      p.insert(a);
      ++s;
    }

    auto it = p.begin();
    ans[i] = (*it)[1];
    if (s < n) {
      step += (*it)[0];
      p.erase(it);
      if (p.empty() && step < tasks[s][0]) {
        step = tasks[s][0];
      }
    } else {
      p.erase(it);
    }
  }
  return ans;
}

#include <queue>
struct Data {
  int t, i;
  bool operator<(const Data &rhs) const {
    return t < rhs.t || (t == rhs.t && i < rhs.i);
  }
};

auto comp = [](const Data &left, const Data &right) {
  return left.t > right.t || (left.t == right.t && left.i > right.i);
};
vector<int> getOrder2(vector<vector<int>> &tasks) {
  int n = tasks.size();
  for (int i = 0; i < n; ++i) {
    tasks[i].push_back(i);
  }
  sort(begin(tasks), end(tasks));

  priority_queue<Data, vector<Data>, decltype(comp)> p(comp);
  vector<int> ans(n);
  for (int i = 0, s = 0, step = tasks[0][0]; i < n; ++i) {
    while (s < n && tasks[s][0] <= step) {
      Data a = {tasks[s][1], tasks[s][2]};
      p.push(a);
      ++s;
    }

    auto it = p.top();
    ans[i] = it.i;
    if (s < n) {
      step += it.t;
      p.pop();
      if (p.empty() && step < tasks[s][0]) {
        step = tasks[s][0];
      }
    } else {
      p.pop();
    }
  }
  return ans;
}

int main() {
  vector<vector<int>> tasks = {{1, 2}, {2, 4}, {3, 2}, {4, 1}};
  auto r = getOrder(tasks);
  auto r1 = getOrder2(tasks);
  for (int i = 0, n = r.size(); i < n; ++i) {
    if (r[i] != r1[i]) {
      cout << "err" << endl;
      return 1;
    }
  }

  tasks = {{7, 10}, {7, 12}, {7, 5}, {7, 4}, {7, 2}};
  r = getOrder(tasks);
  r1 = getOrder2(tasks);
  for (int i = 0, n = r.size(); i < n; ++i) {
    if (r[i] != r1[i]) {
      cout << "err" << endl;
      return 1;
    }
  }

  tasks = {{5, 2}, {7, 2}, {9, 4}, {6, 3}, {5, 10}, {1, 1}};
  r = getOrder(tasks);
  r1 = getOrder2(tasks);
  for (int i = 0, n = r.size(); i < n; ++i) {
    if (r[i] != r1[i]) {
      cout << "err" << endl;
      return 1;
    }
  }

  tasks = {{35, 36}, {11, 7}, {15, 47}, {34, 2},  {47, 19}, {16, 14},
           {19, 8},  {7, 34}, {38, 15}, {16, 18}, {27, 22}, {7, 15},
           {43, 2},  {10, 5}, {5, 4},   {3, 11}};
  r = getOrder(tasks);
  r1 = getOrder2(tasks);
  for (int i = 0, n = r.size(); i < n; ++i) {
    if (r[i] != r1[i]) {
      cout << "err" << endl;
      return 1;
    }
  }
  return 0;
}