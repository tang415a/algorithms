/*
Equations are given in the format A / B = k, where A and B are variables
represented as strings, and k is a real number (floating point number). Given
some queries, return the answers. If the answer does not exist, return -1.0.

Example:
Given a / b = 2.0, b / c = 3.0.
queries are: a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ? .
return [6.0, 0.5, -1.0, 1.0, -1.0].

The input is: vector<pair<string, string>> equations, vector<double>& values,
vector<pair<string, string>> queries, where equations.size() == values.size(),
and the values are positive. This represents the equations. Return
vector<double>.

According to the example above:

equations = [ ["a", "b"], ["b", "c"] ],
values = [2.0, 3.0],
queries = [ ["a", "c"], ["b", "a"], ["a", "e"], ["a", "a"], ["x", "x"] ].

The input is always valid. You may assume that evaluating the queries will
result in no division by zero and there is no contradiction.
*/

#include <unordered_map>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

void addPair(const string &from, const string &to, double v,
             unordered_map<string, unordered_map<string, double>> &edges) {
  auto iter = edges.find(from);
  if (iter == edges.end()) {
    unordered_map<string, double> m;
    m.insert(make_pair(to, v));
    edges.insert(make_pair(from, m));
  } else {
    iter->second[to] = v;
  }
  iter = edges.find(to);
  if (iter == edges.end()) {
    unordered_map<string, double> m;
    m.insert(make_pair(from, 1 / v));
    edges.insert(make_pair(to, m));
  } else {
    iter->second[from] = 1 / v;
  }
}

double findPath(const string &from, const string &to, unordered_map<string, bool> &flags,
                const unordered_map<string, unordered_map<string, double>> &edges) {
  auto &iter = edges.find(from);
  if (iter == edges.end())
    return -1.0;
  if (from == to)
    return 1.0;
  flags[from] = true;
  for (auto &it : iter->second) {
    if (flags[it.first])
      continue;
    double res = findPath(it.first, to, flags, edges);
    if (res > 0)
      return it.second * res;
  }
  return -1.0;
}

vector<double> calcEquation(vector<vector<string>> &equations,
                            vector<double> &values,
                            vector<vector<string>> &queries) {
  unordered_map<string, unordered_map<string, double>> edges;
  int siz = equations.size();
  for (int i = 0; i < siz; i++) {
    addPair(equations[i][0], equations[i][1], values[i], edges);
  }

  siz = queries.size();
  vector<double> res;
  for (int i = 0; i < siz; i++) {
    unordered_map<string, bool> flags;
    res.push_back(findPath(queries[i][0], queries[i][1], flags, edges));
  }
  return res;
}

int main() {
  vector<vector<string>> equations = {{"a", "b"}, {"b", "c"}};
  vector<double> values = {2.0, 3.0};
  vector<vector<string>> queries = {
      {"a", "c"}, {"b", "a"}, {"a", "e"}, {"a", "a"}, {"x", "x"}};
  auto res = calcEquation(equations, values, queries);
  for (auto &v : res)
    printf("%3f ", v);
  return 0;
}