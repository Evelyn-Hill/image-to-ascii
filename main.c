/*
 * Author: Evelyn Plum Hill
 * Date: 2020-03-24
 * Purpose: To convert a png image to "Ascii art".
 *
 */

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize2.h"

void ConvertToAscii(char path[60]) {

  // Open output file.
  FILE *pF = fopen("output.txt", "w");

  int width, height, channels;

  // Get image data.
  unsigned char *image = stbi_load(path, &width, &height, &channels, 0);

  printf("Loaded image with width: %d height: %d and channels: %d\n", width,
         height, channels);

  size_t image_size = width * height * channels;

  // Need to half the image size for easier viewing.
  // Defining the memory allocation for the new image.

  int newWidth = width;
  int newHeight = height;
  int newChans = 3;

  printf("Resizing...\n");
  while (newWidth > 300) {
    newWidth = newWidth >> 1;
    newHeight = newHeight >> 1;
  }

  unsigned char *output_img = malloc(newWidth * newHeight * newChans);
  stbir_resize_uint8_srgb(image, width, height, 0, output_img, newWidth,
                          newHeight, 0, newChans);

  // Writing resized image to disk.
  stbi_write_jpg("temp.jpg", newWidth, newHeight, newChans, output_img, 100);

  stbi_image_free(image);

  // Loading the resized image into memory.
  unsigned char *resized_image =
      stbi_load("temp.jpg", &width, &height, &channels, 0);

  size_t resized_image_size = width * height * channels;

  printf("Loaded resized image with size %dpx by %dpx and %d channels\n", width,
         height, channels);

  // Iterator to keep track of new lines.
  int i;

  // Loop through all of the image data, convert it to black and white, and
  // print character based on brightness.

  for (unsigned char *p = resized_image;
       p != resized_image + resized_image_size; p += channels) {

    int brightness = 0;

    // Black and white conversion
    brightness = *p + *(p + 1) + *(p + 2) / 3.0;

    const char *characters[] = {"@", "&", "*", "/", "^", ".", " "};
    const int brightnessThresholds[] = {85, 170, 255, 340, 425, 510, 596};

    // Check brightness. Brightness level is from 0 - 595.
    for (int j = 0; j < sizeof(characters) / sizeof(characters[0]); j++) {
      if (brightness <= brightnessThresholds[j]) {
        fprintf(pF, "%s", characters[j]);
        i++;
        break;
      }
    }
    // Insert new line.
    if (i >= width) {
      fprintf(pF, "\n");
      i = 0;
    }
  }

  printf("Image data written to file.\n");

  stbi_image_free(resized_image);
  fclose(pF);

  // Remove temporary scaled down image.
  if (remove("temp.jpg") == 0) {
    printf("Temp file removed!\n");
  }
}

char *StringLower(char *str) {
  unsigned char *p = (unsigned char *)str;

  while (*p) {
    *p = tolower((unsigned char)*p);
    p++;
  }

  return str;
}

int main() {

  char path[60];
  int queryUser = 1;
  int width, height, channels;

  do {
    printf("Please provide an image path, or type \"quit\" to quit. : ");
    scanf("%s", path);

    if (strcmp(StringLower(path), "quit") == 0) {
      break;
    }

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
