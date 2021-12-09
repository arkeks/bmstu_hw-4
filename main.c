#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct graph
{
    int length;
    bool** matrix;
};

struct graph get_graph();
unsigned int get_bounds(struct graph* u_graph, size_t str_num);
unsigned int get_odd_num(struct graph* u_graph);

void graph_vis(struct graph);
void mem_clear(struct graph* graph_ptr);

int main(void)
{
    bool result;
    struct graph our_graph = get_graph();
    result = get_odd_num(&our_graph);
    printf("The number of odd degree vortexes is %u.", result);
    graph_vis(our_graph);
    mem_clear(&our_graph);
    system("mimeopen graph.png");
    return 0;
}

struct graph get_graph()
{
    int i;
    struct graph u_graph;
    //struct graph* graph_p = &u_graph;
    printf("Please, write the size of your adjacency matrix: ");   // Get the size of matrix in form of "4"
    scanf("%d", &u_graph.length);                                  // and assign it to the variables.
    bool** matrix = (bool**) malloc(u_graph.length * sizeof(bool*));
    for(i = 0; i < u_graph.length; ++i)                                   // Create a two-dimensional bool array and
    {                                                                     // and allocate memory for it.
        matrix[i] = (bool*) malloc(u_graph.length * sizeof(bool));
    }
    printf("   |");
    for (i = 1; i <= u_graph.length; ++i)  // output of the column numeration
    {
        printf("%d ", i);
    }
    printf("\n");
    for (i = 0; i < u_graph.length; ++i)   // input the user's matrix into 2d array
    {
        printf("  %d|", (i + 1));
        for(int g = 0; g < u_graph.length; ++g)
        {
            scanf(" %3d", (int*)&matrix[i][g]);
        }
    }
    u_graph.matrix = matrix;
    return u_graph;
}

unsigned int get_bounds(struct graph* u_graph, size_t str_num) {
    unsigned int bounds = 0;
    for (size_t i = 0; i < u_graph -> length; i++) {
        bounds += u_graph -> matrix[str_num][i];
    }
    return bounds;
}

unsigned int get_odd_num(struct graph* u_graph) {
    unsigned int odd_num, bounds_num;
    odd_num = 0;
    for (size_t i = 0; i < u_graph -> length; i++) {
        bounds_num = get_bounds(u_graph, i);
        if ((bounds_num % 2) == 0);
        else {
            ++odd_num;
        }
    }
    return odd_num;
}

void graph_vis(struct graph u_graph)
{
    FILE *dot = fopen("graph.dot", "w");
    fprintf(dot, "graph test {\n\t");
    for (int i = 0; i < u_graph.length; ++i)
    {
        for (int g = i; g < u_graph.length; ++g)
        {
            if (u_graph.matrix[i][g] == 0)
            {
                fprintf(dot, "%d;\n\t", (i+1));
            }
            for (int k = 0; k < u_graph.matrix[i][g]; ++k)
            {
                fprintf(dot, "%d -- %d;\n\t", (i+1), (g+1));
            }
        }
    }
    fprintf(dot, "}");
    fclose(dot);
    system("dot -Tpng graph.dot -o graph.png");
}
void mem_clear(struct graph* graph_ptr)
{
    for (int i = 0; i < graph_ptr -> length; ++i)
    {
        free(graph_ptr -> matrix[i]);
    }
    free(graph_ptr -> matrix);
}