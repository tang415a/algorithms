/*
You are playing a variation of the game Zuma.

In this variation of Zuma, there is a single row of colored balls on a board,
where each ball can be colored red 'R', yellow 'Y', blue 'B', green 'G', or
white 'W'. You also have several colored balls in your hand.

Your goal is to clear all of the balls from the board. On each turn:

Pick any ball from your hand and insert it in between two balls in the row or on
either end of the row. If there is a group of three or more consecutive balls of
the same color, remove the group of balls from the board. If this removal causes
more groups of three or more of the same color to form, then continue removing
each group until there are none left. If there are no more balls on the board,
then you win the game. Repeat this process until you either win or do not have
any more balls in your hand. Given a string board, representing the row of balls
on the board, and a string hand, representing the balls in your hand, return the
minimum number of balls you have to insert to clear all the balls from the
board. If you cannot clear all the balls from the board using the balls in your
hand, return -1.

Example 1:

Input: board = "WRRBBW", hand = "RB"
Output: -1
Explanation: It is impossible to clear all the balls. The best you can do is:
- Insert 'R' so the board becomes WRRRBBW. WRRRBBW -> WBBW.
- Insert 'B' so the board becomes WBBBW. WBBBW -> WW.
There are still balls remaining on the board, and you are out of balls to
insert.

Example 2:

Input: board = "WWRRBBWW", hand = "WRBRW"
Output: 2
Explanation: To make the board empty:
- Insert 'R' so the board becomes WWRRRBBWW. WWRRRBBWW -> WWBBWW.
- Insert 'B' so the board becomes WWBBBWW. WWBBBWW -> WWWW -> empty.
2 balls from your hand were needed to clear the board.

Example 3:

Input: board = "G", hand = "GGGGG"
Output: 2
Explanation: To make the board empty:
- Insert 'G' so the board becomes GG.
- Insert 'G' so the board becomes GGG. GGG -> empty.
2 balls from your hand were needed to clear the board.

Constraints:

1 <= board.length <= 16
1 <= hand.length <= 5
board and hand consist of the characters 'R', 'Y', 'B', 'G', and 'W'.
The initial row of balls on the board will not have any groups of three or more
consecutive balls of the same color.
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Status {
  int a[5] = {0};
  vector<pair<int, int>> v;
  int i = 0;
  int steps = 0;
  Status() {}
  Status(int *a_, vector<pair<int, int>> const &v_, int s) : steps(s) {
    for (int j = 0; j < 5; j++)
      a[j] = a_[j];
    v = v_;
  }
};

int getIdx(char c) {
  switch (c) {
  case 'R':
    return 0;
  case 'Y':
    return 1;
  case 'B':
    return 2;
  case 'G':
    return 3;
  case 'W':
    return 4;
  }
  return -1;
}

int findMinStep__(const string &board, const string &hand) {
  Status st;
  for (int i = 0, n = hand.length(); i < n; i++) {
    st.a[getIdx(hand[i])]++;
  }
  vector<pair<int, int>> v[5];
  int n = board.length(), j = 0;
  for (int i = 1; i < n; i++) {
    if (board[i] != board[j]) {
      v[getIdx(board[j])].push_back(make_pair(j, i - j));
      j = i;
    }
  }
  v[getIdx(board[j])].push_back(make_pair(j, n - j));
  st.v = vector<pair<int, int>>{{0, n}};
  vector<Status> vec = {st};
  int ans = INT_MAX;
  for (int i = 0; i < vec.size(); i++) {
    if (ans < vec[i].steps) {
      continue;
    }
    int &z = vec[i].i;
    while (z < vec[i].v.size() && vec[i].v[z].first >= vec[i].v[z].second)
      z++;
    // the balls are clear
    if (z == vec[i].v.size()) {
      if (ans > vec[i].steps)
        ans = vec[i].steps;
      continue;
    }
    auto &p = vec[i].v[z];
    char c = board[p.first];
    // get the index of char
    int k = getIdx(c);
    // locate the index in v
    int x = 0, y = 0;
    for (; x < v[k].size(); x++) {
      if (v[k][x].first == p.first) {
        y = v[k][x].second;
        break;
      }
    }

    for (x++; x < v[k].size(); x++) {
      int l = v[k][x].first + v[k][x].second;
      if (l > p.second)
        break;
      int b = v[k][x].second + y;
      b = b < 3 ? 3 - b : 0;
      if (vec[i].a[k] >= b) {
        vec[i].a[k] -= b;
        p.first += y;
        int m = p.second;
        p.second = v[k][x].first;
        vec.emplace_back(vec[i].a, vec[i].v, vec[i].steps + b);
        if (l < m) {
          vec.back().v.emplace_back(make_pair(l, m));
        }
        // restore the vec
        p.second = m;
        p.first -= y;
        vec[i].a[k] += b;
      }
    }

    int b = y < 3 ? 3 - y : 0;
    if (vec[i].a[k] >= b) {
      vec[i].a[k] -= b;
      p.first += y;
      vec.emplace_back(vec[i].a, vec[i].v, vec[i].steps + b);
    }
  }
  return ans == INT_MAX ? -1 : ans;
}

string updateBoard(const string &s) {
  string res = "";
  int l = 0, r = 0;
  while (r < s.size()) {
    r++;
    if (s[r] != s[l]) {
      if (r - l < 3) {
        for (int i = l; i < r; i++) {
          res += s[i];
        }
      }
      l = r;
    }
  }
  if (l - r < 3) {
    for (int i = l; i < r; i++) {
      res += s[i];
    }
  }
  if (res.size() < s.size()) {
    return updateBoard(res);
  }
  return res;
}

struct Board {
  string balls;
  int steps = 0;
  int a[5] = {0};
  bool equals(const Board &other) const {
    for (int i = 0; i < 5; i++) {
      if (a[i] != other.a[i])
        return false;
    }
    return true;
  }
  bool covers(const Board &other) const {
    for (int i = 0; i < 5; i++) {
      if (a[i] > other.a[i])
        return false;
    }
    return true;
  }
  bool coversAny(const vector<Board> &bds) const {
    for (const auto &bd : bds) {
      if (covers(bd))
        return true;
    }
    return false;
  }
  bool existsIn(const vector<Board> &bds) const {
    for (const auto &bd : bds) {
      if (equals(bd))
        return true;
    }
    return false;
  }
};

#include <unordered_map>

int findMinStep(const string &board, const string &hand) {
  Board bd;
  bd.balls = board;
  for (int i = 0, n = hand.length(); i < n; i++) {
    bd.a[getIdx(hand[i])]++;
  }
  vector<Board> boards = {bd};
  int ans = INT_MAX;
  unordered_map<string, vector<Board>> cache;
  for (int i = 0; i < boards.size(); i++) {
    auto it = cache.find(boards[i].balls);
    if (it != cache.end() && !boards[i].existsIn(it->second)) {
      continue;
    }
    char prev = boards[i].balls[0];
    for (int j = 1, n = boards[i].balls.length(), c = 1; j <= n; j++) {
      if (boards[i].balls[j] == prev) {
        c++;
      } else {
        int t = c < 3 ? 3 - c : 0;
        if (int k = getIdx(prev); boards[i].a[k] >= t) {
          Board cpy;
          cpy.steps = boards[i].steps + t;
          for (int x = 0; x < 5; x++)
            cpy.a[x] = boards[i].a[x];
          cpy.a[k] -= t;
          if (cpy.steps < ans) {
            cpy.balls = updateBoard(boards[i].balls.substr(0, j - c) +
                                    boards[i].balls.substr(j));
            if (cpy.balls.empty()) {
              if (ans > cpy.steps)
                ans = cpy.steps;
            } else {
              auto it = cache.find(cpy.balls);
              if (it == cache.end() || !cpy.coversAny(it->second)) {
                boards.emplace_back(cpy);
                if (it == cache.end()) {
                  cache.insert(make_pair(cpy.balls, vector<Board>{cpy}));
                } else {
                  int i = 0;
                  for (; i < it->second.size(); i++) {
                    if (it->second[i].covers(cpy)) {
                      it->second[i] = cpy;
                      break;
                    }
                  }
                  if (i == it->second.size())
                    it->second.emplace_back(cpy);
                }
              }
            }
          }
        }
        prev = boards[i].balls[j];
        c = 1;
      }
    }
  }
  return ans == INT_MAX ? -1 : ans;
}

string update(string s) {
  string res = "";
  int l = 0, r = 0;
  while (r < s.size()) {
    r++;
    if (s[r] != s[l]) {
      if (r - l < 3) {
        for (int i = l; i < r; i++) {
          res += s[i];
        }
      }
      l = r;
    }
  }
  if (l - r < 3) {
    for (int i = l; i < r; i++) {
      res += s[i];
    }
  }
  return res;
}

string removeAllBalls(string board) {
  string res = update(board);
  while (res != board) {
    board = res;
    res = update(board);
  }
  return res;
}

void dfs(string &board, string &hand, int &res, int balls,
         unordered_multimap<string, string> &cache) {
  if (cache.find(board) != cache.end() && cache.find(board)->second == hand) {
    return;
  }
  if (board.empty()) {
    res = min(res, balls);
    return;
  }
  if (hand.empty()) {
    return;
  }
  for (int i = 0; i < hand.size(); i++) {
    char ch = hand[i];
    hand.erase(i, 1);
    for (int j = 0; j <= board.size(); j++) {
      board.insert(j, 1, ch);
      string tmp = removeAllBalls(board);
      dfs(tmp, hand, res, balls + 1, cache);
      cache.insert(make_pair(tmp, hand));
      board.erase(j, 1);
    }
    hand.insert(i, 1, ch);
  }
}

int findMinStep2(string board, string hand) {
  board = removeAllBalls(board);
  if (board.empty()) {
    return 0;
  }
  int res = INT_MAX;
  unordered_multimap<string, string> cache;
  dfs(board, hand, res, 0, cache);
  return (res == INT_MAX) ? -1 : res;
}

int main() {
  cout << findMinStep("WRRBBW", "RB") << endl;                     // -1
  cout << findMinStep("WWRRBBWW", "WRBRW") << endl;                // 2
  cout << findMinStep("G", "GGGGG") << endl;                       // 2
  cout << findMinStep("BGRGBR", "WWBGR") << endl;                  // -1
  cout << findMinStep("BGRGBR", "WWBGRR") << endl;                 // -1
  cout << findMinStep("BGRGBR", "WWRBGRR") << endl;                // -1
  cout << findMinStep("BGRGBR", "RWWRBGRR") << endl;               // 6
  cout << findMinStep("BGRGBR", "RRWWRBBBGGGRRR") << endl;         // 6
  cout << findMinStep("BGWRGWBR", "RRWWRBBBGGGRRR") << endl;       // -1
  cout << findMinStep("BGWRGWBR", "RRWWWRBBBGGGRRR") << endl;      // -1
  cout << findMinStep("BGWRGWBR", "RRWWWRBBBGGGWRRR") << endl;     // 10
  cout << findMinStep("BGWRGWBR", "RRWWRBBBGGGGRRR") << endl;      // 10
  cout << findMinStep("BGWRGWBR", "RRWWWRBBBGGGGWRRR") << endl;    // 10
  cout << findMinStep("BGYWRGYWBR", "RRWWWRYBBBGGGGWRRR") << endl; // 14
  cout << findMinStep("RWYWRRWRR", "YRY") << endl;                 // 3
  return 0;
}