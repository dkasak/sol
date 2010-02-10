#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#ifndef DBMP_H
#define DBMP_H

#define DEFAULT_WIDTH			640
#define DEFAULT_HEIGHT			480
#define BPP                      24
#define BYPP                     BPP / sizeof (char)

#define BMP_HEADER_SIZE		sizeof (bmp_magic_t) + sizeof (bmp_header_t)
#define DIB_HEADER_SIZE		sizeof (dib_header_t)

typedef struct {
  unsigned char magic[2];
} bmp_magic_t;
 
typedef struct {
  uint32_t file_size;
  uint16_t reserved1;
  uint16_t reserved2;
  uint32_t bmp_offset;
} bmp_header_t;

typedef struct {
  uint32_t header_size;
  uint32_t width;
  uint32_t height;
  uint16_t nplanes;
  uint16_t bpp;
  uint32_t compress_type;
  uint32_t data_size;
  uint32_t hres;
  uint32_t vres;
  uint32_t ncolours;
  uint32_t ncolours_important;
} dib_header_t;

bool write_bmp(const char *data, unsigned int width, unsigned int height, const char *fname);
char *new_image_buffer(unsigned int width, unsigned int height);
void destroy_image_buffer(char *image);

#endif // DBMP_H
