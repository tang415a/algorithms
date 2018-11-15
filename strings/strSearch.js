// Implement a sub-string search algorithm using Boyer Moore algorithm.
// e.g. given a string "aabbccdd" and search for "bcc", then the output is: "found: from 3 to 5".

let badShiftTable = {};
function badShift(c, p) {
	if (c in badShiftTable)
		return badShiftTable[c];

	let offset = p.length;
	for (let i = 1; i < offset; i++) {
		if (p[offset - 1 - i] === c) {
			badShiftTable[c] = i;
			return i;
		}
	}
	return offset;
}

function foundAtHead(i, p) {
	const lp = p.length;
	for (let j = 0; j < i; j++) {
		if (p[j] !== p[lp - i + j])
			return false;
	}
	return true;
}

let goodShiftTable = {};
function goodShift(i, p) {
	if (i <= 0)
		return 1;
	if (i in goodShiftTable)
		return goodShiftTable[i];

	const lp = p.length;
	let offset = 1;
	for (; offset < lp - i; offset++) {
		if (p[lp - i - 1] === p[lp - i - 1 - offset])
			continue;
		let j = 0;
		for (; j < i; j++) {
			if (p[lp - i + j] !== p[lp - i + j - offset])
				break;
		}
		if (j >= i)
			break;
	}
	if (offset < lp - i) {
		goodShiftTable[i] = offset;
		return offset;
	}

	for (let j = i; j > 0; j--) {
		if (foundAtHead(j, p)) {
			goodShiftTable[i] = lp - j;
			return lp - j;
		}
	}
	return lp;
}

function max(a, b) {
	return a > b ? a : b;
}

function sub(s, p) {
	let ls = s.length, lp = p.length, offset = lp - 1;
	while (offset < ls) {
		let i = 0;
		for (; i < lp; i++) {
			if (p[lp - i - 1] !== s[offset - i]) {
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

sub("aabbccdd", "bcc");