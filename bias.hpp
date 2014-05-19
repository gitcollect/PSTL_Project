#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <utility>
#include <fstream>
#include <vector>
#include <string>

#ifndef _BIAS_
#define _BIAS_

using namespace std;

typedef pair<int,double> IntegerDoublePair;

vector<IntegerDoublePair> get_bias (string, int);
int compareTo (double, double);
vector<IntegerDoublePair> get_all_biases(string);
#endif
