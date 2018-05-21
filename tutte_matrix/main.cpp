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
int verify_mod(int, int, int);
void gauss_elimination(vector<vector<int>> *);

/*=====Main===========================================================*/

int main(int argc, char** argv){

// initializing rand seed
    srand(time(0));

    int v = 0;						                // #vertices
    int e = 0;						                // #edges
    int p = 1000000009;                             // prime

    // store number of vertices and edges
    cin >> v >> e;

    vector<vector<int>> g(v, vector<int>(v,0));     // tutte matrix of the graph

    int indice_vertex1, indice_vertex2;             // Indices of vertices
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

    printf("v = %d, e = %d\n", v, e);
    table_toPrint(&g);
    gauss_elimination(&g);
    table_toPrint(&g);

    return 0;
}

/*=====Methods========================================================*/
void table_toPrint(vector<vector<int>> *graph){
    int len = (*graph).size();

    for(int i=0; i<len; i++){
        for(int j=0; j<len; j++){
            printf("%d ", (*graph)[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int mod_inv(int x, int p){
    int n = p-2;
    int x_2 = 0;
    int end_cond = 0;
    int result = 1;

    // Verify if -p < x < p or not to compute in consequence
    x_2 = verify_mod(x, x, p);

    // n is odd
    if(n%2 != 0){
        result = x%p;
        end_cond = (n-1)/2;
    }
        // n is even
    else {
        end_cond = n/2;
    }

    for(int i=0; i<end_cond; i++)
        result = verify_mod(x_2, result, p);

    return result;
}

// Verify if -p < a, b < p or not to compute in consequence
int verify_mod(int a, int b, int p){
    int mod = 0;

    if(abs(a) > p && abs(b) > p) {
        a %= p;
        b %= p;
    }
    mod = a*b%p;

    return mod;
}

void gauss_elimination(vector<vector<int>> *graph){
    int n = (*graph).size();
    int tmp = 0;
    int max_pivot = 0;
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
        printf("After max pivot\n %d\n", r_max_pivot);

        if(r_max_pivot == -1)
            break;

        if(r_max_pivot > c){
            for(int i=0; i<n; i++) {
                tmp = (*graph)[r_max_pivot][i];
                (*graph)[r_max_pivot][i] = (*graph)[c][i];
                (*graph)[c][i] = tmp/max_pivot;
            }
        } else {
            for(int i=0; i<n; i++)
                (*graph)[r_max_pivot][i] /= max_pivot;
        }
        printf("After pivoting and normalization\n");
        table_toPrint(graph);

        for(int r=0; r<n; r++){
            if(r != c){
                tmp = (*graph)[r][c];

                for(int i=0; i<n; i++)
                    (*graph)[r][i] -= tmp*(*graph)[c][i];
            }
        }
        printf("After all\n");
        table_toPrint(graph);
    }
}