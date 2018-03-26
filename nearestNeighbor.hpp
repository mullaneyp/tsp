/**************************************************************
 * Author: Patrick Mullaney
 * Date: 6/1/2017
 * CS325, Spring 2017
 * Description: Header file for nearest Neighbor algorithm 
 * implementation of TSP (modeled after wikipedia description).
 *************************************************************/

#ifndef nearestNeighbor_hpp
#define nearestNeighbor_hpp

#include <stdio.h>
#include "structCity.hpp"
#include <vector>
#include <stdlib.h>
#include <cmath>
#include <iostream>
#include "structTour.h"

using std::vector;

int nearestInt(struct city, struct city);
struct tour nearestNeighbor(vector<struct city>);

struct tour brute(vector<struct city>);
vector<struct tour> bruteHelper(vector<struct city>, int, int**);
int** bruteInit(vector <struct city>);
int bruteDist(struct city a, struct city b, int** t);
void resetBrute(vector<struct city>);


#endif /* nearestNeighbor_hpp */
