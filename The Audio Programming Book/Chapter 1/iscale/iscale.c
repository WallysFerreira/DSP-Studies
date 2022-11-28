#include <stdio.h>

int main(int argc, char* argv[]) {
  int isMidi = 0, writeInterval = 0;

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
        printf("Teste 1\n");
      } else if (flag == 'i') {
        writeInterval = 1;
        printf("Teste 2\n");
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

  // Chapter 1.6.7 150 PDF 123 BOOK
}