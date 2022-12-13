#include <stdio.h>
#include <stdlib.h>

typedef struct {
  double time;
  double value;
}BREAKPOINT;

// Ask for name of breakpoint file
char* findPath() {
  char* path;

  path = (char*) malloc(sizeof(char) * 20);
  printf("Qual é o nome do arquivo (máximo 100 linhas) a ser lido? ");
  scanf("%s", path);

  return path;
}

// Show menu (Show points, find max point, )
void showMenu(int* userAnswer) {
  printf("\nO que você deseja fazer agora?\n1 - Mostrar pontos\n2 - Mostrar ponto com maior valor\n0 - Sair\n");
  scanf("%d", userAnswer);
}

// Show breakpoints
void showPoints(BREAKPOINT* points, int totalReadMain) {
  printf("\n");
  
  for (int i = 0; i < totalReadMain; i++) {
    printf("%.2lf %.2lf\n", points[i].time, points[i].value);
  }
}

// Read breakpoints
BREAKPOINT* readBreakpoints(FILE* fp, int* pointsReadMain) {
  int infoRead = 0, pointsRead = 0, size = 64;
  double lastTime = 0;
  char line[30];
  BREAKPOINT* points;
  
  if (fp == NULL) {
    // printf("No file loaded\n");
    return NULL;
  }
  
  points = (BREAKPOINT*) malloc(sizeof(BREAKPOINT) * size);
  if (points == NULL) return NULL; // memory allocation failed

  while (fgets(line, 30, fp)) {
    infoRead = sscanf(line, "%lf %lf", &points[pointsRead].time, &points[pointsRead].value);

    if (infoRead < 0) continue; // line was empty
    if (infoRead == 1) {
      printf("Information missing on line %d\n", pointsRead + 1);
      break;
    }
    
    if (points[pointsRead].time < lastTime) {
      printf("Time must be increasing\n");
      return NULL;
    }
    lastTime = points[pointsRead].time;

    if (++pointsRead == size) {
      size += pointsRead;
      BREAKPOINT* tmp;
      tmp = (BREAKPOINT*) realloc(points, sizeof(BREAKPOINT) * size);

      if (tmp == NULL) { // memory allocation failed
        free(points);
        pointsRead = 0;
        return NULL;
      }
    }
  }

  *pointsReadMain = pointsRead;
  return points;
}

// Return point with maximum value
BREAKPOINT findMaxPoint(BREAKPOINT* points, int size) {
  BREAKPOINT maxPoint;
  maxPoint.time = points[0].time;
  maxPoint.value = points[0].value;
  
  for (int i = 0; i < size; i++) {
    if (points[i].value > maxPoint.value) {
      maxPoint.value = points[i].value;
      maxPoint.time = points[i].time;
    }
  }

  return maxPoint;
}