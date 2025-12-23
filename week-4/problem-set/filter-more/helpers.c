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

      int average = round((red + green + blue

                           ) /
                          3.0);

      image[i][j].rgbtRed = average;
      image[i][j].rgbtGreen = average;
      image[i][j].rgbtBlue = average;
    }
  }
  return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width]) {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width / 2; j++) {
      RGBTRIPLE pixel = image[i][j];
      image[i][j] = image[i][width - (j + 1)];
      image[i][width - (j + 1)] = pixel;
    }
  }
  return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width]) {
  // Do the blur thing
  return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width]) {
  // Do the edges
  //  thing
  return;
}
