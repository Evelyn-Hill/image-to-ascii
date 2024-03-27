#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main() {

  FILE *pF = fopen("output.txt", "w");

  int width, height, channels;

  unsigned char *image = stbi_load("amogus.png", &width, &height, &channels, 0);

  if (image == NULL) {
    printf("Error loading image!\n");
  }

  printf("Loaded image with width: %d height: %d and channels: %d\n", width,
         height, channels);

  size_t image_size = width * height * channels;
  int i;
  for (unsigned char *p = image; p != image + image_size; p += channels) {
    int brightness = 0;

    brightness = *p + *(p + 1) + *(p + 2) / 3.0;

    if (brightness < 85) {
      fprintf(pF, "@");
    } else if (brightness > 85 && brightness < 170) {
      fprintf(pF, "$");
    } else if (brightness > 170 && brightness < 255) {
      fprintf(pF, "*");
    } else if (brightness > 255 && brightness < 340) {
      fprintf(pF, "/");
    } else if (brightness > 340 && brightness < 425) {
      fprintf(pF, "^");
    } else if (brightness > 425 && brightness < 510) {
      fprintf(pF, ".");
    } else if (brightness > 510) {
      fprintf(pF, " ");
    }
    i++;
    if (i >= width) {
      fprintf(pF, "\n");
      i = 0;
    }
  }

  printf("Image data written to file.");

  stbi_image_free(image);
  fclose(pF);

  return 0;
}
