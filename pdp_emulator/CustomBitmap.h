#pragma once
class CustomBitmap
{
private:
	int height;
	int width;
	unsigned char *buffer;
public:
	CustomBitmap(int height, int width, unsigned char *buffer) {
		this->buffer = buffer;
		this->width = width;
		this->height = height;
	}
	CustomBitmap();
	int getHeight(){ return this->height; };
	int getWidth(){ return this->width; };
	void setWidth(int width){ this->width = width; };
	unsigned char * getBuffer(){ return this->buffer; };
	~CustomBitmap(){ delete[] buffer; };
};

