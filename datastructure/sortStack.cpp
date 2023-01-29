// With only one extra stack (you may declare a few variables too), sort a stack of integers
#include <stack>
using namespace std;
#include <stdio.h>

void insertItem(stack<int>& helper, int item, bool ascending) {
  if (helper.empty())
    helper.push(item);
  else {
    int top = helper.top();
    if (ascending && top >= item) {
      helper.push(item);
    }
    else if (!ascending && top <= item) {
      helper.push(item);
    }
    else {
      helper.pop();
      insertItem(helper, item, ascending);
      helper.push(top);
    }
  }
}

void sort(stack<int>& input, bool ascending = true) {
  stack<int> helper;
  while(!input.empty()) {
    int t = input.top();
    insertItem(helper, t, ascending);
    input.pop();
  }
  while(!helper.empty()) {
    printf("%d ", helper.top());
    helper.pop();
  }
}

int main() {
  stack<int> s;
  auto arr = {3, 4, 0, 2, 9, 6, 7, 1, 5, 8};
  for(auto i: arr) {
    s.push(i);
  }
  sort(s);
  return 0;
}