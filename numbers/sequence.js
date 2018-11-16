// Given a positive integer N, write a function that prints all the continuous positive integer sequences whose sum is N.
// For example,
//    15 = 7 + 8
//    15 = 4 + 5 + 6
//    15 = 1 + 2 + 3 + 4 + 5

function process(n) {
  var i = 1, j = 2, sum = i + j;
  while (i < j) {
    if (sum >= n) {
      if (sum === n)
        console.log(`from ${i} to ${j} = ${n}`);
      sum -= i;
      i++;      
    }
    else {
      j++;
      sum += j;
    }
  }
}

process(15);