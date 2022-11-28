#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char* argv[]) {
  int notes = atoi(argv[1]), midinote = atoi(argv[2]);
  double frequency, ratio, c0, c5;
  double intervals[24];
  
  if (argc != 3) {
    printf("2 arguments needed: notes and midinote\n");
    return 1;
  }

  if (notes < 1) {
    printf("Notes must be positive\n");
    return 1;
  } else if (notes > 24) {
    printf("Maximum value for notes is 24\n");
    return 1;
  }

  if (midinote < 0) {
    printf("MIDI notes can't be negative\n");
    return 1;
  } else if (midinote > 127) {
    printf("MIDI notes maximum is 127\n");
    return 1;
  }

  ratio = pow(2.0, 1.0 / 12);
  c5 = 220 * pow(ratio, 3);
  c0 = c5 * pow(0.5, 5);
  frequency = c0 * pow(ratio, midinote);

  ratio = pow(2.0, 1.0 / notes);
  for (int i = 0; i < notes; i++) {
    intervals[i] = frequency;
    frequency *= ratio;
  }

  for (int i = 0; i < notes; i++) {
    printf("%d: %f\n", i + 1, intervals[i]);
  }
}