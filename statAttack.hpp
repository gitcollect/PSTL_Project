#include "bias.hpp"
#include "rc4.hpp"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <string>
#include <cmath>
#include <sstream>

#ifndef _STAT_ATTACK_
#define _STAT_ATTACK_

using namespace std;

//types
typedef int Matrix [256][256];

string statAttack(vector<unsigned char*> &);
int statAlgo(string, unsigned char*, int);
void clearVectorContents (vector<unsigned char*> &);

#endif