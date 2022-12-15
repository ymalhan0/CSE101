///////////////////////////////////
// Yukti Malhan
// ymalhan
// 2022 Winter CSE101 pa1
// Lex.c
// Main program for List ADT
////////////////////////////////////

#include "List.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 1024

// using FileIO.c with changes for implementation

int main(int argc, char *argv[]) {
  FILE *in, *out;
  char line[MAX_LEN];

  // check command line for correct number of arguments
  if (argc != 3) {

    printf("Usage: %s <input file> <output file>\n", argv[0]);
    exit(1);
  }

  // open files for reading and writing
  in = fopen(argv[1], "r");
  if (in == NULL) {
    printf("Unable to open file %s for reading\n", argv[1]);
    exit(1);
  }

  out = fopen(argv[2], "w");
  if (out == NULL) {
    printf("Unable to open file %s for writing\n", argv[2]);
    exit(1);
  }

  // count the number of lines in the file
  int lineCount = 0;
  while (fgets(line, MAX_LEN, in) != NULL) {
    lineCount++;
  }

  // dynammically allocate array
  char **array;
  array = malloc(lineCount * sizeof(char *));

  rewind(in); // goes to start of input file

  // dynamically allocate each string
  for (int i = 0; i < lineCount; i++) {
    array[i] = malloc(256 * sizeof(char));
  }

  // copy each input string into the array
  int ind = 0;
  while (fgets(line, MAX_LEN, in) != NULL) {
    // for (int i = 0; i < MAX_LEN; i++) {
    // array[lineCount][i] = line[i];
    strcpy(array[ind], line);
    ind++;
  }
  // lineCount++;
  // }

  // start the sorting, using TA eric's pseudo from 1/14 section

  // create new list and append 0 to initialize it
  List L = newList();
  append(L, 0);
  for (int i = 1; i < lineCount; i++) {           // loop through lines
    moveFront(L);                                 // move to front of list
    for (int j = length(L) - 1; j >= 0; j--) {    // iterate through list
      if (strcmp(array[i], array[get(L)]) <= 0) { // compare, if 0 or -1
        insertBefore(L, i);                       // insert index before
        break;
      } else if (strcmp(array[i], array[get(L)]) > 0) {
        if (index(L) == length(L) - 1) { // otherwise if index = length-1
          append(L, i);                  // add to end
          break;
        } else {
          moveNext(L); // move on pls
        }
      }
    }
  }
  // print out ze list
  moveFront(L);
  for (int j = 0; j < lineCount; j++) {
    fprintf(out, "%s", array[get(L)]);
    moveNext(L);
  }
  // free ze arrays and list and each string of array
  for (int i = 0; i < lineCount; i++) {
    free(array[i]);
  }
  free(array);
  freeList(&L);
  L = NULL;
  // close files and let me be free
  fclose(in);
  fclose(out);
  return 0;
}
