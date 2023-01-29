// construct a binary tree to sort an array.

#include <stdio.h>
struct TreeNode {
  int val;
  TreeNode *left, *right;
};

void insert_node(TreeNode *&root, int val) {
  if (!root) {
    root = new TreeNode({val, NULL, NULL});
    return;
  }

  if (val < root->val)
    insert_node(root->left, val);
  else
    insert_node(root->right, val);
}

void free_tree(TreeNode *root) {
  if (root) {
    free_tree(root->left);
    free_tree(root->right);
    delete root;
    root = NULL;
  }
}

void convert(TreeNode *root, int *arr, int &idx) {
  if (root) {
    convert(root->left, arr, idx);
    arr[idx++] = root->val;
    convert(root->right, arr, idx);
  }
}

void tree_sort(int *arr, int siz) {
  TreeNode *root = NULL;
  int i = 0;
  for (; i < siz; i++)
    insert_node(root, arr[i]);
  i = 0;
  convert(root, arr, i);
  free_tree(root);
}

int main() {
  int arr[] = {2, 1, 0, -1, 3, 4, 2, 0, -5, 6, -3};
  tree_sort(arr, sizeof(arr) / sizeof(arr[0]));
  for (auto &v : arr)
    printf("%d ", v);
  return 0;
}