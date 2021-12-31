#!/bin/bash
# Convert 
for i in *.wav; do ffmpeg -i "${i%.*}.wav" "${i%.*}.mp3"; done
