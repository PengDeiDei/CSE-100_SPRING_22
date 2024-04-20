/*
 * Name: Haonan Peng
 * Email: hap045@ucsd.edu
 *
 * Sources Used: Lecture 20 - I use page 13 as reference for reading from file 
 * 
 *
 * This file provides functions to compress a file and store the new compressed
 * version by prasing the command line
 */

#include <fstream>
#include <iostream>
#include <vector>
#include "HCTree.hpp"
#include "Helper.hpp"
using namespace std;


int main(int argc, char* argv[]){
    // check if the format of command is valid
    if(argc != 3){
        error("Invalid format of command");
        return 1;
    }

    // reading from input file
    ifstream inFile;
    vector<int> freqs (256,0);
    int nextByte;

    // open file in binary 
    inFile.open(argv[1], ios::binary);

    // if the file is empty, throw a message and create an empty file
    if(inFile.peek() == EOF){
        inFile.close();
        ofstream empty;
        empty.open(argv[2],ios::binary);
        empty.close();
        cout<<"Empty Input File"<<endl;;
        return 0;
    }

    // count the frequency of specific symbol until reach the end of file
    while((nextByte = inFile.get()) != EOF){
        freqs[nextByte] += 1;
    }
    inFile.close();
    
    // build up HCTree
    HCTree HCT;
    HCT.build(freqs);

    ofstream outFile;
    FancyOutputStream FOStrem(argv[2]);
    outFile.open(argv[2],ios::binary);

    // serialization header
    HCT.serial(FOStrem);

    // open the inFile again to encode each symbol
    inFile.open(argv[1],ios::binary);
    while((nextByte = inFile.get()) != EOF){
        // convert byte to unsigned char and encode it
        HCT.encode((unsigned char) nextByte, FOStrem);
    }
    cout<<"Compression Finished"<<endl;
    FOStrem.flush(); // flush the buffer
    inFile.close(); 
    outFile.close();

    return 0;
}