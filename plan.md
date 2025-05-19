Current Plan
- DONE: home row mod
    <!-- - but with two keys to trigger a modifier  -->
    - ctrl is outer pinky
- DONE: arrow keys with spacebar
- DONE: brackets above arrow keys
- DONE: parenthesis above arrow keys with both right thumb modifiers
<!-- - left thumb modifier plus left pinky makes squiggly brackets above arrow keys -->
- DONE: backspace is spacebar plus letter P
- DONE: add programming button
- DONE: enter is spacebar plus semicolon
- DONE: tab is: fd combo
- DONE: esc is sa combo
- Mouse buttons as left thumb buttons
- Fix what happens when a non-combo is confirmed (replay press-down order)
    - DONE: make a key-history array
    - figure how/when to apply the array
- Scroll as left thumb button (test if it works with modifiers in blender)
- comma and period are below arrow keys on spacebar, shift makes them <>'s
- number is left thumb modifier, which doubles as space
    <!-- - underscore as jk combo -->
    - equals in up top corner
    - underscore where . normally is
    - /? where it normally is
    - "plus" is h + number modifier
    - minus is b + number modifier
    - single quote is jk combo
    - exclamation point right thumb modifier + letter G
    - percent as yu combo
    - at sign as left middle finger under right hand thumb modifier
    - hash as left index finger under right hand thumb modifier
    - dollar sign as letter T under right hand thumb modifier
    - asterisk as jn combo
    - caret as km combo
    - ampersand as hb combo
    - bar as gv combo
    - backslash as io combo
    - double quote as sdf combo
    
- TODO:
    - scroll
    - fn
    - sound
    - brightness

Logic:
    - the algorithm is a function that looks at the history of presses and sends a key value as soon as it can confirm something
    - three aspects of the algorithm:
        - home row mod
        - special mods
        - local combos
    - pattern matching
        - if (start) keydown (end):
            clear all key-up caveats
            and continue
        - if (start) keydown, keyup (end):
            then send the key, flush the history
        - if (start) (left/right hand home row keydown(s)) (other-hand keydown) (other-hand keyup) (end):
            then send the other-hand key, flush the history, keep the modifier array, add key-up caveat for modifiers
        - if (start) keydown, keydown (end); and (neither are home-row) and (neither are special mods) and (there are no local combos with both keys):
            then send each key, flush the history, add key-up caveat for both
        - if (start) (left/right hand home row keydown(s)) (other-hand keydown) (end) and (other-hand keydown is not special mod) and (there are no local combos with the other-hand keys):
            then send the other-hand key, flush the history, add key-up caveat for both
        - if (start) keydown, keydown (end); and (neither are home-row) and (neither are special mods) and (the largest combo involving both keys is 2):
            then send the combo, flush the history, add key-up caveat for both
        - if (start) keydown1, keydown2, keyup1 (end); and (there are no local combos with both keys):
            then send each key1, flush it's keydown/keyup from the history
        - if (start) (left/right hand home row keydown(s)) (other-hand keydown) (end):
            - cancel-out said
        - consider typing "axis", or "said"
            - if non-home row keydown, keydown home row, 
        - if (key is not a part of a local combo) and (no special mods are down):
            - all keys before the 
            - send the key with the home row mod, neutralize the keyup of the home row mod
        - if (key is not a part of a local combo) and (special mod is down): send the special mod-mapped key with the home row mod, neutralize the keyup of the home row mod
        - if (home row mod keys are down) and (key is a part of a local combo): send the key with the home row mod
    - home row mod only activates if a key on the opposite hand is pressed after home row mod was pressed
        - ex1: 
            - right pointer finger (CMD/J) pressed
            - left pointer finger (CMD/F) pressed => triggers CMD+F and "neutralized" the keyup of CMD/F and CMD/J
            - right pinky (semicolon) pressed => ideally ignores that CMD/F is pressed and sends semicolon
        - ex2: 
            - right pointer finger (CMD/J) pressed
            - left middle finger (SHIFT/D) pressed => triggers CMD+D and "neutralized" the keyup of CMD/D and CMD/J
            - left middle finger (SHIFT/D) released => nothing
            - left middle finger (SHIFT/D) pressed => triggers CMD+D and "neutralized" the keyup of CMD/D and CMD/J (even though CMD/J was neutralized)
    - local combos (same-side) and layers
        - if the key is not a part of any combo
            - check if any special mod-keys were pressed (ex: spacebar)
            - if so, trigger the that combo
        - find the largest combo for the keys
            - if all the keys are pressed, trigger the combo with the home row mod (return)
            - if
        - when a key is depressed (ex: spacebar/thumb1)
        - if two keys of a two-or-three key combo are pressed, the 



Older thoughts:

ideas:special 
- full keyboard for each hand, but no meta key combinations
- note: don't make any chord a subset of another chord; otherwise it can't activate on keydown

challenging words for home row mod:
- false
- falls
- last
- ask
- keys
- asm
- fail
- daunt
- lapse


layout:
- no thumb layer
    - querty for single key
    - right hand
        <!-- - h between jk -->
        - y between ju
        - b between jn
        - enter:
            - home[1] + home[4]
        - tab:
            - home[1] + home[3]
        - space:
            - home[1] + home[2]
        - backspace:
            - home[1] + home[3]up1
        - escape:
            - home[1]up1 + home[3]
        - click:
            - home[1]down1 + home[2]down1
        - right click:
            - home[2]down1 + home[3]down1
        - scroll:
            - home[1]down1 + home[3]down1
        - "[": home[2] + home[2]up1
        - "]": home[3] + home[3]up1
        - "`": home[1]up1 + home[4]
        - "=": home[1]up1 + home[3]up1
        - "-": home[1]up1 + home[2]up1
        - "\": home[1] + home[4]up1
        - "/": home[1] + home[4]down1
        - "'": handled
        - ";": handled
        - ",": handled
        - ".": handled
    - left hand
        <!-- - g between fd -->
        - t between fr
        - v between fc
- layer-ish (layers activate on one hand only)
    - symbols & meta:
        - activate: thumb 1
        - keys: (right hand)
            - above home row: ( )
            - below home row: super, ctrl, alt, shift, fn
    - arrow keys
        - activate: thumb 2


need mapping:
    first level:
        symbols: `-=[]\;',./
        specials: enter, tab, space, backspace, escape, click, scroll, right click
        optional specials: home, end, page up, page down, print screen
    second level: 
        symbols: ~!@#$%^&*()_+{}|:"<>?