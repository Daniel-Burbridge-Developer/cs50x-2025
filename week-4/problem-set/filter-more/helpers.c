#include "helpers.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int rgbtBlue;
  int rgbtGreen;
  int rgbtRed;
} __attribute__((__packed__)) INTTRIPLE;

int get_box(int height, int width, int pos_y, int pos_x,
            RGBTRIPLE image[height][width], RGBTRIPLE box[9]);
int get_box_with_black_pixels(int height, int width, int pos_y, int pos_x,
                              RGBTRIPLE image[height][width], RGBTRIPLE box[9]);
void multiply_box_by_matrix(RGBTRIPLE box[9], int matrix[9],
                            INTTRIPLE matrixResult[9]);

RGBTRIPLE get_edged_pixel(INTTRIPLE m1[9], INTTRIPLE m2[9]);

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
  int gx[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
  int gy[9] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};

  RGBTRIPLE edgeTarget[height][width];

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      RGBTRIPLE box[9];
      INTTRIPLE gxResult[9];
      INTTRIPLE gyResult[9];
      int box_size = get_box_with_black_pixels(height, width, i, j, image, box);
      multiply_box_by_matrix(box, gx, gxResult);
      multiply_box_by_matrix(box, gy, gyResult);
      edgeTarget[i][j] = get_edged_pixel(gxResult, gyResult);
    }
  }

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      image[i][j] = edgeTarget[i][j];
    }
  }

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

int get_box_with_black_pixels(int height, int width, int pos_y, int pos_x,
                              RGBTRIPLE image[height][width],
                              RGBTRIPLE box[9]) {
  int box_size = 0;
  RGBTRIPLE blackPixel;
  blackPixel.rgbtRed = 0;
  blackPixel.rgbtGreen = 0;
  blackPixel.rgbtBlue = 0;
  for (int i = -1; i < 2; i++) {
    for (int j = -1; j < 2; j++) {
      if (pos_y + (i) < 0 || pos_y + (i) >= height) {
        box[box_size] = blackPixel;
        box_size++;
        continue;
      }
      if (pos_x + j < 0 || pos_x + j >= width) {
        box[box_size] = blackPixel;
        box_size++;
        continue;
      }
      box[box_size] = image[pos_y + i][pos_x + j];
      box_size++;
    }
  }

  return box_size;
}

void multiply_box_by_matrix(RGBTRIPLE box[9], int matrix[9],
                            INTTRIPLE matrixResult[9]) {
  for (int i = 0; i < 9; i++) {
    matrixResult[i].rgbtRed = box[i].rgbtRed * matrix[i];
    matrixResult[i].rgbtGreen = box[i].rgbtGreen * matrix[i];
    matrixResult[i].rgbtBlue = box[i].rgbtBlue * matrix[i];
  }
  return;
}

RGBTRIPLE get_edged_pixel(INTTRIPLE m1[9], INTTRIPLE m2[9]) {
  RGBTRIPLE pixel;
  INTTRIPLE intPixel;

  int gxRed = 0;
  int gxGreen = 0;
  int gxBlue = 0;

  int gyRed = 0;
  int gyGreen = 0;
  int gyBlue = 0;

  for (int i = 0; i < 9; i++) {
    gxRed += m1[i].rgbtRed;
    gyRed += m2[i].rgbtRed;

    gxGreen += m1[i].rgbtGreen;
    gyGreen += m2[i].rgbtGreen;

    gxBlue += m1[i].rgbtBlue;
    gyBlue += m2[i].rgbtBlue;
  }

  gxRed = (gxRed * gxRed);
  gyRed = (gyRed * gyRed);

  gxGreen = (gxGreen * gxGreen);
  gyGreen = (gyGreen * gyGreen);

  gxBlue = (gxBlue * gxBlue);
  gyBlue = (gyBlue * gyBlue);

  intPixel.rgbtRed = round(sqrt(gxRed + gyRed));
  intPixel.rgbtGreen = round(sqrt(gxGreen + gyGreen));
  intPixel.rgbtBlue = round(sqrt(gxBlue + gyBlue));

  if (intPixel.rgbtRed > 255) {
    intPixel.rgbtRed = 255;
  }

  if (intPixel.rgbtGreen > 255) {
    intPixel.rgbtGreen = 255;
  }

  if (intPixel.rgbtBlue > 255) {
    intPixel.rgbtBlue = 255;
  }

  pixel.rgbtRed = intPixel.rgbtRed;
  pixel.rgbtGreen = intPixel.rgbtGreen;
  pixel.rgbtBlue = intPixel.rgbtBlue;

  return pixel;
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
