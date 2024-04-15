#!/bin/sh

# Use Imagemagick to bulk-convert PNGs to TGA files.  Having both allows
# flexability during the broadcast.

for file in *.png; do
  targafile=`echo $file | sed s/.png\$/.tga/`
  echo $file to $targafile
  convert -auto-orient $file $targafile
done
