# Unoptimized Image Format

## Important Info

All the data is losslessly compressed with LZ4 algorithm

## PPM Formating info

Only the P3 mode is curently supported as an input PPM format.

To make the file compatible, you may have to make some changes before submitting the file to the converter:
- Please remove all commentary lines (starts with #)
- Please adapt the file so all data is in the range of 0-255
- Please remove the maxval line (the one that specifies the maximum value for a pixel, usually 255)

## Format Specification

The header is super simple, is made of 8 bytes and only specifies the width/height.

| 4 Bytes | 4 Bytes |
|:-------:|:-------:|
|  width  |  height |

Before compression, the file is encoded in binary with **always** 3 Bytes per pixel (8 per channel, 
which is an unsigned int). Since this rule is strictly enforced, we don't need separation between the values.

Due to the way the file is made, the minimum size is 8 bytes and the maximum is 55 340 232 195 358 851 075 bytes
(kinda useless info but why not?)

The extensions for the file type are `.uif` (Unoptimized Image Format) and `.cuif` (Compressed Unoptimized Image Format).

## Compression

The useful data is compressed with LZ4 algorithm, which is a fast compression algorithm. However, the 2 first bytes
are reserved for the uncompressed header (necessary for decompression).

This program will store the file in both the compressed and uncompressed format.

> Note: I see a single byte is added after the header when compressing.

## Bug Report & Suggestions

Don't hesitate to write a GitHub issue or dm me on discord (`equalisys`) if you find any bug or have a suggestion.