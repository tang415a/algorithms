// a quick sort algorithm using extra space for array copy
// it is simpler and steable compared with the regular quick sort algorithm
function quick_sort(arr) {
  const len = arr.length;
  if (len < 1)
    return arr;
  let leftarr = [], rightarr = [];
  for(let i = 1; i < len; i++)
    arr[i] < arr[0] ? leftarr.push(arr[i]) : rightarr.push(arr[i]);
  
  return quick_sort(leftarr).concat([arr[0]]).concat(quick_sort(rightarr));
}

let arr = [3, 5, 4, 8, 6, 9, 0, 1, 2, 7];
arr = quick_sort(arr);
console.log(arr);