// Reverse a singly linked list with the following structure:
// struct List {
//  int val;
//  List* next;
// };

#include <stdio.h>

struct List {
  int val;
  List *next;
};

List *reverse(List *head) {
  List *next = NULL;
  while (head != NULL) {
    List *tmp = head->next;
    head->next = next;
    next = head;
    head = tmp;
  }
  return next;
}

List *reverse_recursive(List *head) {
  if (head == NULL || head->next == NULL)
    return head;
  List *h = reverse_recursive(head->next);
  head->next->next = head;
  head->next = NULL;
  return h;
}

int main() {
  const int siz = 5;
  List nodes[siz];
  for (int i = 0; i < siz; i++) {
    nodes[i].val = i + 1;
    nodes[i].next = i == 4 ? NULL : nodes + i + 1;
  }

  List *h = reverse_recursive(nodes);
  while (h) {
    printf("%d ", h->val);
    h = h->next;
  }
  return 0;
}