//
// init keys
//
let nameIndex = 1
const makeKeys = (size, name) => {
    const arr = [...Array(size)].fill(0).map((each) => Symbol(`${nameIndex++}`))
    let output = {}
    for (let each in arr) {
        output[each] = arr[each]
    }
    return output
}
let leftHand = {
    homeRowUp2: makeKeys(4, "homeRowUp2"),
    homeRowUp1: makeKeys(4),
    homeRow: makeKeys(4), // key0 = f, key1 = d,
    homeRowDown1: makeKeys(4),
    thumb: makeKeys(5),
}
let rightHand = {
    homeRowUp2: makeKeys(4, "homeRowUp2"),
    homeRowUp1: makeKeys(4),
    homeRow: makeKeys(4), // key0 = j, key1 = k, key2 = l,
    homeRowDown1: makeKeys(4),
    thumb: makeKeys(3), // NOTE: only one thats not 5
}
// cursed, I know, deal with it
leftHand.homeRowUp2[-1] = makeKeys(1)[0]
leftHand.homeRowUp1[-1] = makeKeys(1)[0]
leftHand.homeRow[-1] = makeKeys(1)[0]
leftHand.homeRowDown1[-1] = makeKeys(1)[0]
rightHand.homeRowUp2[-1] = makeKeys(1)[0]
rightHand.homeRowUp1[-1] = makeKeys(1)[0]
rightHand.homeRow[-1] = makeKeys(1)[0]
rightHand.homeRowDown1[-1] = makeKeys(1)[0]

//
// this is basically the real keyboard definition
//
const rowColumnList = [
    [...Object.values(leftHand.homeRowUp2).toReversed(), leftHand.homeRowUp2[-1], rightHand.homeRowUp2[-1], ...Object.values(rightHand.homeRowUp2)],
    [...Object.values(leftHand.homeRowUp1).toReversed(), leftHand.homeRowUp1[-1], rightHand.homeRowUp1[-1], ...Object.values(rightHand.homeRowUp1)],
    [...Object.values(leftHand.homeRow).toReversed(), leftHand.homeRow[-1], rightHand.homeRow[-1], ...Object.values(rightHand.homeRow)],
    [...Object.values(leftHand.homeRowDown1).toReversed(), leftHand.homeRowDown1[-1], rightHand.homeRowDown1[-1], ...Object.values(rightHand.homeRowDown1)],
    [...Object.values(leftHand.thumb).slice(0, 3), ...Object.values(rightHand.thumb).slice(0, 2), ...Object.values(leftHand.thumb).slice(3, 5), ...Object.values(rightHand.thumb).slice(2, 3)],
]
const keyList = rowColumnList.flat(1)
const rowColumnToIndex = {}
const indexToRowColumn = {}

//
// keep track of indicies for easy lookup later
//
for (const [rowName, nameMapping] of Object.entries(rightHand).concat(Object.entries(leftHand))) {
    for (const [relativeIndex, symbol] of Object.entries(nameMapping)) {
        let row = null
        let column = null
        for (let each of rowColumnList) {
            if (each.includes(symbol)) {
                row = rowName
                column = each.indexOf(symbol)
                break
            }
        }
        
        nameMapping[relativeIndex] = `${keyList.findIndex((each) => each === symbol)} /* ${rowName}[${relativeIndex}] */`
        // if (!Number.isFinite(nameMapping[relativeIndex])) {
        //     throw Error(`error in keyboard mapping`)
        // }
        rowColumnToIndex[row] = rowColumnToIndex[row] || {}
        rowColumnToIndex[row][column] = nameMapping[relativeIndex]
        indexToRowColumn[relativeIndex] = [row, column]
    }
}

export const keyboard = {
    leftHand,
    rightHand,
    rowColumnToIndex,
    indexToRowColumn,
}
