#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>

unsigned long getNextLong(void);

int main(void)
{
    unsigned long num_tests = getNextLong();

    for (unsigned long i = 0; i < num_tests; i++)
    {
        unsigned long len = getNextLong();
        unsigned long k = getNextLong();

        unsigned long countdown = 0;
        unsigned long num_countdowns = 0;
        for (unsigned long j = 0; j < len; j++)
        {
          unsigned long a = getNextLong();
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

// reads and returns the next longeger found in stdin
unsigned long getNextLong(void)
{
  char digits[32];
  unsigned long i = 0;
  bool stop = false;

  while (!stop)
  {
    read(0, &digits[i], sizeof(char));
    if (isdigit(digits[i]))
    {
      i++;
    }
    else if (i > 0)
    {
      stop = true;
    }
  }

  unsigned long res = 0;
  for (unsigned long j = i; i > 0; i--)
  {
    // get the number represented by the ASCII character
    // 0 has an ASCII code of 48
    res += pow(10, (i - 1)) * (digits[j - i] - 48);
  }

  return res;
}
