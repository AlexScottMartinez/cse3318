// My special.txt is a special case because every line only has 1 item

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct struct_stack
{
    int size;
    int* stk;
    int top;
}Stack;


typedef struct dynamic_array
{
    int size;
    int num_elem;
    int* array;
}vector;


struct struct_graph
{
    int nodes;
    int** matrix;
};
typedef struct struct_graph* graphPT;


int getNumberNodes(char* filename, char*** str_nodes);
int** createMatrix(int rows, int columns);
void freeMemoryMatrix(int** array, int nodes);
graphPT createNewGraph(int nodes);
void freeMemoryGraph(graphPT g);
void addEdge(graphPT* g, int x, int y);
int findIndex(char** str_nodes, char* token, int nodes);
void freeMemoryChar(char** words, int n);
void printMatrix(graphPT graph);
void readFile(char* filename, graphPT* g, char** str_nodes);
void pushStack(Stack* s, int item);
int popStack(Stack* s);
void dfsVisit(graphPT* g, Stack* s, vector* white, vector* black, vector* gray, int** d, int** f, int* matrix, int* time, int current, int* cycle);



int getNumberNodes(char* filename, char*** str_nodes)
{
    char line[101];
    char* token;
    int counter = 0;

    FILE* fp = fopen(filename, "r");
    if(fp == NULL)
    {
        printf("Could not open file %s. Exit.\n", filename);
        return -1;
    }
    
    while(!feof(fp))
    {
        fgets(line, 101, fp);
        counter++;
    }
    
    fseek(fp, 0, SEEK_SET);
    *str_nodes = (char**) malloc(sizeof(char*) * counter);
    for(int i = 0; i<counter; i++)
    {
        (*str_nodes)[i] = (char*) malloc(sizeof(char*) * 31);
        if((*str_nodes)[i] == NULL)
        {
            printf("Error Out of Memory\n");
        }
        strcpy((*str_nodes)[i], "" );
    }
    
    int b = 0;
    while(!feof(fp))
    {
        fgets(line, 1001, fp);
        token = strtok(line, " \n");
        strcpy((*str_nodes)[b], token);
        b++;
    }
    
    fclose(fp);
    return counter; 
}

int** createMatrix(int rows, int columns)
{
    int** matrix = (int**) malloc(sizeof(int*) * rows);
    for(int i = 0; i<rows; i++)
    {
        matrix[i] = (int*) malloc(sizeof(int) * columns);
    }
    
    return matrix;
}

void freeMemoryMatrix(int** array, int nodes)
{
    for(int i = 0; i<nodes; i++)
    {
        free(array[i]);
    }
    free(array);
}

graphPT createNewGraph(int nodes)
{
    graphPT temp = malloc(sizeof(*temp));
    temp->nodes = nodes;
    temp->matrix = createMatrix(nodes, nodes);
    
    for(int i = 0; i<nodes; i++)
    {
        for(int j = 0; j<nodes; j++)
        {
            temp->matrix[i][j] = 0;
        }
    }
    
    return temp;
}

void freeMemoryGraph(graphPT g)
{
    if(g == NULL)
    {
        return;
    }
    freeMemoryMatrix(g->matrix, g->nodes);
    free(g);
}

void addEdge(graphPT* g, int x, int y)
{
    (*g)->matrix[x][y] = 1;
}

int findIndex(char** str_nodes, char* token, int nodes)
{
    for(int i = 0; i<nodes; i++)
    {
        if(strcmp(str_nodes[i], token) == 0)
        {
            return i;
        }
    }
    return -1;
}

void freeMemoryChar(char** words, int n)
{
    for(int i = 0; i<n; i++)
    {
        free(words[i]);
    }
    free(words);
}

void printMatrix(graphPT graph)
{
    printf("\n\n");
    int nod = graph->nodes;
    printf("Adjacency matrix: \n");
    printf("   |   ");
    for(int i = 0; i<nod - 1; i++)
    {
        printf("%d   ", i);
    }
    printf("\n");
    
    for(int j = 0; j<nod - 1; j++)
    {
        printf("------");
    }
    printf("\n");
    
    for(int k = 0; k<nod - 1; k++)
    {
        printf("  %d|", k);
        for(int l = 0; l<nod - 1; l++)
        {
           printf("   %d", (graph->matrix)[k][l]); 
        }
        printf("\n");
    }
}

void readFile(char* filename, graphPT* g, char** str_nodes)
{
    FILE* fp = fopen(filename, "r");
    char line[1001];
    char* token;
    int nodes = (*g)->nodes;
    int index;
    
    for(int i = 0; !feof(fp); i++)
    {
        fgets(line, 1001, fp);
        token = strtok(line, " \n");
        while(token != NULL)
        {
            if(strcmp(str_nodes[i], token) != 0)
            {
              index = findIndex(str_nodes, token, nodes);
              addEdge(&(*g), index, i);  
            }
            token = strtok(NULL, " \n");
        }
    }
    
    fclose(fp);
}

