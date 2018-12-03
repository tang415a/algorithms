// Write a Dijkstra algorithm to find out the shortest path between two nodes in a graph.

#include <stdio.h>
#include <vector>
using namespace std;

struct Node;

struct Edge
{
  Node *to;
  float dist;
};

struct Node
{
  char label;
  vector<Edge> edges;  
};

struct Path
{
  Edge* e;
  int pathIdx;
  float dist;
};

int minDist(const vector<Path>& paths)
{
  if (paths.empty())
      return -1;
  int min = 0;
  for (int i = 1; i < paths.size(); i++)
    if (paths[i].dist < paths[min].dist)
      min = i;
  return min;
}

int find(const vector<Path>& paths, Node* n)
{
  for (int i = 0; i < paths.size(); i++)
  {
    if (paths[i].e->to == n)
      return i;
  }
  return -1;
}

void print(Path const& p, const vector<Path>& finals)
{
  if (p.pathIdx >= 0)
    print(finals[p.pathIdx], finals);
  printf("%c - %f\n", p.e->to->label, p.e->dist);
}

float shortestDijkstra(Node* src, Node* dest)
{
  if (src == NULL || dest == NULL)
    return -1;
  Edge start = {src, 0};
  vector<Path> paths = {{&start, -1, 0}}, finals;
  while (!paths.empty())
  {
    int min = minDist(paths);
    finals.push_back(paths[min]);
    int idx = finals.size() - 1;
    auto& p = finals[idx];
    paths.erase(paths.begin() + min);
    
    auto& node = p.e->to;
    if (node == dest)
    {
      print(p, finals);
      return p.dist;
    }    

    for (auto& e: node->edges)
    {
      float d = e.dist + p.dist;
      if (find(finals, e.to) >= 0)
        continue;
      int tmp = find(paths, e.to);
      if (tmp >= 0 && d < paths[tmp].dist)
        paths[tmp] = {&e, idx, d};
      else if (tmp < 0)
        paths.push_back({&e, idx, d});
    }    
  }
  return -1;
}

void construct(Node& from, Node& to, float d, bool bidirectional = true)
{
  from.edges.push_back({&to, d});
  if (bidirectional)
    to.edges.push_back({&from, d});
}

int main()
{
  const int node_size = 6;
  Node nodes[node_size];
  for(int i = 0; i < node_size; i++)
    nodes[i].label = 'a' + i;
  construct(nodes[0], nodes[1], 3);
  construct(nodes[0], nodes[3], 7);
  construct(nodes[1], nodes[2], 4);
  construct(nodes[1], nodes[3], 2);
  construct(nodes[2], nodes[3], 5);
  construct(nodes[2], nodes[4], 6);
  construct(nodes[3], nodes[4], 4);
  
  float d = shortestDijkstra(nodes, nodes + 4);
  if (d < 0)
    printf("impossible to reach");
  else
    printf("altogether the distance is %f", d);
  getchar();
  return 0;
}