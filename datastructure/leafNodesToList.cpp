// Given a binary tree, store the leaf nodes to a singly linked list in a left-to-right order.
// Binary tree structure:
// struct TreeNode
// {
//   TreeNode *left, *right;
//   int val;
// };

#include <stdio.h>

struct TreeNode
{
  TreeNode *left, *right;
  int val;
};

struct ListNode
{
  TreeNode* node;
  ListNode* next;
};

ListNode *convertToList(TreeNode *root)
{
  if (root == NULL)
    return NULL;
  if (root->left == NULL && root->right == NULL)
  {
    ListNode* node = new ListNode({root, NULL});
    return node;
  }

  ListNode *leftList = convertToList(root->left),
    *rightList = convertToList(root->right);
  if (leftList == NULL)
    return rightList;
  ListNode* n = leftList;
  while(n->next)
    n = n->next;
  n->next = rightList;
  return leftList;
}

int main()
{
  const int siz = 8;

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

  ListNode* list = convertToList(nodes);

  while (list)
  {
    printf("%d ", list->node->val);
    ListNode* tmp = list;
    list = list->next;
    delete tmp;
  }
  return 0;
}