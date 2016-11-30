#include <stdio.h>
#include <math.h>

#define EPS 0.00001

int circle_circle_intersection(double x0, double y0, double r0,
                               double x1, double y1, double r1,
                               double *xi, double *yi,
                               double *xi_prime, double *yi_prime, int offset, double possible_solutions[])
{
  double a, dx, dy, d, h, rx, ry;
  double x2, y2;

  /* dx and dy are the vertical and horizontal distances between
   * the circle centers.
   */
  dx = x1 - x0;
  dy = y1 - y0;

  /* Determine the straight-line distance between the centers. */
  //d = sqrt((dy*dy) + (dx*dx));
  d = hypot(dx,dy); // Suggested by Keith Briggs

  /* Check for solvability. */
  if (d > (r0 + r1))
  {
    /* no solution. circles do not intersect. */
    return 0;
  }
  if (d < fabs(r0 - r1))
  {
    /* no solution. one circle is contained in the other */
    return 0;
  }

  /* 'point 2' is the point where the line through the circle
   * intersection points crosses the line between the circle
   * centers.  
   */

  /* Determine the distance from point 0 to point 2. */
  a = ((r0*r0) - (r1*r1) + (d*d)) / (2.0 * d) ;

  /* Determine the coordinates of point 2. */
  x2 = x0 + (dx * a/d);
  y2 = y0 + (dy * a/d);

  /* Determine the distance from point 2 to either of the
   * intersection points.
   */
  h = sqrt((r0*r0) - (a*a));

  /* Now determine the offsets of the intersection points from
   * point 2.
   */
  rx = -dy * (h/d);
  ry = dx * (h/d);

  /* Determine the absolute intersection points. */
  *xi = x2 + rx;
  *xi_prime = x2 - rx;
  *yi = y2 + ry;
  *yi_prime = y2 - ry;

  int index = offset;
  if(round(*xi) == -0.000000){
    possible_solutions[index] = -(round(*xi));
  }
  else{
    possible_solutions[index] = round(*xi);
  }
  index++;
  if(round(*yi) == -0.000000){
    possible_solutions[index] = -(round(*yi));
  }
  else{
    possible_solutions[index] = round(*yi);
  }
  index++;
  if(round(*xi_prime) == -0.000000){
    possible_solutions[index] = -(round(*xi_prime));
  }
  else{
    possible_solutions[index] = round(*xi_prime);
  }
  index++;
  if(round(*yi_prime) == -0.000000){
    possible_solutions[index] = -(round(*yi_prime));
  }
  else{
    possible_solutions[index] = round(*yi_prime);
  }

  return 1;
}

int equals(double a, double b) {
  if(EPS > fabs(a - b)){
    return 1;
  }
  else
    return 0; 
}

double round(double num){
  return (num - floor(num) > 0.0005) ? ceil(num) : floor(num);
}

void run_test(double x0, double y0, double r0,
              double x1, double y1, double r1,
              double x2, double y2, double r2)
{
  double intersection1x1, intersection1y1, intersection1x2, intersection1y2,
         intersection2x1, intersection2y1, intersection2x2, intersection2y2,
         intersection3x1, intersection3y1, intersection3x2, intersection3y2;
  double possible_solutions[12];

  printf("\nFirst Point: (%F,%F), Distance: %F\n", x0, y0, r0);
  printf("Second Point: (%F,%F), Distance: %F\n", x1, y1, r1);
  printf("Third Point: (%F,%F), Distance: %F\n", x2, y2, r2);

  circle_circle_intersection(x0, y0, r0, x1, y1, r1,
                             &intersection1x1, &intersection1y1, &intersection1x2, &intersection1y2, 0, possible_solutions);
  
  circle_circle_intersection(x0, y0, r0, x2, y2, r2,
                             &intersection2x1, &intersection2y1, &intersection2x2, &intersection2y2, 4, possible_solutions);
  
  circle_circle_intersection(x2, y2, r2, x1, y1, r1,
                             &intersection3x1, &intersection3y1, &intersection3x2, &intersection3y2, 8, possible_solutions);
  
  int kqo;
  printf("\nPossible Solutions:\n");
  for(kqo = 0; kqo<12; kqo++){
    printf("[%d]: %F\n", kqo, possible_solutions[kqo]);
  }

  double final_answerx = 0.0, final_answery = 0.0;
  int flag = 0;
  if     ((equals(possible_solutions[0], possible_solutions[4]) == 1) 
       || (equals(possible_solutions[0], possible_solutions[6]) == 1) 
       && (equals(possible_solutions[0], possible_solutions[8]) == 1)
       || (equals(possible_solutions[0], possible_solutions[10]) == 1) 
       && (equals(possible_solutions[1], possible_solutions[5]) == 1) 
       || (equals(possible_solutions[1], possible_solutions[7]) == 1)
       && (equals(possible_solutions[1], possible_solutions[8]) == 1)
       || (equals(possible_solutions[1], possible_solutions[11]) == 1))
  {
    final_answerx = possible_solutions[0];
    final_answery = possible_solutions[1];
  }
  else if((equals(possible_solutions[2], possible_solutions[4]) == 1) 
       || (equals(possible_solutions[2], possible_solutions[6]) == 1) 
       && (equals(possible_solutions[2], possible_solutions[8]) == 1)
       || (equals(possible_solutions[2], possible_solutions[10]) == 1) 
       && (equals(possible_solutions[3], possible_solutions[5]) == 1) 
       || (equals(possible_solutions[3], possible_solutions[7]) == 1)
       && (equals(possible_solutions[3], possible_solutions[8]) == 1)
       || (equals(possible_solutions[3], possible_solutions[11]) == 1))
  {
    final_answerx = possible_solutions[2];
    final_answery = possible_solutions[3];
  }
  else{
    printf("\nSolution not possible.\n");
    flag++;
  } 
  
  if(flag==0){
    printf("\nIntersection Point: (%F,%F)\n", final_answerx, final_answery);
  
    double angle = atan2(final_answery - y2, final_answerx - x2) * (180.0 / M_PI);

    printf("\nAngle to the point: %F degrees\n", angle);
  }
}

int main(int argc, char** argv)
{   
  printf("----------------------------------------------------\n");
  run_test(0.0, 1.0, 6.40312, 0.0, 0.0, 7.07107, 1.0, 0.0, 6.40312);
  printf("\n----------------------------------------------------\n");
  run_test(0.0, 1.0, 4.47214, 0.0, 0.0, 5.38516, 1.0, 0.0, 5.09902);
  printf("\n----------------------------------------------------\n");
  run_test(0.0, 1.0, 2.23607, 0.0, 0.0, 2.0, 1.0, 0.0, 1.0);
  printf("\n----------------------------------------------------\n");
  run_test(0.0, 1.0, 6.32456, 0.0, 0.0, 7.28011, 1.0, 0.0, 7.07107);
  printf("\n----------------------------------------------------\n");
  
  return 0;
}
