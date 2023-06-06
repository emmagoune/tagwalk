#include "headerfile.h"

float im[6][6]= {{7, 6, 5, 5, 6, 7}, {6, 4, 3, 3,  4, 6, },
                 {5, 3, 2, 2, 3, 5, }, {5, 3, 2, 2, 3, 5} ,
                 {6, 4, 3, 3, 4, 6}, {7, 6, 5, 5, 6, 7}};

float im2[4][4] = {{1, 7, 7,5},{5, 2, 7,12}, {-1, 5, 5, -9}, {6, 21, 20, 1}};
float im3[4][4] = {{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}};
float im4[8][8] = {{9, 12.96933, 3.555, 7, 5, 4, 6,0},
                   {5,6,1, 5, 41,6,8,4 },
                   {25,8,0,-60, 0, -8,62,  7 },
                   {2,6,6,9, 23, 1, 4,2},
                   {7, 10, 7, 16, 1, 2, 5, 6},
                   {7, 10, 7, 3, 4, 1, 6,  7},
                   {1, 5, 7, 4, 41, 31, 6,  7},
                   {7, 100, 4, 1, 4, 1, 6,  20}};

int main() {

    float kernel[3][3] = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};
    float pool_mat[2][2] ;

    printf("%s\n", "----------------- Kernel -----------------");
    dispIm( 2, 2, pool_mat);
    printf("%s\n", "----------------- Image -----------------");
    dispIm(4, 4, im3);
    //printf("%s\n", "----------------- Convolution -----------------");
    //convolution( 3, kernel, 6 , 6, im);
    printf("%s\n", "----------------- Max Pooling -----------------");
    max_pooling( 2, pool_mat, 4 , 4 , im3);
    return 0;
}
