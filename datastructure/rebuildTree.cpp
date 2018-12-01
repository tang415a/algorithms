// Rebuld a binary tree from the pre-order and in-order traversal strings.

#include <stdio.h>

struct TreeNode
{
  TreeNode* left, *right;
  char val;
};

void preOrder(TreeNode* root)
{
  if (root == NULL)
    return;
  printf("%c ", root->val);
  preOrder(root->left);
  preOrder(root->right);
}

void inOrder(TreeNode* root)
{
  if (root == NULL)
    return;
  inOrder(root->left);
  printf("%c ", root->val);
  inOrder(root->right);
}

TreeNode* genTree(char* preOrder, char* inOrder, int len)
{
  if (len == 0)
    return NULL;

  char c = preOrder[0];
  int i = 0;
  for (; i < len; i++)
    if (c == inOrder[i])
      break;
  if (i == len)
    return NULL;

  TreeNode* left = i == 0 ? NULL: genTree(preOrder + 1, inOrder, i);
  TreeNode* right = i == len - 1 ? NULL: genTree(preOrder + i + 1, inOrder + i + 1, len - i - 1);
  TreeNode* n = new TreeNode({left, right, c});
  return n;
}

void clear(TreeNode* root)
{
  if(root == NULL)
    return;
  clear(root->left);
  clear(root->right);
  delete root;
}

int main()
{
  auto root = genTree("0135689247", "5386910274", 10);
  preOrder(root);
  printf("\n");
  inOrder(root);
  clear(root);
  return 0;
}