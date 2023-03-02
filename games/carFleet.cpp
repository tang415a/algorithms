/*
There are n cars going to the same destination along a one-lane road. The
destination is target miles away.

You are given two integer array position and speed, both of length n, where
position[i] is the position of the ith car and speed[i] is the speed of the ith
car (in miles per hour).

A car can never pass another car ahead of it, but it can catch up to it and
drive bumper to bumper at the same speed. The faster car will slow down to match
the slower car's speed. The distance between these two cars is ignored (i.e.,
they are assumed to have the same position).

A car fleet is some non-empty set of cars driving at the same position and same
speed. Note that a single car is also a car fleet.

If a car catches up to a car fleet right at the destination point, it will still
be considered as one car fleet.

Return the number of car fleets that will arrive at the destination.

Example 1:

Input: target = 12, position = [10,8,0,5,3], speed = [2,4,1,1,3]
Output: 3
Explanation:
The cars starting at 10 (speed 2) and 8 (speed 4) become a fleet, meeting each
other at 12. The car starting at 0 does not catch up to any other car, so it is
a fleet by itself. The cars starting at 5 (speed 1) and 3 (speed 3) become a
fleet, meeting each other at 6. The fleet moves at speed 1 until it reaches
target. Note that no other cars meet these fleets before the destination, so the
answer is 3.

Example 2:

Input: target = 10, position = [3], speed = [3]
Output: 1
Explanation: There is only one car, hence there is only one fleet.
Example 3:

Input: target = 100, position = [0,2,4], speed = [4,2,1]
Output: 1
Explanation:
The cars starting at 0 (speed 4) and 2 (speed 2) become a fleet, meeting each
other at 4. The fleet moves at speed 2. Then, the fleet (speed 2) and the car
starting at 4 (speed 1) become one fleet, meeting each other at 6. The fleet
moves at speed 1 until it reaches target.


Constraints:

n == position.length == speed.length
1 <= n <= 10^5
0 < target <= 10^6
0 <= position[i] < target
All the values of position are unique.
0 < speed[i] <= 10^6
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int carFleet(int target, const vector<int> &position,
             const vector<int> &speed) {
  const int n = position.size();
  // it is better to use pair<int, int> instead of vector<int>
  vector<pair<int, int>> cars(n);
  for (int i = 0; i < n; i++) {
    cars[i] = {target - position[i], speed[i]};
  }
  sort(cars.begin(), cars.end());
  int ans = n;
  float t = (float)(cars[0].first) / cars[0].second;
  for (int i = 1; i < n; i++) {
    float ti = (float)(cars[i].first) / cars[i].second;
    if (ti <= t) {
      ans--;
    } else {
      t = ti;
    }
  }
  return ans;
}

int carFleet2(int target, const vector<int> &position,
              const vector<int> &speed) {
  if (position.empty())
    return 0;
  if (position.size() == 1)
    return 1;

  const size_t cars_count = position.size();
  vector<pair<int, int>> cars(cars_count);

  for (size_t i = 0; i < cars_count; ++i) {
    cars[i].first = position[i];
    cars[i].second = speed[i];
  }

  sort(cars.begin(), cars.end());

  int fleet_num = 1;

  float fleet_time = float(target - cars[cars_count - 1].first) /
                     float(cars[cars_count - 1].second);

  for (int i = cars_count - 2; i >= 0; i--) {
    const auto [p, s] = cars[i];
    const float time = float(target - p) / float(s);

    // slower than fleet
    if (time > fleet_time) {
      fleet_time = time;
      ++fleet_num;
    }
  }

  return fleet_num;
}

int main() {
  cout << carFleet(12, {10, 8, 0, 5, 3}, {2, 4, 1, 1, 3}) << endl;
  cout << carFleet(10, {3}, {3}) << endl;
  cout << carFleet(100, {0, 2, 4}, {4, 2, 1}) << endl;
  return 0;
}