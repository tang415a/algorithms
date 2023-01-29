/*
A complete binary tree is a binary tree in which every level, except possibly
the last, is completely filled, and all nodes are as far left as possible.

Write a data structure CBTInserter that is initialized with a complete binary
tree and supports the following operations:

CBTInserter(TreeNode root) initializes the data structure on a given tree with
head node root; CBTInserter.insert(int v) will insert a TreeNode into the tree
with value node.val = v so that the tree remains complete, and returns the value
of the parent of the inserted TreeNode; CBTInserter.get_root() will return the
head node of the tree.

Example 1:

Input: inputs = ["CBTInserter","insert","get_root"], inputs = [[[1]],[2],[]]
Output: [null,1,[1,2]]

Example 2:

Input: inputs = ["CBTInserter","insert","insert","get_root"], inputs =
[[[1,2,3,4,5,6]],[7],[8],[]] Output: [null,3,4,[1,2,3,4,5,6,7,8]]

Note:

The initial given tree is complete and contains between 1 and 1000 nodes.
CBTInserter.insert is called at most 10000 times per test case.
Every value of a given or inserted node is between 0 and 5000.
*/

#include <queue>
#include <stdio.h>
#include <vector>

using namespace std;

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

void clear(TreeNode *r) {
  if (r == NULL)
    return;
  clear(r->left);
  clear(r->right);
  delete r;
}

void print(TreeNode *r) {
  if (r == NULL)
    return;
  vector<TreeNode *> temp;
  temp.push_back(r);
  for (int i = 0; i < temp.size(); i++) {
    printf("%d ", temp[i]->val);
    if (temp[i]->left)
      temp.push_back(temp[i]->left);
    if (temp[i]->right)
      temp.push_back(temp[i]->right);
  }
}

class CBTInserter {
public:
  CBTInserter(TreeNode *root) {
    m_root = root;
    process(m_root);
  }

  int insert(int v) {
    TreeNode *child = new TreeNode(v);
    if (m_candidates.empty()) {
      m_root = child;
      m_candidates.push(child);
      return 0;
    }
    TreeNode *parent = m_candidates.front();
    if (parent->left) {
      parent->right = child;
      m_candidates.pop();
    } else {
      parent->left = child;
    }
    m_candidates.push(child);
    return parent->val;
  }

  TreeNode *get_root() { return m_root; }

private:
  void process(TreeNode *root) {
    if (root == NULL)
      return;

    vector<TreeNode *> temp;
    temp.push_back(root);
    bool beginCollect = false;
    for (int i = 0; i < temp.size(); i++) {
      auto pNode = temp[i];
      if (beginCollect) {
        m_candidates.push(pNode);
      }
      if (pNode->left)
        temp.push_back(pNode->left);
      if (pNode->right)
        temp.push_back(pNode->right);
      else if (!beginCollect) {
        m_candidates.push(pNode);
        beginCollect = true;
      }
    }
  }

  TreeNode *m_root;
  queue<TreeNode *> m_candidates;
};

/**
 * Your CBTInserter object will be instantiated and called as such:
 * CBTInserter* obj = new CBTInserter(root);
 * int param_1 = obj->insert(v);
 * TreeNode* param_2 = obj->get_root();
 */

int main() {
  TreeNode *r = new TreeNode(1);
  CBTInserter *p = new CBTInserter(r);
  int v = p->insert(2);
  printf("%d\n", v);
  for (int i = 3; i < 9; i++)
    p->insert(i);

  CBTInserter o(r);
  for (int i = 9; i < 15; i++)
    o.insert(i);
  print(p->get_root());
  clear(p->get_root());
  delete p;
  return 0;
}