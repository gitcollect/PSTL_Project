#include "bias.hpp"

using namespace std;

/* return a vector containing n (length given in param) biais
 */
vector<IntegerDoublePair> get_bias (string path, int length){
  //initialization
  vector<IntegerDoublePair> pairVector (length, make_pair(0, 0.0));

  ifstream ifs;
  ifs.open(path.c_str(), ifstream::in);
  int key;
  double pr;
  IntegerDoublePair pair = make_pair(0, 0.0);
  while ( ifs >> key >> pr){
    pair.first = key;
    pair.second = pr;
    for(vector<IntegerDoublePair>::iterator iter = pairVector.begin() ; iter != pairVector.end(); ++iter){
      switch (compareTo(pair.second, (*iter).second)){
      	case 1 : swap(pair, (*iter));
      }
    }
  } 

  ifs.close();
  return pairVector;
  
}

/*compare two doubles and return 
	1 : pr1 grater than pr2
	-1 : pr1 lower than pr2
	0 : pr1 equals pr2
*/
int compareTo (double pr1, double pr2){
  if( pr1 > pr2)
    return 1;
  else if(pr1 < pr2)
    return -1;
  else
    return 0;
}

//return a table of doubles containing all the statistics
vector<IntegerDoublePair> get_all_biases(string path){
  
  vector <IntegerDoublePair> biases;
  ifstream ifs;
  ifs.open(path.c_str(), ifstream::in);
  int key;
  double pr;
  
  while ( ifs >> key >> pr){
    biases.push_back(make_pair(key,pr));
  }
  
  ifs.close();
  return biases;
}

