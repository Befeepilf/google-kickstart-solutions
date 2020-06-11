#include <stdio.h>
#include <stdbool.h>


bool is_brick_stable(char *order, unsigned int order_len, char brick)
{
    for (unsigned int i = 0; i < order_len; i++)
    {
        if (order[i] == brick)
        {
            return true;
        }
    }

    return false;
}

int main(void)
{
    unsigned int num_cases;
    fscanf(stdin, "%u\n", &num_cases);

    for (unsigned int i = 0; i < num_cases; i++)
    {
        unsigned int rows, columns;
        fscanf(stdin, "%u %u\n", &rows, &columns);

        char wall[rows][columns];

        char bricks[rows * columns]; // holds all different brick types; max num of different bricks is rows*columns
        unsigned int bricks_count = 0;

        // parse wall from stdin
        for (unsigned int r = 0; r < rows; r++)
        {
            for (unsigned int c = 0; c < columns; c++)
            {
                fscanf(stdin, "%c", &wall[r][c]);

                // if end of line skip newline character
                if (c == columns - 1) fscanf(stdin, "%*c");
                
                bool bricks_exists = false;
                // check whether this brick type is already in bricks array
                for (unsigned int b = 0; b < bricks_count; b++)
                {
                    if (bricks[b] == wall[r][c])
                    {
                        bricks_exists = true;
                        break;
                    }
                }

                // if this brick is not yet in bricks array, add it
                if (!bricks_exists)
                {
                    bricks[bricks_count] = wall[r][c];
                    bricks_count++;
                }
            }
        }


        // check whether wall is stable & determine placement order of bricks

        char placement_order[bricks_count]; // order in which bricks were placed
        unsigned int placement_order_i = 0;

        bool is_stable = true;

        while (true)
        {
            // indicates whether we found the next brick in the placement order in this iteration
            // if we didn't the wall is unstable & we can abort
            bool changed = false;

            for (unsigned int b = 0; b < bricks_count; b++)
            {
                // if this bricks hasn't been marked as stable yet
                if (bricks[b] != 0)
                {
                    bool is_stable = true;
                    unsigned int bricks_height = 0; // number of consecutive stable bricks in a column

                    // start from bottom left of wall & check whether a column contains an unstable series of bricks
                    for (unsigned int c = 0; c < columns && is_stable; c++)
                    {
                        for (unsigned int r = rows; r > 0 && is_stable; r--)
                        {
                            if (wall[r - 1][c] == bricks[b] || is_brick_stable(placement_order, placement_order_i, wall[r - 1][c]))
                            {
                                // if a series of stable bricks starts without stable bricks below it, abort
                                if (bricks_height == 0 && r - 1 < rows - 1)
                                {
                                    is_stable = false;
                                }
                                else
                                {
                                    bricks_height++;
                                }
                            }
                            else
                            {
                                bricks_height = 0;
                            }
                        }
                    }

                    // if this type of brick can be placed in a stable way (considering bricks that have already been placed), add it as next brick in placemetn_order
                    if (is_stable)
                    {
                        placement_order[placement_order_i] = bricks[b];
                        placement_order_i++;

                        bricks[b] = 0;

                        changed = true;
                    }
                }
            }

            if (placement_order_i == bricks_count)
            {
                break;
            }

            if (!changed)
            {
                is_stable = false;
                break;
            }
        }


        // print result
        printf("Case #%u: ", i + 1);
        if (is_stable)
        {
            for (unsigned int j = 0; j < placement_order_i; j++)
            {
                printf("%c", placement_order[j]);
            }
            printf("\n");
        }
        else
        {
            printf("-1\n");
        }
    }
}