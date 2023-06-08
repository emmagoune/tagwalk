//
// Created by Emma Gouné on 08/06/2023.
// Contains the methods related to PGM files, this follows standard literature.
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "headerfile.h"


int isspace(int argument);


void init_out_image( pgm* out, pgm image){
    int i, j;
    strcpy(out->version, image.version);
    out->width = image.width;
    out->height = image.height;
    out->maxGrayLevel = image.maxGrayLevel;

    out->imageData = (int**) calloc(out->height, sizeof(int*));
    for(i = 0; i < out->height; i++) {
        out->imageData[i] = calloc(out->width, sizeof(int));
    }

    out->gx = (int**) calloc(out->height, sizeof(int*));
    for(i = 0; i < out->height; i++) {
        out->gx[i] = calloc(out->width, sizeof(int));
    }

    out->gy = (int**) calloc(out->height, sizeof(int*));
    for(i = 0; i < out->height; i++) {
        out->gy[i] = calloc(out->width, sizeof(int));
    }

    for(i = 0; i < out->height; i++) {
        for(j = 0; j < out->width; j++) {
            out->imageData[i][j] = image.imageData[i][j];
            out->gx[i][j] = image.imageData[i][j];
            out->gy[i][j] = image.imageData[i][j];
        };
    }
}

void read_comments(FILE *input_image) {
    char ch;
    char line[100];

    while ((ch = fgetc(input_image)) != EOF && (isspace(ch)))  {
        ;
    }
    if (ch == '#') {
        fgets(line, sizeof(line), input_image);
    }
    else {
        fseek(input_image, -2L, SEEK_CUR);
    }
}

void read_pgm_file(char* dir, pgm* image) {
    FILE* input_image;
    int i, j, num;

    input_image = fopen(dir, "rb");
    if (input_image == NULL) {
        printf("File could not opened!");
        return;
    }

    fgets(image->version, sizeof(image->version), input_image);
    read_comments(input_image);

    fscanf(input_image, "%d %d %d", &image->width, &image->height, &image->maxGrayLevel);

    image->imageData = (int**) calloc(image->height, sizeof(int*));
    for(i = 0; i < image->height; i++) {
        image->imageData[i] = calloc(image->width, sizeof(int));

    }

    if (strcmp(image->version, "P2") == 0) {
        for (i = 0; i < image->height; i++) {
            for (j = 0; j < image->width; j++) {
                fscanf(input_image, "%d", &num);
                image->imageData[i][j] = num;
            }
        }
    }
    else if (strcmp(image->version, "P5") == 0) {
        char *buffer;
        int buffer_size = image->height * image->width;
        buffer = (char*) malloc( ( buffer_size + 1) * sizeof(char));

        if(buffer == NULL) {
            printf("Can not allocate memory for buffer! \n");
            return;
        }
        fread(buffer, sizeof(char), image->width * image-> height, input_image);
        for (i = 0; i < image->height * image ->width; i++) {
            image->imageData[i / (image->width)][i % image->width] = buffer[i];
        }
        free(buffer);
    }
    fclose(input_image);
    printf("_______________IMAGE INFO__________________\n");
    printf("Version: %s \nWidth: %d \nHeight: %d \nMaximum Gray Level: %d \n", image->version, image->width, image->height, image->maxGrayLevel);
}

void padding(pgm* image) {
    int i;
    for (i = 0; i < image->width; i++) {
        image->imageData[0][i] = 0;
        image->imageData[image->height - 1][i] = 0;
    }

    for (i = 0; i < image->height; i++) {
        image->imageData[i][0] = 0;
        image->imageData[i][image->width - 1] = 0;
    }
}

void write_pgm_file(pgm* image, char dir[], int** matrix, char name[]) {
    FILE* out_image;
    int i, j, count = 0;

    char* token = strtok(dir, ".");
    if (token != NULL) {
        strcat(token, name);
        out_image = fopen(token, "wb");
    }

    out_image = fopen(dir, "wb");
    fprintf(out_image, "%s\n", image->version);
    fprintf(out_image, "%d %d\n", image->width, image->height);
    fprintf(out_image, "%d\n", image->maxGrayLevel);

    if (strcmp(image->version, "P2") == 0) {
        for(i = 0; i < image->height; i++) {
            for(j = 0; j < image->width; j++) {
                fprintf(out_image,"%d", matrix[i][j]);
                if (count % 17 == 0)
                    fprintf(out_image,"\n");
                else
                    fprintf(out_image," ");
                count ++;
            }
        }
    }
    else if (strcmp(image->version, "P5") == 0) {
        for(i = 0; i < image->height; i++) {
            for(j = 0; j < image->width; j++) {
                char num = matrix[i][j];
                fprintf(out_image,"%c", num);
            }
        }
    }
    fclose(out_image);
}