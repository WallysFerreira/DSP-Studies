#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char* argv[]) {
  int isMidi = 0, writeInterval = 0, err = 0, notes;
  double startVal, baseFreq, ratio, intervals[25];
  FILE* fp;

  // Find flags anywhere in the command-line
  // for (int i = 0; i < argc; i++) {
  //   if (argv[i][0] == '-') {
  //     char flag = argv[i][1];

  //     if (flag == 'm') {
  //       isMidi = 1;
  //     } else if (flag == 'i') {
  //         writeInterval = 1;
  //     } else {
  //       printf("Invalid flag %s\n", argv[i]);
  //       return 1;
  //     }
  //   }
  // }

  // Find flags in the beginning of command-line arguments (book version)
  while (argc > 1) {
    if (argv[1][0] == '-') {
      char flag = argv[1][1];

      if (flag == 'm') {
        isMidi = 1;
      } else if (flag == 'i') {
        writeInterval = 1;
      } else {
        printf("Invalid flag %s\n", argv[1]);
        return 1;
      }

      argc--;
      argv++;
    } else {
      break;
    }
  }
  
  // There should be 3 arguments now (iscale N startVal), if there isn't, throw an error
  if (argc < 3) {
    printf("Arguments missing\n");
    return 1;
  }

  // Validate number of notes
  notes = atoi(argv[1]);
  if (notes < 1 || notes > 24) {
    printf("Number of notes must be between 1 and 24\n");
    return 1;
  }
  // Validate start value
  startVal = atoi(argv[2]);
  if (isMidi) {
    if (startVal < 0 || startVal > 127) {
      printf("MIDI Notes must be between 0 and 127\n");
      return 1;
    }
  } else {
    if (startVal < 0) {
      printf("Frequencies must be positive\n");
      return 1;
    }
  }

  // Create new file
  fp = NULL;
  if (argc > 3) {
    fp = fopen(argv[3], "w");
    if (fp == NULL) {
      printf("Error creating file\n");
      perror("");
    }
  }

  // Find base frequency with start value being MIDI.
  if (isMidi) {
    double c0, c5;
    ratio = pow(2.0, 1.0 / 12.0);
    c5 = 220.0 * pow(ratio, 3);
    c0 = c5 * pow(0.5, 5);
    baseFreq = c0 * pow(ratio, startVal);
  } else {
    baseFreq = startVal;
  }

  // Calculate ratio for the number of notes and fill array
  ratio = pow(2.0, 1.0 / notes);
  for (int i = 0; i <= notes; i++) {
    intervals[i] = baseFreq;
    baseFreq *= ratio;
  }

  // Write array to screen
  for (int i = 0; i <= notes; i++) {
    if (writeInterval) {
      printf("%d:\t%f\t%f\n", i, pow(ratio, i), intervals[i]);
    } else {
      printf("%d:\t%f\n", i, intervals[i]);
    }

    // and to file if needed
    if (fp) {
      if(writeInterval) {
        // if an error occurs, fprintf will return a negative number
        err = fprintf(fp, "%d:\t%f\t%f\n", i, pow(ratio, i), intervals[i]);
      } else {
        err = fprintf(fp, "%d:\t%f\n", i, intervals[i]);
      }

      if (err < 0) break;
    }
  }

  // If err is negative, an error has occurred while writing to file
  if (err < 0) perror("Error writing to file\n");
  
  if (fp) fclose(fp);

  return 0;
}