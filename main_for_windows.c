#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct graph
{
    size_t length;
    unsigned int** matrix;
};

typedef struct Vertex {
    size_t vertex;
    unsigned int bounds_num;
} Vertex;

struct graph get_graph();
unsigned int get_bounds(struct graph* u_graph, size_t str_num);
unsigned int get_odd_num(struct graph* u_graph, Vertex* array);

void graph_vis(struct graph);
void mem_clear(struct graph* graph_ptr, Vertex* vert_arr);
void print_vertexes(Vertex* vertexes, size_t vert_num);
int compare(const void* vert1, const void* vert2);

int main(void)
{
    unsigned int result;
    struct graph our_graph = get_graph();

    Vertex* vertexes = (Vertex*)malloc(sizeof(Vertex) * our_graph.length);  // alloc memory for odd vertexes array
    if (vertexes == NULL) {
        printf("memalloc error\n");
        return 1;
    }

    result = get_odd_num(&our_graph, vertexes);
    printf("\nThe number of odd degree vertexes is %u.\n\n", result);

    qsort(vertexes, result, sizeof(Vertex), compare);
    print_vertexes(vertexes, result);

    graph_vis(our_graph);

    mem_clear(&our_graph, vertexes);
    return 0;
}

struct graph get_graph()
{
    int i;
    struct graph u_graph;
    printf("Please, write the size of your adjacency matrix: ");   // Get the size of matrix in form of "4"
    scanf("%zu", &u_graph.length);                                  // and assign it to the variables.
    unsigned int** matrix = (unsigned int**) malloc(u_graph.length * sizeof(unsigned int*));
    if (matrix == NULL) {
        printf("memalloc error\n");
        exit(1);
    }

    for(i = 0; i < u_graph.length; ++i)                                   // Create a two-dimensional bool array and
    {                                                                     // and allocate memory for it.
        matrix[i] = (unsigned int*) malloc(u_graph.length * sizeof(unsigned int));
        if (matrix[i] == NULL) {
            printf("memalloc error\n");
            exit(1);
        }
    }

    printf("   |");
    for (i = 0; i < u_graph.length; ++i)  // output of the column numeration
    {
        printf("%d ", i);
    }
    printf("\n");
    for (i = 0; i < u_graph.length; ++i)   // input the user's matrix into 2d array
    {
        printf("  %d|", i);
        for(int g = 0; g < u_graph.length; ++g)
        {
            scanf(" %3u", (unsigned int*)&matrix[i][g]);
        }
    }
    for (size_t i = 1; i < u_graph.length; ++i) {
        for (size_t g = 0; g < i; ++g) {
            if (matrix[i][g] != matrix[g][i]) {
                printf("Invalid graph!\n");
                exit(1);
            }
        }
    }
    u_graph.matrix = matrix;
    return u_graph;
}

unsigned int get_bounds(struct graph* u_graph, size_t str_num) {
    unsigned int bounds = 0;
    for (size_t i = 0; i < u_graph->length; i++) {
        bounds += u_graph->matrix[str_num][i];
    }
    return bounds;
}

unsigned int get_odd_num(struct graph* u_graph, Vertex* array) {
    unsigned int odd_num, bounds_num;
    odd_num = 0;
    for (size_t i = 0; i < u_graph -> length; i++) {
        bounds_num = get_bounds(u_graph, i);
        if ((bounds_num % 2) == 0) {
        }
        else {
            array[odd_num].vertex = i;
            array[odd_num].bounds_num = bounds_num;
            ++odd_num;
        }
    }
    return odd_num;
}

void graph_vis(struct graph u_graph)
{
    FILE* dot = fopen("graph.dot", "w");
    fprintf(dot, "graph test {\n\t");
    for (size_t i = 0; i < u_graph.length; ++i)
    {
        for (size_t g = i; g < u_graph.length; ++g)
        {
            if (u_graph.matrix[i][g] == 0)
            {
                fprintf(dot, "%zu;\n\t", i);
            }
            for (size_t k = 0; k < u_graph.matrix[i][g]; ++k)
            {
                fprintf(dot, "%zu -- %zu;\n\t", i, g);
            }
        }
    }
    fprintf(dot, "}");
    fclose(dot);
    system("dot F:\\bmstu-hw-4\\bmstu_hw-4\\hw-4\\graph.dot -Tbmp -o graph.PNG");
    system("rundll32  \"%ProgramFiles%\\Windows Photo Viewer\\PhotoViewer.dll\", ImageView_Fullscreen F:\\bmstu-hw-4\\bmstu_hw-4\\hw-4\\graph.PNG");
}
void mem_clear(struct graph* graph_ptr, Vertex* vert_arr)
{
    for (int i = 0; i < graph_ptr->length; ++i)
    {
        free(graph_ptr -> matrix[i]);
    }
    free(graph_ptr -> matrix);
    free(vert_arr);
}

void print_vertexes(Vertex* vertexes, size_t vert_num) {
    printf("Sorted odd vertexes:\n");
    for (size_t i = 0; i < vert_num; ++i) {
        printf("%zu ", vertexes[i].vertex);
    }
    printf("\n");
    for (size_t i = 0; i < vert_num; ++i) {
        printf("%u ", vertexes[i].bounds_num);
    }
    printf("\n\n");
}

int compare(const void* vert1, const void* vert2) {
    return ( ((Vertex*)vert1) -> bounds_num) - ( ((Vertex*)vert2) -> bounds_num);
}