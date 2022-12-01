#include <stdlib.h>
#include <stdio.h>

typedef struct {
  long time;
  long value;
} BREAKPOINT;


// Checks if a file is open in the FILE instance.
// Allocates memory to the points instance of BREAKPOINT
// If points CONTINUES to be null, memory allocation has failed and the function must return NULL
// fgets receives the line it is going to read from, the maximum number of caracters to read in that line and the file it's going to read from
// If fgets returns NULL, it means an error or that the file has ended
// sscanf receives the line to read from, the format specifier to look for in that line and the addresses to store them in
// sscanf returns the number of writes it has made
// Makes sure sscanf has read 2 informations from the file (time and value)
//
BREAKPOINT* getPoints(FILE* fp, long* psize) {
  int got;
  long numberOfPoints = 0, size = 64;
  double lastTime = 0.0;
  BREAKPOINT* points = NULL;
  char line[80];

  if (fp == NULL) return NULL;

  points = (BREAKPOINT*) malloc(sizeof(BREAKPOINT) * size);
  if (points == NULL) return NULL;

  while (fgets(line, 80, fp)) {
    got = sscanf(line, "%lf%lf", &points[numberOfPoints].time, &points[numberOfPoints].value);
    
    if (got < 0) continue; // sscanf return less than 0 means empty line
    if (got == 0) printf("Line %d has no numeric values\n", numberOfPoints + 1); 
    if (got == 1) printf("Incomplete breakpoint in line %d\n", numberOfPoints + 1);

    if (points[numberOfPoints].time < lastTime) {
      printf("Time is not increasing at point %d\n", numberOfPoints + 1);
      break;
    }
    lastTime = points[numberOfPoints].time;

    if (++numberOfPoints == size) {
      BREAKPOINT* tmp;
      size += numberOfPoints;
      tmp = (BREAKPOINT*) realloc(points, sizeof(BREAKPOINT) * size);

      if (tmp == NULL) {
        numberOfPoints = 0;
        free(points);
        points = NULL;
        break;
      }
      points = tmp;
    }
  }

  if (numberOfPoints) {
    *psize = numberOfPoints;
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