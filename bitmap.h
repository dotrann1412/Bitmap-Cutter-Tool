#ifndef _BITMAP_H_
#define _BITMAP_H_

#include <stdint.h>

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
public:
	char Signature[3];
	FILEHEADER bmpFileHeader;
	INFORHEADER bmpInfoHeader;
	int32_t bytes_per_row;
	int8_t** data;
/*	Bitmap(){

	}
	~Bitmap(){
		for(int i = 0; i < this->bmpInfoHeader.Height; ++i)
			delete[] data[i];
		delete[] data;
	}*/
};

#endif