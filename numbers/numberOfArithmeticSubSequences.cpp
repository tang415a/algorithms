/*
A sequence of number is called arithmetic if it consists of at least three
elements and if the difference between any two consecutive elements is the same.

For example, these are arithmetic sequence:

1, 3, 5, 7, 9
7, 7, 7, 7
3, -1, -5, -9
The following sequence is not arithmetic.

1, 1, 2, 5, 7

A zero-indexed array A consisting of N numbers is given. The arithmetic
sub-sequence means a sequence constituted by any numbers (at least three
numbers) from the array is arithmetric.

The function should return the number of different arithmetic sub-sequences from
the array A.


Example:

A = [1, 2, 1, 1, 1, 4, 3, 5, 6]

return: 14, for 14 sub-sequences from array A are arithmetic:
[1, 1, 1],
[1, 1, 1, 1],
[1, 2, 3],
[1, 2, 3, 4],
[1, 2, 3, 4, 5],
[1, 2, 3, 4, 5, 6],
[1, 3, 5],
[2, 3, 4],
[2, 3, 4, 5],
[2, 3, 4, 5, 6],
[2, 4, 6],
[3, 4, 5],
[3, 4, 5, 6],
[4, 5, 6]
*/
#include <vector>
using namespace std;

void do_qsort(int *arr, int low, int high) {
  if (low >= high)
    return;
  int item = arr[low], lo = low, hi = high + 1;
  while (true) {
    while (++lo <= high && arr[lo] <= item)
      ;
    while (--hi > low && arr[hi] >= item)
      ;
    if (lo < hi) {
      int tmp = arr[lo];
      arr[lo] = arr[hi];
      arr[hi] = tmp;
    } else {
      break;
    }
  }
  if (hi > low) {
    arr[low] = arr[hi];
    arr[hi] = item;
  }
  do_qsort(arr, low, hi - 1);
  do_qsort(arr, hi + 1, high);
}

void qsort(int *arr, int size) { do_qsort(arr, 0, size - 1); }

class ArithmeticSubSeq {
  int m_start, m_size, m_interval;

public:
  ArithmeticSubSeq(int st, int siz, int i)
      : m_start(st), m_size(siz), m_interval(i) {}

  int count() const {
    if (m_interval == 0) {
      return m_size - 2;
    }
    return (m_size - 1) * (m_size - 2) / 2;
  }

  bool contains(int s, int i) const {
    if (i != m_interval)
      return false;
    if (i == 0)
      return s == m_start;
    return (s - m_start) / i * i == s - m_start;
  }
};

class ArithmeticSubSeqs {
  vector<ArithmeticSubSeq> m_data;

public:
  void insert(int start, int size, int interval) {
    m_data.emplace_back(start, size, interval);
  }

  bool contained(int st, int i) const {
    for (const auto &s : m_data) {
      if (s.contains(st, i)) {
        return true;
      }
    }
    return false;
  }

  int count() const {
    int count = 0;
    for (auto &s : m_data) {
      count += s.count();
    }
    return count;
  }
};

void findSubSeqs(int *p, int size, ArithmeticSubSeqs &subSeqs,
                 const vector<int> &diff) {
  if (size < 3)
    return;
  for (int i = 0; i < size - 2; ++i) {
    for (int j = i + 1; j < size - 1; ++j) {
      int interval = p[j] - p[i];
      if (p[j] + interval > p[size - 1] || subSeqs.contained(p[i], interval))
        continue;
      int n = 0, k = j, delta = 0;
      while (k < size - 1) {
        delta += diff[k];
        if (delta > interval)
          break;
        if (delta == interval) {
          ++n;
          delta = 0;
        }
        ++k;
      }
      if (n > 0) {
        subSeqs.insert(p[i], n + 2, interval);
      }
    }
  }
}

// #include <algorithm>

int numberOfArithmeticSubSeqs(vector<int> &A) {
  int siz = static_cast<int>(A.size());
  qsort(&A[0], siz);
  // sort(A.begin(), A.end());
  vector<int> diff;
  diff.resize(siz - 1);
  for (int i = 1; i < siz; ++i) {
    diff[i - 1] = A[i] - A[i - 1];
  }
  ArithmeticSubSeqs subSeqs;
  findSubSeqs(&A[0], siz, subSeqs, diff);
  return subSeqs.count();
}

int main() {
  {
    vector<int> A = {1, 2, 4, 3};
    printf("%d\n", numberOfArithmeticSubSeqs(A));
  }
  {
    vector<int> A = {1, 2, 1, 4, 3};
    printf("%d\n", numberOfArithmeticSubSeqs(A));
  }
  {
    vector<int> A = {1, 2, 1, 1, 4, 3};
    printf("%d\n", numberOfArithmeticSubSeqs(A));
  }
  {
    vector<int> A = {1, 2, 1, 1, 4, 3, 5, 6};
    printf("%d\n", numberOfArithmeticSubSeqs(A));
  }
  {
    vector<int> A = {1, 2, 1, 1, 1, 4, 3, 5, 6};
    printf("%d\n", numberOfArithmeticSubSeqs(A));
  }
  return 0;
}