/*
Given a list accounts, each element accounts[i] is a list of strings, where the first element accounts[i][0] is a name, and the rest of the elements are emails representing emails of the account.

Now, we would like to merge these accounts. Two accounts definitely belong to the same person if there is some email that is common to both accounts. Note that even if two accounts have the same name, they may belong to different people as people could have the same name. A person can have any number of accounts initially, but all of their accounts definitely have the same name.

After merging the accounts, return the accounts in the following format: the first element of each account is the name, and the rest of the elements are emails in sorted order. The accounts themselves can be returned in any order.

Example 1:
Input: 
accounts = [["John", "johnsmith@mail.com", "john00@mail.com"], ["John", "johnnybravo@mail.com"], ["John", "johnsmith@mail.com", "john_newyork@mail.com"], ["Mary", "mary@mail.com"]]
Output: [["John", 'john00@mail.com', 'john_newyork@mail.com', 'johnsmith@mail.com'],  ["John", "johnnybravo@mail.com"], ["Mary", "mary@mail.com"]]
Explanation: 
The first and third John's are the same person as they have the common email "johnsmith@mail.com".
The second John and Mary are different people as none of their email addresses are used by other accounts.
We could return these lists in any order, for example the answer [['Mary', 'mary@mail.com'], ['John', 'johnnybravo@mail.com'], 
['John', 'john00@mail.com', 'john_newyork@mail.com', 'johnsmith@mail.com']] would still be accepted.

Note:

The length of accounts will be in the range [1, 1000].
The length of accounts[i] will be in the range [1, 10].
The length of accounts[i][j] will be in the range [1, 30].
*/

#include <stdio.h>
#include <vector>
#include <string>
#include <map>
#include <set>
using namespace std;

void doAccountsMerge(vector<vector<string>>& res, vector<vector<string>>& accounts, set<set<int>*>& s, int64_t* rec) {
  map<string, bool> m;
  for (auto& p: s) {
    if (p == NULL || p->empty())
      continue;
    vector<string> item;
    item.push_back(accounts[*p->begin()][0]); // push the name
    for (auto& v: *p) {
      int siz = accounts[v].size();
      for (int i = 1; i < siz; i++) { // merge them
        if (m[accounts[v][i]])  // the mail address has been added, skip it
          continue;
        item.push_back(accounts[v][i]);
        m[accounts[v][i]] = true;
      }
    }
    res.push_back(item);
  }
  int siz = accounts.size();
  for (int i = 0; i < siz; i++) {
    if (rec[i] == NULL) { // not processed yet, should be standalone set
      res.push_back(accounts[i]); 
    }
  }
}

vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
  int siz = accounts.size();
  // 1. gather the raw indices set with same email address
  // e.g. "johnsmith@mail.com" => [1, 2], "john@mail.com" => [0, 1]
  map<string, vector<int>> m;
  for(int j = 0; j < siz; j++) {
    auto& a = accounts[j];
    int siz = a.size();
    for(int i = 1; i < siz; i++) {
      if(m.find(a[i]) != m.end())
        m[a[i]].push_back(j);
      else
        m[a[i]] = {j};
    }
  }
  // 2. 'cook' (merge) the raw indices set from step 1
  // e.g. [1, 2], [0, 1] => [0, 1, 2]
  set<set<int>*> s;
  int64_t *rec = new int64_t[siz];
  memset(rec, 0, siz * sizeof(int64_t));
  for(auto& v: m) {
    auto& indices = v.second;
    if (indices.size() <= 1)
      continue;
    set<int>* available = NULL;
    for(auto& i: indices) {
      if (rec[i] != NULL) {
        if (available == NULL)
          available = (set<int>*)rec[i];
        else {
          set<int>* p = (set<int>*) rec[i];
          for(auto& j: *p)
            available->insert(j);
          auto iter = s.find(p);
          if(iter != s.end())
            s.erase(iter);
          delete p;
        }        
      }
    }
    if (available == NULL) {
      available = new set<int>();
      s.insert(available);
    }      
    for(auto& i: indices) {
      available->insert(i);
      rec[i] = (int64_t)available;
    }
  }

  // 3. merge the accounts (get the result)
  vector<vector<string>> res;
  doAccountsMerge(res, accounts, s, rec);

  // free the memory
  for (auto& p: s) {
    if (p)
      delete p;
  }
  delete[] rec;
  return res;
}

int main() {
  vector<vector<string>> accounts = 
  {{"John", "johnsmith@mail.com", "john00@mail.com"},
   {"John", "johnnybravo@mail.com"},
   {"Tony", "tony1@mail.com", "tony4@mail.com"},
   {"Martin", "mj@mail.com", "blue_horse@mail.com"},
   {"Mary", "mary@mail.com"},
   {"Gary", "yellow_duck@mail.com", "gr@mail.com"},
   {"Tony", "tony1@mail.com", "tony2@mail.com"},
   {"Martin", "m_bird@mail.com", "mjk@mail.com"},
   {"John", "johnsmith@mail.com", "john_newyork@mail.com"},
   {"Gary", "red_sheep@mail.com", "hello_world@mail.com"},
   {"Tony", "tony4@mail.com", "tony5@mail.com"},
   {"Martin", "mj@mail.com"},
   {"Gary", "gr@mail.com", "red_sheep@mail.com"},
   {"Tony", "tony3@mail.com", "tony4@mail.com"}};
  auto r = accountsMerge(accounts);
  for (auto& v: r) {
    for (auto&s: v)
      printf("%s ", s.c_str());
    printf("\n");
  }
  getchar();
  return 0;
}