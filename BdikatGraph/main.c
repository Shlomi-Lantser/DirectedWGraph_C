// A C Program to demonstrate adjacency list
// representation of graphs
#include <stdio.h>
#include <stdlib.h>

// A structure to represent an adjacency list node
struct AdjListNode {
    int dest;
    int weight;
    struct AdjListNode *next;
};

// A structure to represent an adjacency list
struct Node {
    int id;
    struct AdjListNode *head;
    struct Node *next;
};

// A structure to represent a graph. A graph
// is an array of adjacency lists.
// Size of array will be V (number of vertices
// in graph)
struct Graph {
    int V;
    struct Node *head;
};

// A utility function to create a new adjacency list node
struct AdjListNode *newAdjListNode(int dest, int weight) {
    struct AdjListNode *newNode =
            (struct AdjListNode *) malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    newNode->weight = weight;
    return newNode;
}

// A utility function that creates a graph of V vertices
struct Graph *createGraph(int V) {
    struct Graph *graph = (struct Graph *) malloc(sizeof(struct Graph));
    graph->V = V;
    graph->head = NULL;
    struct Node *temp = NULL;
    struct Node *p = NULL;

    for (int i = 0; i < V; ++i) {
        temp = (struct Node *) malloc(sizeof(struct Node));
        temp->id = i;
        temp->head = NULL;
        temp->next = NULL;

        if (graph->head == NULL) {
            graph->head = temp;
        } else {
            p = graph->head;
            while (p->next != NULL) {
                p = p->next;
            }
            p->next = temp;
        }
    }


    // Initialize each adjacency list as empty by
    // making head as NULL

    return graph;
}

void addEdge(struct Graph *graph, int src, int dest, int weight) {
    int bool[2];
    bool[0] = 0;
    bool[1] = 0;


    struct Node *p = graph->head;
    while (p) {
        p = p->next;
        if (p->id == src) {
            bool[0] = 1;
            break;
        }
    }

    struct AdjListNode *q = p->head;
    if (q == NULL) {
        struct AdjListNode *temp = (struct AdjListNode *) malloc(sizeof(struct AdjListNode));
        temp->dest = dest;
        temp->weight = weight;
        temp->next = NULL;
        p->head = temp;
    } else {
        while (q->next != NULL) {
            q = q->next;
        }
        struct AdjListNode *temp = (struct AdjListNode *) malloc(sizeof(struct AdjListNode));
        q->next = temp;
        temp->dest = dest;
        temp->weight = weight;
        temp->next = NULL;
    }
}
//

void addNode(struct Graph *graph, int id) {
    struct Node *temp = graph->head;
    struct Node *newNode = (struct Node *) malloc(sizeof(struct Node));
    newNode->id = id;
    newNode->next = NULL;
    newNode->head = NULL;
    while (temp->next) {
        if (temp->id == id) {
            struct AdjListNode *currEdge = temp->head;
            struct AdjListNode *prevEdge = temp->head;
            if (currEdge != NULL) {
                while (currEdge->next) {
                    prevEdge = currEdge;
                    currEdge = currEdge->next;
                    prevEdge = NULL;
                    free(prevEdge);
                }
                temp->head = NULL;
            }
            return;
        }
        temp = temp->next;
    }
    temp->next = newNode;
    graph->V++;
}

void deleteNode(struct Graph *graph, int id) {
    struct Node *curr = graph->head;
    struct Node *prev = graph->head;
    while (curr->next) {
        prev = curr;
        curr = curr->next;
        if (curr->id == id) {
            if (curr->next) {
                struct AdjListNode *currEdge = curr->head;
                struct AdjListNode *prevEdge = curr->head;
                if (currEdge != NULL) {
                    while (currEdge->next) {
                        prevEdge = currEdge;
                        currEdge = currEdge->next;
                        prevEdge = NULL;
                        free(prevEdge);
                    }
                    curr->head = NULL;
                }
                prev->next = curr->next;
                curr = NULL;
                free(curr);
                graph->V--;
                break;
            } else {
                curr = NULL;
                free(curr);
                graph->V--;
            }
        }
        struct Node *currNode = graph->head;
        while (curr){
            struct AdjListNode *currEdge = currNode->head;
        }
    }
    return;
}
//void printGraph(struct Graph* graph)
//{
//    int v;
//    for (v = 0; v < graph->V; ++v)
//    {
//        struct AdjListNode* pCrawl = graph->array[v].head;
//        printf("\n Adjacency list of vertex %d\n head ", v);
//        while (pCrawl)
//        {
//            printf("-> %d", pCrawl->dest);
//            pCrawl = pCrawl->next;
//        }
//        printf("\n");
//    }
//}

// Driver program to test above functions
int main() {
    // create the graph given in above fugure
    int V = 5;
    struct Graph *graph = createGraph(V);
    addEdge(graph, 2, 3, 8);
    addEdge(graph, 3, 1, 8);
    addEdge(graph, 3, 0, 8);
    addNode(graph, 5);
    addNode(graph,3);


    printf("%d", graph->head->id);
    return 0;
}