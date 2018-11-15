// Say we have two containers A and B. Each of them has a certain volume (a liters and b liters).
// Is it possible to measure out c liters of water exactly using these two containers (suppose we have plenty of water)?
// Hint: the possible actions include: we may fill/empty each container and pour the water out of one container to another.
// e.g. Container A -> 5 liters, Container B -> 3 liters, the goal -> 4 liters of water

class Container {
  constructor(name, cap) {
    this.name = name;
    this.capacity = cap;
  }
}

function gen(a, va, b, vb, from, action) {
  return { [a.name]: va, [b.name]: vb, from, action };
}

function fill(r, a, b) {
  if (r[a.name] < a.capacity) {
    return gen(a, a.capacity, b, r[b.name], r, `${a.name} fill`);
  }
}

function empty(r, a, b) {
  if (r[a.name] > 0) {
    return gen(a, 0, b, r[b.name], r, `${a.name} empty`);
  }
}

function pour(r, a, b) {
  var volume = b.capacity - r[b.name];
  if (volume === 0)
    return;
  var move = r[a.name] > volume ? volume : r[a.name];
  return gen(a, r[a.name] - move, b, r[b.name] + move, r, `${a.name} pour to ${b.name}`);
}

function check(record) {
  return (record[name1] === goal || record[name2] === goal);
}

function print(record) {
  if (record.from)
    print(record.from);
  if (record.action)
    console.log(record.action);
  console.log(`state: (${record[name1]}, ${record[name2]})`);
}

function exists(r, keys) {
  function equals(s1, s2) {
    for (var key of keys) {
      if (s1[key] !== s2[key])
        return false;
    }
    return true;
  }
  for (var rec of records) {
    if (equals(r, rec))
      return true;
  }
  return false;
}

function search(oper, rec, a, b) {
  var record = oper(rec, a, b);
  if (!record)
    return;
  if (check(record)) {
    print(record);
    return true;
  }
  if (!exists(record, [name1, name2]))
    records.push(record);
}

const name1 = "A";
const name2 = "B";
const container1 = new Container(name1, 5);
const container2 = new Container(name2, 3);
const goal = 4;
const actions = [fill, empty, pour];

var record = gen(container1, 0, container2, 0);
if (check(record)) {
  print(record);
  return;
}

var records = [record];
var idx = 0;
while (true) {
  if (idx >= records.length) {
    console.log("impossible state");
    return;
  }
  record = records[idx++];
  for (var a of actions) {
    if (search(a, record, container1, container2) || search(a, record, container2, container1))
      return;
  }
}