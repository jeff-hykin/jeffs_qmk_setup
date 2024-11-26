ideas:
- full keyboard for each hand, but no meta key combinations
- note: don't make any chord a subset of another chord; otherwise it can't activate on keydown

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