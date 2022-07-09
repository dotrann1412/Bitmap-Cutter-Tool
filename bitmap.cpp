#include "bitmap.h"
#include <iostream>

void bmpFileWriter(char* filePath, Bitmap* bmp) {
	FILE* file_output = fopen(filePath, "wb");
	fwrite(&bmp->Signature, 2 , 1, file_output);
	fwrite(&bmp->bmpFileHeader, 12, 1, file_output);
	fwrite(&bmp->bmpInfoHeader, 40, 1, file_output);
	int32_t bytes_per_row = ((bmp->bmpInfoHeader.BitsPerPixel * bmp->bmpInfoHeader.Width + 31) / 32 ) * 4;
	for (int i = bmp->bmpInfoHeader.Height - 1; i >= 0; i--) {
		fwrite(bmp->data[i], bytes_per_row, 1, file_output);
	}
	fclose(file_output);
}

Bitmap* bmpCrop(Bitmap* source, int x_pos, int y_pos, int newWidth, int newHeight) {
	Bitmap* bmap = new Bitmap;
	strcpy(bmap->Signature, "BM");
	bmap->bmpFileHeader = source->bmpFileHeader;
	bmap->bmpInfoHeader = source->bmpInfoHeader;
	bmap->bmpInfoHeader.Height = newHeight;
	bmap->bmpInfoHeader.Width = newWidth;
	bmap->data = new int8_t*[newHeight];
	for (int i = 0; i < newHeight; i++) {
		bmap->data[i] = new int8_t[newWidth * 3];
		memcpy(bmap->data[i], source->data[source->bmpInfoHeader.Height - 1 - i - y_pos] + x_pos * 3, newWidth * 3);
	}

	return bmap;
}

bool bmpFileReader(char* fileName, Bitmap*& bmp) {
	FILE* file_input = fopen(fileName, "rb");
	if (!file_input) return 0;
	else {
		bmp = new Bitmap;
		std::cout << "File checker: opening file is successful.\n";
		fread(&bmp->Signature, 2, 1, file_input);
		bmp->Signature[2] = '\0';
		if (strcmp(bmp->Signature, "BM")) {
			std::cout << "File checker: File format is not supported.\n";
			fclose(file_input); 
			return 0;
		}
		std::cout << "File checker: file checking is done.\n";
	}
	fread(&bmp->bmpFileHeader, 1, 12, file_input); fread(&bmp->bmpInfoHeader, 1, 40, file_input);
	bmp->bytes_per_row = ((bmp->bmpInfoHeader.BitsPerPixel * bmp->bmpInfoHeader.Width + 31) / 32 ) * 4;
	bmp->data = new int8_t*[bmp->bmpInfoHeader.Height];
	std::cout << "Loading image data...\n";
	for (int i = 0; i < bmp->bmpInfoHeader.Height; i++) {
		bmp->data[i] = new int8_t[bmp->bytes_per_row];
		fread(bmp->data[i], bmp->bytes_per_row, 1, file_input);
	}
	std::cout << "Data loaded. \n";
	fclose(file_input);
	return 1;
}

void bmpFreeMemory(Bitmap* &bmp) {
	for (int i = 0; i < bmp->bmpInfoHeader.Height; i++) {
		delete[] bmp->data[i];	
	}
	delete[] bmp->data;
	delete bmp;
}

char* fileNameGenerator(std::string fileName, int num) {
	fileName += std::to_string(num) + ".bmp";
	char* cFileName = new char[fileName.size() + 1];
	cFileName[fileName.size()] = '\0';
	strcpy(cFileName, fileName.c_str());
	return cFileName;
}

char* fileBaseName(char* filename) {
	int n = strlen(filename);
	char* s = new char[n + 1];
	int i = 0;
	for (; i < n && filename[i] != '.'; ++i) {
		s += filename[i]; 
	}
	s[i] = '\0';
	return s;
}


bool bmpSplit(char* fileName, int h, int w) {
	Bitmap* source;
	if (!bmpFileReader(fileName, source)) return 0;
	int newWidth = source->bmpInfoHeader.Width / h, newHeight = source->bmpInfoHeader.Height / w;
	int cnt = 1;
	char* basename = fileBaseName(fileName);
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			char* oFileName = fileNameGenerator("", cnt++);
			Bitmap* piece = bmpCrop(source, j * newWidth, i * newHeight, newWidth, newHeight);
			bmpFileWriter(oFileName, piece);
			bmpFreeMemory(piece);
			delete[] oFileName;
		}
	}
	delete[] basename;
	bmpFreeMemory(source);
	return 1;
}
