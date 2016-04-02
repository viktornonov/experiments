#ifndef READ_1BIT_BMP_H_
#define READ_1BIT_BMP_H_

int lsb_to_int(unsigned char*);

void print_byte_array_as_ascii_art(unsigned char*, int, int, int);

int get_scan_line_size_in_bytes(int, int);

void print_byte_array(unsigned char *, int);

void print_pixel_array(int, int, char (*pixel_array)[]);

int extract_pixel(unsigned char*, int, int, int);

#endif  // READ_1BIT_BMP_H_

