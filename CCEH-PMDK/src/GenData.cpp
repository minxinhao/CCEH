#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;


int main (int argc, char* argv[])
{ 
    int numData = atoi(argv[1]);
    ofstream ofs;
    string dataset = "./input_rand.txt";
    ofs.open(dataset);
    if (!ofs){
        cerr << "No file." << endl;
        exit(1);
    }
    else{
        uint64_t key ;
        for(int i=0; i<numData; i++){
            key = rand();
            ofs << key;
        }   
    ofs.close();
    cout << dataset << " is used." << endl;
    }
}