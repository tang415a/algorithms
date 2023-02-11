/*
You are given an integer array arr. From some starting index, you can make a
series of jumps. The (1st, 3rd, 5th, ...) jumps in the series are called
odd-numbered jumps, and the (2nd, 4th, 6th, ...) jumps in the series are called
even-numbered jumps. Note that the jumps are numbered, not the indices.

You may jump forward from index i to index j (with i < j) in the following way:

During odd-numbered jumps (i.e., jumps 1, 3, 5, ...), you jump to the index j
such that arr[i] <= arr[j] and arr[j] is the smallest possible value. If there
are multiple such indices j, you can only jump to the smallest such index j.
During even-numbered jumps (i.e., jumps 2, 4, 6, ...), you jump to the index j
such that arr[i] >= arr[j] and arr[j] is the largest possible value. If there
are multiple such indices j, you can only jump to the smallest such index j. It
may be the case that for some index i, there are no legal jumps. A starting
index is good if, starting from that index, you can reach the end of the array
(index arr.length - 1) by jumping some number of times (possibly 0 or more than
once).

Return the number of good starting indices.


Example 1:

Input: arr = [10,13,12,14,15]
Output: 2
Explanation:
From starting index i = 0, we can make our 1st jump to i = 2 (since arr[2] is
the smallest among arr[1], arr[2], arr[3], arr[4] that is greater or equal to
arr[0]), then we cannot jump any more. From starting index i = 1 and i = 2, we
can make our 1st jump to i = 3, then we cannot jump any more. From starting
index i = 3, we can make our 1st jump to i = 4, so we have reached the end. From
starting index i = 4, we have reached the end already. In total, there are 2
different starting indices i = 3 and i = 4, where we can reach the end with some
number of jumps.

Example 2:

Input: arr = [2,3,1,1,4]
Output: 3
Explanation:
From starting index i = 0, we make jumps to i = 1, i = 2, i = 3:
During our 1st jump (odd-numbered), we first jump to i = 1 because arr[1] is the
smallest value in [arr[1], arr[2], arr[3], arr[4]] that is greater than or equal
to arr[0]. During our 2nd jump (even-numbered), we jump from i = 1 to i = 2
because arr[2] is the largest value in [arr[2], arr[3], arr[4]] that is less
than or equal to arr[1]. arr[3] is also the largest value, but 2 is a smaller
index, so we can only jump to i = 2 and not i = 3 During our 3rd jump
(odd-numbered), we jump from i = 2 to i = 3 because arr[3] is the smallest value
in [arr[3], arr[4]] that is greater than or equal to arr[2]. We can't jump from
i = 3 to i = 4, so the starting index i = 0 is not good. In a similar manner, we
can deduce that: From starting index i = 1, we jump to i = 4, so we reach the
end. From starting index i = 2, we jump to i = 3, and then we can't jump
anymore. From starting index i = 3, we jump to i = 4, so we reach the end. From
starting index i = 4, we are already at the end. In total, there are 3 different
starting indices i = 1, i = 3, and i = 4, where we can reach the end with some
number of jumps.

Example 3:

Input: arr = [5,1,3,4,2]
Output: 3
Explanation: We can reach the end from starting indices 1, 2, and 4.


Constraints:

1 <= arr.length <= 2 * 10^4
0 <= arr[i] < 10^5
*/

#include <iostream>
#include <vector>

using namespace std;

int oddEvenJumps__(const vector<int> &arr) {
  int ans = 1;
  char p[20000];
  memset(p, 0, sizeof(char) * 20000);
  p[0] = 3;
  int n = arr.size(), m1 = 1, m2 = 1;
  vector<int> st1(n), st2(n);
  st1[0] = st2[0] = n - 1;
  for (int i = n - 2; i >= 0; i--) {
    while (m1 > 0 && arr[st1[m1 - 1]] < arr[i]) {
      m1--;
    }
    // even jump from st1[m2 - 1] here will work
    if (m1 > 0 && ((p[n - 1 - st1[m1 - 1]] & 0x2) > 0)) {
      p[n - 1 - i] = 1; // odd jump from here will work
      ans++;
    }
    st1[m1++] = i;
    while (m2 > 0 && arr[i] < arr[st2[m2 - 1]]) {
      m2--;
    }
    // odd jump from st1[m2 - 1] here will work
    if (m2 > 0 && ((p[n - 1 - st2[m2 - 1]] & 0x1) > 0)) {
      p[n - 1 - i] |= 0x2; // even jump from here will work
    }
    st2[m2++] = i;
  }
  return ans;
}

#include <set>
struct ArrayIndex {
  int index, value;
};
struct ArrayIndexCompare {
  bool operator()(const ArrayIndex &left, const ArrayIndex &right) const {
    return left.value < right.value ||
           (left.value == right.value && left.index < right.index);
  }
};
int oddEvenJumps(const vector<int> &arr) {
  int ans = 1;
  char p[20000];
  memset(p, 0, sizeof(char) * 20000);
  p[0] = 0x3;
  int n = arr.size();
  set<ArrayIndex, ArrayIndexCompare> s;
  s.insert(ArrayIndex{n - 1, arr[n - 1]});
  for (int i = n - 2; i >= 0; i--) {
    ArrayIndex item = {i, arr[i]};
    auto it = s.upper_bound(item);
    if (it != s.end()) {
      if ((p[n - 1 - it->index] & 0x2) > 0) {
        p[n - 1 - i] |= 0x1;
        ans++;
      }
      if (it->value == arr[i] && (p[n - 1 - it->index] & 0x1) > 0) {
        p[n - 1 - i] |= 0x2;
        s.insert(item);
        continue;
      }
    }
    if (it != s.begin()) {
      --it;
      auto iter = it;
      while (iter != s.begin() && (--iter)->value == it->value) {
        it = iter;
      }
      if ((p[n - 1 - it->index] & 0x1) > 0) {
        p[n - 1 - i] |= 0x2;
      }
    }
    s.insert(item);
  }
  return ans;
}

int main() {
  cout << oddEvenJumps({10, 13, 12, 14, 15}) << endl;
  cout << oddEvenJumps({2, 3, 1, 1, 4}) << endl;
  cout << oddEvenJumps({5, 1, 3, 4, 2}) << endl;
  return 0;
}