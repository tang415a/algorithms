// Write an algorithm and print a binary tree line by line.
// for example
//      1
//    2   3
//  4       5
// 6  7    8
//   9 10
// it will print: 1 2 3 4 5 6 7 8 9 10.

#include <stdio.h>
#include <queue>
using namespace std;

struct TreeNode
{
  TreeNode *left;
  TreeNode *right;
  int val;
};

void printByLine(TreeNode *root)
{
  if (root == NULL)
    return;
  queue<TreeNode*> q;
  q.push(root);
  TreeNode* rc = root;
  while(!q.empty())
  {
    auto n = q.front();
    q.pop();

    printf("%d ", n->val);

    TreeNode* rTemp;
    if (n->left)
    {
      q.push(n->left);
      rTemp = n->left;
    }

    if (n->right)
    {
      q.push(n->right);
      rTemp = n->right;
    }

    if (rc == n)
    {
      rc = rTemp;
      printf("\n");
    }
  }
}

int printByLevel(TreeNode* root, int l)
{
  if (l < 0 || root == NULL)
    return 0;
  if (l == 0) {
    printf("%d ", root->val);
    return 1;
  }
  
  return printByLevel(root->left, l - 1) + printByLevel(root->right, l - 1);
}

void printByLevel(TreeNode* root)
{
  for(int i = 0; ; i++)
  {
    if(0 == printByLevel(root, i))
      return;
    printf("\n");
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

  printByLine(nodes);
  printByLevel(nodes);
  getchar();
  return 0;
}