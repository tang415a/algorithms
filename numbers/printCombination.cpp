// print the combination of selecting n objects from the available n objects.
// i.e. implement the function:
// void printCombination(int m, int n)
// In particular, printCombination(3, 2) will yield:
// 1, 2
// 1, 3
// 2, 3
#include <iostream>
using namespace std;

void printCombination(int *selected, int base, int current, int left, int m,
                      int n) {
  if (left == 0) {
    for (int i = 0; i < n; ++i) {
      cout << selected[i] << " ";
    }
    cout << endl;
    return;
  }
  for (int i = 0; i < m - base - left + 1; ++i) {
    selected[current] = base + i + 1;
    printCombination(selected, selected[current], current + 1, left - 1, m, n);
  }
}

void printCombination(int m, int n) {
  if (n > m)
    return;
  int *selected = new int[n];
  printCombination(selected, 0, 0, n, m, n);
  delete[] selected;
}

int main() {
  printCombination(3, 2);
  return 0;
}