#include <iostream>
#include <stdio.h>
#include "bitmap.h"

Bitmap::Bitmap(const char* filename)
{
    int i, k;
    FILE* f = fopen(filename, "rb");

    if(f == NULL)
        throw "Argument Exception";

    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

    // extract image height and width from header
    width = *(int*)&info[18];
    height = *(int*)&info[22];

    //std::cout << std::endl;
    //std::cout << "  Name: " << filename << std::endl;
    //std::cout << " Width: " << width << std::endl;
    //std::cout << "Height: " << height << std::endl;

    int row_padded = (width*3 + 3) & (~3);
    unsigned char* data = new unsigned char[row_padded];
    unsigned char tmp;

    pixels = new RGBQUAD*[height];
    //std::cout << "yes" << std::endl;
    for(i = 0; i < height; i++)
    {
        pixels[i] = new RGBQUAD[width];
	//std::cout << "yup" << i << std::endl;
        fread(data, sizeof(unsigned char), row_padded, f);
        for(int j = 0; j < width; j++)
        {
            k = 3 * j;
            // Convert (B, G, R) to (R, G, B)
            //tmp = data[j];
            //data[j] = data[j+2];
            //data[j+2] = tmp;
            pixels[i][j].rgbBlue = (int)data[k];
            pixels[i][j].rgbGreen = (int)data[k+1];
            pixels[i][j].rgbRed = (int)data[k+2];
            
            //std::cout << "R: "<< (int)data[j] << " G: " << (int)data[j+1]<< " B: " << (int)data[j+2]<< std::endl;
        }
    }

    fclose(f);
}

Bitmap::~Bitmap()
{
  int i;

  for (i = 0; i < height; i++)
    delete [] pixels[i];
  delete [] pixels;
}

