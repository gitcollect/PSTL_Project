#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <utility>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

int main (int argc, const char* argv[]){
    //variables
    ostringstream oss;
    ifstream ifs;
    ofstream ofs;
    long total = pow(2,45);
    int change_counter = 0;
    int position;
    int byte_value;
    double count;
    
    ifs.open("RC4_keystream_dist_2_45.txt", ifstream::in);
    
    ifs >> position >> byte_value >> count;
    oss << "result_parse/stat_rc4_simple_pos_" << position+1 << ".txt";
    ofs.open(oss.str().c_str(), ofstream::out);
    
    ofs << byte_value << " " << (count/total) << endl;
    change_counter++;
    
    while ( ifs >> position >> byte_value >> count){
        if(change_counter == 256){
            ofs.close();
            oss.str("");
            oss.clear();
            oss << "result_parse/stat_rc4_simple_pos_" << position+1 << ".txt";
            ofs.open(oss.str().c_str(), ofstream::out);
            change_counter = 0;
        }
        ofs << byte_value << " " << (count/total) << endl;
        change_counter++;
    }
    
    ofs.close();
    ifs.close();
    oss.str("");
    oss.clear();
    return 0;
}