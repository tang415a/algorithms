// Given an integer array, pick the most integers which constitute an increased sequence
// Note that the order of integers appearing in the sequence may not be switched.
// e.g. given an array: 1,2,5,4,3,7,8,0,9,6 then it will output 1,2,3,7,8,9

let hash = {};
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
  for (let i = 0; i < arr.length; i++)
    process(arr, i);
  let max = 0, s;
  for (let i = 0; i < arr.length; i++) {
    let tmp = hash[i].length;
    if (tmp > max) {
      max = tmp;
      s = i;
    }
  }
  return hash[s];
}

console.log(increased([1,2,5,4,3,7,8,0,9,6]));