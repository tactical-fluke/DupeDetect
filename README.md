DupeDetect
==========

A small terminal utility to help find duplicate files.

Thanks
======

This uses the BLAKE3 reference implementation from https://github.com/BLAKE3-team/BLAKE3 .
Big thanks to the team over there.

Building
========

Dependencies (Linux)
--------------------
Thread Building Blocks

Build Instructions
------------------
- create some folder to hold the build files (for example, bin)
- run  `cmake -B <folder>`
- run `cmake --build <folder>`

TODO's
======

The BLAKE3 reference implementation used supports SIMD instructions.
Currently these are disabled due to build issues (that are likely entirely my fault).

Testing on Mac and Windows.

Some manual work needed to be done for TBB to work correctly with the build. Some work
needs to be done in order to ensure a simple build process.