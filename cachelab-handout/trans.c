/*
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);
void trans(int M, int N, int A[N][M], int B[M][N]);
void test32x32_trans(int M, int N, int A[N][M], int B[M][N]);
void test64x64_trans(int M, int N, int A[N][M], int B[M][N]);
void test61x67_trans(int M, int N, int A[N][M], int B[M][N]);

/*
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded.
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
    // M=N=32
    if (M == 32 && N == 32)
    {
        test32x32_trans(M, N, A, B);
    }
    else if (M == 64 && N == 64)
    {
        test64x64_trans(M, N, A, B);
    }
    else if (M == 61 && N == 67)
    {
        test61x67_trans(M, N, A, B);
    }
    else
    {
        trans(M, N, A, B);
    }
}

/*
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started.
 */

 /*
  * trans - A simple baseline transpose function, not optimized for the cache.
  */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }

}

char trans_test32x32_desc[] = "32 X 32 Matrix Test";
void test32x32_trans(int M, int N, int A[N][M], int B[M][N])
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            for (int ii = 0; ii < 8; ii++)
            {
                int a0 = A[i * 8 + ii][j * 8 + 0];
                int a1 = A[i * 8 + ii][j * 8 + 1];
                int a2 = A[i * 8 + ii][j * 8 + 2];
                int a3 = A[i * 8 + ii][j * 8 + 3];
                int a4 = A[i * 8 + ii][j * 8 + 4];
                int a5 = A[i * 8 + ii][j * 8 + 5];
                int a6 = A[i * 8 + ii][j * 8 + 6];
                int a7 = A[i * 8 + ii][j * 8 + 7];
                B[j * 8 + 0][i * 8 + ii] = a0;
                B[j * 8 + 1][i * 8 + ii] = a1;
                B[j * 8 + 2][i * 8 + ii] = a2;
                B[j * 8 + 3][i * 8 + ii] = a3;
                B[j * 8 + 4][i * 8 + ii] = a4;
                B[j * 8 + 5][i * 8 + ii] = a5;
                B[j * 8 + 6][i * 8 + ii] = a6;
                B[j * 8 + 7][i * 8 + ii] = a7;
            }
}

