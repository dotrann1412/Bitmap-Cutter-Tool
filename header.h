#include <iostream>
#include <string.h>
#include <iomanip>
#include "bitmap.h" //24 bits format

using namespace std;

void handle(int, char**);
int parseInt(char[]); 
bool checkNum(char[]); 
bool bmpSplit(char*, int, int); 
char* fileNameGenerator(string, int); 
void bmpFileWriter(char*, Bitmap); 
Bitmap bmpCrop(Bitmap, int, int, int, int);
bool bmpFileReader(char*, Bitmap&);