#define _CRT_SECURE_NO_WARNINGS



// Hill Cipher Implementation with dynamic memory allocation

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Parameters {

  // How many characters are contained within the message.
  int messageLength;

  int keyColumns;
  int keyRows;
  int keyElements;
  int *keyPtr;

} Parameters;

// Prints the originally entered string.
void printStringArray(char *pt) {
  for (int i = 0; i < strlen(pt); i++) {

    printf("%c", pt[i]);
  }
  printf("\n");
}

int asciiToIndex(char pt) {
  if (pt == ' ') {
    return 27;
  } else {
    return pt - 'a';
  }
}

// Generates an array with the number indexes used in the hill cipher encoding
// stream.
void asciiArrayToIndex(char *src, int *dst) {

  for (int i = 0; i < strlen(src); i++) {

    dst[i] = asciiToIndex(src[i]);
  }
}

void printIndices(Parameters p, int *src) {
  for (int i = 0; i < p.messageLength; i++) {
    printf("%d ", src[i]);
  }
  printf("\n");
}

char indexToAscii(int pt) {
  if (pt == 26) {
    return ' ';
  } else {
    return pt + 'a';
  }
}
// Print the plaintext number value of the letter in the alphabet
// A = 0
// B = 1
// ...
// Z = 25
// ' ' = 26
void printIndexArray(int *pt, Parameters p) {
  for (int i = 0; i < p.messageLength; i++) {
    printf("%c", indexToAscii(pt[i]));
  }
  printf("\n");
}

void convertArrayToAscii(int *src, char *dst) {

  for (int i = 0; i < strlen(dst); i++) {
    dst[i] = indexToAscii(src[i]);
  }
}

// Conducts the actual encoding processes given the correct values.
void cipherEncode(int *src, int *dst, Parameters p) {

  int keyRows = p.keyRows;
  int keyColumns = p.keyColumns;

  int dstRows = 2;
  int dstColumns = 2;

  for (int i = 0; i < keyRows; i++) {
    for (int j = 0; j < dstColumns; j++) {

      int temp = 0;

      for (int k = 0; k < dstRows; k++) {
        // printf("%d + %d = %d\t", src[i * columns + k], key[i * columns + k],
        // src[i * columns + k] * key[i * columns + k]);
        temp += src[i * keyColumns + k] * p.keyPtr[k * keyColumns + j];
      }

      // temp = temp % 27;
      dst[i * p.keyColumns + j] = temp;
      printf("%d\t", temp);
    }

    printf("\n");
  }
}

int main(int argc, char *argv[]) {

  char *messageArray;
  int *ptIndexArray;
  Parameters p;

  // if user enters a string
  if (argc == 2) {
    int size = strlen(argv[1]);
    messageArray = (char *)malloc(sizeof(char) * size + 1);
    strcpy(messageArray, argv[1]);
  }
  // Default String
  else if (argc == 1) {

    char standard[] =
        "meet me at the usual place at ten rather than eight oclock";

    int size = strlen(standard);
    messageArray = (char *)malloc(sizeof(char) * size + 1);
    strcpy(messageArray, standard);

  }
  // Print Error/Help.
  else {
    printf("Invalid use.\n");
    return 1;
  }

  // Message Length
  p.messageLength = strlen(messageArray);

  // Generate the plaintext number matrix
  ptIndexArray = (int *)malloc(sizeof(int) * p.messageLength);

  // Assign the encoded values for the work to make the cipher.
  asciiArrayToIndex(messageArray, ptIndexArray);

  /* This is part of the actual cipher encoding.
  // int *cipherNums = (int *)malloc(sizeof(int) * numberOfElements);
  // int key[2][2] = {{9, 4}, {5, 7}};
  // cipherEncode(ptNums, cipherNums, key);
   */

  int cipherIndexArray[50];

  /*
   * Hard-coded key at the moment.
   */
  p.keyRows = 2;
  p.keyColumns = 2;

  p.keyElements = 4;

  p.keyPtr = (int *)malloc(sizeof(int) * p.keyElements);

  p.keyPtr[0] = 9;
  p.keyPtr[1] = 4;
  p.keyPtr[2] = 5;
  p.keyPtr[3] = 7;

  printIndices(p, ptIndexArray);

  // printIndexArray(ptIndexArray, p);

  // cipherEncode(ptIndexArray, cipherIndexArray, p);

  // printIndexArray(cipherIndexArray, p);

  // convertArrayToAscii(ptIndexArray, ptCharArray);
  // convertArrayToAscii(cipherIndexArray, messageArray);

  // printStringArray(ptCharArray);
  // printStringArray(messageArray);

  free(messageArray);
  free(ptIndexArray);
  free(p.keyPtr);

  return 0;
}
