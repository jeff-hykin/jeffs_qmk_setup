```bash
git clone THIS_REPO
cd THIS_REPO
virkshop/enter

# Compile and flash
virkshop/commands/compile_and_flash
# then put your keyboard into bootloader/DFU mode to finish the flash
# (you'll probably have to ask the keyboard manufacturer to know how to do this)
# ex: on Charybdis, there's a special gold reset button on the bottom and it needs to be double-tapped to enter DFU mode
```

To customize: edit `./keymaps/via/keymap.c` and read stuff in `./home/docs/`
