#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void ConvertToAscii(char path[60]) {
  // Open output file.
  FILE *pF = fopen("output.txt", "w");

  int width, height, channels;
  // Get image data.
  unsigned char *image = stbi_load(path, &width, &height, &channels, 0);

  printf("Loaded image with width: %d height: %d and channels: %d\n", width,
         height, channels);

  size_t image_size = width * height * channels;

  // Iterator to keep track of new lines.
  int i;
  // Loop through all of the image data, convert it to black and white, and
  // print character based on brightness.
  for (unsigned char *p = image; p != image + image_size; p += channels) {

    int brightness = 0;

    // Black and white conversion
    brightness = *p + *(p + 1) + *(p + 2) / 3.0;

    // Check brightness.
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
    // Insert new line.
    if (i >= width) {
      fprintf(pF, "\n");
      i = 0;
    }
  }

  printf("Image data written to file.\n");

  stbi_image_free(image);
  fclose(pF);
}

int main() {

  char path[60];
  int queryUser = 1;
  int width, height, channels;

  do {
    printf("Please provide an absolute image path.: ");
    scanf("%s", &path);
    if (stbi_info(path, &width, &height, &channels) != 0) {
      queryUser = 0;
      printf("Image found! Converting... \n");
      ConvertToAscii(path);
      break;
    } else {
      printf("Error finding image. Are you sure the path is correct?\n");
    }
  } while ((queryUser = 1));

  return 0;
}
