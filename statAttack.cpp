#include "statAttack.hpp"


//generate cipher texts for a single message, and then invock the statistical algorithm
//takes a byte of plain text and the position of this byte
string statAttack(vector<unsigned char*> & cipher_array){
    //variable
    unsigned char* cipher_one_position;
    string result("");
    string first_part_of_path("");
    ostringstream fileName;
    
    int one_cipher_size = 0;
    
    while (cipher_array[0][one_cipher_size] != '\0') {
        one_cipher_size ++;
    }

    first_part_of_path = "Biases/stat_rc4_wep/stat_rc4_wep_pos_";
    
    
    cipher_one_position = new unsigned char[cipher_array.size()];
    //processing
    for (int pos = 0; pos < one_cipher_size ; pos++){
        
        for (int i =0; i < cipher_array.size(); i++) {
            //extracting all the byte in the position "pos" of all cipher texts
            cipher_one_position[i] = (cipher_array.at(i))[pos];
        }
        
        //generation of the path to the file of position's biases
        fileName << first_part_of_path << pos+1 << ".txt";
        
        //getting the result of attack on one byte
        int one_byte_result = statAlgo(fileName.str(),cipher_one_position, cipher_array.size());
        
        result+= (char) one_byte_result;
        fileName.str("");
        fileName.clear();
    }
    
    //clear
    fileName.str("");
    fileName.clear();
    clearVectorContents(cipher_array);
    delete[] cipher_one_position;
    return result;
}

//statistical attack on a single byte
//path is the fils containing all statistics
//this algorithm uses the cipher text generated without iv
int statAlgo (string path, unsigned char* cipher_seq, int length_seq){
    cout.precision(15);
    
    //variables
    Matrix vote;
    vector<IntegerDoublePair> biases;
    long double * lambdas = new long double [256];
    int* N = new int[256];
    
    //initialization
    for (int i=0 ; i < 256 ; i++)
        for(int j=0; j < 256 ; j++)
            vote[i][j] = 0;
    for (int i=0; i < 256 ; i++){
        lambdas[i]=0;
        N[i] =0;
    }
    
    //VOTE
    for(int i = 0; i < length_seq; i++){
        N[((int)(cipher_seq[i]))]++;
    }
    //second stage of vote
    for (int u = 0; u < 256; u++)
        for(int k = 0; k < 256 ; k++)
            vote[u][k] = N[u^k];
    
    //GETTING ALL BIASES
    biases = get_all_biases(path);
    
    //APPLICATION FORMULA
    for (int u=0; u< 256; u++)
        for(int k = 0; k<256 ;k++)
            lambdas[u] += vote[u][k] * log(biases.at(k).second);
    
    //getting the result
    double val = lambdas[0];
    int result = 0; //initializing
    for(int i = 1; i < 256; i++){
        if (lambdas[i] > val){
            val = lambdas[i];
            result = i;
        }
    }
    
    //clear
    biases.clear();
    delete[] N;
    delete[] lambdas;
    
    return result;
    
}

//delete the content of a vector
void clearVectorContents (vector<unsigned char*> & theArray){
    for (int i = 0; i < theArray.size(); i++) {
        delete[] theArray.at(i);
    }
    theArray.clear();
}

