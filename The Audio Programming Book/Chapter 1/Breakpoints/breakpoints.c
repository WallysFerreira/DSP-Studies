#include <stdlib.h>
#include <stdio.h>

typedef struct {
  double time;
  double value;
}BREAKPOINT;

BREAKPOINT* readBreakpoints(FILE* fp, int* pointsReadMain) {
  int infoRead = 0, pointsRead = 0, size = 8;
  double lastTime = 0;
  char line[50];
  BREAKPOINT* points;
  
  if (fp == NULL) {
    printf("No file loaded\n");
    return NULL;
  }
  
  points = (BREAKPOINT*) malloc(sizeof(BREAKPOINT) * size);
  if (points == NULL) return NULL; // memory allocation failed

  while (fgets(line, 50, fp)) {
    infoRead = sscanf(line, "%lf %lf", &points[pointsRead].time, &points[pointsRead].value);

    if (infoRead < 0) continue; // line was empty
    if (infoRead == 1) {
      printf("Information missing on line %d\n", pointsRead + 1);
      break;
    }

    if (lastTime > points[pointsRead].time) {
      printf("Time must be increasing\n");
      return NULL;
    }
    lastTime = points[pointsRead].time;

    if (++pointsRead == size) {
      size += pointsRead;
      BREAKPOINT* tmp;
      tmp = (BREAKPOINT*) realloc(points, sizeof(BREAKPOINT) * size);

      if (tmp == NULL) { // memory allocation failed
        return NULL;
      }
    }
  }

  *pointsReadMain = pointsRead;
  return points;
}

int main(int argc, char* argv[]) {
  int totalRead = 0;
  FILE* fp;
  BREAKPOINT* points;

  fp = fopen("breakpointExample.brk", "r");
  printf("%d\n", totalRead);
  points = readBreakpoints(fp, &totalRead);
  printf("%d\n", totalRead);

  for (int i = 0; i < totalRead; i++) {
    printf("%lf %lf\n", points[i].time, points[i].value);
  }
}