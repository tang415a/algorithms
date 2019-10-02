/*
We run a preorder depth first search on the root of a binary tree.

At each node in this traversal, we output D dashes (where D is the depth of this node), then we output the value of this node.  (If the depth of a node is D, the depth of its immediate child is D+1.  The depth of the root node is 0.)

If a node has only one child, that child is guaranteed to be the left child.

Given the output S of this traversal, recover the tree and return its root.

Example 1:

Input: "1-2--3--4-5--6--7"
Output: [1,2,5,3,4,6,7]

Example 2:

Input: "1-2--3---4-5--6---7"
Output: [1,2,5,3,null,6,null,4,null,7]
 
Example 3:

Input: "1-401--349---90--88"
Output: [1,401,null,349,88,90]
 
Note:
1. The number of nodes in the original tree is between 1 and 1000.
2. Each node will have a value between 1 and 10^9.
*/

#include <stdio.h>
#include <string>
#include <vector>
using namespace std;

struct TreeNode
{
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

TreeNode *recoverFromPreorder(string S)
{
  int siz = S.size();
  if (siz <= 0 || (S[0] < '1' && S[0] > '9'))
    return NULL;
  vector<TreeNode *> vec;
  int level = 0, val = S[0] - '0';
  for (auto i = 1; i <= siz; i++)
  {
    if (i == siz || (S[i] == '-' && S[i - 1] != '-'))
    {
      TreeNode *n = new TreeNode(val);
      if (level < vec.size())
        vec[level] = n;
      else
        vec.push_back(n);
      if (level > 0)
      {
        if (vec[level - 1]->left)
          vec[level - 1]->right = n;
        else
          vec[level - 1]->left = n;
      }

      level = 1;
    }
    else if (S[i] == '-')
      level++;
    else if (S[i] != '-' && S[i - 1] == '-')
      val = S[i] - '0';
    else
      val = val * 10 + S[i] - '0';
  }
  return vec[0];
}

void print(TreeNode *root)
{
  vector<TreeNode *> vec;
  vec.push_back(root);

  for (auto i = 0; i < vec.size(); i++)
  {
    if (vec[i] && (vec[i]->left || vec[i]->right))
    {
      vec.push_back(vec[i]->left);
      vec.push_back(vec[i]->right);
    }
  }

  size_t siz = vec.size();
  for (auto i = 0; i < siz; i++)
  {
    if (vec[i])
      printf("%d ", vec[i]->val);
    else if(i < siz - 1)
      printf("null ");
  }
}

void clear(TreeNode *root)
{
  if (root == NULL)
    return;
  clear(root->left);
  clear(root->right);
  delete root;
}

int main()
{
  const string S = "1";

  TreeNode *root = recoverFromPreorder(S);
  print(root);
  clear(root);
  getchar();
  return 0;
}