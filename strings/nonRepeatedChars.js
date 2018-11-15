// Find the substring with most non-repeated characters inside a string.
// e.g. given a string: "foobaa", the result should be: "from 2 to 4 : oba"

function nonRepeated(str) {
    let len = str.length;
    if (len === 0) {
        console.log("The string is empty.");
        return;
    }
    
    let hash = {[str[0]]: 0}, rec = 1, max = 1, ed = 0;
    for (let i = 1; i < len; i++) {
        let c = str[i];
        if (c in hash && hash[c] >= i - rec) 
            rec = i - hash[c];
        else 
            rec++;
        hash[c] = i;
        if (max < rec) {
            ed = i;
            max = rec;
        }
    }
    console.log(`from ${ed - max + 1} to ${ed} : ${str.substr(ed - max + 1, max)}`);
}

nonRepeated("foobaa");