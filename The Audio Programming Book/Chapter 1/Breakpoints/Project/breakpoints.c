#include "header.h"

int main(int argc, char* argv[]) {
  int totalRead = 0;
  FILE* fp;
  BREAKPOINT* points;

  fp = fopen("breakpointExample.brk", "r");
  points = readBreakpoints(fp, &totalRead);

  for (int i = 0; i < totalRead; i++) {
    printf("%lf %lf\n", points[i].time, points[i].value);
  }
}