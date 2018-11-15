// Given an integer N, write a program to print out the numbers from 1 to the largest N-digit number.
// e.g. N = 3, then print 1, 2, 3, ..., 998, 999.

function next(arr, i) {
  if (i === arr.length) {
    arr.push(1);
    return;
  }

  if (arr[i] < 9 && arr[i] >= 0) {
    arr[i]++;
    return;
  }

  if (arr[i] === 9) {
    arr[i] = 0;
    next(arr, i + 1);
  }
}

function print(arr) {
  let o = "";
  for (let i = arr.length; i > 0; i--) {
    o += arr[i - 1];
  }
  console.log(o);
}

function list(n) {
  let arr = [];
  while (true) {
    next(arr, 0);
    if (arr.length > n)
      break;
    print(arr);
  }
}

list(5);