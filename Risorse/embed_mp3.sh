#!/bin/bash
# Convert 
for i in *.mp3; do ffmpeg -i "${i%.*}.mp3" -c copy -f wav "${i%.*}.wav"; done


