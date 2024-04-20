/**
 * Name: Haonan Peng
 * Email: hap045@ucsd.edu
 *
 * Sources Used: 
 * https://rosettacode.org/wiki/Burrows%E2%80%93Wheeler_transform#C.2B.2B
 * I take this resource as reference for generating all cyclic rotatation
 * of input string
 * 
 * This file is the header file of defenition of BWT.
 */
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

/**
 * Construct the Burrows-Wheeler Transform of a given string
 *
 * @param s The input string (which must end in $)
 * @return A string representing the Burrows-Wheeler Transform of s
 */
string bwt(const string & s);
