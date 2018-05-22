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
void table_toPrint(vector<vector<long int>> *);
long int mod_inv(long int, long int, long int);
long int mod_mul(long int, long int, long int);
long int gauss_elimination(vector<vector<long int>> *, long int);

/*=====Main===========================================================*/

int main(int argc, char** argv){
// initializing rand seed
    srand(time(0));

    int v = 0;						                // #vertices
    int e = 0;						                // #edges
    long int p = 1000000009;                        // prime

    // store number of vertices and edges
    cin >> v >> e;

    vector<vector<long int>> g(v, vector<long int>(v,0));     // tutte matrix of the graph

    long int indice_vertex1, indice_vertex2;                  // Indices of vertices
    for(int i=0; i<e; i++){
        cin >> indice_vertex1 >> indice_vertex2;

        if(indice_vertex1 < indice_vertex2) {
            g[indice_vertex1-1][indice_vertex2-1] = 1;
            g[indice_vertex2-1][indice_vertex1-1] = -1;
        } else {
            g[indice_vertex1-1][indice_vertex2-1] = -1;
            g[indice_vertex2-1][indice_vertex1-1] = 1;
        }
    }

    /*printf("v = %d, e = %d\n", v, e);
    table_toPrint(&g);*/

    if(gauss_elimination(&g, p) != v){
        printf("NO");
    } else {
        printf("YES");
    }

    //table_toPrint(&g);

    return 0;
}

/*=====Methods========================================================*/
void table_toPrint(vector<vector<long int>> *graph){
    int len = (*graph).size();

    for(int i=0; i<len; i++){
        for(int j=0; j<len; j++){
            printf("%ld ", (*graph)[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

long int mod_inv(long int x, long int n, long int p){
    long int x_2 = 0;

    // Verify if -p < x < p or not to compute in consequence
    x_2 = mod_mul(x, x, p);

    if(n == 0)
        return 1;
    else if(n == 1)
        return x;
    // n is odd
    else if(n%2 != 0){
        return mod_mul(x, mod_inv(x_2, (n-1)/2, p), p);
    }
    // n is even
    else if(n%2 == 0){
        return mod_inv(x_2, n/2, p);
    }
}

// Verify if -p < a, b < p or not to compute in consequence
long int mod_mul(long int a, long int b, long int p){
    long int mod = 0;

    if(abs(a) > p && abs(b) > p) {
        a %= p;
        b %= p;
    }
    mod = (a*b)%p;

    return mod;
}

long int gauss_elimination(vector<vector<long int>> *graph, long int p){
    int n = (*graph).size();
    long int tmp = 0;
    long int max_pivot = 0;
    int r_max_pivot = 0;

    for(int c=0; c<n; c++){
        max_pivot = 0;
        r_max_pivot = -1;

        for(int r=c; r<n; r++){
            if(abs((*graph)[r][c]) > abs(max_pivot)){
                max_pivot = (*graph)[r][c];
                r_max_pivot = r;
            }
        }
        //printf("After max pivot\n %d\n", r_max_pivot);

        if(r_max_pivot == -1)
            return c;

        if(r_max_pivot > c){
            for(int i=0; i<n; i++) {
                tmp = (*graph)[r_max_pivot][i];
                (*graph)[r_max_pivot][i] = (*graph)[c][i];
                (*graph)[c][i] = mod_mul(tmp, mod_inv(max_pivot, p-2, p), p);
            }
        } else {
            for(int i=0; i<n; i++)
                (*graph)[r_max_pivot][i] = mod_mul((*graph)[r_max_pivot][i], mod_inv(max_pivot, p-2, p), p);
        }
        /*printf("After pivoting and normalization\n");
        table_toPrint(graph);*/

        for(int r=0; r<n; r++){
            if(r != c){
                tmp = (*graph)[r][c];

                for(int i=0; i<n; i++)
                    (*graph)[r][i] -= mod_mul(tmp, (*graph)[c][i], p);
            }
        }
        /*printf("After all\n");
        table_toPrint(graph);*/
    }

    return (long int) (*graph).size();
}