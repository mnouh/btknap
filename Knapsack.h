/* 
 * File:   Knapsack.h
 * Author: mnouh
 *
 * Created on March 11, 2012, 6:05 PM
 */

#ifndef KNAPSACK_H
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <bitset>
#include <string.h>
#include <math.h>
#include <sstream>
#include <time.h>
#include <sys/time.h>
#define	KNAPSACK_H

using namespace std;

class Knapsack {
public:
    Knapsack();
    Knapsack(vector< pair<int, int> > problems, int &knapsack_weight, int &numItems, int &problem_Num, int improve, ofstream & output);
    bool promising(int index, double size, double value);
    void sack(int index, double currentSize, double currentValue, vector< pair<int, int> > & copyList);
    virtual ~Knapsack();
private:

    int MAX_WEIGHT;
    vector< pair<int, int> > * items; //sorted p/v
    int num_items;
    int problem_Num;
    int MAX_VALUE;
    vector< pair<int, int> > * solution; //Solution with the best list.
    vector< vector < pair <int, int> > * > * instance_list;
 
};

#endif	/* KNAPSACK_H */

