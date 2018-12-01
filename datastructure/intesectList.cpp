// Check if two singly linked list intersect, i.e. if they have a common node.
// The list structure:
// struct List {
//  List* next;
// };

#include <stdio.h>

struct List
{
  List* next;
};

bool ifIntersect(List* l1, List* l2)
{
  if (l1 == NULL || l2 == NULL)
    return false;
  
  while(l1->next) l1 = l1->next;
  while(l2->next) l2 = l2->next;
  return l1 == l2;
}

int main()
{
  const int siz = 5;
  List nodes[siz];
  for(int i = 0; i < siz - 1; i++)
    nodes[i].next = nodes + i + 1;
  
  nodes[siz - 1].next = NULL;

  List n = {NULL}, l1 = {&n}, l2 = {nodes};

  printf("%d %d", ifIntersect(&l1, nodes), ifIntersect(&l2, nodes));
  return 0;
}