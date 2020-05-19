#include <stdio.h>

int main(void)
{
    unsigned int num_tests;
    fscanf(stdin, "%u", &num_tests);

    for (unsigned int i = 0; i < num_tests; i++)
    {
        unsigned int len, k;
        fscanf(stdin, "%u %u", &len, &k);

        unsigned int countdown = 0;
        unsigned int num_countdowns = 0;
        for (unsigned int j = 0; j < len; j++)
        {
          unsigned int a;
          fscanf(stdin, "%u", &a);

          // if beginning of k-countdown
          if (a == k) countdown = a;
          /// if start of k-countdown has already been found
          else if (countdown > 0)
          {
            // if a is next in countdown
            if (a == countdown - 1)
            {
              // if a is not end of countdown
              if (a != 1) countdown = a;
              else
              {
                num_countdowns++;
                countdown = 0;
              }
            }
            // reset countdown
            else
            {
              countdown = 0;
            }
          }
        }

        printf("Case #%i: %i\n", i + 1, num_countdowns);
    }
}
