//
// Created by Emma Gouné on 04/06/2023.
//
//
#include "headerfile.h"

//test matrices
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
                   {7, 200, 4, 1, 4, 1, 6,  20}};
float kernel[3][3] = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};


int main() {

    // ---------------------- 2D Convolution ----------------------

    printf("%s\n", "----------------- Image -----------------");
    dispIm(4, 4, im3);
    printf("%s\n", "----------------- Kernel -----------------");
    dispIm( 3, 3, kernel);
    printf("%s\n", "----------------- Convolution -----------------");
    convolution( 3, kernel, 6 , 6, im);


    // ---------------------- Max Pooling ----------------------
    float pool_mat[2][2] ;
    printf("%s\n", "----------------- Max Pooling -----------------");
    max_pooling( 2, pool_mat, 4 , 4 , im3);

    // ---------------------- Edge detection ----------------------

    int i, j, temp = 0;
    int width = 13, height = 13;
    // This array will be our image for the sobel filter
    int pixel[13][13] = {
            { 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15 },
            { 31, 31, 31, 200, 200, 200, 31, 31, 31, 31, 31, 31, 31},
            { 47, 47, 200, 47, 47, 47, 200, 200, 47, 47, 47, 47, 47},
            { 63, 200, 63, 63, 63, 63, 63, 63, 200, 63, 63, 63, 63},
            { 79, 200, 79, 79, 79, 79, 79, 79, 200, 79, 79, 79, 79},
            { 95, 200, 95, 95, 95, 95, 95, 95, 200, 95, 95, 95, 95 },
            { 63, 200, 63, 63, 63, 63, 63, 63, 200, 63, 63, 63, 63},
            { 79, 200, 79, 79, 79, 79, 79, 79, 200, 79, 79, 79, 79},
            { 95, 200, 95, 95, 95, 95, 95, 200, 95, 95, 95, 95, 95 },
            { 15, 15, 200, 15, 15, 15, 200, 15, 15, 15, 15, 15, 15 },
            { 31, 31, 31, 200, 200, 200, 31, 31, 31, 31, 31, 31, 31},
            { 47, 47, 200, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47},
            { 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63},
    };

    // convert it to a pgm file and save it in dir (can vbe read with LibreOffice)
    FILE* pgmimg;
    pgmimg = fopen("C:\\Users\\milky\\CLionProjects\\tagwalk1\\pgmimg.pgm", "wb");

    // Writing Magic Number to the File
    fprintf(pgmimg, "P2\n");

    // Writing Width and Height
    fprintf(pgmimg, "%d %d\n", width, height);

    // Writing the maximum gray value
    fprintf(pgmimg, "255\n");
    int count = 0;
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            temp = pixel[i][j];

            // Writing the gray values in the 2D array to the file
            fprintf(pgmimg, "%d ", temp);
        }
        fprintf(pgmimg, "\n");
    }


    fclose(pgmimg);

    /* -------------------- SOBEL filter ----------------------
     * To do this I used the PGM structure (see header) to store
     * the derivatives, dimensions, pixel data etc.
     * */

    pgm image, out_image;
    char dir[200] ="C:\\Users\\milky\\CLionProjects\\tagwalk1\\pgmimg.pgm"; // enter your directory path

    read_pgm_file(dir, &image);
    init_out_image(&out_image, image);
    sobel_edge_detector(&image, &out_image);

    normalization(&out_image, out_image.imageData);
    normalization(&out_image, out_image.gx);
    normalization(&out_image, out_image.gy);


    write_pgm_file(&out_image, dir, out_image.imageData, ".G.pgm");
    printf("\nGradient saved: %s \n", dir);
    write_pgm_file(&out_image, dir, out_image.gx, ".GX.pgm");
    printf("Gradient X saved: %s \n", dir);
    write_pgm_file(&out_image, dir, out_image.gy, ".GY.pgm");
    printf("Gradient Y saved: %s \n", dir);

    free(image.imageData);
    free(out_image.imageData);
    free(out_image.gx);
    free(out_image.gy);

    return 0;
}
