/*
You are given an integer array nums and you have to return a new counts array. The counts array has the property where counts[i] is the number of smaller elements to the right of nums[i].

Example:

Input: [5,2,6,1]
Output: [2,1,1,0] 
Explanation:
To the right of 5 there are 2 smaller elements (2 and 1).
To the right of 2 there is only 1 smaller element (1).
To the right of 6 there is 1 smaller element (1).
To the right of 1 there is 0 smaller element.
*/

#include <stdio.h>
#include <vector>
using namespace std;

struct TreeNode {
  int val;
  TreeNode *left, *right;
  int count;
  int equals;
  TreeNode(int v): val(v), left(NULL), right(NULL), count(0), equals(1) {}
};

int insert(TreeNode* root, int num) {
  if (root == NULL)
    return 0;
  if (num > root->val) {
    if (root->right == NULL) {
      root->right = new TreeNode(num);
      return root->count + root->equals;
    }
    return root->count + root->equals + insert(root->right, num);
  }

  if (num < root->val) {
    root->count++;
    if (root->left == NULL) {
      root->left = new TreeNode(num);
      return 0;
    }
    return insert(root->left, num);
  }

  root->equals++;
  return root->count;
}

void clear(TreeNode*root) {
  if (root == NULL)
    return;
  clear(root->left);
  clear(root->right);
  delete root;
}

vector<int> countSmaller(vector<int>& nums) {
  if (nums.empty())
    return {};
  vector<int> res;
  int siz = nums.size();
  TreeNode* root = new TreeNode(nums[siz - 1]);
  res.push_back(0);

  for(int i = siz - 2; i >= 0; i--) {
    res.push_back(insert(root, nums[i]));
  }

  clear(root);
  std::reverse(res.begin(), res.end());
  return res;
}

int main() {
  vector<int> nums = {5,2,2,1};
  auto r = countSmaller(nums);
  for(auto i: r)
    printf("%d ", i);
  getchar();
}
