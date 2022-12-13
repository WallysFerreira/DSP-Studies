#include "functions.h"

int main(int argc, char* argv[]) {
  int totalRead = 0, userAnswer;
  char* path;
  FILE* fp;
  BREAKPOINT* points;
  BREAKPOINT maxPoint;

  // Ask for name of file here (100 lines maximum)
  path = findPath();

  fp = fopen(path, "r");
  if (fp == NULL) {
      printf("Arquivo não foi lido\n");
      return 1;
  } else {
    printf("Arquivo lido com sucesso.\n");
  }
  points = readBreakpoints(fp, &totalRead);

  // Menu here (Show points, find max point, )
  do {
    showMenu(&userAnswer);

    switch (userAnswer) {
      case 0:
        break;
      case 1: 
        showPoints(points, totalRead);
        break;
      case 2:
        maxPoint = findMaxPoint(points, totalRead);
        printf("\n%.2lf %.2lf\n", maxPoint.time, maxPoint.value);
        break;
      default:
        printf("Opção inválida, tente novamente:");
    }
  } while (userAnswer != 0);
}