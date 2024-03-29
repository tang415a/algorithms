/*
In a deck of cards, each card has an integer written on it.

Return true if and only if you can choose X >= 2 such that it is possible to split the entire deck into 1 or more groups of cards, where:

Each group has exactly X cards.
All the cards in each group have the same integer.

Example 1:

Input: [1,2,3,4,4,3,2,1]
Output: true
Explanation: Possible partition [1,1],[2,2],[3,3],[4,4]

Example 2:

Input: [1,1,1,2,2,2,3,3]
Output: false
Explanation: No possible partition.

Example 3:

Input: [1]
Output: false
Explanation: No possible partition.

Example 4:

Input: [1,1]
Output: true
Explanation: Possible partition [1,1]

Example 5:

Input: [1,1,2,2,2,2]
Output: true
Explanation: Possible partition [1,1],[2,2],[2,2]

Note:

1 <= deck.length <= 10000
0 <= deck[i] < 10000 
*/

#include <stdio.h>
#include <vector>
#include <map>
using namespace std;

int commonDivisor(int a, int b) {
  if (a > b)
    return commonDivisor(b, a);
  if (a == 0)
    return b;
  return commonDivisor(b % a, a); 
}

bool hasGroupsSizeX(vector<int>& deck) {
  map<int, int> m;
  for (auto& c: deck) {
    m[c]++;
  }
  int groupSize = 0;
  for (auto& i: m) {
    if (i.second == 1)
      return false;
    groupSize = groupSize == 0 ? i.second : commonDivisor(groupSize, i.second);
    if (groupSize == 1)
      return false;     
  }
  return true;
}

int main() {
  vector<int> deck = {1,1,1,2,2,2,3,3};
  printf("%d", hasGroupsSizeX(deck));
  return 0;
}