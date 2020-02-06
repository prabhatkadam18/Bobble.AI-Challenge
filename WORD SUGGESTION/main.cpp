#include <fstream>          //fstream header file for ifstream class 
#include<bits/stdc++.h>

using namespace std; 

int comapre(pair<pair<string,int>,int> p1,pair<pair<string,int>,int> p2)
{
    
    if(p1.second != p2.second)
    {
        return p1.second > p2.second ;
    }
    else {
        return p1.first.second > p2.first.second ;
    }

}

int main(int argc, char *argv[]) 
{ 
	ifstream fin;               // Creation of ifstream class object to read the file
    fin.open(argv[1]);
	// fin.open(argv[1]);      // by default open mode = ios::in mode 
    if(!fin){
        cout<<"File Can't Be Opened";
        return -1;
    }

    // string matching_word = argv[2];
    string matching_word = argv[2];

    string line;

    vector<pair <pair <string,int> ,int> > inputs;     // inputs is vector of pairs which holds word + its count in file + its matching characters count with the given word
 	 
	while (fin) {                       // Execute a loop until EOF (End of File)
		 
		getline(fin, line);         // Read a Line from File
        
        int n = line.length();      //Store the length of the line in a variable

        if(n==0){                   //Check if the line if empty and the skip a loop for it
            continue;
        }

        int k;
        string word = "";
        
        for(k=0;k<n&&line[k]!=',';k++){           //Loop to extract each character. ',' acts as a delimiter and characters stored in vector temp
            word += line[k];
        }

        k += 2;
        string word_count = "";
        while(k<n)
        {
            word_count += line[k];
            k++;
        }

        int count_of_word = stoi(word_count);

        for(k=0;k<word.size() && k<matching_word.size() && (word[k] == matching_word[k] || word[k] + 32 == matching_word[k] || word[k] == matching_word[k] + 32 );k++){}

        inputs.push_back({{word,count_of_word},k});

	}

    sort(inputs.begin(),inputs.end(),comapre);

    for(int i=0;i<inputs.size() && i<5;i++)
    {
        cout<<endl<<inputs[i].first.first;
    }
	
    return 0; 
}