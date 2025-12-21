#include "helpers.h"

#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]) {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      BYTE red = image[i][j].rgbtRed;
      BYTE green = image[i][j].rgbtGreen;
      BYTE blue = image[i][j].rgbtBlue;

      int average = round((red + blue + green) / 3.0);

      image[i][j].rgbtRed = average;
      image[i][j].rgbtGreen = average;
      image[i][j].rgbtBlue = average;
    }
  }
  return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width]) {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      BYTE red = image[i][j].rgbtRed;
      BYTE green = image[i][j].rgbtGreen;
      BYTE blue = image[i][j].rgbtBlue;

      int sepiaRed = round(.393 * red + .769 * green + .189 * blue);
      int sepiaGreen = round(.349 * red + .686 * green + .168 * blue);
      int sepiaBlue = round(.272 * red + .534 * green + .131 * blue);

      if (sepiaRed > 255) {
        sepiaRed = 255;
      }

      if (sepiaGreen > 255) {
        sepiaGreen = 255;
      }

      if (sepiaBlue > 255) {
        sepiaBlue = 255;
      }

      image[i][j].rgbtRed = sepiaRed;
      image[i][j].rgbtGreen = sepiaGreen;
      image[i][j].rgbtBlue = sepiaBlue;
    }
  }
  return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width]) {
  RGBTRIPLE reversed[height][width];
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      RGBTRIPLE pixel = image[i][j];
      reversed[i][width - (j + 1)] = pixel;

      //   BYTE red = image[i][j].rgbtRed;
      //   BYTE green = image[i][j].rgbtGreen;
      //   BYTE blue = image[i][j].rgbtBlue;

      //   BYTE rRed = reversed[i][j].rgbtRed;
      //   BYTE rGreen = reversed[i][j].rgbtGreen;
      //   BYTE rBlue = reversed[i][j].rgbtBlue;

      //   printf(
      //       "Image Red: %i\nImage Green: %i\n Image Blue: %i\n Reversed Red:
      //       "
      //       "%i\n Reversed Green: %i\n Reversed Blue: %i\n",
      //       red, green, blue, rRed, rGreen, rBlue);
    }
  }

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      image[i][j].rgbtRed = reversed[i][j].rgbtRed;
      image[i][j].rgbtGreen = reversed[i][j].rgbtGreen;
      image[i][j].rgbtBlue = reversed[i][j].rgbtBlue;
    }
  }
  return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width]) { return; }
