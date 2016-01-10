#pragma once
class BITMAP
{
private:
	int height;
	int width;
	unsigned char *buffer;
public:
	BITMAP(int height, int width, unsigned char *buffer) {
		this->buffer = buffer;
		this->width = width;
		this->height = height;
	}
	BITMAP();
	int getHeight(){ return this->height; };
	int getWidth(){ return this->width; };
	unsigned char * getBuffer(){ return this->buffer; };
	~BITMAP(){ delete[] buffer; };
};

