/*
You are given an array of k linked-lists lists, each linked-list is sorted in
ascending order.

Merge all the linked-lists into one sorted linked-list and return it.

Example 1:

Input: lists = [[1,4,5],[1,3,4],[2,6]]
Output: [1,1,2,3,4,4,5,6]
Explanation: The linked-lists are:
[
  1->4->5,
  1->3->4,
  2->6
]
merging them into one sorted list:
1->1->2->3->4->4->5->6
Example 2:

Input: lists = []
Output: []
Example 3:

Input: lists = [[]]
Output: []


Constraints:

k == lists.length
0 <= k <= 10^4
0 <= lists[i].length <= 500
-10^4 <= lists[i][j] <= 10^4
lists[i] is sorted in ascending order.
The sum of lists[i].length will not exceed 10^4.
*/

#include <iostream>
#include <vector>

using namespace std;

/**
 * Definition for singly-linked list.
 */
struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// helper functions
void clear(ListNode *head) {
  while (head) {
    ListNode *n = head->next;
    delete head;
    head = n;
  }
}

void print(ListNode *head) {
  while (head) {
    cout << head->val << " ";
    head = head->next;
  }
  cout << endl;
}

ListNode *create(const vector<int> &vec) {
  ListNode *h = nullptr;
  for (int n = vec.size(), i = n - 1; i >= 0; i--) {
    ListNode *p = new ListNode(vec[i]);
    p->next = h;
    h = p;
  }
  return h;
}

vector<ListNode *> createLists(const vector<vector<int>> &v) {
  int n = v.size();
  vector<ListNode *> ans(n);
  for (int i = 0; i < n; i++) {
    ans[i] = create(v[i]);
  }
  return ans;
}

#include <queue>
ListNode *mergeKLists(const vector<ListNode *> &lists) {
  if (lists.empty()) {
    return nullptr;
  }
  priority_queue<pair<int, ListNode *>, vector<pair<int, ListNode *>>,
                 greater<pair<int, ListNode *>>>
      pq;
  for (auto n : lists) {
    if (n != nullptr) {
      pq.push({n->val, n});
    }
  }
  ListNode head;
  ListNode *dummy = &head;
  while (!pq.empty()) {
    dummy->next = pq.top().second;
    dummy = dummy->next;
    pq.pop();
    if (dummy->next) {
      pq.push({dummy->next->val, dummy->next});
    }
  }
  return head.next;
}

int main() {
  auto lists = createLists({{1, 4, 5}, {1, 3, 4}, {2, 6}});
  auto list = mergeKLists(lists);
  print(list);
  clear(list);

  list = mergeKLists({});
  print(list);
  clear(list);

  list = mergeKLists({{}});
  print(list);
  clear(list);
  return 0;
}
