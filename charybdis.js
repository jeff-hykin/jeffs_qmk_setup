//
// init keys
//
let nameIndex = 1
const makeKeys = (size, rangeStart) => {
    let output = {}
    if (rangeStart < 0) {
        while (rangeStart++) {
            output[rangeStart-1] = Symbol(`${nameIndex++}`)
        }
    }
    const arr = [...Array(size)].fill(0).map((each) => Symbol(`${nameIndex++}`))
    for (let each in arr) {
        output[each+".0"] = arr[each]
        Object.defineProperty(output, each, {
            get: ()=>output[each+".0"],
            set: (v)=>(output[each+".0"] = v),
            enumerable: false,
        })
    }
    return output
}
let leftHand = {
    homeRowUp2: makeKeys(5, -1),
    homeRowUp1: makeKeys(5, -1),
    homeRow: makeKeys(5, -1), // key0 = f, key1 = d,
    homeRowDown1: makeKeys(5, -1),
    thumb: makeKeys(5),
}
let rightHand = {
    homeRowUp2: makeKeys(5, -1),
    homeRowUp1: makeKeys(5, -1),
    homeRow: makeKeys(5, -1), // key0 = j, key1 = k, key2 = l,
    homeRowDown1: makeKeys(5, -1),
    thumb: makeKeys(3), // NOTE: only one thats not 5
}

//
// this is basically the real keyboard definition
//
const rowColumnList = [
    [...Object.values(leftHand.homeRowUp2).toReversed(), ...Object.values(rightHand.homeRowUp2)],
    [...Object.values(leftHand.homeRowUp1).toReversed(), ...Object.values(rightHand.homeRowUp1)],
    [...Object.values(leftHand.homeRow).toReversed(), ...Object.values(rightHand.homeRow)],
    [...Object.values(leftHand.homeRowDown1).toReversed(), ...Object.values(rightHand.homeRowDown1)],
    [...Object.values(leftHand.thumb).slice(0, 3), ...Object.values(rightHand.thumb).slice(0, 2), ...Object.values(leftHand.thumb).slice(3, 5), ...Object.values(rightHand.thumb).slice(2, 3)],
]
const keyList = rowColumnList.flat(1)
const rowColumnToIndex = {}
const indexToRowColumn = {}

// I don't know why this is so convoluted, the following is the row/col printout based on the keyboard itself and QMK
const MATRIX_COLS = 6 // From QMK
const realIndexList = [
     {r:0, c:0},{r:0, c:1},{r:0, c:2},{r:0, c:3},{r:0, c:4},{r:0, c:5},    {r:5, c:5},{r:5, c:4},{r:5, c:3},{r:5, c:2},{r:5, c:1},{r:5, c:0},
     {r:1, c:0},{r:1, c:1},{r:1, c:2},{r:1, c:3},{r:1, c:4},{r:1, c:5},    {r:6, c:5},{r:6, c:4},{r:6, c:3},{r:6, c:2},{r:6, c:1},{r:6, c:0},
     {r:2, c:0},{r:2, c:1},{r:2, c:2},{r:2, c:3},{r:2, c:4},{r:2, c:5},    {r:7, c:5},{r:7, c:4},{r:7, c:3},{r:7, c:2},{r:7, c:1},{r:7, c:0},
     {r:3, c:0},{r:3, c:1},{r:3, c:2},{r:3, c:3},{r:3, c:4},{r:3, c:5},    {r:8, c:5},{r:8, c:4},{r:8, c:3},{r:8, c:2},{r:8, c:1},{r:8, c:0},
                                      {r:4, c:3},{r:4, c:4},{r:4, c:1},    {r:9, c:1},{r:9, c:3},
                                                 {r:4, c:5},{r:4, c:2},    {r:9, c:5},
]

//
// keep track of indicies for easy lookup later
//
for (const [handName, hand] of Object.entries({leftHand, rightHand})) {
    for (const [rowName, nameMapping] of Object.entries(hand)) {
        for (const [relativeIndex, symbol] of Object.entries(nameMapping)) {
            const theIndexThatWouldMakeSense = keyList.findIndex((each) => each === symbol)
            const qmksRowCol = realIndexList[theIndexThatWouldMakeSense]
            const { r: row, c: column } = qmksRowCol
            const qmksIndex = row * MATRIX_COLS + column;
            nameMapping[relativeIndex] = qmksIndex
            rowColumnToIndex[qmksRowCol.r] = rowColumnToIndex[qmksRowCol.r] || {}
            rowColumnToIndex[qmksRowCol.r][qmksRowCol.c] = qmksIndex
            indexToRowColumn[relativeIndex] = [row, column]
        }
    }
}


export const keyboard = {
    leftHand,
    rightHand,
    rowColumnToIndex,
    indexToRowColumn,
}
