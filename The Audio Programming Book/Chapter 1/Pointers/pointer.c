#include <stdio.h>

int main(int argc, char* argv[]) {
  double buffer[24];

  // Setting each sample to 0 efficiently with pointers.
  // double* ptr = buffer;
  // for (int i = 0; i < 24; i++) {
  //   *ptr++ = 0.0;
  // }

  // Finding the maximum value nearest to the start of the buffer.
  double* ptr = buffer + 24; // Or ptr = &buffer[23].
  double max = 0;
  int pos = 0;

  while (--ptr != buffer) {
    if (*ptr >= max) {
      max = *ptr;
      pos = ptr - buffer;    
    }
  }
}