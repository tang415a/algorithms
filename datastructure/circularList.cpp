// Check if a singly linked list has a circle.
// The list structure:
// struct List {
//   List* next;
// };

#include <stdio.h>

struct List
{
  List *next;
};

bool hasCircle(List *l)
{
  List *fast = l, *slow = l;
  while (fast)
  {
    fast = fast->next;
    if (fast == NULL)
      return false;
    fast = fast->next;
    slow = slow->next;
    if (fast == slow)
      return true;
  }
  return false;
}

int main()
{
  const int siz = 5;
  List nodes[siz];
  for (int i = 0; i < siz - 1; i++)
    nodes[i].next = nodes + i + 1;
  nodes[siz - 1].next = nodes + siz / 2;

  printf("%d ", hasCircle(nodes));

  nodes[siz - 1].next = NULL;
  printf("%d ", hasCircle(nodes));

  return 0;
}