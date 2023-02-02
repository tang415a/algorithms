// Implement a sub-string search algorithm using Boyer Moore algorithm.
// e.g. given a string "aabbccdd" and search for "bcc", then the output is:
// "found at 3".

#include <iostream>
#include <string>
using namespace std;

int badShift(char c, const string &pattern, int (&badShiftTable)[256]) {
  if (badShiftTable[c] > 0)
    return badShiftTable[c];
  int n = pattern.length();
  for (int i = 1; i < n; ++i) {
    if (pattern[n - 1 - i] == c) // c also appears at length - 1 - i in pattern;
                                 // it is safe to move right i characters
    {
      badShiftTable[c] = i;
      return i;
    }
  }
  return n;
}

// do i characters of suffix also appear at the head of pattern?
bool foundAtHead(int i, const string &p) {
  for (int j = 0, n = p.length(); j < i; j++) {
    if (p[j] != p[n - i + j])
      return false;
  }
  return true;
}

int goodShift(int i, const string &p, int *goodShiftTable) {
  if (i <= 0)
    return 1;
  if (goodShiftTable[i] > 0)
    return goodShiftTable[i];
  int lp = p.length(), offset = 1;
  for (; offset < lp - i;
       offset++) // this iteration does not include the head since the offset
                 // never goes to lp - i (p[lp - i - offset] is the leftmost
                 // character we are trying to match)
  {
    // this considers the bad shift too; if the character before the Ci
    // (lp - i - 1, i + 1 character from right) repeats, ignore it, because it
    // fails to match (only i characters have been matched, i + 1 character from
    // right fails)
    if (p[lp - i - 1] == p[lp - i - 1 - offset])
      continue;
    int j = 0;
    for (; j < i; j++) {
      if (p[lp - i + j] !=
          p[lp - i - offset + j]) // the j characters of Ci match so far
        break;
    }
    if (j >= i) // found all the matched i characters (Ci)
      break;
  }
  // found the matched i characters (Ci) elsewhere in pattern
  if (offset < lp - i) {
    goodShiftTable[i] = offset;
    return offset;
  }
  // does Ci or suffix of Ci appear at the head?
  for (int j = i; j > 0; j--) {
    if (foundAtHead(j, p)) // j characters from Ci (the suffix of Ci) are found
                           // at the head of pattern
    {
      goodShiftTable[i] = lp - j;
      return lp - j;
    }
  }
  goodShiftTable[i] = lp;
  return lp;
}

int search(const std::string &s, const std::string &p,
           int (&badShiftTable)[256]) {
  int ls = s.length(), lp = p.length(), offset = lp - 1;
  int *goodShiftTable = new int[lp];
  memset(goodShiftTable, 0, sizeof(int) * lp);
  if (offset < ls) {
    for (int i = 0; i < lp; i++) {
      if (s[offset - i] != p[lp - 1 - i]) {
        offset += max(badShift(s[offset], p, badShiftTable),
                      goodShift(i, p, goodShiftTable));
        if (offset >= ls) {
          delete[] goodShiftTable;
          return -1;
        }
        i = -1;
      }
    }
    delete[] goodShiftTable;
    return offset - lp + 1;
  }
  delete[] goodShiftTable;
  return -1;
}

int main() {
  {
    int badShiftTable[256];
    memset(badShiftTable, 0, sizeof(int) * 256);
    int r = search("aabbccdd", "bcc", badShiftTable);
    if (r >= 0)
      cout << "found at " << r << endl;
    else
      cout << "not found" << endl;
  }
  {
    int badShiftTable[256];
    memset(badShiftTable, 0, sizeof(int) * 256);
    int r = search("abcdefegioioas", "gio", badShiftTable);
    if (r >= 0)
      cout << "found at " << r << endl;
    else
      cout << "not found" << endl;
  }
  {
    int badShiftTable[256];
    memset(badShiftTable, 0, sizeof(int) * 256);
    int r = search("mitiozebionioiojisd", "nioio", badShiftTable);
    if (r >= 0)
      cout << "found at " << r << endl;
    else
      cout << "not found" << endl;
  }
  return 0;
}