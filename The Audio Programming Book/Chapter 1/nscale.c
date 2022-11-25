#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char* argv[]) {
  int note = atoi(argv[1]), midinote = atoi(argv[2]);

  if (argc != 3) {
    printf("2 arguments needed: notes and midinote\n");
    return 1;
  }

  if (note < 1) {
    printf("Notes must be positive\n");
    return 1;
  } else if (note > 24) {
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
}