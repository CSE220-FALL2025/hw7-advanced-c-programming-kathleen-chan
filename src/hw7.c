#include "hw7.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

bst_sf* insert_bst_sf(matrix_sf *mat, bst_sf *root) {
    
    return NULL;
}

matrix_sf* find_bst_sf(char name, bst_sf *root) {
    return NULL;
}

void free_bst_sf(bst_sf *root) {
}

matrix_sf* add_mats_sf(const matrix_sf *mat1, const matrix_sf *mat2) {
    if(mat1 == NULL || mat2 == NULL)
        return NULL;
    if(mat1->num_rows != mat2->num_rows || mat1->num_cols != mat2->num_cols)
        return NULL;
    matrix_sf *sum = malloc(sizeof(matrix_sf) + (mat1->num_rows) * (mat1->num_cols) * sizeof(int));
    if(sum == NULL)
        return NULL;

    sum->name = '?';
    sum->num_rows = mat1->num_rows;
    sum->num_cols = mat1->num_cols;

    for(unsigned int i=0; i<mat1->num_rows; i++){
        for(unsigned int j=0; j<mat1->num_cols; j++){
            sum->values[i*mat1->num_cols + j] = mat1->values[i*mat1->num_cols + j] + mat2->values[i*mat1->num_cols + j];
        }
    }
    return sum;
}

matrix_sf* mult_mats_sf(const matrix_sf *mat1, const matrix_sf *mat2) {
    if(mat1 == NULL || mat2 == NULL)
        return NULL;
    if(mat1->num_cols != mat2->num_rows)
        return NULL;
    matrix_sf *product = malloc(sizeof(matrix_sf) + (mat1->num_rows) * (mat2->num_cols) * sizeof(int));
    if(product == NULL)
        return NULL;
        
    product ->name = '?';
    product->num_rows = mat1->num_rows;
    product->num_cols = mat2->num_cols;

    for(unsigned int i=0; i<mat1->num_rows; i++){
        for(unsigned int j=0; j<mat2->num_cols; j++){
            int sum = 0;
            for(unsigned int k=0; k<mat1->num_cols; k++){
                sum += mat1->values[i*mat1->num_cols+k] * mat2->values[k*mat2->num_cols+j];
            }
            product->values[i*mat2->num_cols+j] = sum;
        }
    }
    return product;
}

matrix_sf* transpose_mat_sf(const matrix_sf *mat) {
    if(mat == NULL)
        return NULL;

    matrix_sf *transpose = malloc(sizeof(matrix_sf) + (mat->num_rows) * (mat->num_cols) * sizeof(int));
    if(transpose == NULL)
        return NULL;

    transpose->name = '?';
    transpose->num_rows = mat->num_cols;
    transpose->num_cols = mat->num_rows;

    for(unsigned int i=0; i<mat->num_rows; i++){
        for(unsigned int j=0; j<mat->num_cols; j++){
            transpose->values[j*transpose->num_cols+i] = mat->values[i*mat->num_cols+j];
        }
    }
    return transpose;    
}

matrix_sf* create_matrix_sf(char name, const char *expr) {
    return NULL;
}

char* infix2postfix_sf(char *infix) {
    return NULL;
}

matrix_sf* evaluate_expr_sf(char name, char *expr, bst_sf *root) {
    return NULL;
}

matrix_sf *execute_script_sf(char *filename) {
   return NULL;
}

// This is a utility function used during testing. Feel free to adapt the code to implement some of
// the assignment. Feel equally free to ignore it.
matrix_sf *copy_matrix(unsigned int num_rows, unsigned int num_cols, int values[]) {
    matrix_sf *m = malloc(sizeof(matrix_sf)+num_rows*num_cols*sizeof(int));
    m->name = '?';
    m->num_rows = num_rows;
    m->num_cols = num_cols;
    memcpy(m->values, values, num_rows*num_cols*sizeof(int));
    return m;
}

// Don't touch this function. It's used by the testing framework.
// It's been left here in case it helps you debug and test your code.
void print_matrix_sf(matrix_sf *mat) {
    assert(mat != NULL);
    assert(mat->num_rows <= 1000);
    assert(mat->num_cols <= 1000);
    printf("%d %d ", mat->num_rows, mat->num_cols);
    for (unsigned int i = 0; i < mat->num_rows*mat->num_cols; i++) {
        printf("%d", mat->values[i]);
        if (i < mat->num_rows*mat->num_cols-1)
            printf(" ");
    }
    printf("\n");
}
