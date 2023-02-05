/*
There is a hotel with n rooms. The rooms are represented by a 2D integer array
rooms where rooms[i] = [roomIdi, sizei] denotes that there is a room with room
number roomIdi and size equal to sizei. Each roomIdi is guaranteed to be unique.

You are also given k queries in a 2D array queries where queries[j] =
[preferredj, minSizej]. The answer to the jth query is the room number id of a
room such that:

The room has a size of at least minSizej, and
abs(id - preferredj) is minimized, where abs(x) is the absolute value of x.
If there is a tie in the absolute difference, then use the room with the
smallest such id. If there is no such room, the answer is -1.

Return an array answer of length k where answer[j] contains the answer to the
jth query.


Example 1:

Input: rooms = [[2,2],[1,2],[3,2]], queries = [[3,1],[3,3],[5,2]]
Output: [3,-1,3]
Explanation: The answers to the queries are as follows:
Query = [3,1]: Room number 3 is the closest as abs(3 - 3) = 0, and its size of 2
is at least 1. The answer is 3. Query = [3,3]: There are no rooms with a size of
at least 3, so the answer is -1. Query = [5,2]: Room number 3 is the closest as
abs(3 - 5) = 2, and its size of 2 is at least 2. The answer is 3.

Example 2:

Input: rooms = [[1,4],[2,3],[3,5],[4,1],[5,2]], queries = [[2,3],[2,4],[2,5]]
Output: [2,1,3]
Explanation: The answers to the queries are as follows:
Query = [2,3]: Room number 2 is the closest as abs(2 - 2) = 0, and its size of 3
is at least 3. The answer is 2. Query = [2,4]: Room numbers 1 and 3 both have
sizes of at least 4. The answer is 1 since it is smaller. Query = [2,5]: Room
number 3 is the only room with a size of at least 5. The answer is 3.


Constraints:

n == rooms.length
1 <= n <= 10^5
k == queries.length
1 <= k <= 10^4
1 <= roomIdi, preferredj <= 10^7
1 <= sizei, minSizej <= 10^7
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<int> closestRoom__(const vector<vector<int>> &rooms,
                          const vector<vector<int>> &queries) {
  int m = queries.size(), n = rooms.size();
  vector<int> ret(m);
  for (int i = 0; i < m; ++i) {
    int a = 0;
    ret[i] = -1;
    for (int j = 0; j < n; ++j) {
      if (rooms[j][1] < queries[i][1])
        continue;
      int b = abs(rooms[j][0] - queries[i][0]);
      if (ret[i] < 0 || a > b) {
        a = b;
        ret[i] = rooms[j][0];
      } else if (a == b && ret[i] >= 0 && ret[i] > rooms[j][0]) {
        ret[i] = rooms[j][0];
      }
    }
  }
  return ret;
}

#include <numeric>
#include <set>

vector<int> closestRoom(vector<vector<int>> &rooms,
                        vector<vector<int>> &queries) {
  int m = queries.size();
  vector<int> idx(m);
  iota(idx.begin(), idx.end(), 0);

  sort(idx.begin(), idx.end(), [&queries](int idx1, int idx2) {
    return queries[idx1][1] > queries[idx2][1];
  });
  sort(rooms.begin(), rooms.end(),
       [](const vector<int> &room1, const vector<int> &room2) {
         return room1[1] > room2[1];
       });

  vector<int> ans(m, -1);
  int room_idx = 0;
  set<int> valid_rooms;
  for (int e : idx) {
    int preferred = queries[e][0];
    int min_size = queries[e][1];

    while (room_idx < rooms.size() && rooms[room_idx][1] >= min_size) {
      valid_rooms.insert(rooms[room_idx][0]);
      room_idx++;
    }

    if (valid_rooms.empty()) {
      continue;
    }

    auto it = valid_rooms.upper_bound(preferred);
    if (it != valid_rooms.end()) {
      ans[e] = *it;
    }
    if (it != valid_rooms.begin()) {
      it--;
      if (ans[e] == -1) {
        ans[e] = *it;
      } else if (preferred - *it <= ans[e] - preferred) {
        ans[e] = *it;
      }
    }
  }

  return ans;
}

struct TreeNode {
  TreeNode *left = nullptr, *right = nullptr;
  int val = 0;
};

void clear(TreeNode *root) {
  if (root == nullptr)
    return;
  clear(root->left);
  clear(root->right);
  delete root;
}

void insert(TreeNode *root, int v) {
  if (v < root->val) {
    if (root->left == nullptr) {
      root->left = new TreeNode();
      root->left->val = v;
    } else {
      insert(root->left, v);
    }
  } else if (v > root->val) {
    if (root->right == nullptr) {
      root->right = new TreeNode();
      root->right->val = v;
    } else {
      insert(root->right, v);
    }
  }
}

int find(TreeNode *root, int target) {
  if (root == nullptr)
    return 0;
  if (root->val == target)
    return root->val;
  if (root->val < target) {
    int i = find(root->right, target);
    if (i == 0)
      return root->val;
    if (i <= target)
      return i;
    return i + root->val < 2 * target ? i : root->val;
  }
  int i = find(root->left, target);
  if (i == 0)
    return root->val;
  if (i >= target)
    return i;
  return i + root->val < 2 * target ? root->val : i;
}

vector<int> closestRoom2(vector<vector<int>> &rooms,
                         vector<vector<int>> &queries) {
  int m = queries.size(), n = rooms.size();
  for (int i = 0; i < m; i++) {
    queries[i].emplace_back(i);
  }
  sort(queries.begin(), queries.end(),
       [](const vector<int> &l, const vector<int> &r) { return l[1] > r[1]; });
  sort(rooms.begin(), rooms.end(),
       [](const vector<int> &l, const vector<int> &r) { return l[1] > r[1]; });

  vector<int> ans(m, -1);
  TreeNode *root = nullptr;
  int i = 0;
  for (const auto &q : queries) {
    while (i < n && q[1] <= rooms[i][1]) {
      if (root == nullptr) {
        root = new TreeNode();
        root->val = rooms[i][0];
      } else {
        insert(root, rooms[i][0]);
      }
      ++i;
    }
    if (root) {
      ans[q[2]] = find(root, q[0]);
    }
  }
  clear(root);
  return ans;
}

int main() {
  vector<vector<int>> rooms = {{2, 2}, {1, 2}, {3, 2}},
                      queries = {{3, 1}, {3, 3}, {5, 2}};
  auto a = closestRoom(rooms, queries);
  for (int b : a)
    cout << b << " ";
  cout << endl;

  a = closestRoom2(rooms, queries);
  for (int b : a)
    cout << b << " ";
  cout << endl;

  rooms = {{1, 4}, {2, 3}, {3, 5}, {4, 1}, {5, 2}};
  queries = {{2, 3}, {2, 4}, {2, 5}};
  a = closestRoom(rooms, queries);
  for (int b : a)
    cout << b << " ";
  cout << endl;

  a = closestRoom2(rooms, queries);
  for (int b : a)
    cout << b << " ";
  cout << endl;

  rooms = {{4, 5}, {1, 4}, {3, 4}};
  queries = {{2, 3}, {2, 4}, {2, 5}};
  a = closestRoom(rooms, queries);
  for (int b : a)
    cout << b << " ";
  cout << endl;

  a = closestRoom2(rooms, queries);
  for (int b : a)
    cout << b << " ";
  cout << endl;
  return 0;
}