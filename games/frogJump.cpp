/*
A frog is crossing a river. The river is divided into x units and at each unit there may or may not exist a stone. The frog can jump on a stone, but it must not jump into the water.

Given a list of stones' positions (in units) in sorted ascending order, determine if the frog is able to cross the river by landing on the last stone. Initially, the frog is on the first stone and assume the first jump must be 1 unit.

If the frog's last jump was k units, then its next jump must be either k - 1, k, or k + 1 units. Note that the frog can only jump in the forward direction.

Note:

The number of stones is ≥ 2 and is < 1,100.
Each stone's position will be a non-negative integer < 231.
The first stone's position is always 0.

Example 1:

[0,1,3,5,6,8,12,17]

There are a total of 8 stones.
The first stone at the 0th unit, second stone at the 1st unit,
third stone at the 3rd unit, and so on...
The last stone at the 17th unit.

Return true. The frog can jump to the last stone by jumping 
1 unit to the 2nd stone, then 2 units to the 3rd stone, then 
2 units to the 4th stone, then 3 units to the 6th stone, 
4 units to the 7th stone, and 5 units to the 8th stone.

Example 2:

[0,1,2,3,4,8,9,11]

Return false. There is no way to jump to the last stone as 
the gap between the 5th and 6th stone is too large.
*/

#include <stdio.h>
#include <vector>
using namespace std;

struct Status
{
  int pos;
  int units;
  Status* from;
};

bool existsInRec(int pos, const vector<Status>& records)
{
  for (auto& r: records){
    if (r.pos == pos)
      return true;
  }
  return false;
}

bool existsInRiver(int pos, const vector<int>& stones)
{
  for (auto& p: stones)
  {
    if (p == pos)
      return true;
  }
  return false;
}

void printSuccess(const Status& stat)
{
  if (stat.from)
  {
    printSuccess(*stat.from);
    printf("from %d jumps %d units to %d\n", stat.from->pos, stat.units, stat.pos);
  }
}

void printFail(const vector<Status>& records, const vector<int>& stones)
{
  for(auto& s: stones)
  {
    if(!existsInRec(s, records)) 
    {
      printf("No way. The stone at %d cannot reach.", s);
      return;
    }
  }
}

bool jump(vector<int> stones) 
{
  if (stones.size() == 0 || stones[0] != 0)
    return false;
  vector<Status> records;
  records.push_back({0, 0, NULL});
  int i = 0;
  int steps[] = {-1, 0, 1};
  const int& target = stones[stones.size() - 1];
  while(i < records.size())
  {
    auto& r = records[i];
    for (auto& s: steps)
    {
      int units = r.units + s;
      if (units > 0)
      {
        int p = units + r.pos;
        if (existsInRiver(p, stones) && !existsInRec(p, records))
        {
          records.push_back({p, units, &r});
          if (target == p)
          {
            printSuccess(records[records.size() - 1]);
            return true;
          }
        }
      }
    }
    i++;
  }
  printFail(records, stones);
  return false;
}

int main()
{
  jump({0,1,2,3,4,8,9,11});
  getchar();
  return 0;
}