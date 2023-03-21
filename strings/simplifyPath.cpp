/*
Given a string path, which is an absolute path (starting with a slash '/') to a
file or directory in a Unix-style file system, convert it to the simplified
canonical path.

In a Unix-style file system, a period '.' refers to the current directory, a
double period '..' refers to the directory up a level, and any multiple
consecutive slashes (i.e. '//') are treated as a single slash '/'. For this
problem, any other format of periods such as '...' are treated as file/directory
names.

The canonical path should have the following format:

The path starts with a single slash '/'.
Any two directories are separated by a single slash '/'.
The path does not end with a trailing '/'.
The path only contains the directories on the path from the root directory to
the target file or directory (i.e., no period '.' or double period '..').

Return the simplified canonical path.

Example 1:

Input: path = "/home/"
Output: "/home"
Explanation: Note that there is no trailing slash after the last directory name.

Example 2:

Input: path = "/../"
Output: "/"
Explanation: Going one level up from the root directory is a no-op, as the root
level is the highest level you can go.

Example 3:

Input: path = "/home//foo/"
Output: "/home/foo"
Explanation: In the canonical path, multiple consecutive slashes are replaced by
a single one.

Constraints:

1 <= path.length <= 3000
path consists of English letters, digits, period '.', slash '/' or '_'.
path is a valid absolute Unix path.
*/

#include <iostream>
#include <stack>
#include <string>

using namespace std;

string simplifyPath(string path) {
  const int n = path.length();
  string ans(n, 0);
  int j = 0;
  stack<int> st;
  for (int i = 0; i < n; i++) {
    // "./" and "../" must follow '/' otherwise '.' is part of file/directory
    // name
    if (path[i] == '.' && j > 0 && ans[j - 1] == '/') {
      // if it is followed with '/' or it is the last char - means the cur dir
      if (i == n - 1 || (i < n - 1 && path[i + 1] == '/')) {
        i++;
        continue;
      }
      // if it is followed with './' or it is followed with '.' at the end of
      // string - means the parent dir
      if (path[i + 1] == '.' &&
          ((i < n - 2 && path[i + 2] == '/') || i == n - 2)) {
        i += 2;
        if (st.size() > 1) {
          st.pop();
        }
        j = st.top() + 1;
        continue;
      }
    } else if (path[i] == '/') {
      if (j > 0 && ans[j - 1] == '/') {
        continue;
      }
      st.push(j);
    }
    ans[j++] = path[i];
  }
  ans.resize(j);
  if (ans.length() > 1 && ans.back() == '/')
    ans.pop_back();
  return ans;
}

string simplifyPath2(string path) {
  stack<string> st;
  string res;

  for (int i = 0; i < path.size(); ++i) {
    if (path[i] == '/')
      continue;
    string temp;
    // iterate till we doesn't traverse the whole string and doesn't encounter
    // the last /
    while (i < path.size() && path[i] != '/') {
      // add path to temp string
      temp += path[i];
      ++i;
    }
    if (temp == ".")
      continue;
    // pop the top element from stack if exists
    else if (temp == "..") {
      if (!st.empty())
        st.pop();
    } else
      // push the directory file name to stack
      st.push(temp);
  }

  // adding all the stack elements to res
  while (!st.empty()) {
    res = "/" + st.top() + res;
    st.pop();
  }

  // if no directory or file is present
  if (res.size() == 0)
    return "/";

  return res;
}

int main() {
  cout << simplifyPath("/home/") << endl;               // /home
  cout << simplifyPath("/../") << endl;                 // /
  cout << simplifyPath("/home//foo/") << endl;          // /home/foo
  cout << simplifyPath("/home//.../") << endl;          // /home/...
  cout << simplifyPath("/home/../") << endl;            // /
  cout << simplifyPath("/home/..foo/") << endl;         // /home/..foo
  cout << simplifyPath("/a/./b/../../c/") << endl;      // /c
  cout << simplifyPath("/a/../../") << endl;            // /
  cout << simplifyPath("/a/../../b/../c//.//") << endl; // /c
  cout << simplifyPath("/a/..") << endl;                // /
  cout << simplifyPath("/hello../world") << endl;       // /hello../world
  cout << simplifyPath("/hello./world") << endl;        // /hello./world
  cout << simplifyPath("/hello./.") << endl;            // /hello.
  return 0;
}