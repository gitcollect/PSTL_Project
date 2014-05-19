#include "rc4.hpp"

const int N = 256;

/*
 generation of keystream with rc4 algorithm
 */
unsigned char* rc4(int number_of_bytes, int* key, int key_length){
	
	/*struct timeval time;
     gettimeofday(&time,NULL);
     srand((time.tv_sec * 1000) + (time.tv_usec / 1000));*/
	
    int* S = new int[N];
	
	//result
	unsigned char* keystream = new unsigned char[number_of_bytes];
    
    int i, j;
    int tmp;
	
	// KSA
	for (i = 0; i < N; i ++)
        S[i] = i;
    
	j = 0;
	for (i = 0; i < N; i++) {
		j = (j + S[i] + key[i % key_length]) % N;
		tmp = S[i];
		S[i] = S[j];
		S[j] = tmp;
	}
	
	// PRGA
	i = 0;
	j = 0;
	int counter = 0;
	
	while (counter < number_of_bytes){
		i = (i + 1) % N;
		j = (j + S[i]) % N;
		tmp = S[i];
		S[i] = S[j];
		S[j] = tmp;
		tmp = S[(S[i] + S[j]) % N];
		
        //register the result
		keystream[counter] = (unsigned char) tmp;
		counter ++;
	}
    //clear
    delete[] S;
    
	return keystream;
}

//generation of a random byte
int random_byte (){
    return (rand() % 256);
}

//get a sequence of results with length given in param,
//these results are generated with the same message given in param
vector<unsigned char*> cipher_mess_seq_rc4 (long length, string message){
    unsigned char* keystream;
    int key_length = 8;
    int* key = new int[key_length]; //key used with rc4
    
    //the result
    vector <unsigned char *> cipher_array;
    
    for(int i = 0; i < length; i++){
        unsigned char * cipher_text = new unsigned char[message.length()];
        //initialisation of the key
        for(int i = 0; i < key_length ; i++){
            key[i] = random_byte();
        }
        //getting the keystream
        keystream = rc4(message.length(), key, key_length);
        
        for (int j = 0; j < message.length(); j++){
            unsigned char char_tmp = message.at(j);
            cipher_text[j] = keystream[j]^char_tmp;
        }
        //adding cipher_text
        cipher_array.push_back(cipher_text);
        delete[] keystream;
    }
    //clear
    delete[] key;
    
    return cipher_array;
}

//get cipher text sequence generated from fake keystream
// 1/3 of keys are 0
vector<unsigned char*> cipher_mess_seq_fake(long length, string message){
    unsigned char * keystream; //keystream from rc4
    int key_length = 8;
    int* key = new int[key_length]; //key used with rc4
    
    //the final result of this function
    vector<unsigned char*> cipher_array;
    //getting all the keystream with rc4
    for (int i = 0; i < length; i++) {
        //initialisation of the key
        for(int i = 0; i < key_length ; i++){
            key[i] = random_byte();
        }
        
        //cipher_text
        unsigned char * cipher_text = new unsigned char[message.length()];
        unsigned char char_tmp;
        if(i%3 == 0){
            for (int j = 0; j < message.length(); j++){
                char_tmp = message.at(j);
                cipher_text[j] = 0^char_tmp;
            }
        }
        else{
            //getting the keystream
            keystream = rc4(message.length(), key, key_length);
            for (int j = 0; j < message.length(); j++){
                char_tmp = message.at(j);
                cipher_text[j] = keystream[j]^char_tmp;
            }
            delete[] keystream;
        }
        
        //adding cipher_text
        cipher_array.push_back(cipher_text);
        
    }
    delete[] key;
    
    return cipher_array;
}

//get cipher text sequence generated with keys in wep mode (using IV)
//the result is an array of cipher text
//the argument position is the position of the byte (message) giving in parametre
vector<unsigned char*> cipher_mess_seq_wep(long length, string message){
    unsigned char* keystream;
    int key_length = 8;
    int* key =  new int[key_length]; //key used with rc4
    //initialisation of the key
    for(int i = 3; i < key_length ; i++){
        key[i] = random_byte();
    }
    
    //the result
    vector <unsigned char*> cipher_array;
    
    for(int i = 0; i < length; i++){
        //cipher_text
        unsigned char * cipher_text = new unsigned char[message.length()];
        //generation of the first part of the key : IV
        for (int j = 0; j < 3; j++)
            key[j] = random_byte();
        
        //getting the keystream
        keystream = rc4(message.length(), key, key_length);

        for (int j = 0; j < message.length(); j++){
            cipher_text[j] = keystream[j]^(unsigned char)message.at(j);
        }
        //adding cipher_text
        cipher_array.push_back(cipher_text);
        delete[] keystream;
    }
    //clear
    delete[] key;

    return cipher_array;
}

