#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "map.h"
#include "random.h"
#include "strlib.h"
#include "vector.h"
#include "filelib.h"
using namespace std;

const int num = 2000; // the number of characters that should be generated

string filename; //input filename

Map<string, Vector<char> > seeds; //the k-order seeds with possible chars following


// ask user to reprompt the source file name until it's valid
bool isFileValid(ifstream & infile);

//get the size of the input file
int fileSize(ifstream & infile);


//build the Markov model
void buildMarkov(ifstream & infile, int order, int file_size);

//get the most frequent seed
string getFirstSeed();

//get the most frequent char following the current seed
char nextChar(string cur_seed);

//generate the output file
void generateFile(ofstream & outfile, string seed);

int main() {
    ifstream infile;
    
    cout<<"Enter the source text file: ";
    cin>>filename;
    cout<<endl;
    while (isFileValid(infile) == false);
    
    int order;
    cout<<"Enter the order of Markov model: ";
    cin>>order;
    
    int file_size = fileSize(infile);
    buildMarkov(infile, order, file_size);
    
    string outfilename = "TheNewFile.txt";
    ofstream outfile(outfilename.c_str());
    
    string seed = getFirstSeed();
    for (int i = 0; i < seed.size(); i++) {
        outfile.put(seed[i]);
    }
    
    generateFile(outfile, seed);
    cout<<"The result has been written in "<<outfilename<<". Please check out!";
    cout<<endl;
    
    return 0;
}

//the implement of all the functions declared above

bool isFileValid(ifstream & infile){
    infile.open(filename.c_str());
    if (!infile.is_open()) {
        infile.clear();
        return false;
    }
    return true;
}

int fileSize(ifstream & infile){
    int size = 0;
    char ch;
    
    while (infile.get(ch)) {
        size++;
    }
    
    infile.close();
    return size;
    
}

void buildMarkov(ifstream & infile, int order, int file_size){
    char ch;
    string s,prev="";
    int temp = order;
    temp++;
    while (file_size-->0) {
        if (prev=="") {
            while (temp-->0) {
                infile.get(ch);
                s += ch;
            }
        }
        else {
            s += prev;
            infile.get(ch);
            s += ch;
        }
        prev = s.substr(1);
        seeds[s.substr(0,order)].add(s[order]);
        temp = order;
        s = "";
    }
    return;
    
}

string getFirstSeed() {
    int max = 0;
    string w;
    foreach(string s in seeds){
        if (seeds[s].size() >= max) {
            max = seeds[s].size();
            w = s;
        }
    }
    
    return w;
    
}

char nextChar(string cur_seed) {
    Map<char, int> freq;
    int max = 0;
    char next;
    
    for (int i = 0 ; i < (seeds[cur_seed].size() - 1) ; i++) {
        freq[seeds[cur_seed][i]]++;
    }
    
    foreach (char c in freq){
        if (freq[c] >= max) {
            max = freq[c];
            next = c;
        }
    }
    
    return next;
    
}

void generateFile(ofstream & outfile, string seed){
    static int count = 0;
    char ch = nextChar(seed);
    while (count++<num) {
        count++;
        outfile.put(ch);
        seed+=ch;
        
        generateFile(outfile, seed.substr(1));
    }
    return;
    
}



