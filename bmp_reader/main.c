#include <stdio.h>
#include <stdlib.h>
#include "read_1bit_bmp.h"

#define BMP_HEADER_SIZE 14

int main()
{
    FILE *fp = fopen("test.bmp", "rb"); //read in binary
    unsigned char bmp_header[BMP_HEADER_SIZE];
    fread(bmp_header, 1, BMP_HEADER_SIZE, fp);

    unsigned char* dib_header_data = read_dib_header(fp);

    unsigned char *color_pallette;
    color_pallette = (unsigned char *)malloc(8 * sizeof(unsigned char)); //magic number 8 should be fixed
    fread(color_pallette, 1, 8, fp);

    DibHeader *dib_header = (DibHeader *)malloc(sizeof(DibHeader));
    extract_dib_header_data(dib_header, dib_header_data);

    unsigned char* pixel_array = (unsigned char *)malloc(sizeof(int) * dib_header->pixel_array_size);
    fread(pixel_array, 1, dib_header->pixel_array_size, fp);

    fclose(fp);

    print_byte_array_as_ascii_art(pixel_array, dib_header);

    return 0;
}
