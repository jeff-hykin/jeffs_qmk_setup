How to use Miryoku

1. `git clone https://github.com/miryoku/miryoku.git`
2. `cd miryoku`
3. `qmk setup -H ./home`
4. `qmk compile -kb YOUR_KEYBOARD -km manna-harbour_miryoku`
<!-- 5. `qmk compile -kb bastardkb/charybdis/4x6/v2/splinky_2 -km via` -->
5. `qmk flash -c -kb YOUR_KEYBOARD -km manna-harbour_miryoku`
<!-- 5. `qmk flash -kb bastardkb/charybdis/4x6/v2/splinky_2 -km via` -->

qmk compile -kb bastardkb/charybdis/4x6/v2/splinky_2 -km via && qmk flash -c -kb bastardkb/charybdis/4x6/v2/splinky_2 -km via
<!-- ```sh
qmk setup -H ./home
qmk compile -kb bastardkb/charybdis/4x6/v2/splinky_2 -km default
qmk compile -kb bastardkb/charybdis/4x6/v2/splinky_2 -km manna-harbour_miryoku
``` -->


Keyboard visualizer
- Create physical keyboard layout (drag and drop keys around)
- Chord mode
    - List which virtual key combos need what physical keys
- Layer mode
    - Mention a layer
    - List physical to virtual key mappings
    