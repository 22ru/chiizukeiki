#!/bin/bash

for d in /sys/class/drm/*/edid; do
	if cat $d | grep "Cintiq 16"; then
		[[ "$d" =~ DP-[0-9] ]]
		display=${BASH_REMATCH[0]}
		echo "Cintiq 16 is on $display."
	fi
done

if [[ -z "$display" ]]; then
	echo "Cintiq 16 not found."
	exit 1
fi

xrandr --output $display --scale 2x2
xsetwacom set $(xinput list --id-only "Wacom Cintiq 16 Pen stylus") MapToOutput $display
xsetwacom set $(xinput list --id-only "Wacom Cintiq 16 Pen eraser") MapToOutput $display

sudo /home/hat/repo/chiizukeiki/chiizukeiki /home/hat/repo/chiizukeiki/default.map
