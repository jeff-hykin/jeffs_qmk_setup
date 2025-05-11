// 
// init keys
// 
const makeKeys = (size)=>[...Array(size)].map(each=>Symbol())
let leftHand = {
    homeRowUp2: makeKeys(5),
    homeRowUp1: makeKeys(5),
    homeRow: makeKeys(5),
    homeRowDown1: makeKeys(5),
    thumb: makeKeys(5) 
}
let rightHand = {
    homeRowUp2: makeKeys(5),
    homeRowUp1: makeKeys(5),
    homeRow: makeKeys(5),
    homeRowDown1: makeKeys(5),
    thumb: makeKeys(3), // NOTE: only one thats not 5 
}
// cursed, I know, deal with it
leftHand.homeRowUp2[-1]    = makeKeys(1)[0]
leftHand.homeRowUp1[-1]    = makeKeys(1)[0]
leftHand.homeRow[-1]       = makeKeys(1)[0]
leftHand.homeRowDown1[-1]  = makeKeys(1)[0]
rightHand.homeRowUp2[-1]   = makeKeys(1)[0]
rightHand.homeRowUp1[-1]   = makeKeys(1)[0]
rightHand.homeRow[-1]      = makeKeys(1)[0]
rightHand.homeRowDown1[-1] = makeKeys(1)[0]


// 
// this is basically the real keyboard definition
// 
const rowColumnList = [
    [...leftHand.homeRowUp2.toReversed(),   leftHand.homeRowUp2[-1]  , rightHand.homeRowUp2[-1]  , ...rightHand.homeRowUp2], 
    [...leftHand.homeRowUp1.toReversed(),   leftHand.homeRowUp1[-1]  , rightHand.homeRowUp1[-1]  , ...rightHand.homeRowUp1], 
    [...leftHand.homeRow.toReversed(),      leftHand.homeRow[-1]     , rightHand.homeRow[-1]     , ...rightHand.homeRow], 
    [...leftHand.homeRowDown1.toReversed(), leftHand.homeRowDown1[-1], rightHand.homeRowDown1[-1], ...rightHand.homeRowDown1], 
    [...leftHand.thumb.slice(0, 3), ...rightHand.thumb.slice(0, 2)],
    [...leftHand.thumb.slice(3, 5), ...rightHand.thumb.slice(2, 3)],
]
const keyList = rowColumnList.flat(1)
const rowColumnToIndex = {}
const indexToRowColumn = {}

// 
// keep track of indicies for easy lookup later
// 
for (const [rowName, list] of Object.entries(rightHand).concat(Object.entries(leftHand))) {
    for (let [index, symbol] in Object.entries(list)) {
        let row = null
        let column = null
        for (let each of rowColumnList) {
            if (each.includes(symbol)) {
                row = rowName
                column = each.indexOf(symbol)
                break
            }
        }
        rowColumnToIndex[row] = rowColumnToIndex[row] || {}
        rowColumnToIndex[row][column] = index
        indexToRowColumn[index] = [row, column]
        // replace the symbol with true/total index of the key
        list[index] = keyList.find(each=>each===symbol)
    }
}

export const keyboard = {
    leftHand,
    rightHand,
    rowColumnToIndex,
    indexToRowColumn,
}