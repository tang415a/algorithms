// implement a function to print the permuation of N,
// i.e. N factorial.
// void printPermutation(int n)
// for example, printPermutation(3) will yield:
// 1, 2, 3
// 1, 3, 2
// 2, 1, 3
// 2, 3, 1
// 3, 2, 1
// 3, 1, 2
#include <iostream>
using namespace std;

void printPermutation(int *selected, int *candidates, int current, int left, int n) {
    if (left == 0) {
        for (int i = 0; i < n; ++i) {
            cout << selected[i] << " ";
        }
        cout << endl;
        return;
    }
    selected[current] = candidates[0];
    printPermutation(selected, candidates + 1, current + 1, left - 1, n);

    for (int i = 1; i < left; ++i) {
        selected[current] = candidates[i];
        candidates[i] = candidates[0];
        printPermutation(selected, candidates + 1, current + 1, left - 1, n);
        candidates[i] = selected[current];
    }
}

void printPermutation(int n) {
    int *selected = new int[n];
    int *candidates = new int[n];
    for (int i = 0; i < n; ++i)
        candidates[i] = i + 1;
    printPermutation(selected, candidates, 0, n, n);
    delete[] candidates;
    delete[] selected;
}

int main() {
    printPermutation(4);
    return 0;
}