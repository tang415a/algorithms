/*
Given N axis-aligned rectangles where N > 0, determine if they all together form an exact cover of a rectangular region.

Each rectangle is represented as a bottom-left point and a top-right point. For example, a unit square is represented as [1,1,2,2]. (coordinate of bottom-left point is (1, 1) and top-right point is (2, 2)).

Example 1:

rectangles = [
  [1,1,3,3],
  [3,1,4,2],
  [3,2,4,4],
  [1,3,2,4],
  [2,3,3,4]
]

Return true. All 5 rectangles together form an exact cover of a rectangular region.

Example 2:

rectangles = [
  [1,1,2,3],
  [1,3,2,4],
  [3,1,4,2],
  [3,2,4,4]
]

Return false. Because there is a gap between the two rectangular regions.

Example 3:

rectangles = [
  [1,1,3,3],
  [3,1,4,2],
  [1,3,2,4],
  [3,2,4,4]
]

Return false. Because there is a gap in the top center.

Example 4:

rectangles = [
  [1,1,3,3],
  [3,1,4,2],
  [1,3,2,4],
  [2,2,4,4]
]

Return false. Because two of the rectangles overlap with each other.
*/

#include <stdio.h>
#include <vector>
#include <map>
#include <string>
using namespace std;

bool isRectangleCover(vector<vector<int>>& rectangles) {
  if (rectangles.empty())
    return false;
  int N = rectangles[0].size() / 2;
  map<string, int> hash;
  vector<vector<int>> all;
  for(auto& r: rectangles)
  {
    vector<vector<int>> minmax;
    for(int i = 0; i < N; i++)
    {
      vector<int> c;
      c.push_back(r[i]);
      c.push_back(r[i+N]);
      minmax.push_back(c);
    }

    for(int i = 0; i < (1<<N); i++)
    {
      vector<int> coords;      
      for(int j = 0; j < N; j++)
        coords.push_back(minmax[j][(i&(1<<j))?1:0]);
      string key = "";
      for(auto& c: coords)
        key += (to_string(c) + ",");
      if((hash[key] & (1<<i)))
        return false;
      hash[key] |= (1<<i);
      all.push_back(coords);
    }
  }
  int cnt = 0;
  for(auto& h: hash)
  {
    int v = h.second;
    if(!(v&v-1) && ++cnt > (1<<N)) return false;
    else if(v&v-1) 
    {
      vector<vector<int>> pts;
      int i = 0;
      for(; i < (1<<N); i++)
      {
        if(v & (1 << i))
          pts.push_back(all[i]);
      }

      int siz = pts.size();
      if (siz == (1 << N))
        continue;
      int same = 0;
      for(i = 0; i < N; i++)
      {
        int j = 1;
        for(; j < siz; j++)
          if(pts[0][i] != pts[j][i])
            break;
        if (j == siz)
          same++;
      }
      if(same == 0)
        return false;
    }
  }
  return true;
}

int main() {
  vector<vector<int>> rectangles = {
    {1,1,3,3},
    {3,1,4,2},
    {1,3,2,4},
    {2,2,4,4}
  };
/*
  rectangles = {
    {1,1,3,3},
    {3,1,4,2},
    {3,2,4,4},
    {1,3,2,4},
    {2,3,3,4}
  };*/

  rectangles = {
    {1,1,1,2,3,2},
    {1,1,2,6,6,6},
    {1,3,1,6,6,2},
    {2,1,1,6,3,2}
  };

  printf("%d", isRectangleCover(rectangles));
  getchar();
  return 0;
}