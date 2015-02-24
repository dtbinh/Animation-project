#ifndef BMPIMAGE_H
#define BMPIMAGE_H

#include "core.h"

class BMPImage {
public:
	~BMPImage()
	{
		delete[] data;
	}

	bool load(char* filename);

	unsigned long sizeX;
	unsigned long sizeY;
	char *data;

};

#endif