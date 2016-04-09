#ifndef READ_1BIT_BMP_H_
#define READ_1BIT_BMP_H_

struct DibHeader {
    int size;
    int img_width;
    int img_height;
    int pixel_array_size;
};

typedef struct DibHeader DibHeader;

int lsb_to_int(unsigned char*);

void print_byte_array_as_ascii_art(unsigned char*, DibHeader *);

int get_scan_line_size_in_bytes(int, int);

void print_byte_array(unsigned char *, int);

void print_pixel_array(int, int, char (*pixel_array)[]);

int extract_pixel(unsigned char*, int, int, int);

#endif  // READ_1BIT_BMP_H_

