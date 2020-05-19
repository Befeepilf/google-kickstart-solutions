#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>

int main(void)
{
    unsigned int num_tests;
    fscanf(stdin, "%u", &num_tests);

    for (unsigned long i = 0; i < num_tests; i++)
    {
        unsigned int len, k;
        fscanf(stdin, "%u %u", &len, &k);

        unsigned long countdown = 0;
        unsigned long num_countdowns = 0;
        for (unsigned long j = 0; j < len; j++)
        {
          unsigned int a;
          fscanf(stdin, "%u", &a);

          // if start of k-countdown has been found
          if (countdown > 0)
          {
            // if a is next in countdown
            if (a == countdown - 1)
            {
              // if a is end of countdown
              if (a == 1)
              {
                num_countdowns++;
                countdown = 0;
              }
              else
              {
                countdown = a;
              }
            }
            // reset countdown
            else
            {
              countdown = a == k ? a : 0;
            }
          }
          // beginning of k-countdown
          else if (a == k)
          {
            countdown = a;
          }
        }

        printf("Case #%lu: %lu\n", i + 1, num_countdowns);
    }
}
