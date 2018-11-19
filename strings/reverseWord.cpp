// Reverse each word in a sentence. For example, given a string "hello world", then output "world hello".

#include <stdio.h>
#include <string.h>

void reverse(char* w, int s, int e) {
  int l = e - s;
  char* p = w + s;
  for (int i = 0; i < l / 2; i++) {
    char tmp = p[i];
    p[i] = p[l - i - 1];
    p[l - i - 1] = tmp;
  }
}

void reverse(char* s) {
  int l = strlen(s), st = 0;
  reverse(s, 0, l);
  for (int i = 0; i <= l; i++) {
    if (s[i] == ' ' || s[i] == '\0') {
      if (i > st)
        reverse(s, st, i);
      st = i + 1;
    }
  }
}

int main() {
  char s[] = "hello world";
  reverse(s);
  printf(s);
  return 0;
}