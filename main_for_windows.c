#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct graph
{
    int length;
    bool** matrix;
};

typedef struct Vertex {
    unsigned int vertex;
    unsigned int bounds_num;
} Vertex;

struct graph get_graph();
unsigned int get_bounds(struct graph* u_graph, size_t str_num);
unsigned int get_odd_num(struct graph* u_graph, Vertex* array);

void graph_vis(struct graph);
void mem_clear(struct graph* graph_ptr, Vertex* vert_arr);
void print_vertexes(Vertex* vertexes, size_t vert_num);
void graph_open();
int compare(const void* vert1, const void* vert2);

int main(void)
{
    unsigned int result;
    struct graph our_graph = get_graph();
    Vertex* vertexes = (Vertex*)malloc(sizeof(Vertex) * our_graph.length);  // alloc memory for odd vertexes array

    result = get_odd_num(&our_graph, vertexes);
    printf("\nThe number of odd degree vertexes is %u.\n\n", result);

    graph_vis(our_graph);

    qsort(vertexes, result, sizeof(Vertex), compare);
    print_vertexes(vertexes, result);

    mem_clear(&our_graph, vertexes);
    graph_open();
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
            scanf(" %3d", (int*)&matrix[i][g]);
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
            printf("1\n");
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
    for (int i = 0; i < u_graph.length; ++i)
    {
        for (int g = i; g < u_graph.length; ++g)
        {
            if (u_graph.matrix[i][g] == 0)
            {
                fprintf(dot, "%d;\n\t", i);
            }
            for (int k = 0; k < u_graph.matrix[i][g]; ++k)
            {
                fprintf(dot, "%d -- %d;\n\t", i, g);
            }
        }
    }
    fprintf(dot, "}");
    fclose(dot);
    system("dot C:\\Users\\duhin\\source\\repos\\senyaloh\\graph.dot -Tbmp -o graph.PNG");
    system("rundll32  \"%ProgramFiles%\\Windows Photo Viewer\\PhotoViewer.dll\", ImageView_Fullscreen C:\\Users\\duhin\\source\\repos\\senyaloh\\graph.PNG");
}
void mem_clear(struct graph* graph_ptr, Vertex* vert_arr)
{
    for (int i = 0; i < graph_ptr -> length; ++i)
    {
        free(graph_ptr -> matrix[i]);
    }
    free(graph_ptr -> matrix);
    free(vert_arr);
}

void print_vertexes(Vertex* vertexes, size_t vert_num) {
    printf("Sorted odd vertexes:\n");
    for (size_t i = 0; i < vert_num; ++i) {
        printf("%u ", vertexes[i].vertex);
    }
    printf("\n");
    for (size_t i = 0; i < vert_num; ++i) {
        printf("%u ", vertexes[i].bounds_num);
    }
    printf("\n\n");
}

void graph_open() {
    getchar();
    do {
        printf("Press enter to open the graph.\n");
    } while(getchar() != '\n');
    system("mimeopen graph.png");
}

int compare(const void* vert1, const void* vert2) {
    return ( ((Vertex*)vert1) -> bounds_num) - ( ((Vertex*)vert2) -> bounds_num);
}