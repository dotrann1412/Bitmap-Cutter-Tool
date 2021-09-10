#include "header.h"

void handle(int argsCount, char** argsVariable){ //main processing
	int w = 1, h = 1;
	bool flag = 1;
	if(argsCount == 6){
		if(checkNum(argsVariable[3]) && checkNum(argsVariable[5])){
			if((string)argsVariable[2] == "-h" && (string)argsVariable[4] == "-w") w = parseInt(argsVariable[3]), h = parseInt(argsVariable[5]);
			else if((string)argsVariable[4] == "-h" && (string)argsVariable[2] == "-w") w = parseInt(argsVariable[5]), h = parseInt(argsVariable[3]);
			else flag = 0;
		}
		else flag = 0;
	}
	else if(argsCount == 4){
		if(checkNum(argsVariable[3])){
			if((string)argsVariable[2] == "-h") h = parseInt(argsVariable[3]);
			else if((string)argsVariable[2] == "-w") w = parseInt(argsVariable[3]);
			else flag = 0;
		}
		else flag = 0;
	}
	else flag = 0;
	if(!flag) cout << "Syntax Error!" << '\n';
	else {
		bool (*func)(char*, int w, int h) = bmpSplit;
		if(func(argsVariable[1], w, h)) cout << "successful!" << '\n';
		else cout << "Failed!" << '\n';
	}
}

int parseInt(char s[]){
	int res = 0;
	for(int i = 0; i < strlen(s); i++)
		(res *= 10) += s[i] - '0';
	return res;
}

bool checkNum(char s[]){
	for(int i = 0; i < strlen(s); i++) {
		if(s[i] > '9' && s[i] < '0') return 0;
	}
	return 1;
}

bool bmpSplit(char* fileName, int h, int w){
	Bitmap source;
	if(!bmpFileReader(fileName, source)) return 0;
	int newWidth = source.bmpInfoHeader.Width / h, newHeight = source.bmpInfoHeader.Height / w;
	int cnt = 1;
	for(int i = 0; i < w; i++){
		for(int j = 0; j < h; j++){
			bmpFileWriter(fileNameGenerator("", cnt++), bmpCrop(source, j * newWidth, i * newHeight, newWidth, newHeight));
		}
	}
	return 1;
}

char* fileNameGenerator(string fileName, int num){
	fileName += to_string(num) + ".bmp" + "\0";
	char* cFileName = new char[fileName.size()];
	strcpy(cFileName, fileName.c_str());
	return cFileName;
}

void bmpFileWriter(char* filePath, Bitmap bmp){
	FILE* file_output = fopen(filePath, "wb");
	fwrite(&bmp.Signature, 2 , 1, file_output);
	fwrite(&bmp.bmpFileHeader, 12, 1, file_output);
	fwrite(&bmp.bmpInfoHeader, 40, 1, file_output);
	int32_t bytes_per_row = ((bmp.bmpInfoHeader.BitsPerPixel * bmp.bmpInfoHeader.Width + 31) / 32 ) * 4;
	for(int i = bmp.bmpInfoHeader.Height - 1; i >= 0; i--){
		fwrite(bmp.data[i], 1, bytes_per_row, file_output);
	}
	fclose(file_output);
}

Bitmap bmpCrop(Bitmap source, int x_pos, int y_pos, int newWidth, int newHeight){
	Bitmap bmap;
	strcpy(bmap.Signature, source.Signature);
	bmap.bmpFileHeader = source.bmpFileHeader;
	bmap.bmpInfoHeader = source.bmpInfoHeader;
	bmap.bmpInfoHeader.Height = newHeight;
	bmap.bmpInfoHeader.Width = newWidth;
	bmap.data = new int8_t*[newHeight];
	int bytes_per_pixel = source.bmpInfoHeader.BitsPerPixel / 8;
	for(int i = 0; i < newHeight; i++){
		bmap.data[i] = new int8_t[newWidth * bytes_per_pixel];
		bmap.data[i] = source.data[source.bmpInfoHeader.Height - 1 - i - y_pos] + x_pos * bytes_per_pixel;
	}
	return bmap;
}

bool bmpFileReader(char* fileName, Bitmap& bmp){
	FILE* file_input = fopen(fileName, "rb");
	if(!file_input) return 0;
	else{
		cout << "File checker: opening file is successful.\n";
		fread(&bmp.Signature, 2, 1, file_input);
		if(!strcmp(bmp.Signature, "BM")){
			cout << "File checker: File format is not supported.\n";
			fclose(file_input); return 0;
		}
		cout << "File checker: file checking is done.\n";
	}
	fread(&bmp.bmpFileHeader, 1, 12, file_input); fread(&bmp.bmpInfoHeader, 1, 40, file_input);
	bmp.bytes_per_row = ((bmp.bmpInfoHeader.BitsPerPixel * bmp.bmpInfoHeader.Width + 31) / 32 ) * 4;
	bmp.data = new int8_t*[bmp.bmpInfoHeader.Height];
	cout << "Loading image data...\n";
	for(int i = 0; i < bmp.bmpInfoHeader.Height; i++){
		bmp.data[i] = new int8_t[bmp.bytes_per_row];
		fread(bmp.data[i], bmp.bytes_per_row, 1, file_input);
	}
	cout << "Data loaded. \n";
	fclose(file_input);
	return 1;
}
