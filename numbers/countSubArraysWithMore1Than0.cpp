/*
You are given a binary array nums containing only the integers 0 and 1. Return
the number of subarrays in nums that have more 1's than 0's. Since the answer
may be very large, return it modulo 10^9 + 7.

A subarray is a contiguous sequence of elements within an array.

Example 1:

Input: nums = [0,1,1,0,1]
Output: 9
Explanation:
The subarrays of size 1 that have more ones than zeros are: [1], [1], [1]
The subarrays of size 2 that have more ones than zeros are: [1,1]
The subarrays of size 3 that have more ones than zeros are: [0,1,1], [1,1,0],
[1,0,1]
The subarrays of size 4 that have more ones than zeros are: [1,1,0,1]
The subarrays of size 5 that have more ones than zeros are: [0,1,1,0,1]

Example 2:

Input: nums = [0]
Output: 0
Explanation:
No subarrays have more ones than zeros.

Example 3:

Input: nums = [1]
Output: 1
Explanation:
The subarrays of size 1 that have more ones than zeros are: [1]


Constraints:

1 <= nums.length <= 10^5
0 <= nums[i] <= 1
*/
#include <iostream>
#include <vector>

using namespace std;

int countOfSubArrays(const vector<int> &arr) {
  int n = arr.size();
  vector<int> c(n + 1, 0);
  for (int i = 0; i < n; i++) {
    if (arr[i] == 1)
      c[i + 1] = c[i] + 1;
    else
      c[i + 1] = c[i] - 1;
  }

  long long ans = 0;
  for (int j = 0; j < n; j++) {
    int i = j + 1;
    while (i <= n) {
      int d = c[i] - c[j];
      if (d > 0) {
        ans += min(d, n - i + 1);
        i += d;
      } else if (d == 0) {
        i++;
      } else {
        i -= d;
      }
    }
  }
  return ans % 1000000007;
}

int countOfSubArrays2(const vector<int> &arr) {
  int n = arr.size();
  vector<int> c(n + 1, 0);
  for (int i = 0; i < n; i++) {
    if (arr[i] == 1)
      c[i + 1] = c[i] + 1;
    else
      c[i + 1] = c[i] - 1;
  }

  long long ans = 0;
  for (int j = 0; j < n; j++) {
    for (int i = j + 1; i <= n; i++) {
      if (c[i] > c[j])
        ans++;
    }
  }
  return ans % 100000007;
}

/* https://www.geeksforgeeks.org/binary-indexed-tree-or-fenwick-tree-2/
some important observations
* BITree[0] is a dummy node.
* BITree[y] is the parent of BITree[x], if and only if y can be obtained by
  removing the last set bit from the binary representation of x, that is y = x
  – (x & (-x)).
* The child node BITree[x] of the node BITree[y] stores the sum of the
  elements between y(inclusive) and x(exclusive): arr[y,…,x).
e.g.
  arr: 2, 1, 1, 3, 2, 3, 4, 5, 6, 7, 8, 9
  BI:                   Dummy(0)
      2(1)    3(2)         7(4)             21(8)
              1(3)      2(5)  5(6)     6(9) 13(10) 30(12)
                              4(7)          8(11)

getSum(x): Returns the sum of the sub-array arr[0,…,x]
// Returns the sum of the sub-array arr[0,…,x] using BITree[0..n], which is
constructed from arr[0..n-1] 1) Initialize the output sum as 0, the current
index as x+1. 2) Do following while the current index is greater than 0. …a) Add
BITree[index] to sum …b) Go to the parent of BITree[index]. The parent can be
obtained by removing the last set bit from the current index, i.e., index =
index – (index & (-index)) 3) Return sum.

update(x, val): Updates the Binary Indexed Tree (BIT) by performing arr[index]
+= val
// Note that the update(x, val) operation will not change arr[]. It only makes
changes to BITree[] 1) Initialize the current index as x+1. 2) Do the following
while the current index is smaller than or equal to n. …a) Add the val to
BITree[index] …b) Go to next element of BITree[index]. The next element can be
obtained by incrementing the last set bit of the current index, i.e., index =
index + (index & (-index))

How does Binary Indexed Tree work?
The idea is based on the fact that all positive integers can be represented as
the sum of powers of 2. For example 19 can be represented as 16 + 2 + 1. Every
node of the BITree stores the sum of n elements where n is a power of 2. For
example, in the first diagram above (the diagram for getSum()), the sum of the
first 12 elements can be obtained by the sum of the last 4 elements (from 9 to
12) plus the sum of 8 elements (from 1 to 8). The number of set bits in the
binary representation of a number n is O(Logn). Therefore, we traverse at-most
O(Logn) nodes in both getSum() and update() operations. The time complexity of
the construction is O(nLogn) as it calls update() for all n elements.
*/

// the tree stores the times of num(1) - num(0) that falls in the range [-n, n].
// need to remap it to the positive integers plus n + 1.
class FenwickTree {
public:
  FenwickTree(int n) : n(n), sums(2 * n + 1) {}

  void update(int i, int delta) {
    i += n + 1; // Re-mapping to positive
    while (i < sums.size()) {
      sums[i] += delta;
      i += i & -i; // get the next node
    }
  }

  int get(int i) {
    i += n + 1; // Re-mapping to positive
    int sum = 0;
    while (i > 0) {
      sum += sums[i];
      i -= i & -i; // get the parent node
    }
    return sum;
  }

private:
  const int n;
  vector<int> sums;
};

/*
we calculate the subtraction between the count of ones and zeros from 0 to i,
say it is j (remapping to k = j + n + 1) and store how many times it has
appeared at array[k]. Then the sum of array[0]...array[k-1] is how many
subarrays with more ones than zeros ending at i.
For example, array[k-1] says among the subarrays starting from 0 and ending at
any number in [0...i], count(1) - count(0) == j-1 appears array[k-1] times, then
among the subarrays starting from any number in [0...i] and ending at i,
count(1) - count(0) == 1 also appears array[k-1] times.
Use Fenwick tree to get the sum.
     ____________   j
                i
*/
// a better approach
int subarraysWithMoreOnesThanZeros(const vector<int> &nums) {
  constexpr int kMod = 1'000'000'007;
  int ans = 0;
  int prefix = 0;
  FenwickTree tree(nums.size());
  tree.update(0, 1);

  for (const int num : nums) {
    prefix += num == 0 ? -1 : 1;
    ans += tree.get(prefix - 1);
    ans %= kMod;
    tree.update(prefix, 1);
  }

  return ans;
}

#include <time.h>
int main() {
  cout << countOfSubArrays({0, 1, 1, 0, 1}) << endl;
  cout << countOfSubArrays({0}) << endl;
  cout << countOfSubArrays({1}) << endl;
  srand((unsigned int)time(NULL));
  vector<int> arr(100000);
  for (int i = 0; i < 100000; i++) {
    arr[i] = rand() % 2;
  }
  cout << countOfSubArrays(arr) << endl;
  cout << countOfSubArrays2(arr) << endl;
  cout << subarraysWithMoreOnesThanZeros({0, 0, 0, 0}) << endl;
  return 0;
}