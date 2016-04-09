#include <stdio.h>
#include <stdlib.h>
#include "read_1bit_bmp.h"

#define BMP_HEADER_SIZE 14

int lsb_to_int(unsigned char* lsb_array) {
    int result;
    result = ((int)lsb_array[0]) + (((int)lsb_array[1]) << 8) +
             (((int)lsb_array[2]) << 16) + (((int)lsb_array[3]) << 24);
    return result;
}

//[40, 00, 00, 00, 80, 00, 00, 00], 8, 2, 2
void print_byte_array_as_ascii_art(unsigned char *byte_array, DibHeader* dib_header) {
    print_byte_array(byte_array, dib_header->pixel_array_size);

    int width = dib_header->img_width;
    int height = dib_header->img_height;
    dib_header->pixel_array_size -= 2; //2 btyes padding at the end of the byte array
    int scan_line_size_in_bytes = get_scan_line_size_in_bytes(dib_header->pixel_array_size,
                                                              height);
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

int get_scan_line_size_in_bytes(int byte_array_size, int height)
{
    //The bits representing the bitmap pixels are packed in rows.
    //The size of each row is rounded up to a multiple of 4 bytes (a 32-bit DWORD) by padding.
    //For images with height > 1, multiple padded rows are stored consecutively, forming a Pixel Array.
    int padding = 0;
    padding = (byte_array_size / height) % 4;

    int scan_line_size_in_bytes = 0;
    if(padding == 0) {
        scan_line_size_in_bytes = byte_array_size / height;
    }
    else {
        scan_line_size_in_bytes = byte_array_size / height + padding; //not tested
    }

    //printf("space for pixels=%d\n", scan_line_size_in_bytes);

    scan_line_size_in_bytes += padding; //add the padding
    //printf("scan line size in bytes=%d, padding=%d\n", scan_line_size_in_bytes, padding);
    return scan_line_size_in_bytes;
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
    int byte_array_index;
    if (row == 0) {
        byte_array_index = col / 8;
    }
    else {
        byte_array_index = (scan_line_size_in_bytes * row) + (col/8);
    }
    unsigned char current_byte_element = byte_array[byte_array_index]; // the calculation will get fucked up if the bmp is not 1 bit
            //printf("%d\n", scan_line_size_in_bytes * row);
    //0000 0000 8 bits
    //1 << 7 - col 0100 0000
    /*
    0 % 7 = 0
    1 % 7 = 1
    2 % 7 = 2
    ...
    7 % 7 = 0
    8 % 7 = 1
    */
    unsigned char pixel_mask = 1 << (7 - (col % 8));
    //printf("current %d index in byte array [%d], [%d][%d] - %d - %d = %c\n", current_byte_element, byte_array_index, row, col, pixel_mask, current_byte_element & pixel_mask, ((current_byte_element & pixel_mask) == 0 ? '`' : '#'));
    //mask for col 0 => 1000 0000
    //    byte => 0100 0000
    //mask for col 1 => 0100 0000
    //    byte => 0100 0000
    if((current_byte_element & pixel_mask) == 0) {
        return 0;
    }
    else {
        return 1;
    }
}
