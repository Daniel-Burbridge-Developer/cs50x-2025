// Modifies the volume of an audio file

#include <cs50.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;
typedef uint8_t BYTE;
typedef int16_t TWOBYTE;

int main(int argc, char *argv[]) {
  // Check command-line arguments
  if (argc != 4) {
    printf("Usage: ./volume input.wav output.wav factor\n");
    return 1;
  }

  // Open files and determine scaling factor
  FILE *input = fopen(argv[1], "r");
  if (input == NULL) {
    printf("Could not open file.\n");
    return 1;
  }

  FILE *output = fopen(argv[2], "w");
  if (output == NULL) {
    printf("Could not open file.\n");
    return 1;
  }

  float factor = atof(argv[3]);

  // TODO: Read samples from input file and write updated data to output

  BYTE *header = malloc(sizeof(BYTE) * 44);
  fread(header, sizeof(BYTE), 44, input);
  fwrite(header, sizeof(BYTE), 44, output);

  fclose(output);

  output = fopen(argv[2], "a");
  if (output == NULL) {
    printf("Could not open file.\n");
    return 1;
  }

  //   printf("header %s\n", header);

  //   BYTE b;
  TWOBYTE tb;
  TWOBYTE new_val;
  while (fread(&tb, sizeof(tb), 1, input)) {
    tb = tb * factor;
    fwrite(&tb, sizeof(tb), 1, output);
    // printf("tb: %f \n", (float)tb * factor);
  }

  free(header);
  // Close files
  fclose(input);
  fclose(output);
}
