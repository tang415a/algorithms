/*
Find out the two nodes which have the largest distance from each other in a
binary tree.

The distance between two nodes is defined by the number of levels which need to
be crossed from one to another.

Example 1:
      1
    2   3
  4       5
 6  7    8
   9 10
Output: from 9(10) to 8, max distance: 7

Example 2:
        1
     2     3
  4    5
6     7
 9   8
      10
Output: from 9 to 10, max distance: 7
*/

#include <stdio.h>

struct TreeNode {
  TreeNode *left, *right;
  int val;
};

int analyzeRoot(TreeNode *root, int &d, int &v, int &from, int &to) {
  if (root == nullptr) {
    return -1;
  }
  if (root->left == nullptr && root->right == nullptr) {
    v = root->val;
    return 0;
  }
  int v1 = root->val, v2 = root->val;
  int d1 = analyzeRoot(root->left, d, v1, from, to) + 1,
      d2 = analyzeRoot(root->right, d, v2, from, to) + 1;
  if (d < d1 + d2) {
    from = v1;
    to = v2;
    d = d1 + d2;
  }
  if (d1 < d2) {
    v = v2;
    return d2;
  }
  v = v1;
  return d1;
}

int farthestTo(TreeNode *root, TreeNode *&res) {
  if (root == NULL || (root->left == NULL && root->right == NULL)) {
    res = root;
    return 0;
  }

  int dist = 0, tmp;
  TreeNode *n;
  if (root->left) {
    tmp = farthestTo(root->left, n) + 1;
    if (dist < tmp) {
      dist = tmp;
      res = n;
    }
  }
  if (root->right) {
    tmp = farthestTo(root->right, n) + 1;
    if (dist < tmp) {
      dist = tmp;
      res = n;
    }
  }

  return dist;
}

int farthest(TreeNode *root, TreeNode *&one, TreeNode *&two) {
  if (root == NULL || (root->left == NULL && root->right == NULL)) {
    one = two = root;
    return 0;
  }

  struct {
    int dist;
    TreeNode *one, *two;
  } options[3] = {{0, root, root}, {0, root, root}, {0, root, root}};

  if (root->left) {
    options[0].dist = farthest(root->left, options[0].one, options[0].two);
    options[2].dist += (1 + farthestTo(root->left, options[2].one));
  }
  if (root->right) {
    options[1].dist = farthest(root->right, options[1].one, options[1].two);
    options[2].dist += (1 + farthestTo(root->right, options[2].two));
  }

  int max = 0;
  for (int i = 1; i < 3; i++)
    if (options[i].dist > options[max].dist)
      max = i;

  one = options[max].one;
  two = options[max].two;
  return options[max].dist;
}

int main() {
  const int siz = 10;

  TreeNode nodes[siz];
  for (int i = 0; i < siz; i++) {
    nodes[i].left = nodes[i].right = NULL;
    nodes[i].val = i + 1;
  }

  nodes[0].left = nodes + 1;
  nodes[0].right = nodes + 2;
  nodes[1].left = nodes + 3;
  nodes[1].right = nodes + 4;
  nodes[3].left = nodes + 5;
  nodes[4].left = nodes + 6;
  nodes[5].right = nodes + 8;
  nodes[6].left = nodes + 7;
  nodes[7].right = nodes + 9;

  TreeNode *one, *two;
  int d = farthest(nodes, one, two);
  printf("from %d to %d we have maximum distance %d", one->val, two->val, d);
  {
    int d = 0, _v = 0, from = 0, to = 0;
    analyzeRoot(nodes, d, _v, from, to);
    printf("\nfrom %d to %d we have maximum distance %d", from, to, d);
  }
  return 0;
}