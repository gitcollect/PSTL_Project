#include "naiveAttack.hpp"

using namespace std;

vector <unsigned char*> getCiphers (string path){
    ifstream cipheredFile;
    cipheredFile.open(path , ios::in|ios::binary);

    vector<unsigned char *> cipher;
    int sz;
    
    while ((sz = cipheredFile.get()) != -1) {
        cipheredFile.get();
        cipheredFile.get();
        cipheredFile.get();
        unsigned char *arr = (unsigned char *)calloc(sz + 1 - 3, sizeof(char));
        cipheredFile.read((char *)arr, sz - 3);
        arr[sz - 3] = '\0';
        cipher.push_back(arr);
    }
    
    return cipher;
}


//main function
//take one argument : path of the file containing ciphers
int main (int argc, const char * argv[]){
    //to have a better precision with random senquences
    struct timeval time;
    gettimeofday(&time,NULL);
    srand((time.tv_sec * 1000) + (time.tv_usec / 1000));
    
    //Variable
    string result;
    vector<unsigned char*> cipher_array;
    
    cout << endl <<"Statistical naive attack" << endl << endl;
    
    //verifying arguments
    switch (argc) {
        case 2:
            break;
            
        default:
            cout << endl << "The program doesn't have the right arguments, please add one argument to set the path to the file (that contains ciphers) :" << endl;
            cout << endl << endl;
            return 1;
            break;
    }
    
    string path(argv[1]);
    
    cout << "Extracting ciphers from the file ..." << endl << endl;
    cipher_array = getCiphers(path);
    
    cout << "Starting the attack ..." << endl << endl;
    result = naiveAlgo(cipher_array);
    
    cout << "Result  :" << endl;
    cout << result;
    
    cout << endl << endl;
    
    path.erase(path.begin(), path.end());
    result.erase(result.begin(), result.begin());
    
    return 0;
}

