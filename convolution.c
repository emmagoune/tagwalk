//
// Created by Emma Gouné on 04/06/2023.
// This is the filter methods with:
// 2d convolution, max pooling and sobel filters
//
#include "headerfile.h"
#include <math.h>
#include <string.h>

// ---------------------- Display the array ----------------------

void dispIm( int row, int col, float (*array)[col])
{

    int i,j ;
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {

            printf("%f ", array[i][j]);
        }
        printf("\n");
    }
}

// ---------------------- 2D convolution ----------------------

void convolution( int kernel_col, float (*kernel)[kernel_col], int im_row, int im_col, float (*im)[im_col])
{
    int row = im_row +2;
    int col = im_col +2;
    float convoluted[6][6];
    int K = 3;
    int i , ii, j, jj ;

    float arr[row][col];
    memset(arr, 0, sizeof arr);

    for (i = 1; i < row ; ++i) // fix computation on the edges
    {
        for (j= 1; j < col ; ++j){
            arr[i][j]= im[i-1][j-1];
        }

    }

    int ligne = 0;
    int colo = 0;

    for (i = K/2; i < (row - K/2); ++i) // iterate over image
    {
        for (j = K / 2; j < col - K / 2; ++j)
        {
            float sum = 0;
            for (ii = - K / 2; ii <= K / 2; ++ii) // iterate over kernel
            {
                for (jj = - K / 2; jj <= K / 2; ++jj)
                {
                    float image = arr[i + ii][j +jj];
                    float coeff = kernel[ii + K / 2][jj + K / 2];

                    sum += image * coeff;

                }
            }
            convoluted[ligne][colo] = sum ;
            colo +=1 ;
        }
        ligne += 1;
        colo = 0;
    }


    dispIm( im_row, im_col, convoluted);

}

// ---------------------- Max Pooling ----------------------

void max_pooling( int pool_col, float (*pool_mat)[pool_col], int im_row, int im_col, float (*im)[im_col]){
    int row, col;
    if (im_col < im_row){
        row = im_row;
        col = im_row;}
    else if (im_col < im_row){
        row = im_col;
        col = im_col ;}
    else {
        row = im_row;
        col = im_col;
    }

    int i, j, k , l;
    int mat_i = 0 ;
    int mat_j = 0 ;
    float arr[row][col];
    memset(arr, 0, sizeof arr);

    for (k = 0; k < row ; ++k) // fix computation on the edges, padding
    {
        for (l= 0; l < col ; ++l){
            arr[k][l]= im[k][l];
        }

    }
    int stride = row / pool_col;

    float buffermat[stride][stride];
    memset(buffermat, 0, sizeof buffermat);

    for (int   i= 0;  i < row; i += stride ) {
        if (i+pool_col > row){
            break;
        }
        for ( int j = 0 ; j < col ; j+= stride ){
            if (j + pool_col > col){
                break;
            }
            int n = 0;
            int m = 0;
            for(int x=i; x<i+stride; x++){
                m= 0;
                for(int y=j; y<j + stride; y++){
                    buffermat[n][m] = arr[x][y];
                    m += 1;
                }
                n += 1;
            }
            float max = max_mat( stride, stride, buffermat);
            pool_mat[mat_i][mat_j] = max;
            mat_j += 1;
        }
        mat_i +=1;
        j = 0;
        mat_j = 0;
    }
    dispIm( pool_col, pool_col, pool_mat);
}


float max_mat(int row, int col, float (*mat)[col]) {
    int i, j;
    float max;
    max = mat[0][0];

    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            if (mat[i][j] > max)
                max = mat[i][j];
        }
    }
    return max;
}

// ---------------------- SOBEL EDGE DETECTOR ----------------------


int conv_sum(pgm* image, int kernel[3][3], int row, int col) {
    int i, j, sum = 0;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            sum += image->imageData[i + row][j + col] * kernel[i][j];
        }
    }
    return sum;
}

void sobel_edge_detector(pgm* image, pgm* out_image) {
    int i, j, gx, gy;
    int mx[3][3] = {
            {-1, 0, 1},
            {-2, 0, 2},
            {-1, 0, 1}
    };
    int my[3][3] = {
            {-1, -2, -1},
            {0, 0, 0},
            {1, 2, 1}
    };

    for (i = 1; i < image->height - 2; i++) {
        for (j = 1; j < image->width - 2; j++) {
            gx = conv_sum(image, mx, i, j);
            gy = conv_sum(image, my, i, j);
            out_image->imageData[i][j] = sqrt(gx*gx + gy*gy);
            out_image->gx[i][j] = gx;
            out_image->gy[i][j] = gy;
        }
    }

}

void normalization(pgm* image, int** matrix) {
    int min = 1000000, max = 0, i, j;

    for(i = 0; i < image->height; i++) {
        for(j = 0; j < image->width; j++) {
            if (matrix[i][j] < min) {
                min = matrix[i][j];
            }
            else if (matrix[i][j] > max) {
                max = matrix[i][j];
            }
        }
    }

    for(i = 0; i < image->height; i++) {
        for(j = 0; j < image->width; j++) {
            double ratio = (double) (matrix[i][j] - min) / (max - min);
            matrix[i][j] = ratio * 255;
        }
    }
}
