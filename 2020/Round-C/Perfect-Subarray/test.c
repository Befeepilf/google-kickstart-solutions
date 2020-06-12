#include <stdio.h>

int main(void)
{
    unsigned int num_tests = 100;

    printf("%u\n", num_tests);

    for (unsigned int t = 0; t < num_tests; t++)
    {
        unsigned int arr_len = t < 5 ? 100000 : 1000;
        printf("%u\n", arr_len);
        for (unsigned int i = 0; i < arr_len; i++)
        {
            printf(i == arr_len - 1 ? "%u\n" : "%u ", i);
        }
    }
}