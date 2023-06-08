//
// Created by milky on 04/06/2023.
//
#include <stdio.h>

#ifndef TAGWALK1_HEADERFILE_H
#define TAGWALK1_HEADERFILE_H

void dispIm( int row, int col, float (*array)[col]);
void convolution( int kernel_col, float (*kernel)[kernel_col], int im_row,int im_col, float (*im)[im_col]);
void max_pooling( int pool_col, float (*pool_mat)[pool_col], int im_row, int im_col, float (*im)[im_col]);
float max_mat(int row, int col, float (*mat)[col]);

int isspace(int argument);
typedef struct {
    char version[3];
    int width;
    int height;
    int maxGrayLevel;
    int **imageData;
    int **gx;
    int **gy;
} pgm;
void init_out_image( pgm* out, pgm image);
void read_comments(FILE *input_image);
void read_pgm_file(char* dir, pgm* image);
void padding(pgm* image);
int conv_sum(pgm* image, int kernel[3][3], int row, int col);
void sobel_edge_detector(pgm* image, pgm* out_image);
void normalization(pgm* image, int** matrix);
void write_pgm_file(pgm* image, char dir[], int** matrix, char name[]);
#endif //TAGWALK1_HEADERFILE_H


