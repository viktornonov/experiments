#include "mystring.h"

int string_length(char *str) {
  int size = 0;
  char c = str[0];
  while(c != '\0') {
    size++;
    c = str[size];
  }
  return size;
}

void string_copy(char *dst, char *src) {
  int dst_length = string_length(dst);
  int src_length = string_length(src);
  int copy_until = 0;
  if (dst_length > src_length) {
    copy_until = dst_length;
  }
  else {
    copy_until = src_length;
  }
  int i = 0;
  for(i = 0; i < copy_until; i++) {
    dst[i] = src[i];
  }

  dst[copy_until] = '\0';
}
