// Implement a sub-string search algorithm using Boyer Moore algorithm.
// e.g. given a string "aabbccdd" and search for "bcc", then the output is: "found: from 3 to 5".

// you may refer to strSearch.cpp for more

const badShiftTable = {};
function badShift(c, p) {
	if (c in badShiftTable)
		return badShiftTable[c];

	const offset = p.length;
	for (let i = 1; i < offset; i++) {
		if (p[offset - 1 - i] === c) { // c also appears at length - 1 - i in pattern; we can move i
			badShiftTable[c] = i;
			return i;
		}
	}
	return offset;
}

// do i characters of suffix also appear at the head of pattern?
function foundAtHead(i, p) {
	const lp = p.length;
	for (let j = 0; j < i; j++) {
		if (p[j] !== p[lp - i + j])
			return false;
	}
	return true;
}

const goodShiftTable = {};
function goodShift(i, p) { // i characters have been matched (denoted by Ci)
	if (i <= 0)
		return 1;
	if (i in goodShiftTable)
		return goodShiftTable[i];

	const lp = p.length;
	let offset = 1;
	for (; offset < lp - i; offset++) {	// this iteration does not include the head since the offset never goes to lp - i (p[lp - i - offset] is the leftmost character we are trying to match)
		if (p[lp - i - 1] === p[lp - i - 1 - offset])	// this considers the bad shift too; if the character before the Ci (lp - i - 1, i + 1 character from right) repeats, ignore it, because it fails to match (only i characters have been matched, i + 1 character from right fails)
			continue;
		let j = 0;
		for (; j < i; j++) {
			if (p[lp - i + j] !== p[lp - i + j - offset])	// the j characters of Ci match so far
				break;
		}
		if (j >= i)	// found all the matched i characters (Ci)
			break;
	}
	// found the matched i characters (Ci) elsewhere in pattern
	if (offset < lp - i) {
		goodShiftTable[i] = offset;
		return offset;
	}

	// Does Ci or suffix of Ci appear at the head?
	for (let j = i; j > 0; j--) {
		if (foundAtHead(j, p)) {	// j characters from Ci (the suffix of Ci) are found at the head of pattern
			goodShiftTable[i] = lp - j;
			return lp - j;
		}
	}
	return lp;	// move the length of pattern
}

function max(a, b) {
	return a > b ? a : b;
}

function sub(s, p) {
	let ls = s.length, lp = p.length, offset = lp - 1;
	while (offset < ls) {
		let i = 0;
		for (; i < lp; i++) {
			if (p[lp - i - 1] !== s[offset - i]) { // dose not match
				// use the rightmost character (either matched when i > 1 or not when i == 0, either case p[p.length - 1] would be ignored) for bad shift
				offset += max(badShift(s[offset], p), goodShift(i, p));
				break;
			}
		}
		if (i >= lp) {
			console.log(`found: from ${offset - lp + 1} to ${offset}`);
			break;
		}
	}
	if (offset >= ls)
		console.log('not found');
}

// sub("aabbccdd", "bcc");
sub("mitiozebionioiojisd", "nioio");