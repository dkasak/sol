#include "dbmp.h"

int main(void) {
    bmp_meta_t meta;
    unsigned char* image = read_bmp("test.bmp", &meta);
    if (image) {
        write_bmp(image, meta.width, meta.height, "test-copy.bmp");
    }

    return 0;
}

