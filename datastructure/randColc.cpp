/*
Design a data structure that supports all following operations in average O(1) time.

insert(val): Inserts an item val to the set if not already present.
remove(val): Removes an item val from the set if present.
getRandom: Returns a random element from current set of elements. Each element must have the same probability of being returned.
Example:

// Init an empty set.
RandomizedSet randomSet = new RandomizedSet();

// Inserts 1 to the set. Returns true as 1 was inserted successfully.
randomSet.insert(1);

// Returns false as 2 does not exist in the set.
randomSet.remove(2);

// Inserts 2 to the set, returns true. Set now contains [1,2].
randomSet.insert(2);

// getRandom should return either 1 or 2 randomly.
randomSet.getRandom();

// Removes 1 from the set, returns true. Set now contains [2].
randomSet.remove(1);

// 2 was already in the set, so return false.
randomSet.insert(2);

// Since 2 is the only number in the set, getRandom always return 2.
randomSet.getRandom();
*/

#include <time.h>
#include <stdio.h>
#include <map>
#include <vector>
using namespace std;

class RandomizedSet {
public:
  /** Initialize your data structure here. */
  RandomizedSet() {
    srand(time(NULL));
  }
  
  /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
  bool insert(int val) {
    if (m_indices.find(val) == m_indices.end()){
      m_indices[val] = m_data.size();
      m_data.push_back(val);
      return true;
    }
    return false;
  }
  
  /** Removes a value from the set. Returns true if the set contained the specified element. */
  bool remove(int val) {
    auto& iter = m_indices.find(val);
    if (iter == m_indices.end())
      return false;
    int idx = iter->second, last = m_data.size() - 1;
    if (idx < last) {
      m_data[idx] = m_data[last];
      m_indices[m_data[last]] = idx;
    }
    m_data.erase(m_data.end() - 1);
    m_indices.erase(iter);
    return true;
  }
  
  /** Get a random element from the set. */
  int getRandom() {
    int idx = rand() % m_data.size();
    return m_data[idx];
  }
private:
  map<int, int> m_indices;
  vector<int> m_data;
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet obj = new RandomizedSet();
 * bool param_1 = obj.insert(val);
 * bool param_2 = obj.remove(val);
 * int param_3 = obj.getRandom();
 */

int main() {
  RandomizedSet set;
  printf("Insert: %d\n", set.insert(1));
  printf("Insert: %d\n", set.insert(1));
  printf("Insert: %d\n", set.insert(2));
  int one = 0, two = 0;
  for (int i = 0; i < 1000; i++)
  {
    int v = set.getRandom();
    if (v == 1)
      one++;
    else if(v == 2)
      two++;
  }
  printf("one: %d, two: %d\n", one, two);
  printf("Value: %d\n", set.getRandom());
  printf("Remove: %d\n", set.remove(2));
  printf("Remove: %d\n", set.remove(3));
  printf("Value: %d\n", set.getRandom());
  getchar();
  return 0;
}