/*
 * Name: Haonan Peng
 * Email: hap045@ucsd.edu
 *
 * Sources Used: Lecture 20
 *  I use page 13 as reference for reading from file,
 *  and page 16 for writing to file.
 *
 * This file provides functions to decompress a compressed file and store 
 * the decompressed version by prasing the command line
 */

#include <fstream>
#include <iostream>
#include <vector>
#include "HCTree.hpp"
#include "Helper.hpp"
using namespace std;

int main(int argc, char* argv[]) { 
    // check if the format of command is valid
    if(argc != 3){
        error("Invalid format of command");
        return 1;
    }

    // open the input file and initialize a FancyInputStream object
    // for reading int from file in binary format
    fstream inFile;

    // debug version
    //FancyInputStream FIStrem("dna_com.txt");
    //inFile.open("dna_com.txt",ios::binary);

    FancyInputStream FIStrem(argv[1]);
    inFile.open(argv[1],ios::binary);

    // if the input file is empty, throw a message
    // and create an empty output file
    if(FIStrem.filesize() == 0){
        inFile.close();
        ofstream empty;
        empty.open(argv[2],ios::binary);
        empty.close();
        cout<<"Empty Input File"<<endl;;
        return 0;
    }

    // build the frequency vector of symbols, and initialize 
    // a counter to count the total number of chars
    vector<int> freqs (256,0);
    unsigned int tot_num_char = 0;
    for(unsigned int i = 0; i < freqs.size(); i++){
        freqs[i] = FIStrem.read<int>();
        tot_num_char += freqs[i];
    }

    // build up the HC tree
    HCTree HCT;
    HCT.build(freqs);

    ofstream outFile;

    // debug version
    //outFile.open("txt_decom.txt",ios::binary);

    outFile.open(argv[2],ios::binary);
    for(unsigned int i = 0; i < tot_num_char; i++){
        unsigned char symbol = HCT.decode(FIStrem);
        outFile.write((char*) &symbol, sizeof(symbol));
    }
    cout<<"Decompression Complete"<<endl;
    FIStrem.reset();
    inFile.close();
    outFile.close();
    return 0;
}