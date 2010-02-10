#include "dbmp.h"

int main(void) {

    srand(time(NULL));
    
    char *img = new_image_buffer(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    
    char colour;
    int index;
    for (int j = 0; j < DEFAULT_HEIGHT; ++j) {
        for (int i = 0; i < DEFAULT_WIDTH; ++i) {
            colour = 127 - 127 * cos(0.1 * sqrt(i * i + j * j));
            index = j * DEFAULT_WIDTH + i;
            index *= BYPP;
            img[index] = colour;
            img[index + 1] = colour;
            img[index + 2] = colour;
        }
    }
    
    write_bmp(img, DEFAULT_WIDTH, DEFAULT_HEIGHT, "test.bmp");
    destroy_image_buffer(img);

	return 0;
}
			
	
	
