#ifndef NUMBER_WITH_UNITS_H
#define NUMBER_WITH_UNITS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include<map>
#include <limits.h>
using namespace std;

struct Graph{
public:
    double vertArr[100][100] = {0}; //the adjacency matrix initially 0
    int count;
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
            parent[i] = -1;
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
        int c = count;
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

};


namespace ariel{

    class NumberWithUnits{
    private:
        static map<string, int> unitsName;
        static int id;
        static Graph tabla;
        double number;
        string unit;
        double getRatio(string otherUnit) const;
        double getRatio(string otherUnit, bool increase) const;

    public:
        NumberWithUnits(double number, string unit);
        ~NumberWithUnits(){}

//        static void printTable();
        static void read_units(ifstream& input);
        //Getters&Setters.
        double get_number() const;
        void set_number(double num);

        string get_unit() const;
        void set_unit(string s);

        //Add two numbers.
        NumberWithUnits operator+(const NumberWithUnits& aother);
        //Add to this.
        NumberWithUnits& operator+=(const NumberWithUnits& other);
        //Unary +. (Does nothing)
        NumberWithUnits& operator+();

        //Sub two numbers.
        NumberWithUnits operator-(const NumberWithUnits& other);
        //Sub to this.
        NumberWithUnits& operator-=(const NumberWithUnits& other);
        //Unary -. (Change sign)
        NumberWithUnits& operator-();

        //LET.
        friend bool operator< (const NumberWithUnits &current, const NumberWithUnits &other);
        //LEQ.
        friend bool operator<= (const NumberWithUnits &current, const NumberWithUnits &other);
        //Equals.
        friend bool operator== (const NumberWithUnits &current, const NumberWithUnits &other);
        //GEQ.
        friend bool operator>= (const NumberWithUnits &current, const NumberWithUnits &other);
        //GET.
        friend bool operator> (const NumberWithUnits &current, const NumberWithUnits &other);
        //DIFF.
        friend bool operator!= (const NumberWithUnits &current, const NumberWithUnits &other);

        //Pre-increment.
        NumberWithUnits& operator++();
        //Post-increment.
        NumberWithUnits& operator++(int);

        //Pre-deccrement.
        NumberWithUnits& operator--();
        //Post-deccrement.
        NumberWithUnits& operator--(int);

        //Mult with double.
        NumberWithUnits operator*(double d);
        friend NumberWithUnits operator*(double d, const NumberWithUnits& other);

        //Input-Output stream.
        friend ostream& operator<< (ostream& os, const NumberWithUnits& other);
        friend istream& operator>> (istream& in, NumberWithUnits& other);
    };
    ostream& operator<< (ostream& os, const NumberWithUnits& other);
    istream& operator>> (istream& in, NumberWithUnits& other);}

#endif