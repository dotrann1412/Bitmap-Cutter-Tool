# Bitmap Cutter Tool
Cut the bitmap file to w piece by width and h piece by height.

## Re-compile
Open terminal and run command: `g++ -o program_name main.cpp header.h handle.cpp bitmap.h -std=c++17`.

## How to use?
Open terminal and run command: `./program_name bitmap_filename.bmp [-w num] [-h num]`.

## Note
This program only work with 40 bytes of DIB format.<br>
Bitmap file structure [here](https://en.wikipedia.org/wiki/BMP_file_format#:~:text=The%20BMP%20file%20format%2C%20also,and%20OS%2F2%20operating%20systems).
