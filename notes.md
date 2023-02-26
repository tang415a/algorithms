# Classic
## Sorting
* bubble sort
* selection sort
* insertion sort
* merge sort
* heap sort
* quick sort

## Searching
* binary search

## Numbers
* ugly num
* two sums
* odd one / odd two / odd three
* increased
* number of arithmetic slices / sub sequences
* hamming distance
* ones
* remove k digits
* print combination
* print permutation
* largest sum of sub arrays of a (circular) array

## Strings
* first single char
* asterisk
* non-repeated chars
* n chars out of m chars (combination)
* string distance
* reverse words
* longest sub palindrome
* add strings
* words sum equal

## Games
* rotate image
* burst balloons
* elimination game
* friend circles
* broken calculator
* frog jump
* min speed to arrive on time (binary search)
* video stitching

## Data structure
* reverse list
* circular list
* intersect list
* rand colc
* rand colc duplicate
* min stack
* preOrder/inOrder/postOrder iteration over binary tree
* binary tree output by levels

# Shaders
* For ads shading, the following types of vectors are needed in calculation:
  1. n: vertex normal in eye space, normalized vector;
  2. ve: vertex position in eye space;
  3. light position in eye space;
  4. s = light pos in eyespace - ve, normalized vector;
  5. r: the reflection of -s regarding n, normalized vector;
  6. v: the direction of where we are looking at in eye space, i.e. normalize(-ve), normalized vector.
  7. h: the halfway vector between s and v, i.e. normalize(s + v), normalized vector.
* We will be using gl_VertexIndex to generate a fullscreen triangle that acts like a fullscreen quad. Why a triangle? Because it only requires 3 vertex shader invocations (instead of 6 for a quad made up of two triangles). The triangle contains our whole screen and with that the whole uv range of [0..1] so that we can use it like a normal fullscreen quad for applying a post processing effect. Thanks to the GPU clipping everything outside of the screen boundaries we actually get a quad that only requires 3 vertices. And since clipping is for free, we won’t waste bandwitdh as the clipped parts of the triangle (grayed out parts) are not sampled.

# Advanced
## Numbers
* min stranger
* find ones
* fast inv sqrt
* min interval
* max sub array sum min product (monotonic stack)
* count sub arrays with more ones than zeros (Fenwick tree)

## Strings
* shortest palindrome
* string search
* longest palindrome 1

## Games
* max building height
* water trap
* closest pair / convex hull

# Skills
* dynamic programming
* divide and conquer
* decrease and conquer
* transform and conquer
* space and time tradeoffs
* monotonic stack
* Fenwick tree
# References
1. What is `Monotonic Stack`? 
https://algo.monster/problems/mono_stack_intro
2. Problems for mono stack on LeetCode
https://leetcode.com/tag/monotonic-stack/
3. Fast I/O for Competitive Programming
https://www.geeksforgeeks.org/fast-io-for-competitive-programming/
```C++
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
```
4. Vulkan tutorial on rendering a fullscreen quad without buffers
https://www.saschawillems.de/blog/2016/08/13/vulkan-tutorial-on-rendering-a-fullscreen-quad-without-buffers/
5. GLSL Sandbox Gallery
https://glslsandbox.com/
6. OpenGL API Documentation
https://docs.gl/
7. Deferred Rendering Is Here To Save The Day!
https://www.gamedesigning.org/learn/deferred-rendering/