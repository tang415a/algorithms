/*
Given the root of a binary search tree, return a balanced binary search tree
with the same node values. If there is more than one answer, return any of them.

A binary search tree is balanced if the depth of the two subtrees of every node
never differs by more than 1.

Example 1:

Input: root = [1,null,2,null,3,null,4,null,null]
Output: [2,1,3,null,null,null,4]
Explanation: This is not the only correct answer, [3,1,4,null,2] is also
correct.

Example 2:

Input: root = [2,1,3]
Output: [2,1,3]

Constraints:

The number of nodes in the tree is in the range [1, 10^4].
1 <= Node.val <= 10^5
*/

#include <iostream>
#include <vector>
using namespace std;
/**
 * Definition for a binary tree node.
 */
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
  // a helper function to construct a binary tree from an integer array
  static TreeNode *from(const vector<int> &arr);

private:
  static TreeNode *from(const vector<int> &arr, int l, int &c);
};

// c is the next element we are going to read
TreeNode *TreeNode::from(const vector<int> &arr, int l, int &c) {
  if (l >= arr.size() || arr[l] < 0) // any negative number means it is null
    return nullptr;
  int d = c;
  // the left child and right child will be read in this call
  // the next element we are going to read in the next call is c + 2
  c += 2;
  TreeNode *left = from(arr, d, c);
  TreeNode *right = from(arr, d + 1, c);
  return new TreeNode(arr[l], left, right);
}

TreeNode *TreeNode::from(const vector<int> &arr) {
  int c = 1;
  return from(arr, 0, c);
}

void convertToArr(TreeNode *r, vector<int> &arr) {
  if (r == nullptr)
    return;
  convertToArr(r->left, arr);
  arr.emplace_back(r->val);
  convertToArr(r->right, arr);
}

TreeNode *convertToTree(const vector<int> &arr, int l, int h) {
  if (l > h)
    return nullptr;
  int i = l + (h - l) / 2;
  TreeNode *r = new TreeNode(arr[i]);
  r->left = convertToTree(arr, l, i - 1);
  r->right = convertToTree(arr, i + 1, h);
  return r;
}

TreeNode *balanceBST(TreeNode *root) {
  vector<int> arr;
  convertToArr(root, arr);
  return convertToTree(arr, 0, arr.size() - 1);
}

void clear(TreeNode *p) {
  if (p == nullptr)
    return;
  clear(p->left);
  clear(p->right);
  delete p;
}

// a helper function to print the tree by levels
void print(TreeNode *p) {
  if (p == nullptr)
    return;
  vector<TreeNode *> vec = {p};
  int start = 0, n = vec.size();
  for (; start < vec.size(); start++) {
    if (vec[start]) {
      cout << vec[start]->val << " ";
    } else {
      cout << "null ";
      continue;
    }
    // n is the last element we see so far that is not a leaf (i.e. has at least
    // one non-null child). once start is greater than n, there will be only
    // leaves from now on
    if (start < n) {
      vec.emplace_back(vec[start]->left);
      if (vec.back() && (vec.back()->left || vec.back()->right))
        n = vec.size();
      vec.emplace_back(vec[start]->right);
      if (vec.back() && (vec.back()->left || vec.back()->right))
        n = vec.size();
    }
  }
}

int main() {
  TreeNode *r = TreeNode::from({1, -1, 2, -1, 3, -1, 4, -1, -1});
  print(r);
  cout << endl;
  TreeNode *b = balanceBST(r);
  print(b);
  cout << endl;
  clear(r);
  clear(b);
  r = TreeNode::from({2, 1, 3});
  print(r);
  cout << endl;
  b = balanceBST(r);
  print(b);
  cout << endl;
  return 0;
}
