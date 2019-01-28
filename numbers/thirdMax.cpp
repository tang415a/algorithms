/*
Given a non-empty array of integers, return the third maximum number in this array. If it does not exist, return the maximum number. The time complexity must be in O(n).

Example 1:
Input: [3, 2, 1]

Output: 1

Explanation: The third maximum is 1.
Example 2:
Input: [1, 2]

Output: 2

Explanation: The third maximum does not exist, so the maximum (2) is returned instead.
Example 3:
Input: [2, 2, 3, 1]

Output: 1

Explanation: Note that the third maximum here means the third maximum distinct number.
Both numbers with value 2 are both considered as second maximum.
*/

#include <stdio.h>
#include <vector>
#include <set>
using namespace std;

int nthMax(const vector<int>& nums, int n) {
    set<int> s;
    for(auto& num: nums) {
        s.insert(num);
        if (s.size() > n)
            s.erase(s.begin());
    }
    return s.size() < n ? *s.rbegin() : *s.begin();
}

int thirdMax(const vector<int>& nums) {
    return nthMax(nums, 3);
}

int main() {
    printf("%d\n", thirdMax({3,2,1}));
    printf("%d\n", thirdMax({1,2}));
    printf("%d\n", thirdMax({2,2,3,1}));
    getchar();
    return 0;
}