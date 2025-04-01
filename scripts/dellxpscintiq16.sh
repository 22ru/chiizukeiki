#!/bin/bash

xrandr --output DP-2 --scale 2x2
xsetwacom set $(xinput list --id-only "Wacom Cintiq 16 Pen stylus") MapToOutput DP-2
xsetwacom set $(xinput list --id-only "Wacom Cintiq 16 Pen eraser") MapToOutput DP-2

sudo /home/hat/repo/chiizukeiki/chiizukeiki /home/hat/repo/chiizukeiki/default.map