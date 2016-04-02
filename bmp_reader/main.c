#include <stdio.h>
#include <stdlib.h>
#include "read_1bit_bmp.h"

#define BMP_HEADER_SIZE 14

int main() {
    FILE *fp = fopen("test2.bmp", "rb");
    unsigned char bmp_header[BMP_HEADER_SIZE]; //describe why unsigned char
    fread(bmp_header, 1, BMP_HEADER_SIZE, fp);

    unsigned char dib_header_size[4]; //the size of the dib header takes 4 bytes
    fread(dib_header_size, 1, 4, fp);

    int dib_header_size_as_int = lsb_to_int(dib_header_size) - 4; //substracting 4 bytes that we read already for the dib header size
    //printf("%d\n", dib_header_size_as_int);
    unsigned char *dib_header;
    dib_header = (unsigned char *)malloc(dib_header_size_as_int * sizeof(unsigned char));

    fread(dib_header, 1, dib_header_size_as_int, fp); //this is the dib header without the size of it

    unsigned char *color_pallette;
    color_pallette = (unsigned char *)malloc(8 * sizeof(unsigned char)); //magic number 8 should be fixed
    fread(color_pallette, 1, 8, fp);

    unsigned char byte_array_size[4];
    int i;
    int byte_array_size_start_position = 16;
    for(i = 0; i < 4; i++) {
        byte_array_size[i] = dib_header[byte_array_size_start_position + i];
    }
    int byte_array_size_as_int = lsb_to_int(byte_array_size);
    printf("byte array size=%d\n", byte_array_size_as_int);
    unsigned char* byte_array = (unsigned char *)malloc(sizeof(int)*byte_array_size_as_int);
    fread(byte_array, 1, byte_array_size_as_int, fp);

    unsigned char bmp_width[4];
    int bmp_width_start_position = 0;
    for(i = 0; i < 4; i++) {
        bmp_width[i] = dib_header[bmp_width_start_position + i];
    }
    int bmp_width_as_int = lsb_to_int(bmp_width);
    printf("width=%d\n", bmp_width_as_int);

    unsigned char bmp_height[4];
    int bmp_height_start_position = 4;
    for(i = 0; i < 4; i++) {
        bmp_height[i] = dib_header[bmp_height_start_position + i];
    }
    int bmp_height_as_int = lsb_to_int(bmp_height);
    printf("height=%d\n", bmp_height_as_int);

    fclose(fp);

    print_byte_array_as_ascii_art(byte_array, byte_array_size_as_int, bmp_width_as_int, bmp_height_as_int);

    return 0;
}
