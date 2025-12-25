#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[]) {
  const int BLOCK_SIZE = 512;

  if (argc != 2) {
    printf("Usage: ./filter infile\n");
    return 1;
  }

  char *infile = argv[1];

  FILE *inptr = fopen(infile, "r");

  if (inptr == NULL) {
    printf("Could not open %s.\n", infile);
    return 1;
  }

  BYTE block[512];
  int jpg_count = 0;

  char fileName[16];
  sprintf(fileName, "%03d.jpg", jpg_count);

  FILE *outptr = NULL;

  while (fread(block, 1, BLOCK_SIZE, inptr) != 0) {
    if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff &&
        (block[3] & 0xf0) == 0xe0) {
      if (outptr == NULL) {
        outptr = fopen(fileName, "w");
      } else {
        fclose(outptr);
        jpg_count++;
        sprintf(fileName, "%03d.jpg", jpg_count);
        outptr = fopen(fileName, "w");
      }
    }
    if (outptr != NULL) {
      fwrite(&block, BLOCK_SIZE, 1, outptr);
    }
  }

  fclose(outptr);
  fclose(inptr);

  return 0;
}
