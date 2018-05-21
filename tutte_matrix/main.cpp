/*-----Head---------*/
/*
 * tutte_matrix.cc
 *
 * Project: 	Advanced Algorithms HW2 randomized perfect matching Algorithm
 * Group: 		JF - Fischer Joel;
 * 				LM - Louis Munier;
 *
 * Description:	C++ implement a randomized test for perfect matching algorithm
 * 				to be tested on codeforces.com (hopefully faster version)
 * Date:		20.05.18
*/

/*-----Changelog----*/
/*
*/

/*-----TODO---------*/
/*
 * 
*/

/*-----Notes--------*/
/*
*/

/*=====Implementation=================================================*/
/*====================================================================*/

// includes
#include <cstdlib> 		// for srand
#include <ctime>		// for time
#include <iostream> 	// for I/O
#include <sstream>		// for Input parsing
#include <string> 		// for hashing
#include <vector> 		// for lists of edges
#include <array> 		// "
#include <algorithm> 	// for random_shuffle
#include <cmath> 		// for log
#include <set> 			// for set for storing cut hashes

using namespace std;

/*=====Class Declarations=============================================*/

/*=====Method Declarations============================================*/
void table_toPrint(vector<vector<int>> *);
int mod_inv(int, int);

/*=====Main===========================================================*/

int main(int argc, char** argv){

// initializing rand seed
    srand(time(0));

    /*int v = 0;						                // #vertices
    int e = 0;						                // #edges
    int p = 1000000009;                             // prime

    // store number of vertices and edges
    cin >> v >> e;

    vector<vector<int>> g(v, vector<int>(v,0));     // tutte matrix of the graph

    int indice_vertex1, indice_vertex2;             // Indices of vertices
    for(int i=0; i<e; i++){
        cin >> indice_vertex1 >> indice_vertex2;

        if(indice_vertex1 > indice_vertex2) {
            g[indice_vertex1-1][indice_vertex2-1] = -1;
            g[indice_vertex2-1][indice_vertex1-1] = 1;
        } else {
            g[indice_vertex1-1][indice_vertex2-1] = 1;
            g[indice_vertex2-1][indice_vertex1-1] = -1;
        }
    }

    printf("v = %d, e = %d\n", v, e);
    table_toPrint(&g);*/

    int result = mod_inv(22, 211);
    printf("%d", result);

    return 0;
}

/*=====Methods========================================================*/
void table_toPrint(vector<vector<int>> *graph){
    int len = (*graph).size();

    for(int i=0; i<len; i++){
        for(int j=0; j<len; j++){
            printf("%d ", (*graph)[j][i]);
        }
        printf("\n");
    }
}

int mod_inv(int x, int p){
    int n = p-2;
    int x_2 = 0;
    int result = 1;

    if(abs(x) < p)
        x_2 = x*x%p;

    // n is odd
    if(n%2 != 0){
        result = x%p;

        for(int i=0; i<(n-1)/2; i++)
            result = (x_2*result)%p;
    }
    // n is even
    else {
        for(int i=0; i<n/2; i++)
            result = (x_2*result)%p;
    }

    return result;
}