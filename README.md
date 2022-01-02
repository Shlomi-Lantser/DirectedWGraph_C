The main veriables which we use in this class are:
  - nodes (struct)
  - AdjlistNode (struct)
    - here we held all our edges using three variables:
      - src : what is the node id i came from
      - dest : what is the node id i go to
      - weight: what is the "weight" of this edge

|Main Functions|Explenation|RunTime|
|---|---|---|
|add_node| adding a new node to our data structure(if his id exsist)|O(|V|+|E|)
|add_edge| create new edge in the graph|O(1)
|deleteNode| in this function we removing a node from our graph, we need to find the givven id delete the edge go from it and into it|O(|V|+|E|)|


## Algorithms
   
|Main Functions|Explenation|RunTime|
|---|---|---|
|Djikstra shortest Path| in this function i have used in the Dijkstra algorythm, at first we update al the nodes "weight" to inf execept the src node which we update to 0, we ran on all the nodes and update their weight to the min, and also saved the prev node of each node in the shortest path in aim to return the distance between the nodes we walk in |O(|E| + |V|log|V|)|
|TSP| in a given list of cities we need to find the shortest path distance, int path which contain all of them and the weight of it|O(n^4)

## Main (exe)

in the main the algorithms works by a command from the user :
A (int)- creating a new graph with number of nodes that the user puts.
B (int)- adding a new node to the graph , if the given id exists it deletes all the edges that going out from this node.
D (int)- deleting a node and deleting all the edges that going out from the node and eigher the edges going in the given node.
S (int ,int)- doing Djikstra shortest path to find the minimum distance bewteed 2 given nodes.
T (int v) , (int,int,int....->v times)- doing TSP algorithm with giving nodes (cities) that must include the path.
