#include "helpers.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int get_box(int height, int width, int pos_y, int pos_x,
            RGBTRIPLE image[height][width], RGBTRIPLE box[9]);

RGBTRIPLE get_blurred_pixel(RGBTRIPLE box[9], int box_size);

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
  RGBTRIPLE blurTarget[height][width];

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      RGBTRIPLE box[9];
      int box_size = get_box(height, width, i, j, image, box);
      blurTarget[i][j] = get_blurred_pixel(box, box_size);
    }
  }

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      image[i][j] = blurTarget[i][j];
    }
  }

  return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width]) {
  // Do the edges
  //  thing
  return;
}

int get_box(int height, int width, int pos_y, int pos_x,
            RGBTRIPLE image[height][width], RGBTRIPLE box[9]) {
  int box_size = 0;
  for (int i = -1; i < 2; i++) {
    if (pos_y + (i) < 0 || pos_y + (i) >= height) {
      continue;
    }
    for (int j = -1; j < 2; j++) {
      if (pos_x + j < 0 || pos_x + j >= width) {
        continue;
      }
      box[box_size] = image[pos_y + i][pos_x + j];
      box_size++;
    }
  }

  return box_size;
}

RGBTRIPLE get_blurred_pixel(RGBTRIPLE box[9], int box_size) {
  RGBTRIPLE pixel;

  int redCount = 0;
  int greenCount = 0;
  int blueCount = 0;

  for (int i = 0; i < box_size; i++) {
    redCount += box[i].rgbtRed;
    blueCount += box[i].rgbtBlue;
    greenCount += box[i].rgbtGreen;
  }

  pixel.rgbtRed = round(redCount / (box_size * 1.0));
  pixel.rgbtGreen = round(greenCount / (box_size * 1.0));
  pixel.rgbtBlue = round(blueCount / (box_size * 1.0));

  return pixel;
}
