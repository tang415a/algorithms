// Given an array, find a continuous sub array whose sum is as largest as possible.
// e.g. for [3,2,-8,9,-4,0,6,-7,5,1], the output is: [9,-4,0,6].

function findSub(arr) {
  let len = arr.length;
  if (len === 0) {
    console.log("The array is empty.");
    return;
  }
  let max = arr[0], ed = 0, st = 0, sum = arr[0], tmp = 0;
  for (let i = 1; i < len; i++) {
    if (sum > 0) {
      sum += arr[i];
    }
    else {
      sum = arr[i];
      tmp = i;
    }
    if (sum > max) {
      max = sum;
      ed = i;
      st = tmp;
    }
  }
  console.log(`The largest sub array is from ${st} to ${ed} with sum ${max}.`);
}

findSub([3,2,-8,9,-4,0,6,-7,5,1]);