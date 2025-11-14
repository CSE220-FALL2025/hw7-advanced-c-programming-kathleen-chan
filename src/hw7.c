#include "hw7.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
typedef struct{
    char *data;
    int size;
    int top;
} Stack;

static Stack* create(int size){
    Stack *stack = malloc(sizeof(Stack));
    if(stack == NULL)
        return NULL;
    stack->data = malloc(size * sizeof(char));
    if(stack->data == NULL){
        free(stack);
        return NULL;
    }
    stack->top = -1;
    stack->size = size;
    return stack;
}

static void push(Stack *stack, char c){
    if(stack->top < stack->size-1)
        stack->data[++stack->top] = c;
}

static char pop(Stack *stack){
    if(stack->top == -1)
        return '\0';
    return stack->data[stack->top--];
}

static char peek(Stack *stack){
    if(stack->top == -1)
        return'\0';
    return stack->data[stack->top];
}
    
static int precedence(char c){
    if(c == '\'')
        return 3;
    if(c == '*')
        return 2;
    if(c == '+')
        return 1;
    return 0;
}

int is_right_associative(char c) {
    return c == '\'';
}

bst_sf* insert_bst_sf(matrix_sf *mat, bst_sf *root) {
    if(mat == NULL)
        return root;
    if(root == NULL){
        bst_sf *node = malloc(sizeof(bst_sf));
        if(node == NULL)
            return NULL;
        node->mat = mat;
        node->left_child = NULL;
        node->right_child = NULL;
        return node;
    }

    if(mat->name < root->mat->name)
        root->left_child = insert_bst_sf(mat, root->left_child);
    else if(mat->name > root->mat->name)
        root->right_child = insert_bst_sf(mat, root->right_child);
    return root;
}

matrix_sf* find_bst_sf(char name, bst_sf *root) {
    if(root == NULL)
        return NULL;
    
    if(root->mat->name == name)
        return root->mat;
    else if((name < root->mat->name))
        return find_bst_sf(name, root->left_child);
    else
        return find_bst_sf(name, root->right_child);
}

void free_bst_sf(bst_sf *root) {
    if(root == NULL)
        return;

    if(root->left_child != NULL)
        free_bst_sf(root->left_child);
    if(root->right_child != NULL)
        free_bst_sf(root->right_child);
    if(root->mat != NULL)
        free(root->mat);
    free(root);
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
            for(unsigned int k=0; k<mat1->num_cols; k++)
                sum += mat1->values[i*mat1->num_cols+k] * mat2->values[k*mat2->num_cols+j];
            product->values[i*mat2->num_cols+j] = sum;
        }
    }
    return product;
}

matrix_sf* transpose_mat_sf(const matrix_sf *mat) {
    if(mat == NULL)
        return NULL;
    matrix_sf *transpose = malloc(sizeof(matrix_sf) + (mat->num_cols) * (mat->num_rows) * sizeof(int));
    if(transpose == NULL)
        return NULL;

    transpose->name = '?';
    transpose->num_rows = mat->num_cols;
    transpose->num_cols = mat->num_rows;

    for(unsigned int i=0; i<mat->num_rows; i++){
        for(unsigned int j=0; j<mat->num_cols; j++)
            transpose->values[j*transpose->num_cols+i] = mat->values[i*mat->num_cols+j];
    }
    return transpose;    
}

matrix_sf* create_matrix_sf(char name, const char *expr) {
    if(expr == NULL)
        return NULL;
    unsigned int rows = 0, cols = 0;
    if(sscanf(expr, "%u", &rows) != 1 || rows == 0)
        return NULL;
    while (*expr && !isspace(*expr))
        expr++;
    while (*expr && isspace(*expr))
        expr++;
    if(sscanf(expr, "%u", &cols) != 1 || cols == 0)
        return NULL;
    while (*expr && !isspace(*expr)) 
        expr++;
    while (*expr && isspace(*expr)) 
    expr++;

    const char *start = strchr(expr,'[');
    const char *end = strchr(expr,']');
    if(start == NULL || end == NULL || end<=start)
        return NULL;

    size_t length = end - start - 1;
    char *content = malloc(length + 1);
    if(content == NULL)
        return NULL;
    memcpy(content, start + 1, length);
    content[length] = '\0';
    
    matrix_sf *create = malloc(sizeof(matrix_sf) + rows * cols * sizeof(int));
    if(create == NULL){
        free(content);
        return NULL;
    }

    create->name = name;
    create->num_rows = rows;
    create->num_cols = cols;

    unsigned int count = 0;
    char *tok = strtok(content, " ;,\n\t");
    while(tok != NULL){
        create->values[count++] = atoi(tok);
        tok = strtok(NULL, " ;,\n\t");
    }
    free(content);
    if(count != rows * cols){
        free(create);
        return NULL;
    }
    return create;
}

