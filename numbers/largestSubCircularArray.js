// Given an array, find a continuous sub array whose sum is as largest as possible.
// Note that the array is circular, i.e. for an array with N elements, 
// we can jump from index N - 1 to index 0.

function findPositive(arr) {
  let sum = arr[0], tmp = arr[0];
  for(let i = 1; i < arr.length; i++) {
    tmp = tmp > 0 ? tmp + arr[i] : arr[i];
    if (tmp > sum)
      sum = tmp;
  }
  return sum;
}

function findNegative(arr) {
  let sum = arr[1], tmp = arr[1];
  for(let i = 2; i < arr.length - 1; i++) {
    tmp = tmp < 0 ? tmp + arr[i] : arr[i];
    if (tmp < sum)
      sum = tmp;
  }
  tmp = arr.reduce((a, c) => a + c);
  return tmp - sum;
}

function findMaxSub(arr) {
  if (arr.length === 0)
    return "the array is empty.";
  
  let p = findPositive(arr);
  if (arr.length === 1)
    return p;
    
  let n = findNegative(arr);
  return p < n ? n : p;
}

console.log(findMaxSub([2,3,-4,5,6,7]));
console.log(findMaxSub([-12,-3,-4,-5,-1,-6,-7]));
console.log(findMaxSub([2,-3,8,-4,-5,10,-1,-6,-7]));