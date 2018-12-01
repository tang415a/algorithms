// Given two integers, return the greatest common divisor of them.
// e.g. input 36 and 60, then output 12

function gcd(a, b) {
	if (b === 0)
		return a;
	return gcd(b, a % b);
}

const a = 36, b = 60;
console.log(`GCD of ${a} and ${b} is ${gcd(a, b)}`);