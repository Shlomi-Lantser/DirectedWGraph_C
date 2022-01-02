// A C Program to demonstrate adjacency list
// representation of graphs
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>

struct AdjListNode {
    int dest;
    int weight;
    struct AdjListNode *next;
}; //v

struct Node {
    int id;
    int priority;
    int visited;
    int parent;
    struct AdjListNode *head;
    struct Node *next;
}; //v

struct Graph {
    int V;
    struct Node *head;
}; //v

struct Node *nodeCopy(struct Node *nodeToCopy){
    struct Node *result = (struct Node*) malloc(sizeof(struct Node));
    result->head = nodeToCopy->head;
    result->id = nodeToCopy->id;
    result->priority = nodeToCopy->priority;
    result->visited = 0;
    result->next = NULL;
    result->parent = nodeToCopy->parent;
    return result;
}

struct AdjListNode *newAdjListNode(int dest, int weight) {
    struct AdjListNode *newNode =
            (struct AdjListNode *) malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    newNode->weight = weight;
    return newNode;
} //v

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
        temp->visited =0;
        temp->priority = INT_MAX;

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

void addNode(struct Graph *graph, int id) {
    struct Node *temp = graph->head;
    struct Node *newNode = (struct Node *) malloc(sizeof(struct Node));
    newNode->id = id;
    newNode->next = NULL;
    newNode->head = NULL;
    newNode->visited =0;
    newNode->priority = INT_MAX;
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
} //v

