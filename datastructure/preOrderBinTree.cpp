// Write an algorithm to traverse a binary tree in a pre order without recursion.
// For example,
//      1
//    2   3
//  4       5
// 6  7    8
//   9 10
// it prints out: 1 2 4 6 7 9 10 3 5 8

#include <stdio.h>
#include <stack>

using namespace std;

struct TreeNode
{
  TreeNode *left;
  TreeNode *right;
  int val;
};

void preOrder(TreeNode *root)
{
  if (root == NULL)
    return;
  stack<TreeNode*> s;
  s.push(root);
  while(!s.empty())
  {
    auto n = s.top();
    s.pop();
    printf("%d ", n->val);
    if (n->right)
      s.push(n->right);
    if (n->left)
      s.push(n->left);
  }
}

int main()
{
  const int siz = 10;

  TreeNode nodes[siz];
  for(int i = 0; i < siz; i++) {
    nodes[i].left = nodes[i].right = NULL;
    nodes[i].val = i + 1;
  }

  nodes[0].left = nodes + 1;
  nodes[0].right = nodes + 2;
  nodes[1].left = nodes + 3;
  nodes[2].right = nodes + 4;
  nodes[3].left = nodes + 5;
  nodes[3].right = nodes + 6;
  nodes[4].left = nodes + 7;
  nodes[6].left = nodes + 8;
  nodes[6].right = nodes + 9;

  preOrder(nodes);
  return 0;
}