/*
You are given two 0-indexed arrays nums1 and nums2 of length n, both of which
are permutations of [0, 1, ..., n - 1].

A good triplet is a set of 3 distinct values which are present in increasing
order by position both in nums1 and nums2. In other words, if we consider pos1v
as the index of the value v in nums1 and pos2v as the index of the value v in
nums2, then a good triplet will be a set (x, y, z) where 0 <= x, y, z <= n - 1,
such that pos1x < pos1y < pos1z and pos2x < pos2y < pos2z.

Return the total number of good triplets.

Example 1:

Input: nums1 = [2,0,1,3], nums2 = [0,1,2,3]
Output: 1
Explanation:
There are 4 triplets (x,y,z) such that pos1x < pos1y < pos1z. They are (2,0,1),
(2,0,3), (2,1,3), and (0,1,3). Out of those triplets, only the triplet (0,1,3)
satisfies pos2x < pos2y < pos2z. Hence, there is only 1 good triplet.

Example 2:

Input: nums1 = [4,0,1,3,2], nums2 = [4,1,0,2,3]
Output: 4
Explanation: The 4 good triplets are (4,0,3), (4,0,2), (4,1,3), and (4,1,2).


Constraints:

n == nums1.length == nums2.length
3 <= n <= 10^5
0 <= nums1[i], nums2[i] <= n - 1
nums1 and nums2 are permutations of [0, 1, ..., n - 1].
*/

#include <iostream>
#include <vector>

using namespace std;
struct TreeNode {
  int val;
  int count;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr), count(1) {}
};

void clear(TreeNode *r) {
  if (r == nullptr)
    return;
  clear(r->left);
  clear(r->right);
  delete r;
}

// the vector counts the elements greater than val
// the count of nodes is the number of nodes in right child and itself
void insertBackwards(TreeNode *r, int val, vector<int> &m) {
  if (r->val < val) {
    r->count++; // r->val < val -> it is a right child node of r
    if (r->right == nullptr) {
      r->right = new TreeNode(val);
      return;
    }
    insertBackwards(r->right, val, m);
  } else {
    m[val] += r->count; // add the count of parent and parent's right nodes
    if (r->left == nullptr) {
      r->left = new TreeNode(val);
      return;
    }
    insertBackwards(r->left, val, m);
  }
}

// the vector counts the elements less than val
// the count of nodes is the number of nodes in left child and itself
void insertForwards(TreeNode *r, int val, vector<int> &m) {
  if (r->val < val) {
    m[val] += r->count; // add the count of parent and parent's left nodes
    if (r->right == nullptr) {
      r->right = new TreeNode(val);
      return;
    }
    insertForwards(r->right, val, m);
  } else { // val < r->val -> it is a left child node of r
    r->count++;
    if (r->left == nullptr) {
      r->left = new TreeNode(val);
      return;
    }
    insertForwards(r->left, val, m);
  }
}

long long goodTriplets(const vector<int> &nums1, const vector<int> &nums2) {
  int n = nums1.size();
  vector<int> m1(n), m2(n), m3(n);
  for (int i = 0; i < n; i++) {
    m1[nums1[i]] = i;
  }
  for (int i = 0; i < n; i++) {
    m2[i] = m1[nums2[i]];
  }
  memset(&m1[0], 0, sizeof(int) * n);
  TreeNode *root1 = new TreeNode(m2[0]), *root2 = new TreeNode(m2[n - 1]);
  for (int i = 1; i < n; i++) {
    insertForwards(root1, m2[i], m1);
    insertBackwards(root2, m2[n - 1 - i], m3);
  }
  clear(root1);
  clear(root2);
  long long ans = 0;
  for (int i = 0; i < n; i++) {
    ans += (m1[i] * m3[i]);
  }
  return ans;
}

int main() {
  cout << goodTriplets({2, 0, 1, 3}, {0, 1, 2, 3}) << endl;
  cout << goodTriplets({4, 0, 1, 3, 2}, {4, 1, 0, 2, 3}) << endl;
  cout << goodTriplets({0, 1, 2, 3, 4}, {0, 1, 2, 3, 4}) << endl;
  cout << goodTriplets({0, 1, 2, 3, 4}, {4, 3, 2, 1, 0}) << endl;
  cout << goodTriplets({0, 1, 2, 3, 4}, {1, 4, 2, 0, 3}) << endl;
  cout << goodTriplets({0, 1, 2, 3, 4, 5, 6}, {1, 4, 2, 0, 3, 5, 6}) << endl;
  /*  0, 3, 5   0, 3, 6   0, 5, 6   1, 2, 3
      1, 2, 5   1, 2, 6   1, 3, 5   1, 3, 6
      1, 4, 5   1, 4, 6   1, 5, 6   2, 3, 5
      2, 3, 6   2, 5, 6   3, 5, 6   4, 5, 6
  */
  return 0;
}