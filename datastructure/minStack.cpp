/*
Design a data structure that supports all following operations in average O(1)
time.

push(val): Pushes an item val to the stack.
pop(): Pops the top item out of the stack.
top(): Returns the top item.
min(): Returns the minimum value of all the items in the stack.
*/

#include <stack>
#include <stdio.h>

using namespace std;

class MinStack {
public:
  /** Pushes an item val to the stack **/
  void push(int val) {
    m_data.push(val);
    if (m_min.empty() || m_min.top() > val)
      m_min.push(val);
    else
      m_min.push(m_min.top());
  }

  /** Pops the top item out of the stack **/
  void pop() {
    m_data.pop();
    m_min.pop();
  }

  /** Returns the top item **/
  int top() { return m_data.top(); }

  /** Returns the minimum value of all the items in the stack **/
  int min() { return m_min.top(); }

private:
  stack<int> m_data;
  stack<int> m_min;
};

int main() {
  MinStack s;
  s.push(1);
  printf("top: %d\n", s.top());
  printf("min: %d\n", s.min());
  s.push(2);
  printf("top: %d\n", s.top());
  printf("min: %d\n", s.min());
  s.push(0);
  printf("top: %d\n", s.top());
  printf("min: %d\n", s.min());
  s.pop();
  printf("top: %d\n", s.top());
  printf("min: %d\n", s.min());
  return 0;
}