#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fp;
    long fileSize;
    fp = fopen("test.bmp", "rb");
    fseek(fp, 0, SEEK_END);
    fileSize = ftell(fp);
    rewind(fp);
    unsigned char * buffer;
    buffer = (unsigned char *)malloc(sizeof(unsigned char) * fileSize);
    fread(buffer, 1, fileSize, fp);

    unsigned char current = buffer[0];
    int count = 1;

    unsigned char *output = (unsigned char *)malloc(sizeof(unsigned char) * fileSize);
    int output_index = 0;
    for (int i = 1; i < fileSize; i++) {
        printf("%x ", current);
        if (current == buffer[i]) {
            count++;
        }
        else {
            if (count > 1) {
                output[output_index++] = current;
                output[output_index++] = current;
                output[output_index++] = count;
            }
            else {
                output[output_index++] = current;
            }
            count = 1;
        }
        current = buffer[i];
    }

    fclose(fp);

    printf("\n\n");
    printf("%d\n", output_index);
    for (int i = 0; i < output_index; i++) {
        printf("%x ", output[i]);
    }

    return 0;
}