char* infix2postfix_sf(char *infix) {
    if(infix == NULL)
        return NULL;

    char *postfix = malloc(2 * (strlen(infix) + 1));
    if(postfix == NULL)
        return NULL;
    Stack *stack = create(strlen(infix));
    int j = 0;
    for(int i=0; i<strlen(infix); i++){
        char c = infix[i];
        if(isalpha(c))
            postfix[j++] = c;
        else if(c == '(')
            push(stack, c);
        else if(c == ')'){
            while(stack->top != -1 && peek(stack) != '(')
                postfix[j++] = pop(stack);
            if(stack->top != -1)
                pop(stack);
        } else if(c == '\'' || c == '*' || c == '+'){
            while(stack->top != -1 && peek(stack) != '('){
                char top = peek(stack);
                if(precedence(top) > precedence(c) || (precedence(top) == precedence(c) && !is_right_associative(c)))
                    postfix[j++] = pop(stack);
                else
                    break;
            }
            push(stack, c);
        }
    }
    while(stack->top != -1)
        postfix[j++] = pop(stack);
    postfix[j] = '\0';
    free(stack->data);
    free(stack);
    return postfix;
}

typedef struct{
    matrix_sf **data;
    int size;
    int top;
} MatrixStack;

MatrixStack* create_matrix_stack(int size){
    MatrixStack *stack = malloc(sizeof(MatrixStack));
    if(stack == NULL)
        return NULL;
    stack->data = malloc(size * sizeof(matrix_sf*));
    if(stack->data == NULL){
        free(stack);
        return NULL;
    }
    stack->top = -1;
    stack->size = size;
    return stack;
}

void push_matrix(MatrixStack *stack, matrix_sf *matrix){
    if(stack->top < stack->size-1) 
        stack->data[++stack->top] = matrix;
}

matrix_sf* pop_matrix(MatrixStack *stack){
    if(stack->top == -1)
        return NULL;
    return stack->data[stack->top--];
}

matrix_sf* evaluate_expr_sf(char name, char *expr, bst_sf *root) {    
    if(expr == NULL)
        return NULL;
    char *postfix = infix2postfix_sf(expr);
    if(postfix == NULL)
        return NULL;
    MatrixStack *stack = create_matrix_stack(strlen(postfix));
    if(stack == NULL){
        free(postfix);
        return NULL;
    }

    for(int i=0; i<strlen(postfix); i++){
        char c = postfix[i];
        if(isalpha(c)){
            matrix_sf *matrix = find_bst_sf(c, root);
            if(matrix == NULL){
                free(stack->data);
                free(stack);
                free(postfix);
                return NULL;
            }
            push_matrix(stack, matrix);
        } else if(c == '+'){
            matrix_sf *b = pop_matrix(stack);
            matrix_sf *a = pop_matrix(stack);
            if(a == NULL || b == NULL){
                free(stack->data);
                free(stack);
                free(postfix);
                return NULL;
            }
            matrix_sf *sum = add_mats_sf(a,b);
            push_matrix(stack, sum);
        } else if(c == '*'){
            matrix_sf *b = pop_matrix(stack);
            matrix_sf *a = pop_matrix(stack);
            if(a == NULL || b == NULL){
                free(stack->data);
                free(stack);
                free(postfix);
                return NULL;
            }
            matrix_sf *product = mult_mats_sf(a,b);
            push_matrix(stack, product);
        } else if(c == '\''){
            matrix_sf *a = pop_matrix(stack);
            if(a == NULL){
                free(stack->data);
                free(stack);
                free(postfix);
                return NULL;
            }
            matrix_sf *transpose = transpose_mat_sf(a);
            push_matrix(stack, transpose);
        }
    }
    matrix_sf *evaluated = pop_matrix(stack);
    if(evaluated != NULL)
        evaluated->name = name;
    free(stack->data);
    free(stack);
    free(postfix);
    return evaluated;
}

matrix_sf *execute_script_sf(char *filename) {
    if(filename == NULL)
        return NULL;
    FILE *f = fopen(filename, "r");
    if(f == NULL)
        return NULL;
    bst_sf *root = NULL;
    matrix_sf *last_matrix = NULL;

    char line[1024];
    while(fgets(line, sizeof(line), f) != NULL){
        line[strcspn(line, "\n")] = '\0';
        if(strlen(line) == 0)
            continue;
        char name = line[0];
        char *expr = strchr(line, '=');
        if(expr == NULL) 
            continue;
        expr++;
        while(*expr == ' ')
            expr++;
        matrix_sf *mat = evaluate_expr_sf(name, expr, root);
        if(mat == NULL)
            continue;
        root = insert_bst_sf(mat, root);
        last_matrix = mat;
    }
    fclose(f);
    return last_matrix;
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
