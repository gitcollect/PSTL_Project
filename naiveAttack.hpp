#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include "bias.hpp"
#include "rc4.hpp"

#ifndef _NAIVE_ATTACK_
#define _NAIVE_ATTACK_

using namespace std;

string naiveAlgo(vector<unsigned char*> &);
void clearVectorContents (vector<unsigned char*> &);

#endif