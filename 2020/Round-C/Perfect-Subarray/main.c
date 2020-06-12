#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <sys/resource.h> // for benchmarking


double calculate(const struct rusage *b, const struct rusage *a);

static inline bool is_sqr(int x)
{
    // https://www.johndcook.com/blog/2008/11/17/fast-way-to-test-whether-a-number-is-a-square/

    if (0x0213 & (1 << (x & 15)))
    {
        int t = (int) sqrtf(x);
        return t*t == x;
    }

    return false;
}

int main(void)
{
    struct rusage before, after;
  
    unsigned int num_tests;
    fscanf(stdin, "%u\n", &num_tests);

    getrusage(RUSAGE_SELF, &before);

    for (unsigned int t = 0; t < num_tests; t++)
    {
        // get array length from stdin
        unsigned int len;
        fscanf(stdin, "%u\n", &len);

        // get array from stdin
        int arr[len];
        for (unsigned int i = 0; i < len; i++)
        {
            fscanf(stdin, i == len - 1 ? "%i" : "%i ", &arr[i]);
        }


        // check all possible subarrays

        unsigned int num_perfect_subarrays = 0;

        int sums[len];

        sums[0] = arr[0];

        if (is_sqr(sums[0]))
        {
            num_perfect_subarrays++;
        }

        for (unsigned int end = 1; end < len; end++)
        {
            //printf("---- %u -> %u ----\n", 0, end);

            sums[end] = arr[end] + sums[end - 1];
            //printf("sum: %i\n", sums[end]);

            if (is_sqr(sums[end]))
            {
                //puts("is perfect");
                num_perfect_subarrays++;
            }
        }

        unsigned int sum_i;
        for (unsigned int start = 1; start < len; start++)
        {
            sum_i = start;
            int before = arr[start - 1];
            for (unsigned int end = start; end < len; end++)
            {
                //printf("---- %u -> %u ----\n", start, end);

                //printf("before: %i | ", sums[sum_i]);
                sums[sum_i] -= before;
                //printf("after: %i\n", sums[sum_i]);

                if (is_sqr(sums[sum_i]))
                {
                    //puts("is perfect");
                    num_perfect_subarrays++;
                }

                sum_i++;
            }
        }

        printf("Case #%u: %u\n", t + 1, num_perfect_subarrays);
    }

    getrusage(RUSAGE_SELF, &after);
    float duration = calculate(&before, &after);
    printf("DURATION: %.2fs\n", duration);
}


// returns number of seconds between a and b
double calculate(const struct rusage *b, const struct rusage *a)
{
  if (b == NULL || a == NULL)
  {
    return 0.0;
  }
  else
  {
    return ((((a->ru_utime.tv_sec * 1000000 + a->ru_utime.tv_usec) -
              (b->ru_utime.tv_sec * 1000000 + b->ru_utime.tv_usec)) +
             ((a->ru_stime.tv_sec * 1000000 + a->ru_stime.tv_usec) -
              (b->ru_stime.tv_sec * 1000000 + b->ru_stime.tv_usec)))
            / 1000000.0);
  }
}