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
#endif //TAGWALK1_HEADERFILE_H


