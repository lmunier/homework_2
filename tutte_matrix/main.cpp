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
/*void table_toPrint(int **graph){
    int len = sizeof(graph)/sizeof(graph[0]);

    for(int i=0; i<len; i++){
        for(int j=0; j<len; j++){
            printf("%d ", graph[j][i]);
        }
        printf("\n");
    }
}*/

/*=====Main===========================================================*/

int main(int argc, char** argv){

// initializing rand seed
    srand(time(0));

// parsing input & and set up graph
    int parser1;
    int parser2;

    istringstream iss;
    string line;
    getline(cin,line);
    iss = istringstream(line);

    // read number of vertices and edges
    iss >> parser1 >> parser2;

    int v(parser1);						// #vertices
    int e(parser2);						// #edges
    int g[v][v] = {0};

    /*for(int i=0; i<e; i++){
        getline(cin,line);
        iss = istringstream(line);
        iss >> parser1 >> parser2;

        if(parser1 > parser2) {
            g[parser1][parser2] = -1;
            g[parser2][parser1] = 1;
        } else {
            g[parser1][parser2] = 1;
            g[parser2][parser1] = -1;
        }
    }*/

    printf("v = %d, e = %d\n", v, e);

    for(int i=0; i<v; i++){
        for(int j=0; j<v; j++){
            printf("%d ", g[j][i]);
        }
        printf("\n");
    }

    return 0;
}

/*=====Methods========================================================*/
