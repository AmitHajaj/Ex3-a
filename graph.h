#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <map>

using namespace std;
class graph {
    double vertArr[100][100]; //the adjacency matrix initially 0
    int count = 0;
public:
    void displayMatrix(int v) {
        int i, j;
        for (i = 0; i < v; i++) {
            for (j = 0; j < v; j++) {
                cout << vertArr[i][j] << " ";
            }
            cout << endl;
        }
    }

    void add_edge(int u, int v, double weight) { //function to add edge into the matrix
        vertArr[u][v] = weight;
        vertArr[v][u] = weight;
    }

    void addNode(int i){
        count++;
    }
};