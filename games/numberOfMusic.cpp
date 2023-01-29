/*
Your music player contains N different songs and she wants to listen to L (not necessarily different) songs during your trip.  You create a playlist so that:

Every song is played at least once
A song can only be played again only if K other songs have been played
Return the number of possible playlists.  As the answer can be very large, return it modulo 10^9 + 7.

Example 1:

Input: N = 3, L = 3, K = 1
Output: 6
Explanation: There are 6 possible playlists. [1, 2, 3], [1, 3, 2], [2, 1, 3], [2, 3, 1], [3, 1, 2], [3, 2, 1].

Example 2:

Input: N = 2, L = 3, K = 0
Output: 6
Explanation: There are 6 possible playlists. [1, 1, 2], [1, 2, 1], [2, 1, 1], [2, 2, 1], [2, 1, 2], [1, 2, 2]

Example 3:

Input: N = 2, L = 3, K = 1
Output: 2
Explanation: There are 2 possible playlists. [1, 2, 1], [2, 1, 2]

Note:
0 <= K < N <= L <= 100
*/

#include <stdio.h>

const int modulo = 10E9 + 7;
__int64 count(int N, int L, int K, int D)
{
  if (D == L)
    return 1L;
  __int64 options = D < K ? N - D : N - K;
  return options * count(N, L, K, D + 1);
}

int combination(int N, int M)
{
  int all = N, divider = 1;
  for (int i = 1; i < M; i++)
  {
    all *= (N - i);
    divider *= i + 1;
  }
  return all / divider;
}

int possiblePlaylists(int N, int L, int K)
{
  __int64 r = count(N, L, K, 0);
  int sign = -1;
  for (int i = N - 1; i > K; i--)
  {
    r += sign * combination(N, i) * count(i, L, K, 0);
    sign = -sign;
  }
  return r % modulo;
}

#include <memory.h>
int possiblePlaylists2(int N, int L, int K)
{
  __int64 **options = new __int64 *[N];
  for (int i = 0; i < N + 1; i++)
  {
    options[i] = new __int64[L + 1];
    memset(options[i], 0, sizeof(__int64) * L);
  }

  options[0][0] = 1;

  for (int i = 1; i <= N; i++)
  {
    for (int j = 1; j <= L; j++)
    {
      options[i][j] += options[i - 1][j - 1] * (N - i + 1);
      int availables = i - K;
      if (availables > 0)
        options[i][j] += options[i][j - 1] * availables;
    }
  }

  int res = options[N][L] % modulo;
  for (int i = 0; i < N + 1; i++)
    delete[] options[i];
  delete[] options;
  return res;
}

bool expect(int value, int expected, char *desc)
{
  if (value == expected)
  {
    printf("%s succeeded.\n", desc);
    return true;
  }
  printf("%s failed.\n", desc);
  printf("Actual: %d. Expected: %d.\n", value, expected);
  return false;
}

int main()
{
  const bool runTest = false;
  if (runTest)
  {
    expect(possiblePlaylists(3, 3, 1), 6, "(3,3,1)");
    expect(possiblePlaylists(2, 3, 0), 6, "(2,3,0)");
    expect(possiblePlaylists(2, 3, 1), 2, "(2,3,1)");

    expect(possiblePlaylists(2, 2, 0), 2, "(2,2,0)");
    expect(possiblePlaylists(4, 4, 2), 24, "(4,4,2)");
    expect(possiblePlaylists(3, 4, 2), 6, "(3,4,2)");

    expect(possiblePlaylists(3, 4, 1), 18, "(3,4,1)");
  }
  printf("%d\n", possiblePlaylists2(10, 20, 5));

  return 0;
}