char trans_test64x64_desc[] = "64 X 64 Matrix Test";
void test64x64_trans(int M, int N, int A[N][M], int B[M][N])
{
    int a0, a1, a2, a3;
    int a4, a5, a6, a7;
    for (int i = 0, j = 0; i < 64 && j < 64; i += 8, j += 8)
    {
        /*
            [++++++++][        ][       ]  move       [++++++++][++++++++][        ]
            [--------][        ][       ]  to next    [--------][        ][        ]
            +,- means 4 x 1 vector
        */
        for (int ii = 0; ii < 4; ii++)
        {
            a0 = A[i + ii][j + 0];
            a1 = A[i + ii][j + 1];
            a2 = A[i + ii][j + 2];
            a3 = A[i + ii][j + 3];
            a4 = A[i + ii][j + 4];
            a5 = A[i + ii][j + 5];
            a6 = A[i + ii][j + 6];
            a7 = A[i + ii][j + 7];

            B[i + ii][(j + 8) % 64 + 0] = a0;
            B[i + ii][(j + 8) % 64 + 1] = a1;
            B[i + ii][(j + 8) % 64 + 2] = a2;
            B[i + ii][(j + 8) % 64 + 3] = a3;
            B[i + ii][(j + 8) % 64 + 4] = a4;
            B[i + ii][(j + 8) % 64 + 5] = a5;
            B[i + ii][(j + 8) % 64 + 6] = a6;
            B[i + ii][(j + 8) % 64 + 7] = a7;
        }

        /*
            [++++++++][        ][       ]  move      [++++++++][++++++++][--------]
            [--------][        ][       ]  to next   [--------][        ][        ]
            +,- means 4 x 1 vector
        */
        for (int ii = 4; ii < 8; ii++)
        {
            a0 = A[i + ii][j + 0];
            a1 = A[i + ii][j + 1];
            a2 = A[i + ii][j + 2];
            a3 = A[i + ii][j + 3];
            a4 = A[i + ii][j + 4];
            a5 = A[i + ii][j + 5];
            a6 = A[i + ii][j + 6];
            a7 = A[i + ii][j + 7];

            B[i + ii - 4][(j + 16) % 64 + 0] = a0;
            B[i + ii - 4][(j + 16) % 64 + 1] = a1;
            B[i + ii - 4][(j + 16) % 64 + 2] = a2;
            B[i + ii - 4][(j + 16) % 64 + 3] = a3;
            B[i + ii - 4][(j + 16) % 64 + 4] = a4;
            B[i + ii - 4][(j + 16) % 64 + 5] = a5;
            B[i + ii - 4][(j + 16) % 64 + 6] = a6;
            B[i + ii - 4][(j + 16) % 64 + 7] = a7;
        }

        /*
             ┌           ┌
               ++++||----    ++++||----
               ++++||----    ++++||----
               ++++||----    ++++||----
               ++++||----    ++++||----
                         ┘            ┘
             transpose first part to
             ┌
               ++++++++
               ++++++++
               ++++++++
               ++++++++
               ========
                        ┘
             ┌





                        ┘
         */
        for (int k = j + 8; k <= j + 16; k += 8) {
            for (int ii = 0; ii < 4; ii++)
            {
                a0 = B[i + ii][k % 64 + 0];
                a1 = B[i + ii][k % 64 + 1];
                a2 = B[i + ii][k % 64 + 2];
                a3 = B[i + ii][k % 64 + 3];

                B[j + 0][i + ii + ((k == (j + 8)) ? 0 : 4)] = a0;
                B[j + 1][i + ii + ((k == (j + 8)) ? 0 : 4)] = a1;
                B[j + 2][i + ii + ((k == (j + 8)) ? 0 : 4)] = a2;
                B[j + 3][i + ii + ((k == (j + 8)) ? 0 : 4)] = a3;
            }
        }

        /*
            ┌           ┌
              ++++||----    ++++||----
              ++++||----    ++++||----
              ++++||----    ++++||----
              ++++||----    ++++||----
                        ┘            ┘
            transpose second part to
            ┌
              ++++++++
              ++++++++
              ++++++++
              ++++++++
              ========
                       ┘
            ┌
              ========
              --------
              --------
              --------
              --------
                       ┘
        */
        for (int k = j + 12; k <= j + 20; k += 8)
            for (int ii = 0; ii < 4; ii++)
            {
                a0 = B[i + ii][k % 64 + 0];
                a1 = B[i + ii][k % 64 + 1];
                a2 = B[i + ii][k % 64 + 2];
                a3 = B[i + ii][k % 64 + 3];

                B[j + 4][i + ii + ((k == j + 12) ? 0 : 4)] = a0;
                B[j + 5][i + ii + ((k == j + 12) ? 0 : 4)] = a1;
                B[j + 6][i + ii + ((k == j + 12) ? 0 : 4)] = a2;
                B[j + 7][i + ii + ((k == j + 12) ? 0 : 4)] = a3;
            }
    }
    for (int i = 0; i < 64; i += 8)
        for (int j = 0; j < 64; j += 8)
        {
            if (i != j)
            {
                // divided into 8 X 8 Blocks
                for (int ii = 0; ii < 8; ii++)
                {
                    // deal left 8 x 4 Blocks from top to bottom
                    a0 = A[i + ii][j + 0];
                    a1 = A[i + ii][j + 1];
                    a2 = A[i + ii][j + 2];
                    a3 = A[i + ii][j + 3];

                    if (ii == 0)
                    {
                        a4 = A[i + ii][j + 4];
                        a5 = A[i + ii][j + 5];
                        a6 = A[i + ii][j + 6];
                        a7 = A[i + ii][j + 7];
                    }

                    B[j + 0][i + ii] = a0;
                    B[j + 1][i + ii] = a1;
                    B[j + 2][i + ii] = a2;
                    B[j + 3][i + ii] = a3;
                }

                j += 4;

                for (int ii = 7; ii > 0; ii--)
                {
                    // deal right 8 x 4 Blocks from bottom to top
                    a0 = A[i + ii][j + 0];
                    a1 = A[i + ii][j + 1];
                    a2 = A[i + ii][j + 2];
                    a3 = A[i + ii][j + 3];

                    B[j + 0][i + ii] = a0;
                    B[j + 1][i + ii] = a1;
                    B[j + 2][i + ii] = a2;
                    B[j + 3][i + ii] = a3;

                }

                B[j + 0][i + 0] = a4;
                B[j + 1][i + 0] = a5;
                B[j + 2][i + 0] = a6;
                B[j + 3][i + 0] = a7;

                j -= 4;
            }
        }
}

char trans_test61x67_desc[] = "61 X 67 Matrix Test";
void test61x67_trans(int M, int N, int A[N][M], int B[M][N])
{
        for (int j = 0; j < 56; j+=8)
    for (int i = 0; i < 56; i+=8)
            for (int ii = 0; ii < 8; ii++)
            {
                int a0 = A[i + ii][j + 0];
                int a1 = A[i + ii][j + 1];
                int a2 = A[i + ii][j + 2];
                int a3 = A[i + ii][j + 3];
                int a4 = A[i + ii][j + 4];
                int a5 = A[i + ii][j + 5];
                int a6 = A[i + ii][j + 6];
                int a7 = A[i + ii][j + 7];
                B[j + 0][i + ii] = a0;
                B[j + 1][i + ii] = a1;
                B[j + 2][i + ii] = a2;
                B[j + 3][i + ii] = a3;
                B[j + 4][i + ii] = a4;
                B[j + 5][i + ii] = a5;
                B[j + 6][i + ii] = a6;
                B[j + 7][i + ii] = a7;
            }
    for(int i = 0; i < 67;i++)
        for(int j = 56; j < 61; j++)
                B[j][i] = A[i][j];
       for(int j = 0; j < 61; j++)
    for(int i = 56; i < 67; i++)
               B[j][i] = A[i][j];
}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc);

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc);

    registerTransFunction(test32x32_trans, trans_test32x32_desc);

    registerTransFunction(test64x64_trans, trans_test64x64_desc);
    
    registerTransFunction(test61x67_trans, trans_test61x67_desc);
}

/*
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

