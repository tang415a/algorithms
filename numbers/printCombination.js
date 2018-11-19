// Given a positive integer N, print out all the combinations of positive integers (less than N) whose sum equals to N.
// e.g. if N = 5, then print out: [4,1] and [3,2].

function print(arr, n, m) {
  if (n === 0) {
    console.log(arr);
    return;
  }

  if (n > (1 + m) * m * 0.5)
    return;

  if (n >= m) {
    arr.push(m);
    print(arr, n - m, m - 1);
    arr.pop();
  }
  print(arr, n, m - 1);
}

function process(n) {
  print([], n, n - 1);
}
process(5);