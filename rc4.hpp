#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <utility>
#include <string>

#ifndef _RC4_
#define _RC4_

using namespace std;

unsigned char* rc4(int, int*, int);
int random_byte();
vector<unsigned char*> cipher_mess_seq_rc4 (long, string);
vector<unsigned char*> cipher_mess_seq_fake(long, string);
vector<unsigned char*> cipher_mess_seq_wep(long, string);

#endif
