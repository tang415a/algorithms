// Write an algorithm to traverse a binary tree in a post order without recursion.
// For example,
//      1
//    2   3
//  4       5
// 6  7    8
//   9 10
// it prints out: 6 9 10 7 4 2 8 5 3 1


#include <stdio.h>
#include <stack>

using namespace std;

struct TreeNode
{
  TreeNode *left;
  TreeNode *right;
  int val;
};

void postOrder(TreeNode *root)
{
  if (root == NULL)
    return;

  const char ST_LEFT = 0;
  const char ST_RIGHT = 1;
  const char ST_NONE = 2;
  char action = ST_LEFT;

  stack<TreeNode *> s;
  s.push(root);
  while (true)
  {
    auto n = s.top();
    if (action == ST_LEFT)
    {
      if (n->left)
        s.push(n->left);
      else
        action = ST_RIGHT;
    }
    else if (action == ST_RIGHT)
    {
      if (n->right)
      {
        s.push(n->right);
        action = ST_LEFT;
      }
      else
        action = ST_NONE;
    }
    else
    {
      printf("%d ", n->val);
      s.pop();
      if (!s.empty())
        action = s.top()->right == n ? ST_NONE : ST_RIGHT;
      else
        break;
    }
  }
}

int main()
{
  const int siz = 10;

  TreeNode nodes[siz];
  for (int i = 0; i < siz; i++)
  {
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

  postOrder(nodes);
  getchar();
  return 0;
}