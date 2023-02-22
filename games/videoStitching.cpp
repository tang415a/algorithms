/*
You are given a series of video clips from a sporting event that lasted T
seconds. These video clips can be overlapping with each other and have varied
lengths.

Each video clip clips[i] is an interval: it starts at time clips[i][0] and ends
at time clips[i][1]. We can cut these clips into segments freely: for example,
a clip [0, 7] can be cut into segments [0, 1] + [1, 3] + [3, 7].

Return the minimum number of clips needed so that we can cut the clips into
segments that cover the entire sporting event ([0, T]). If the task is
impossible, return -1.

Example 1:
Input: clips = [[0,2],[4,6],[8,10],[1,9],[1,5],[5,9]], T = 10
Output: 3
Explanation:
We take the clips [0,2], [8,10], [1,9]; a total of 3 clips.
Then, we can reconstruct the sporting event as follows:
We cut [1,9] into segments [1,2] + [2,8] + [8,9].
Now we have segments [0,2] + [2,8] + [8,10] which cover the sporting event [0,
10].

Example 2:
Input: clips = [[0,1],[1,2]], T = 5
Output: -1
Explanation:
We can't cover [0,5] with only [0,1] and [0,2].

Example 3:
Input: clips =
[[0,1],[6,8],[0,2],[5,6],[0,4],[0,3],[6,7],[1,3],[4,7],[1,4],[2,5],[2,6],[3,4],[4,5],[5,7],[6,9]],
T = 9

Output: 3
Explanation: We can take clips [0,4], [4,7], and [6,9].

Example 4:
Input: clips = [[0,4],[2,8]], T = 5
Output: 2
Explanation:
Notice you can have extra video after the event ends.

Note:

1 <= clips.length <= 100
0 <= clips[i][0], clips[i][1] <= 100
0 <= T <= 100
*/

#include <algorithm>
#include <stdio.h>
#include <vector>
using namespace std;

int videoStitching(vector<vector<int>> &clips, int T) {
  sort(clips.begin(), clips.end(), [](vector<int> &x, vector<int> &y) {
    return x[0] < y[0] || (x[0] == y[0] && x[1] < y[1]);
  });

  vector<int> dp(T, -1);
  for (auto c : clips) {
    if (c[0] < 0)
      continue;
    if (c[0] == 0) {
      for (auto i = 0; i < c[1]; i++)
        dp[i] = 1;
      continue;
    }
    if (c[0] > T)
      break;
    if (dp[c[0] - 1] == -1)
      return -1;
    for (auto i = c[0]; i < c[1]; i++) {
      int m = dp[c[0] - 1] + 1;
      if (dp[i] == -1 || m < dp[i])
        dp[i] = m;
    }
  }
  return dp[T - 1];
}

int main() {
  vector<vector<int>> clips = {{0, 1}, {6, 8}, {0, 2}, {5, 6}, {0, 4}, {0, 3},
                               {6, 7}, {1, 3}, {4, 7}, {1, 4}, {2, 5}, {2, 6},
                               {3, 4}, {4, 5}, {5, 7}, {6, 9}};
  const int T = 9;
  printf("%d", videoStitching(clips, T));
  return 0;
}