/*
Given an integer array nums, return the number of range sums that lie in [lower, upper] inclusive.
Range sum S(i, j) is defined as the sum of the elements in nums between indices i and j (i ≤ j), inclusive.

Note:
A naive algorithm of O(n2) is trivial. You MUST do better than that.

Example:

Input: nums = [-2,5,-1], lower = -2, upper = 2,
Output: 3 
Explanation: The three ranges are : [0,0], [2,2], [0,2] and their respective sums are: -2, -1, 2.
*/

#include <stdio.h>
struct TreeNode {
  int val;
  int cnt;
  TreeNode *left, *right;
};

void insert_node(TreeNode* &root, int val) {
  if (!root) {
    root = new TreeNode({val, 1, NULL, NULL});
    return;
  }

  root->cnt++;
  if (val < root->val)
    insert_node(root->left, val);
  else if (val > root->val)
    insert_node(root->right, val);
}

void free_node(TreeNode* root) {
  if (root) {
    free_node(root->left);
    free_node(root->right);
    delete root;
  }
}

int greater_than(TreeNode* root, int val) {
  if (root) {
    if (root->val < val)
      return greater_than(root->right, val);
    if (root->val > val)
      return root->cnt - (root->left ? root->left->cnt : 0) + greater_than(root->left, val);
    return root->right ? root->right->cnt : 0;
  }
  return 0;
}

int countRangeSum(int *arr, int siz, int lower, int upper) {
  int s = 0, res = 0;
  TreeNode* root = NULL;  
  insert_node(root, s);
  for(int i = 0; i < siz; i++) {
    s += arr[i];
    int overCnt = greater_than(root, s - upper - 1);
    int underCnt = greater_than(root, s - lower);
    res += overCnt - underCnt;
    insert_node(root, s);
  }
  free_node(root);
  return res;
}

int main() {
  int arr[] = {-2, 5, -1};
  int lower = -2, upper = 2;
  printf("%d", countRangeSum(arr, sizeof(arr) / sizeof(arr[0]), lower, upper));
  return 0;
}