// A C Program to demonstrate adjacency list
// representation of graphs
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

struct AdjListNode {
    int dest;
    int weight;
    struct AdjListNode *next;
}; //v

struct Node {
    int id;
    struct AdjListNode *head;
    struct Node *next;
}; //v

struct Graph {
    int V;
    struct Node *head;
}; //v

struct AdjListNode *newAdjListNode(int dest, int weight) {
    struct AdjListNode *newNode =
            (struct AdjListNode *) malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    newNode->weight = weight;
    return newNode;
} //v

int buildNumber(char *str) {
    int result = 0;
    for (int i = 0; i < strlen(str); ++i) {
        result += pow(10, strlen(str) - i - 1) * (str[i] - 48);
    }
    return result;
}

struct Graph *createGraph(int V) {
    struct Graph *graph = (struct Graph *) malloc(sizeof(struct Graph) + (V * sizeof(struct Node)));
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
} //v

void addEdge(struct Graph *graph, int src, int dest, int weight) {
    int bool[2];
    bool[0] = 0;
    bool[1] = 0;


    struct Node *p = graph->head;
    while (p) {
        if (p->id == src) {
            bool[0] = 1;
            break;
        }
        p = p->next;
    }

    struct Node *z = graph->head;
    while (z) {
        if (z->id == dest) {
            bool[1] = 1;
            break;
        }
        z = z->next;
    }

    if (bool[0] == 0 || bool[1] == 0) return;
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
} //v
//

void addNode(struct Graph *graph, int id) {
    struct Node *temp = graph->head;
    struct Node *newNode = (struct Node *) malloc(sizeof(struct Node));
    newNode->id = id;
    newNode->next = NULL;
    newNode->head = NULL;
    if (graph->head == NULL) {
        graph->head = newNode;
        graph->V++;
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
//    realloc(graph, sizeof(graph->V * sizeof(struct Node) + 1));
} //v

void deleteNode(struct Graph *graph, int id) {
    struct Node *currNode = graph->head;
    struct Node *prevNode = graph->head;
    if (graph->head->id == id) {
        graph->head = graph->head->next;
        graph->V--;
        free(currNode);
    } else {
        while (currNode) {
            if (currNode->id == id) {
                struct AdjListNode *currEdge = currNode->head;
                struct AdjListNode *prevEdge = currNode->head;
                if (currEdge != NULL) {
                    while (currEdge->next) {
                        prevEdge = currEdge;
                        currEdge = currEdge->next;
                        free(prevEdge);
                    }
                }
                if (currNode->next) {
                    prevNode->next = currNode->next;
                    graph->V--;
                    free(currNode);
                } else {
                    prevNode->next = NULL;
                }
            }
            prevNode = currNode;
            currNode = currNode->next;
        }
    }

    currNode = graph->head;
    while (currNode) {
        struct AdjListNode *currEdge = currNode->head;
        struct AdjListNode *prevEdge = currNode->head;
        while (currEdge) {
            if (currEdge->dest == id) {
                if (currEdge == currNode->head) {
                    currNode->head = currNode->head->next;
                    free(currEdge);
                    currEdge = NULL;
                    break;
                } else {
                    prevEdge->next = currEdge->next;
                    free(currEdge);
                    currEdge = NULL;
                    break;
                }
            }
            prevEdge = currEdge;
            currEdge = currEdge->next;
        }
        currNode = currNode->next;
    }
    return;
} //v

void deleteGraph(struct Graph *graph) {
    struct Node *currNode = graph->head;
    struct Node *prevNode = graph->head;
    while (currNode) {
        struct AdjListNode *currEdge = currNode->head;
        struct AdjListNode *prevEdge = currNode->head;

        while (currEdge) {
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
    graph->V = 0;
    realloc(graph, sizeof(graph));
    graph->head = NULL;
} //v

void printGraph(struct Graph *graph) {
    if (graph->V == 0) {
        printf("Empty Graph!");
        return;
    }
    struct Node *currNode = graph->head;
    while (currNode) {
        printf("Node %d : ->", currNode->id);
        struct AdjListNode *currEdge = currNode->head;
        while (currEdge) {
            if (currEdge->next) {
                printf("%d ->", currEdge->dest);
                currEdge = currEdge->next;
            } else {
                printf("%d", currEdge->dest);
                currEdge = currEdge->next;
            }
        }
        printf("\n");
        currNode = currNode->next;
    }
} //v

int checkIfNum(char str[]) {
    if (strlen(str) == 1) {
        return isdigit(str);
    }
    for (int i = 0; i < strlen(str); ++i) {
        if (!isdigit(str[i])) return 0;
    }
    return 1;
}

int main() {
    struct Graph *graph;
    struct Graph *graphCopy;
    char input;
    char inputA;
    int numOfNodes;
    char inputIfA;
    char inputA1 = "R";
    while (1) {
        if (inputA == 'x' || inputA == 'A' || inputA == 'B' || inputA == 'D' || inputA == 'S' || inputA == 'T') {
            input = inputA;
        } else {
            scanf("%s", &input);
        }
        if (input == 'A') {
            scanf("%d", &numOfNodes);
            graphCopy = createGraph(numOfNodes);
            int src;
            while (scanf("%s", &inputA)) {
                if (inputA == 'x' || inputA == 'A' || inputA == 'B' || inputA == 'D' || inputA == 'S' ||
                    inputA == 'T')
                    break;
                if (inputA == 'n') {
                    scanf("%d", &src);
                }
                int dest, weight;
                while (scanf("%d", &dest)) {
                    if (inputA != ' ' && inputA != 'n') break;

                    scanf("%d", &weight);
                    addEdge(graphCopy, src, dest, weight);
                    graph = graphCopy;
                }
            }
            graph = graphCopy;
        }
        if (input == 'B') {
            graphCopy = graph;
            int newNode;
            int newDest;
            int weight;
            inputA = "";
            scanf("%d", &newNode);
            addNode(graphCopy, newNode);
            while (scanf("%d", &newDest)) {
                scanf("%d", &weight);
                addEdge(graphCopy, newNode, newDest, weight);
                graph = graphCopy;
            }
            graph = graphCopy;
        }

        if (input == 'D') {
            int delNode;
            scanf("%d", &delNode);
            deleteNode(graph, delNode);
            scanf("%s", &input);
        }

        if (input == 'x') {
            printGraph(graph);
            return 0;
        }
    }
}