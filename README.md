DupeDetect
==========

A small terminal utility to help find duplicate files.

Thanks
======

This uses the BLAKE3 reference implementation from https://github.com/BLAKE3-team/BLAKE3 .
Big thanks to the team over there.

Building
========

Build Instructions
------------------
- create some folder to hold the build files (for example, bin)
- run  `cmake -B <folder>`
- run `cmake --build <folder>`

TODO's
======

The BLAKE3 reference implementation used supports SIMD instructions.
Currently these are disabled due to build issues (that are likely entirely my fault).

Testing on Windows.