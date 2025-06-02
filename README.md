# Unoptimized Image Format

## Important Info

All the data is losslessly compressed with LZ4 algorithm

## PPM Formating info

Only the P3 mode is curently supported as an input PPM format.

To make the file compatible, you may have to make some changes before submitting the file to the converter:
- Please remove all commentary lines (starts with #)

## Format Specification

The header is super simple, is made of 8 bytes and only specifies the width/height.

| 4 Bytes | 4 Bytes |
|:-------:|:-------:|
|  width  |  height |

Before compression, the file is encoded in binary with **always** 24 bits per pixels (8 per channel)
Since this rule is strictly enforced, we don't need separation between the values