#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define T 100
#define R 30
#define C 30
#define NUM_BRICKS 26 // max 26


int main(void)
{
  srand(time(NULL));

  printf("%i\n", T);
  for (unsigned t = 0; t < T; t++)
  {
    printf("%i %i\n", R, C);
    for (unsigned int i = 0; i < R; i++)
    {
      for (unsigned int j = 0; j < C; j++)
      {
        printf("%c", (int) fmin(90, fmax(65, ((int) (rand() % (int) fmax(R - pow(i, 1.2), 1))) + 65)));
      }
      printf("\n");
    }
  }
}
