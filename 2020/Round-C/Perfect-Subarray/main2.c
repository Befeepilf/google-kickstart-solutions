#include <stdio.h>
#include <stdbool.h>
#include <math.h>

int main(void)
{
    unsigned int num_tests;
    fscanf(stdin, "%u\n", &num_tests);

    for (unsigned int t = 0; t < num_tests; t++)
    {
        // get array length from stdin
        unsigned int len;
        fscanf(stdin, "%u\n", &len);

        // get array from stdin
        int arr[len];
        unsigned int largest = NULL;
        for (unsigned int i = 0; i < len; i++)
        {
            fscanf(stdin, i == len - 1 ? "%i" : "%i ", &arr[i]);

            if (largest == NULL || arr[i] > largest)
            {
                largest = 
            }
        }


        
        printf("Case #%u: %u\n", t + 1, num_perfect_subarrays);
    }
}