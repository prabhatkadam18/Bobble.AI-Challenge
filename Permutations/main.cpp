#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>

using namespace std;

class CSVReader{
  string fileName;

  public: 
  CSVReader(string filename) :
    fileName(filename)
    {}

  vector<vector<char> > getData();
};

vector<vector<char> > CSVReader::getData()
{

  vector<vector<char> > dataList;
	ifstream file(fileName);

  if(!file){
    cout<<"CANNOT OPEN FILE\n";
    return dataList;
  }
 
 
	string line = "";
  
	while (getline(file, line))
	{	
    vector<char> vec;
    
		for(int i=0;i<line.length();i++){
      if(line[i]!=','&& line[i]!=' '){
        vec.push_back(line[i]);
      }
    }
    vector<char>::iterator it; 
    it = unique(vec.begin(), vec.end());                 //removing duplicate elements
    vec.resize(distance(vec.begin(), it));

    dataList.push_back(vec);
	}
  
	file.close();
 
	return dataList;
}

void printPermutations(vector<vector<char> >&arr) 
{ 
    // number of arrays 
    int n = arr.size(); 
  
    // to keep track of next element in each of 
    // the n arrays 
    int* indices = new int[n]; 
  
    int flag=0;
    // initialize with first element's index 
    for (int i = 0; i < n; i++) 
        indices[i] = 0; 
  
    while (1) {
      // printing combinations
      if(!flag){
          for (int i = 0; i < n; i++) {
            cout << arr[i][indices[i]];
          }
          flag=1;
        }
        else{
          cout<<", ";
          for (int i = 0; i < n; i++) {
            cout << arr[i][indices[i]];
          }
        }
           
  
        // find the rightmost array that has more 
        // elements left after the current element  
        // in that array 
        int next = n - 1; 
        while (next >= 0 && (indices[next] + 1 >= arr[next].size())) 
          next--; 
  
        // no such array is found so no more  
        // combinations left 
        if (next < 0) 
          return; 
  
        // if found move to next element in that  
        // array 
        indices[next]++; 
  
        // for all arrays to the right of this  
        // array current index again points to  
        // first element 
        for (int i = next + 1; i < n; i++) 
            indices[i] = 0; 
    } 
}

int main(int argc, char *argv[]){

  if(!argv[1]){
    cout<<"Problem occured in opening File.";
    return -1;
  }
  CSVReader reader(argv[1]);
  vector<vector<char> > data = reader.getData();   //reading and storing the input


  printPermutations(data);
  cout<<endl;

	return 0;
}

