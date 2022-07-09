#ifndef _BITMAP_H_
#define _BITMAP_H_

#include <stdint.h>
#include <string>
#include <cstring>

struct FILEHEADER {
	int32_t FileSize;
	int32_t Reserved;
	int32_t DataOffset;
};

struct INFORHEADER { //40 bytes DIB format
	int32_t m_Size;
	int32_t Width;
	int32_t Height;
	int16_t Planes;
	int16_t BitsPerPixel;
	int32_t Compression;
	int32_t ImageSize;
	int32_t XpixelsPerM;
	int32_t YpixelsPerM;
	int32_t ColorUsed;
	int32_t ImportantColors;
};

struct Bitmap { //for 24 bits format
	char Signature[3];
	FILEHEADER bmpFileHeader;
	INFORHEADER bmpInfoHeader;
	int32_t bytes_per_row;
	int8_t** data;
};

void bmpFileWriter(char* filePath, Bitmap* bmp);

Bitmap* bmpCrop(Bitmap* source, int x_pos, int y_pos, int newWidth, int newHeight);

bool bmpFileReader(char* fileName, Bitmap*& bmp);

void bmpFreeMemory(Bitmap*& bmp);

char* fileNameGenerator(std::string fileName, int num);

bool bmpSplit(char* fileName, int h, int w);

#endif