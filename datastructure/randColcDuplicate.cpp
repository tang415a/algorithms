/*
Design a data structure that supports all following operations in average O(1) time.

Note: Duplicate elements are allowed.
insert(val): Inserts an item val to the collection.
remove(val): Removes an item val from the collection if present.
getRandom: Returns a random element from current collection of elements. The probability of each element being returned is linearly related to the number of same value the collection contains.
Example:

// Init an empty collection.
RandomizedCollection collection = new RandomizedCollection();

// Inserts 1 to the collection. Returns true as the collection did not contain 1.
collection.insert(1);

// Inserts another 1 to the collection. Returns false as the collection contained 1. Collection now contains [1,1].
collection.insert(1);

// Inserts 2 to the collection, returns true. Collection now contains [1,1,2].
collection.insert(2);

// getRandom should return 1 with the probability 2/3, and returns 2 with the probability 1/3.
collection.getRandom();

// Removes 1 from the collection, returns true. Collection now contains [1,2].
collection.remove(1);

// getRandom should return 1 and 2 both equally likely.
collection.getRandom();
*/

#include <stdio.h>
#include <time.h>
#include <map>
#include <vector>
using namespace std;

class RandomizedCollection {
public:
  /** Initialize your data structure here. */
  RandomizedCollection() {
    srand(time(NULL));
  }
  
  /** Inserts a value to the collection. Returns true if the collection did not already contain the specified element. */
  bool insert(int val) {
    m_data.push_back(val);
    bool existed = m_indices.find(val) == m_indices.end();
    m_indices[val].push_back(m_data.size() - 1);
    return existed;
  }
  
  /** Removes a value from the collection. Returns true if the collection contained the specified element. */
  bool remove(int val) {
    if (m_indices[val].empty())
      return false;
    int idx = m_indices[val][m_indices[val].size() - 1];
    if (idx < m_data.size() - 1) {
      int last = m_data[m_data.size() - 1];
      m_data[idx] = last;
      m_indices[last][m_indices[last].size() - 1] = idx;
    }    
    m_data.erase(m_data.end() - 1);
    m_indices[val].erase(m_indices[val].end() - 1);
    return true;
  }
  
  /** Get a random element from the collection. */
  int getRandom() {
    int idx = rand() % m_data.size();
    return m_data[idx];
  }
private:
  vector<int> m_data;
  map<int, vector<int>> m_indices;
};

/**
 * Your RandomizedCollection object will be instantiated and called as such:
 * RandomizedCollection obj = new RandomizedCollection();
 * bool param_1 = obj.insert(val);
 * bool param_2 = obj.remove(val);
 * int param_3 = obj.getRandom();
 */

int main()
{
  RandomizedCollection colc;
  printf("Insert: %d\n", colc.insert(1));
  printf("Insert: %d\n", colc.insert(1));
  printf("Insert: %d\n", colc.insert(2));
  int one = 0, two = 0;
  for (int i = 0; i < 1000; i++)
  {
    int v = colc.getRandom();
    if (v == 1)
      one++;
    else if(v == 2)
      two++;
  }
  printf("one: %d, two: %d\n", one, two);
  printf("Value: %d\n", colc.getRandom());
  printf("Remove: %d\n", colc.remove(2));
  printf("Remove: %d\n", colc.remove(3));
  printf("Value: %d\n", colc.getRandom());
  getchar();
  return 0;
}