#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <map>

typedef struct graph{
    double vertArr[100][100]; //the adjacency matrix initially 0
    int count = 0;
public:
    void add_edge(int u, int v, double weight) { //function to add edge into the matrix
        vertArr[u][v] = weight;
        vertArr[v][u] = 1/weight;
    }
    void addNode(){
        count++;
    }
    // A utility function to find the
    // vertex with minimum distance
    // value, from the set of vertices
    // not yet included in shortest
    // path tree
    int minDistance(int dist[],
                    bool sptSet[])
    {

        // Initialize min value
        int min = INT_MAX, min_index;

        for (int v = 0; v < count; v++)
            if (sptSet[v] == false &&
                dist[v] <= min)
                min = dist[v], min_index = v;

        return min_index;
    }

    //    // Function to print shortest
    //    // path from source to j
    //    // using parent array
    //    double printPath(int parent[], int j)
    //    {
    //         double multBy = 1;
    //        // Base Case : If j is source
    //        if (parent[j] == - 1)
    //            return 1;
    //
    //        return multBy*printPath(parent, parent[j]);
    //
    ////        printf("%d ", j);
    //    }
    //
    //// A utility function to print
    //// the constructed distance
    //// array
    //    int printSolution(int dist[], int n,
    //                      int parent[], int dest)
    //    {
    //            double multBy = 1;
    //        int src = 0;
    //        printf("Vertex\t Distance\tPath");
    //        for (int i = 1; i < n && i = dest; i++)
    //        {
    //            printf("\n%d -> %d \t\t %d\t\t%d ", src, i, dist[i], src);
    //            multBy *= printPath(parent, i);
    //        }
    //    }
    double dijkstra(int src, int dest)
    {
        int dst = dest;

        // The output array. dist[i]
        // will hold the shortest
        // distance from src to i
        int dist[count];
        double dista[count];

        // sptSet[i] will true if vertex
        // i is included / in shortest
        // path tree or shortest distance
        // from src to i is finalized
        bool sptSet[count];

        // Parent array to store
        // shortest path tree
        int parent[count];

        // Initialize all distances as
        // INFINITE and stpSet[] as false
        for (int i = 0; i < count; i++)
        {
            parent[0] = -1;
            dist[i] = INT_MAX;
            dista[i] = 1;
            sptSet[i] = false;
        }

        // Distance of source vertex
        // from itself is always 0
        dist[src] = 0;
        dista[src] = 1;

        // Find shortest path
        // for all vertices
        for (int counter = 0; counter < count - 1; counter++)
        {
            // Pick the minimum distance
            // vertex from the set of
            // vertices not yet processed.
            // u is always equal to src
            // in first iteration.
            int u = minDistance(dist, sptSet);

            // Mark the picked vertex
            // as processed
            sptSet[u] = true;

            // Update dist value of the
            // adjacent vertices of the
            // picked vertex.
            for (int v = 0; v < count; v++)

                // Update dist[v] only if is
                // not in sptSet, there is
                // an edge from u to v, and
                // total weight of path from
                // src to v through u is smaller
                // than current value of
                // dist[v]
                if (!sptSet[v] && vertArr[u][v] &&
                    dist[u] + vertArr[u][v] < dist[v])
                {
                    parent[v] = u;
                    dist[v] = dist[u] + vertArr[u][v];
                    dista[v] = dista[u]*vertArr[u][v];
                }
        }

        // print the constructed
        // distance array
        //        printSolution(dist, V, parent, dst);
        return dista[dest];
    }

}graph;