void pushStack(Stack* s, int item)
{
    if(s->top == (s->size - 1))
    {
        printf("Stack is full.\n");
        return;
    }
    s->top += 1;
    s->stk[s->top] = item;
}

int popStack(Stack* s)
{
    int num;
    if(s->top == -1)
    {
        printf("Stack is empty.\n");
        return -1;
    }
    else {
        num = s->stk[s->top];
        s->top = s->top - 1;
        return num;
    }
}

void dfsVisit(graphPT* g, Stack* s, vector* white, vector* black, vector* gray, int** d, int** f, int* matrix, int* time, int current, int* cycle)
{
    *time = *time + 1;
    (*d)[current] = *time;
    
    gray->array[current] = 1;
    
    white->array[current] = 0;
    white->num_elem = white->num_elem - 1;
    
    int n = s->size - 1;
    int neighbors [n];
    int neighborsSze = 0;
    
    
    for(int i = 0; i<n; i++)
    {
        if((*g)->matrix[current][i] == 1)
        {
            neighbors[neighborsSze] = i;
            neighborsSze += 1;
        }
    }
    
    for(int j = 0; j<neighborsSze; j++)
    {
        int next = neighbors[j];
        if(black->num_elem > 0 && (black->array[next] == 1))
        {
            continue;
        }
        if(gray->num_elem > 0 && (gray->array[next] == 1))
        {
            *cycle = 1;
        }
        if(white->num_elem > 0 && (white->array[next] == 1))
        {
            dfsVisit(g, s, white, black, gray, d, f, (*g)->matrix[next], time, next, cycle);
        }
    }
    
    *time = *time + 1;
    (*f)[current] = *time;
    
    gray->array[current] = 0;
    black->array[current] = 1;
    
    pushStack(s, current);
}


int main()
{
    graphPT graph;
    Stack stack;
    char** str_nodes;
    char filename[31];
    int time = 0;
    int cycle = 0;
    
    printf("This program will read, from a file, a list of courses and their prerequisites and will print the list in which to take cousres.\n");
    printf("Enter filename: ");
    scanf("%s", filename);
    
    int num_nodes = getNumberNodes(filename, &str_nodes);
    if(num_nodes == 0 || num_nodes == -1)
    {
        printf("\nFailed to read from file. Program will terminate.\n\n");
        return -1;
    }
    
    printf("Number of vertices in built in graph: N = %d\n", num_nodes - 1);
    printf("Vertex - coursename correspondence\n");
    for(int i = 0; i<num_nodes - 1; i++)
    {
        printf("%d - %s\n", i, str_nodes[i]);
    }
    
    graph = createNewGraph(num_nodes);
    readFile(filename, &graph, str_nodes);
    printMatrix(graph);
    
    
    stack.size = num_nodes + 1;
    stack.stk = (int*) malloc(sizeof(int*) * stack.size);
    stack.top = -1;
    
    vector white;
    vector black;
    vector gray;
    
    white.array = (int*) malloc(sizeof(int*) * num_nodes);
    white.size = num_nodes;
    white.num_elem = num_nodes;
    
    black.array = (int*) malloc(sizeof(int*) * num_nodes);
    black.size = num_nodes;
    black.num_elem = num_nodes;
    
    gray.array = (int*) malloc(sizeof(int*) * num_nodes);
    gray.size = num_nodes;
    gray.num_elem = num_nodes;
    
    for(int k = 0; k<num_nodes; k++)
    {
        white.array[k] = 1;
        black.array[k] = 0;
        gray.array[k] = 0;
    }
    
    int* discov = (int*) calloc(num_nodes, sizeof(int));
    int* fini = (int*) calloc(num_nodes, sizeof(int));
    
    for(int j = 0; j<num_nodes - 1 && white.num_elem > 0; j++)
    {
        if(white.array[j] == 1)
        {
            dfsVisit(&graph, &stack, &white, &black, &gray, &discov, &fini, graph->matrix[j], &time, j, &cycle);
        }
    }
    
    if(cycle)
    {
        printf("\n\nThere was at least one cycle. There is no possible ordering of the courses\n\n");
    }
    else {
        printf("\n\nOrder in which to take the courses:\n");
        for(int m = 0; m<num_nodes - 1; m++)
        {
            int pop = popStack(&stack);
            printf("%d. - %s (corresponds to graph vertex %d)\n", m+1, str_nodes[pop], pop);
        }
        printf("\n");
    }
    
    free(discov);
    free(fini);
    free(white.array);
    free(black.array);
    free(gray.array);
    free(stack.stk);
    freeMemoryGraph(graph);
    freeMemoryChar(str_nodes, num_nodes);
    
    return 0;
}
