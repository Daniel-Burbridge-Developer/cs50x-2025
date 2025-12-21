// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;
typedef uint8_t BYTE;

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
  // file

  BYTE b;

  int count = 0;
  while (fread(&b, sizeof(b), 1, input) != 0) {
    count++;
    if (count < HEADER_SIZE) {
      fwrite(&b, sizeof(b), 1, output);
    } else {
      float c = b * factor;
      fwrite(&c, sizeof(b), 1, output);
    }
  }

  // Close files
  fclose(input);
  fclose(output);
}
