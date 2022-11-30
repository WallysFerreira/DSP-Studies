#include <stdlib.h>
#include <stdio.h>

typedef struct {
  long time;
  long value;
} BREAKPOINT;

BREAKPOINT* getPoints(FILE* fp, long* psize) {
  int got;
  long pointsNumber = 0, size = 64;
  double lastTime = 0.0;
  BREAKPOINT* points = NULL;
  char line[80];

  if (fp == NULL) return NULL;

  points = (BREAKPOINT*) malloc(sizeof(BREAKPOINT) * size);
  if (points == NULL) return NULL;

  while (fgets(line, 80, fp)) {
    got = sscanf(line, "%lf%lf",  &points[pointsNumber].time, &points[pointsNumber].value);
    
    if (got < 0) continue; // sscanf return less than 0 means empty line
    if (got == 0) printf("Line %d has no numeric values\n", pointsNumber + 1); 
    if (got == 1) printf("Incomplete breakpoint in line %d\n", pointsNumber + 1);

    if (points[pointsNumber].time < lastTime) {
      printf("Time is not increasing at point %d\n", pointsNumber + 1);
      break;
    }
    lastTime = points[pointsNumber].time;

    if (++pointsNumber == size) {
      BREAKPOINT* tmp;
      size += pointsNumber;
      tmp = (BREAKPOINT*) realloc(points, sizeof(BREAKPOINT) * size);

      if (tmp == NULL) {
        pointsNumber = 0;
        free(points);
        points = NULL;
        break;
      }
      points = tmp;
    }
  }

  if (pointsNumber) {
    *psize = pointsNumber;
    return points;
  }
}

BREAKPOINT findMaxPoint(const BREAKPOINT points[], long size) {
  BREAKPOINT maxPoint;
  maxPoint.time = points[0].time;
  maxPoint.value = points[0].value;

  for (int i = 0; i < size; i++) {
    if (maxPoint.value < points[i].value) {
      maxPoint.value = points[i].value;
      maxPoint.time = points[i].time;
    }
  }

  return maxPoint;
}