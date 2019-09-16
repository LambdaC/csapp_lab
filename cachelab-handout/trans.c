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
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            for (int ii = 0; ii < 8; ii++)
            {
                int a0 = A[i*8 + ii][j*8 + 0];
                int a1 = A[i*8 + ii][j*8 + 1];
                int a2 = A[i*8 + ii][j*8 + 2];
                int a3 = A[i*8 + ii][j*8 + 3];
                int a4 = A[i*8 + ii][j*8 + 4];
                int a5 = A[i*8 + ii][j*8 + 5];
                int a6 = A[i*8 + ii][j*8 + 6];
                int a7 = A[i*8 + ii][j*8 + 7];
                B[j*8 + 0][i*8 + ii] = a0;
                B[j*8 + 1][i*8 + ii] = a1;
                B[j*8 + 2][i*8 + ii] = a2;
                B[j*8 + 3][i*8 + ii] = a3;
                B[j*8 + 4][i*8 + ii] = a4;
                B[j*8 + 5][i*8 + ii] = a5;
                B[j*8 + 6][i*8 + ii] = a6;
                B[j*8 + 7][i*8 + ii] = a7;
            }
    }
    else if(M == 64 && N == 64)
    {
    for (int i = 0; i < 16; i++)
        for (int j = 0; j < 16; j++)
            for (int ii = 0; ii < 4; ii++)
            {
                int a0 = A[i * 4 + ii][j * 4 + 0];
                int a1 = A[i * 4 + ii][j * 4 + 1];
                int a2 = A[i * 4 + ii][j * 4 + 2];
                int a3 = A[i * 4 + ii][j * 4 + 3];
                B[j * 4 + 0][i * 4 + ii] = a0;
                B[j * 4 + 1][i * 4 + ii] = a1;
                B[j * 4 + 2][i * 4 + ii] = a2;
                B[j * 4 + 3][i * 4 + ii] = a3;
            }
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

char trans_test_desc[] = "My Test function";
void test_trans(int M, int N, int A[N][M], int B[M][N])
{
    int a0, a1, a2, a3;
    for(int i = 0; i < 64; i+=4)
    for(int j = 0; j < 64; j+=4)
    for(int ii = 0; ii < 4; ii++)
    {
        a0 = A[i + ii][j + 0];
        a1 = A[i + ii][j + 1];
        a2 = A[i + ii][j + 2];
        a3 = A[i + ii][j + 3];
        B[j + 0][i + ii] = a0;
        B[j + 1][i + ii] = a1;
        B[j + 2][i + ii] = a2;
        B[j + 3][i + ii] = a3;
    }

    for(int j = 4; j < 64; j+=4)
        for(int ii = 0; ii < j; ii++)
        {
            a0 = A[ii][j + 0];
            a1 = A[ii][j + 1];
            a2 = A[ii][j + 2];
            a3 = A[ii][j + 3];
            B[j + 0][ii] = a0;
            B[j + 1][ii] = a1;
            B[j + 2][ii] = a2;
            B[j + 3][ii] = a3;
        }

    for(int i = 4; i < 64; i+=4)
       for(int j = 0; j < i; j+=4)
       for(int ii = 0; ii < 4; ii++)
       {
           a0 = A[i+ii][j + 0];
           a1 = A[i+ii][j + 1];
           a2 = A[i+ii][j + 2];
           a3 = A[i+ii][j + 3];
           B[j + 0][i + ii] = a0;
           B[j + 1][i + ii] = a1;
           B[j + 2][i + ii] = a2;
           B[j + 3][i + ii] = a3;
       }
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

    registerTransFunction(test_trans, trans_test_desc); 

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

