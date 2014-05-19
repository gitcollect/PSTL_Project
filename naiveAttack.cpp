#include "naiveAttack.hpp"

//naive attack using biais
string naiveAlgo (vector<unsigned char*> & cipher_array){
    //variables
    int* T = new int[256];
    vector<IntegerDoublePair> bias;
    ostringstream fileName;
    unsigned char * pointer_tmp;
    string result_str;
    string first_part_of_path;
//    int one_cipher_size = sizeof(cipher_array[0])/sizeof(*cipher_array[0]);
    int one_cipher_size = 0;
    
    while (cipher_array[0][one_cipher_size] != '\0') {
        one_cipher_size ++;
    }
    
    first_part_of_path = "Biases/stat_rc4_wep/stat_rc4_wep_pos_";
    
    //for every byte of cipher
    for (int pos = 0; pos < one_cipher_size; pos++) {
        
        //initialization
        for (int i = 0; i<256; i++)
            T[i] = 0;
        
        //configurating the name of the file and extracting the bias
        fileName << first_part_of_path << pos+1 << ".txt";
        bias = get_bias(fileName.str(), 1);
        
        //Vote
        for(int j = 0 ; j < cipher_array.size(); j++){
            pointer_tmp = cipher_array.at(j);
            int tmp = pointer_tmp[pos]^bias.at(0).first;
            T[tmp]++;
        }
        
        //getting the result
        int val = T[0];
        int result = 0;
        for(int i = 1; i < 256; i++){
            if (T[i] > val){
                val = T[i];
                result = i;
            }
        }
        
        char result_in_char = (char) result;
        
        result_str += result_in_char;
        
        //cleaning
        fileName.str("");
        fileName.clear();
        bias.clear();
        
    }
    
    clearVectorContents(cipher_array);
    delete[] T;
    first_part_of_path.erase(first_part_of_path.begin(), first_part_of_path.end());
    
    return result_str;
    
}

//delete the content of a vector
void clearVectorContents (vector<unsigned char*> & theArray){
    for (int i = 0; i < theArray.size(); i++) {
        delete[] theArray.at(i);
    }
    theArray.clear();
}