void deleteNode(struct Graph *graph, int id) {
    struct Node *currNode = graph->head;
    struct Node *prevNode = graph->head;
//    if (graph->head == NULL) return;
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

struct priorityQueue{
    struct Node *head;
};

struct Node *peek(struct priorityQueue *pq){
    return pq->head;
}

struct Node *pop(struct priorityQueue *pq){
    struct Node *temp = pq->head;
    if (pq->head->next) {
        pq->head = pq->head->next;
//        free(temp);
    }else {
//        free(temp);
        pq->head = NULL;
    }
    free(temp);
}

void push(struct priorityQueue *pq , struct Node *nodeToAdd){
    struct Node* nodeToAddCopy = nodeCopy(nodeToAdd);
    if (pq->head == NULL){
        pq->head = nodeToAddCopy;
        return;
    }
    struct Node *start = pq->head;
    if (pq->head->priority > nodeToAddCopy->priority){
        nodeToAddCopy->next = pq->head;
        pq->head = nodeToAddCopy;
    }else {
        while (start->next != NULL && start->next->priority < nodeToAddCopy->priority){
            start = start->next;
        }
        nodeToAddCopy->next = start->next;
        start->next = nodeToAddCopy;
    }
}

int isEmpty(struct priorityQueue *pq){
    return pq->head == NULL;
}

int contains(struct Graph* graph , int arr[] , int v){
    for (int i = 0; i < graph->V; ++i) {
        if (arr[i] == v) return 1;
    }
    return 0;
}

struct Node *getNode(struct Graph *graph , int id){
    struct Node *curr = graph->head;
    while (curr){
        if (curr->id == id){
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

struct nodePath{
    struct Node *head;
};

int Dijkstra(struct Graph *graph , int src , int dest){
    struct Node *temp = graph->head;
    while (temp){
        temp->priority = INT_MAX;
        temp = temp->next;
    }

    int counter =0;
    struct priorityQueue *pq = (struct priorityQueue*) malloc(sizeof(struct priorityQueue));
    pq->head = NULL;
    int visited[graph->V];
    for (int i = 0; i < graph->V; ++i) {
        visited[i] = -1;
    }
    getNode(graph , src)->priority =0;
    struct Node *curr = nodeCopy(getNode(graph , src));
    curr->priority =0;
    push(pq,curr);

    while (!isEmpty(pq)){
        curr = nodeCopy(peek(pq));
        pop(pq);
        visited[counter] = curr->id;
        counter++;
        struct AdjListNode *currEdge = curr->head;
        while (currEdge != NULL) {
            int distance = currEdge->weight;
            if (!contains(graph, visited, currEdge->dest)) {
                int prevCost = getNode(graph, currEdge->dest)->priority;
                int newCost = curr->priority + distance;
                if (newCost < prevCost) {
                    getNode(graph, currEdge->dest)->priority = newCost;
                    struct Node *neighbor = nodeCopy(getNode(graph, currEdge->dest));
                    neighbor->parent = curr->id;
                    push(pq, neighbor);
                }
            }
            currEdge = currEdge->next;
        }
    }
    printf("dijkstra : %d \n", getNode(graph,dest)->priority);
    free(pq);
    free(curr);
    return getNode(graph , dest)->priority;
}

struct nodePath *DijkstraPath(struct Graph *graph , int src , int dest){
    struct Node *temp = graph->head;
    while (temp){
        temp->priority = INT_MAX;
        temp = temp->next;
    }

    int counter =0;
    struct priorityQueue *pq = (struct priorityQueue*) malloc(sizeof(struct priorityQueue));
    pq->head = NULL;
    int visited[graph->V];
    for (int i = 0; i < graph->V; ++i) {
        visited[i] = -1;
    }
    getNode(graph , src)->priority =0;
    struct Node *curr = nodeCopy(getNode(graph , src));
    curr->priority =0;
    push(pq,curr);

    while (!isEmpty(pq)){
        curr = nodeCopy(peek(pq));
        pop(pq);
        visited[counter] = curr->id;
        counter++;
        struct AdjListNode *currEdge = curr->head;
        while (currEdge != NULL) {
            int distance = currEdge->weight;
            if (!contains(graph, visited, currEdge->dest)) {
                int prevCost = getNode(graph, currEdge->dest)->priority;
                int newCost = curr->priority + distance;
                if (newCost < prevCost) {
                    getNode(graph, currEdge->dest)->priority = newCost;
                    struct Node *neighbor = nodeCopy(getNode(graph, currEdge->dest));
                    getNode(graph , currEdge->dest)->parent = curr->id;
                    neighbor->parent = curr->id;
                    push(pq, neighbor);
                }
            }
            currEdge = currEdge->next;
        }
    }
    struct Node *destNode = nodeCopy(getNode(graph , dest));
    struct nodePath *path = (struct nodePath*) malloc(sizeof(struct nodePath));
    struct Node *buildingPath = nodeCopy(getNode(graph , dest));
    path->head = buildingPath;
    while (destNode){
        if (destNode->id == src) break;
        destNode = nodeCopy(getNode(graph , destNode->parent));
//        buildingPath->next = destNode;
        destNode->next = path->head;
        path->head = destNode;
//        buildingPath = buildingPath->next;
    }

    return path;
}

int calculatePath(struct nodePath *path){
    if (path == NULL) return INT_MAX;

    int result =0;
    struct Node *pathCurr = path->head;
    while (pathCurr){
        if (pathCurr->next == NULL){
            break;
        }
        struct AdjListNode *currEdge = pathCurr->head;
        while (currEdge){
            if (currEdge->dest == pathCurr->next->id){
                result += currEdge->weight;
                break;
            }
            currEdge = currEdge->next;
        }
        pathCurr = pathCurr->next;
    }
    return result;
}

int pathContainsAll(struct nodePath *path , struct nodePath *cities){
    if (path == NULL) return 0;
    struct Node *currCity = cities->head;
    while (currCity){
        struct Node *currPath = path->head;
        while (currPath){
            if (currCity->id == currPath->id) break;
            if (currPath->next == NULL) return 0;
            currPath = currPath->next;
        }
        currCity = currCity->next;
    }
    return 1;
}

struct Node *lastNode(struct nodePath *path){
    struct Node *curr = path->head;
    while (curr->next){
        curr = curr->next;
    }
    return curr;
}
//3 2 1 3

int TSP(struct Graph *graph){
    int result =INT_MAX;
    int nodeId;
    int numOfCities;
    int i=1;
    scanf("%d" , &numOfCities);
    struct nodePath *arrayOfLists[numOfCities*numOfCities - numOfCities];
    struct nodePath *arrayNotContains[numOfCities*numOfCities - numOfCities];
    int counter1=0;
    for (int k = 0; k < numOfCities*numOfCities - numOfCities; ++k) {
        arrayOfLists[k]= NULL;
        arrayNotContains[k] = NULL;
    }
    int counter =0;
    struct nodePath *cities = (struct nodePath*) malloc(sizeof(struct nodePath));
    cities->head = NULL;
    while (i != numOfCities){
        scanf("%d" , &nodeId);
        if (cities->head == NULL){
            cities->head = nodeCopy(getNode(graph , nodeId));
        }else {
            struct Node *currCity = cities->head;
            while (currCity->next) {
                currCity = currCity->next;
            }
            i++;
            currCity->next = nodeCopy(getNode(graph, nodeId));
        }
    }
    struct Node *srcNode = cities->head;
    while (srcNode){
        struct Node *destNode = cities->head;
        while (destNode){
            if (destNode == srcNode){
                destNode = destNode->next;
                continue;
            }
            if (srcNode->head == NULL) break;
            arrayOfLists[counter] = DijkstraPath(graph , srcNode->id , destNode->id);
            counter++;
            destNode = destNode->next;
        }
        srcNode = srcNode->next;
    }
    for (int j = 0; j < numOfCities*numOfCities - numOfCities; ++j) {
        int checkk = calculatePath(arrayOfLists[j]);
        int boolll = pathContainsAll(arrayOfLists[j] , cities);
        if (boolll == 1 && checkk < result){
            result = checkk;
        }
    }
    for (int q = 0; q < numOfCities*numOfCities - numOfCities; ++q) {
        int boolll = pathContainsAll(arrayOfLists[q] , cities);
        if (boolll == 0){
            arrayNotContains[counter1] = arrayOfLists[q];
        }
    }
    for (int j = 0; j < numOfCities*numOfCities - numOfCities; ++j) {
        if (arrayOfLists[j] == NULL) break;
        for (int k = 0; k < numOfCities*numOfCities - numOfCities; ++k) {
            if (arrayNotContains[k] == NULL) break;
            if (arrayNotContains[k] == arrayOfLists[j]) continue;
            if (lastNode(arrayNotContains[j])->id == arrayOfLists[k]->head->id && lastNode(arrayNotContains[j])->id != lastNode(arrayOfLists[j])->id){
                lastNode(arrayNotContains[k])->next = arrayOfLists[j]->head;
            }
        }
    }

    for (int j = 0; j < numOfCities*numOfCities - numOfCities; ++j) {
        int checkk = calculatePath(arrayNotContains[j]);
        int boolll = pathContainsAll(arrayNotContains[j] , cities);
        if (boolll == 1 && checkk < result){
            result = checkk;
        }
    }

    free(cities);


    printf("TSP : %d" , result);
    return result;
}

//int main() {
//    struct Graph *graph;
//    struct Graph *graphCopy;
//    char input;
//    char inputA;
//    int numOfNodes;
//    char inputIfA;
//    char inputA1 = "R";
//    while (1) {
//        if (inputA == 'x' || inputA == 'A' || inputA == 'S') {
//            input = inputA;
//        } else {
//            scanf("%s", &input);
//        }
//        if (input == 'A') {
//            scanf("%d", &numOfNodes);
//            graphCopy = createGraph(numOfNodes);
//            int src;
//            while (scanf("%s", &inputA)) {
//                if (inputA == 'x' || inputA == 'A' || inputA == 'B' || inputA == 'D' || inputA == 'S' ||inputA == 'T')
//                    break;
//                if (inputA == 'n') {
//                    scanf("%d", &src);
//                }
//                int dest, weight;
//                while (scanf("%d", &dest)) {
//                    if (inputA != ' ' && inputA != 'n') break;
//
//                    scanf("%d", &weight);
//                    addEdge(graphCopy, src, dest, weight);
//                    graph = graphCopy;
//                }
//            }
//            graph = graphCopy;
//        }
//        if (input == 'B') {
//            graphCopy = graph;
//            int newNode;
//            int newDest;
//            int weight;
//            inputA = "";
//            scanf("%d", &newNode);
//            addNode(graphCopy, newNode);
//            while (scanf("%d", &newDest)) {
//                scanf("%d", &weight);
//                addEdge(graphCopy, newNode, newDest, weight);
//                graph = graphCopy;
//            }
//            graph = graphCopy;
//        }
//
//        if (input == 'D') {
//            int delNode;
//            scanf("%d", &delNode);
//            deleteNode(graph, delNode);
//            scanf("%s", &input);
//        }
//
//        if (input == 'S'){
//            int src;
//            int dest;
//            scanf("%d" , &src);
//            scanf("%d" , &dest);
//            Dijkstra(graph , src , dest);
//            scanf("%s" , &input);
//        }
//
//        if (input == 'x') {
//            printGraph(graph);
//            return 0;
//        }
//    }
//}

int main(){
    struct Graph *graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph = createGraph(4);
    addEdge(graph , 0 , 2, 5);
    addEdge(graph , 0 , 3, 3);
    addEdge(graph , 2 , 0, 4);
    addEdge(graph , 2 , 1, 1);
    addEdge(graph , 1 , 3, 7);
    addEdge(graph , 1 , 0, 2);
    Dijkstra(graph , 2, 0);
    deleteGraph(graph);
    free(graph);


}