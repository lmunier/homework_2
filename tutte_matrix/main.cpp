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
#include <random>       // for random number

using namespace std;

/*=====Class Declarations=============================================*/

/*=====Method Declarations============================================*/
void table_toPrint(vector<vector<long int>> *);
long int mod_inv(long int, long int, long int);
long int mod_mul(long int, long int, long int);
int gauss_elimination(vector<vector<long int>> *, long int);

/*=====Main===========================================================*/

int main(int argc, char** argv){
    // Initialize random numbers
    srand(time(NULL));

    int v = 0;						                // #vertices
    int e = 0;						                // #edges
    long int nbYES = 0;
    long int nbNO = 0;
    long int rnd = 0;
    long int repeat = 500000;                       // # of repeating randomize + gaussian eliminnation
    long int p = 1000000009;                        // prime

    // store number of vertices and edges
    cin >> v >> e;

    int indice_vertex[e][2];                        // store the indices of each vertex

    for(int i=0; i<e; i++) {
        cin >> indice_vertex[i][0] >> indice_vertex[i][1];
    }

    vector<vector<long int>> g(v, vector<long int>(v,0));     // tutte matrix of the graph

    while(repeat > 0) {
        for(int r=0; r<v; r++){
            for(int c=0; c<v; c++)
                g[r][c] = 0;
        }

        for (int i = 0; i < e; i++) {
            rnd = abs(mod_mul((long int) rand(), (long int) rand(), p));

            if (indice_vertex[i][0] < indice_vertex[i][1]) {
                g[indice_vertex[i][0] - 1][indice_vertex[i][1] - 1] = rnd;
                g[indice_vertex[i][1] - 1][indice_vertex[i][0] - 1] = -rnd;
            } else {
                g[indice_vertex[i][0] - 1][indice_vertex[i][1] - 1] = -rnd;
                g[indice_vertex[i][1] - 1][indice_vertex[i][0] - 1] = rnd;
            }
        }

        if(gauss_elimination(&g, p) != v){
            nbNO++;
        } else {
            nbYES++;
        }
        repeat--;
    }

    printf("nbNO: %ld, nbYES: %ld", nbNO, nbYES);

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

int gauss_elimination(vector<vector<long int>> *graph, long int p){
    int n = (*graph).size();
    long int tmp = 0;
    long int max_pivot = 0;
    int r_max_pivot = 0;

    for(int c=0; c<n; c++) {
        max_pivot = 0;
        r_max_pivot = -1;

        for (int r = c; r < n; r++) {
            if (abs((*graph)[r][c]) > abs(max_pivot)) {
                max_pivot = (*graph)[r][c];
                r_max_pivot = r;
            }
        }

        if (r_max_pivot == -1){
            if(max_pivot == 0)
                return -1;
            else
                return c;
        }

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

        for(int r=0; r<n; r++){
            if(r != c){
                tmp = (*graph)[r][c];

                for(int i=0; i<n; i++)
                    (*graph)[r][i] -= mod_mul(tmp, (*graph)[c][i], p);
            }
        }
    }

    return (int) (*graph).size();
}