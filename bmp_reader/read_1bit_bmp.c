#include <stdio.h>
#include <stdlib.h>
#include "read_1bit_bmp.h"

unsigned char* read_dib_header(FILE *fp)
{
    unsigned char dib_header_size[4]; //the size of the dib header takes 4 bytes
    fread(dib_header_size, 1, 4, fp);
    int dib_header_size_as_int = lsb_to_int(dib_header_size) - 4; //substracting 4 bytes that we read already for the dib header size
    unsigned char *dib_header;
    dib_header = (unsigned char *)malloc(dib_header_size_as_int * sizeof(unsigned char));
    fread(dib_header, 1, dib_header_size_as_int, fp); //this is the dib header without the size

    return dib_header;
}

int extract_value_from_byte_array(unsigned char* byte_array, int start_position, int length) {
    unsigned char slice[length];
    for(int i = 0; i < length; i++) {
        slice[i] = byte_array[start_position + i];
    }
    return lsb_to_int(slice);
}

void extract_dib_header_data(DibHeader *dib_header, unsigned char *dib_header_data)
{
    dib_header->pixel_array_size = extract_value_from_byte_array(dib_header_data, 16, 4);
    printf("byte array size=%d\n", dib_header->pixel_array_size);

    dib_header->img_width = extract_value_from_byte_array(dib_header_data, 0, 4);
    printf("width=%d\n", dib_header->img_width);

    dib_header->img_height = extract_value_from_byte_array(dib_header_data, 4, 4);
    printf("height=%d\n", dib_header->img_height);
}

int lsb_to_int(unsigned char* lsb_array)
{
    int result;
    result = ((int)lsb_array[0]) + (((int)lsb_array[1]) << 8) +
             (((int)lsb_array[2]) << 16) + (((int)lsb_array[3]) << 24);
    return result;
}

//[40, 00, 00, 00, 80, 00, 00, 00], 8, 2, 2
void print_byte_array_as_ascii_art(unsigned char *byte_array, DibHeader* dib_header)
{
    print_byte_array(byte_array, dib_header->pixel_array_size);

    int width = dib_header->img_width;
    int height = dib_header->img_height;
    dib_header->pixel_array_size -= 2; //2 btyes padding at the end of the byte array
    int scan_line_size_in_bytes = dib_header->pixel_array_size / dib_header->img_height;
    char pixel_array[height][width];
    //0000 0000 0000 1100 1100 0111 0000 000
    //0000 0000 0000 0111 1111 0000 0000 0000 0000 00000 0000 0000

    //63 254 0 0 63 254 0 0 0 0
    //00111111 11111110 00000000 00000000 00111111 11111110  00000000 00000000 00000000 00000000
    for(int row = 0; row < height; row++) {
        for(int col = 0; col < width; col++) {
            int current_pixel = extract_pixel(byte_array, scan_line_size_in_bytes, row, col);
            if (current_pixel == 0) {
                pixel_array[row][col] = '`';
            }
            else {
                pixel_array[row][col] = '#';
            }
        }
    }

    print_pixel_array(height, width, pixel_array);
}

void print_byte_array(unsigned char *byte_array, int byte_array_size)
{
    for(int i = 0; i < byte_array_size; i++) {
        printf("%2.2X ", byte_array[i]);
    }
    printf("\n");
}

void print_pixel_array(int rows, int cols, char (*pixel_array)[cols])
{
    for(int row = rows - 1; row >= 0; row--) {
        for(int col = 0; col < cols; col++) {
            printf("%c ", pixel_array[row][col]);
        }
        printf("\n");
    }
}

int extract_pixel(unsigned char* byte_array, int scan_line_size_in_bytes,
                  int row, int col) {
    //The bits representing the bitmap pixels are packed in rows.
    //The size of each row is rounded up to a multiple of 4 bytes (a 32-bit DWORD) by padding.
    int byte_array_index;
    if (row == 0) {
        byte_array_index = col / 8;
    }
    else {
        byte_array_index = (scan_line_size_in_bytes * row) + (col/8);
    }
    unsigned char current_byte_element = byte_array[byte_array_index]; // the calculation will get fucked up if the bmp is not 1 bit
    unsigned char pixel_mask = 1 << (7 - (col % 8));
    if((current_byte_element & pixel_mask) == 0) {
        return 0;
    }
    else {
        return 1;
    }
}
