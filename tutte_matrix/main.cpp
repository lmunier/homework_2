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
void table_toPrint(vector<vector<long long int>> *);
long long int mod_inv(long long int, long long int, long long int);
long long int mod_mul(long long int, long long int, long long int);
int gauss_elimination(vector<vector<long long int>> *, long long int);

/*=====Main===========================================================*/

int main(int argc, char** argv){
    unsigned int v = 0;						                // #vertices
    unsigned int e = 0;						                // #edges
    unsigned int repeat = 1000000;                          // # of repeating randomize + gaussian eliminnation
    long long int rnd = 0;
    long int p = 1000000009;                                // prime

    random_device rd;
    uniform_real_distribution<long double> dist(-p, p);

    // store number of vertices and edges
    cin >> v >> e;

    int index_vertex[e][2];                        // store the indices of each vertex

    for(int i=0; i<e; i++) {
        cin >> index_vertex[i][0] >> index_vertex[i][1];
    }

    vector<vector<long long int>> g(v, vector<long long int>(v,0));     // tutte matrix of the graph

    //clock_t begin = clock();
    while(repeat > 0){
        for (int i = 0; i < e; i++) {
            rnd = (long long int) dist(rd);

            if (index_vertex[i][0] < index_vertex[i][1]) {
                g[index_vertex[i][0] - 1][index_vertex[i][1] - 1] = rnd;
                g[index_vertex[i][1] - 1][index_vertex[i][0] - 1] = -rnd;
            } else {
                g[index_vertex[i][0] - 1][index_vertex[i][1] - 1] = -rnd;
                g[index_vertex[i][1] - 1][index_vertex[i][0] - 1] = rnd;
            }
        }

        if(gauss_elimination(&g, p) == v) {
            printf("YES");
            break;
        } else {
            repeat--;
        }

        // Reinitialize g vector table
        for (auto &i : g)
            fill(i.begin(), i.end(), 0);
    }

    /*clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

    printf("%f\n", elapsed_secs);*/

    if(repeat == 0)
        printf("NO");

    return 0;
}

/*=====Methods========================================================*/
void table_toPrint(vector<vector<long long int>> *graph){
    int len = (*graph).size();

    for(int i=0; i<len; i++){
        for(int j=0; j<len; j++){
            printf("%lld ", (*graph)[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

long long int mod_inv(long long int x, long long int n, long long int p){
    if(x == 0)
        return 0;

    long long int x_2 = 0;

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
long long int mod_mul(long long int a, long long int b, long long int p){
    if(a == 0 || b == 0)
        return 0;

    a %= p;
    b %= p;

    return (a*b)%p;
}

int gauss_elimination(vector<vector<long long int>> *graph, long long int p){
    int r_max_pivot = 0;
    int n = (*graph).size();
    long long int tmp = 0;
    long long int max_pivot = 0;

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

        // Normalize pivot row
        for(auto &it : (*graph)[r_max_pivot])
                it = mod_mul(it, mod_inv(max_pivot, p - 2, p), p);

        // Swap lines if pivot is not in the diagonal
        if(r_max_pivot > c)
            (*graph)[r_max_pivot].swap((*graph)[c]);

        for(int r=c+1; r<n; r++){
            tmp = (*graph)[r][c];

            for(int i=c; i<n; i++)
                (*graph)[r][i] -= mod_mul(tmp, (*graph)[c][i], p);
        }

        /*printf("After all\n");
        table_toPrint(graph);*/
    }

    return n;
}