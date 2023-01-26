// Given an integer array, pick the most integers which constitute an increased sequence
// Note that the order of integers appearing in the sequence may not be switched.
// e.g. given an array: 1,5,2,8,3,7,4,6,0 then it will output 1,2,3,4,6

// you may see increased.cpp for a solution in C++

let hash;
function process(arr, i) {
  if (i in hash)
    return hash[i];
  let max = 1, s = -1;
  for (let j = i - 1; j >= 0; j--) {
    if (arr[i] > arr[j]) {
      let v = process(arr, j).length;
      if (max < 1 + v) {
        max = 1 + v;
        s = j;
      }
    }
  }
  if (0 > s)
    hash[i] = [arr[i]];
  else
    hash[i] = [...hash[s], arr[i]];
  return hash[i];
}

function increased(arr) {
  hash = {};
  for (let i = 0; i < arr.length; i++)
    process(arr, i);
  let max = 0, s;
  for (let k in hash) {
    let tmp = hash[k].length;
    if (tmp > max) {
      max = tmp;
      s = k;
    }
  }
  return hash[s];
}

console.log(increased([1,5,2,8,3,7,4,6,0]));