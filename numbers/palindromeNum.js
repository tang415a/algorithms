/*
Determine whether an integer is a palindrome. An integer is a palindrome when it reads the same backward as forward.

Example 1:

Input: 121
Output: true
Example 2:

Input: -121
Output: false
Explanation: From left to right, it reads -121. From right to left, it becomes 121-. Therefore it is not a palindrome.
Example 3:

Input: 10
Output: false
Explanation: Reads 01 from right to left. Therefore it is not a palindrome.
Follow up:

Could you solve it without converting the integer to a string?
*/

function isPalindrome(n) {
  if (n < 0)
    return false;

  let digits = [];
  do {
    digits.push(n % 10);
    n = Math.floor(n / 10);
  } while(n);

  const l = Math.floor(digits.length / 2);
  for (let i = 0; i < l; i++) {
    if (digits[i] !== digits[digits.length - i - 1])
      return false;
  }
  return true;
}

function isPalindrome2(n) {
  if (n < 0)
    return false;
  let x = n, y = 0;
  while (x) {
    y = y * 10 + x % 10;
    x = Math.floor(x / 10);
  }
  return y === n;
}

console.log(isPalindrome2(0));
console.log(isPalindrome2(121));
console.log(isPalindrome2(10));