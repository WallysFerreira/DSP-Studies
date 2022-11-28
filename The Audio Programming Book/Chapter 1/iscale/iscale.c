#include <stdio.h>

int main(int argc, char* argv[]) {
  int isMidi = 0, writeInterval = 0;
  argc--;
  argv++;

  for (int i = 0; i < argc; i++) {
    if (argv[i][0] == '-') {
      char flag = argv[i][1];

      if (flag == 'm') {
        isMidi = 1;
      } else if (flag == 'i') {
          writeInterval = 1;
      } else {
        printf("Invalid flag %s\n", argv[i]);
        return 1;
      }
    }
  }
}