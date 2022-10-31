#!/bin/bash

# if you have windows use this
sudo qemu-system-x86_64 -hda Image/x64BareBonesImage.qcow2 -soundhw pcspk -m 512
# if you hava mac use this
#qemu-system-x86_64 -hda Image/x64BareBonesImage.qcow2 -m 512 -audiodev sdl,id=audio0 -machine pcspk-audiodev=audio0
