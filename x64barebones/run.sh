#!/bin/bash

# if you have windows use this
# sudo qemu-system-x86_64 -hda Image/x64BareBonesImage.qcow2 -m 512 -soundhw pcspk
# if you hava mac use this
qemu-system-x86_64 -hda Image/x64BareBonesImage.qcow2 -m 512 #-audiodev sdl,id=audio0 -machine pcspk-audiodev=audio0
