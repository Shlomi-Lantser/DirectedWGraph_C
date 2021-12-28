// A C Program to demonstrate adjacency list
// representation of graphs
#include <stdio.h>
#include <stdlib.h>

struct AdjListNode {
    int dest;
    int weight;
    struct AdjListNode *next;
};

struct Node {
    int id;
    struct AdjListNode *head;
    struct Node *next;
};

struct Graph {
    int V;
    struct Node *head;
};

struct AdjListNode *newAdjListNode(int dest, int weight) {
    struct AdjListNode *newNode =
            (struct AdjListNode *) malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    newNode->weight = weight;
    return newNode;
}

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
    if (graph->head == NULL){
        graph->head = newNode;
        graph->V ++;
        return;
    }
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
    struct Node *head = graph->head;
    if (graph->head->id == id) {
        graph->head = graph->head->next;
        head = NULL;
        return;
    }
    struct Node *curr = graph->head;
    struct Node *prev = graph->head;
    while (curr) {
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
                break;
            }
        }
    }
    struct Node *currNode = graph->head;
    while (currNode) {
        if (currNode->head != NULL) {
            struct AdjListNode *currEdge = currNode->head;
            struct AdjListNode *prevEdge = currNode->head;
            while (currEdge) {
                if (currEdge->dest == id) {
                    if (currEdge == currNode->head && currEdge->next == NULL){
                        free(currNode->head);
                        currNode->head = NULL;
                        break;
                    }
                    if (prevEdge != currEdge){
                        prevEdge->next = currEdge->next;
                    }else {
                        currNode->head = currEdge->next;
                    }
                    free(currEdge);
                    currEdge = NULL;
                    break;
                }
                prevEdge = currEdge;
                currEdge = currEdge->next;
            }

        }
        currNode = currNode->next;
    }
    return;
}

void deleteGraph(struct Graph *graph){
    struct Node *currNode = graph->head;
    struct Node *prevNode = graph->head;
    while (currNode){
        struct AdjListNode *currEdge = currNode->head;
        struct AdjListNode *prevEdge = currNode->head;

        while (currEdge){
            prevEdge = currEdge;
            currEdge = currEdge->next;
            free(prevEdge);
        }
        currNode->head = NULL;

        prevNode = currNode;
        currNode = currNode->next;
        free(prevNode);
    }
    graph->head = NULL;
    graph->V =0;
    realloc(graph , sizeof(graph));
}

int main() {
    int V = 5;
    struct Graph *graph = createGraph(V);
    addEdge(graph, 2, 3, 8);
    addEdge(graph, 2, 4, 8);
    addEdge(graph, 2, 5, 8);
    addEdge(graph, 3, 1, 8);
    addEdge(graph, 3, 0, 8);
    addNode(graph, 5);
    addNode(graph, 3);
    deleteNode(graph, 3);
    deleteGraph(graph);

    printf("%d" , graph->V);

    addNode(graph, 0 );
    printf("LOL");
    return 0;
}