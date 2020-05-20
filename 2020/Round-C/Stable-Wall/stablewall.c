#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int main (void)
{
  unsigned int num_tests;
  fscanf(stdin, "%u\n", &num_tests);

  for (unsigned int i = 0; i < num_tests; i++)
  {
    unsigned int r, c;
    fscanf(stdin, "%u %u\n", &r, &c);

    char bricks[r*c];
    unsigned int num_bricks = 0;

    char wall[r][c];
    for (unsigned int j = 0; j < r; j++)
    {
      for (unsigned int k = 0; k < c; k++)
      {
        fscanf(stdin, "%c", &wall[j][k]);

        // if end of line skip newline character
        if (k == c - 1) fscanf(stdin, "%*c");

        // store every possible type of brick used for wall in bricks[]
        if (num_bricks < r*c)
        {
          bool is_new_brick = true;
          for (unsigned int l = 0; l < num_bricks; l++)
          {
            if (bricks[l] == wall[j][k])
            {
              is_new_brick = false;
              l = num_bricks;
            }
          }

          if (is_new_brick)
          {
            bricks[num_bricks] = wall[j][k];
            num_bricks++;
          }
        }
      }
    }


    char *order = malloc(num_bricks * sizeof(char));
    unsigned int order_i = 0;
    unsigned int last_order_i = -1;

    while (order_i != num_bricks && last_order_i != order_i)
    {
      last_order_i = order_i;

      // for every type of brick
      for (unsigned int j = 0; j < num_bricks; j++)
      {
        //printf("\n--- %i %c ---\n", j, bricks[j]);

        if (bricks[j] != 0)
        {
          bool columns_stable = false;

          // for every column
          for (unsigned int k = 0; k < c; k++)
          {
            bool found_brick = false;
            bool is_supported = false;

            // for every row
            for (unsigned int l = 0; l < r; l++)
            {
              //printf("%i %i %c\n", k, l, wall[l][k]);

              if (!found_brick)
              {
                if (wall[l][k] == bricks[j])
                {
                  //printf("\tfound\n");
                  found_brick = true;
                  is_supported = true;
                }
                else
                {
                  //printf("\tnot found\n");
                }
              }
              else
              {
                is_supported = wall[l][k] == bricks[j];
                if (!is_supported)
                {
                  for (unsigned int m = 0; m < order_i; m++)
                  {
                    if (wall[l][k] == order[m])
                    {
                      is_supported = true;
                      m = order_i;
                    }
                  }
                }

                // check next brick
                if (!is_supported)
                {
                  //printf("\tnot supported\n");
                  l = r;
                  k = c;
                }
                else
                {
                  //printf("\tsupported\n");
                }
              }
            }

            //printf(is_supported ? "Column is supported\n" : "Column is not supported\n");

            columns_stable = found_brick ? is_supported : columns_stable;
          }

          if (columns_stable)
          {
            //printf("Added %c\n", bricks[j]);
            order[order_i] = bricks[j];
            bricks[j] = 0;
            order_i++;
          }
        }
      }
    }


    printf("Case #%i: %s\n", i + 1, order_i < num_bricks ? "-1" : order);

    free(order);
  }
}
