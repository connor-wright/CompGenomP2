//Patrick Keppler and Connor Wright, 2019
#ifndef STDATA_H
#define STDATA_H

#include <iostream>
#include <sys/time.h>
#include <cassert>
#include <string>

#include "SuffixTreeNode.h"

using std::cout;
using std::string;

//Static class for handling data from the suffix tree. Call "init: before using.
class STData {
private:
//***********data*****************
  static unsigned int internalNodes, leafNodes, len, position;
  static char * bwt;
  static string * inputStr;
  static struct timeval * startTime, * endTime;
  static SuffixTreeNode * deepestInternal;

//******private methods***********

  //recursive contstruction of longest repeating string
  static bool constructLongestRepeat(SuffixTreeNode * currentNode, Label * cumulativeLabel);

public:

//*******public methods*************


  //increment counters for notable values
  static void incrementInternalNodes();
  static void incrementLeafNodes();
  //Will save the deepest internal node of the suffix tree to STData
  static void findLongestRepeat(SuffixTreeNode * inNode);
  //give the index for adding to the BWT. Conversion from index to character handled by  STData
  static void pushBwt(unsigned int index);
  static void startTimer();
  static void stopTimer();

  //initialize the static class
  static void init(string * str, const unsigned int & length);
  //destroy the dynamically-sized bwt table, as well as timers if used
  static void done();

  //print the bwt 1 character to a line
  static void printBwt();
  //print non-bwt data
  static void printData();

  //print time elapsed between startTimer and stopTimer calls
  static void printElapsedTime();

  //print the longest repeating substring, based on the deepest internal node
  static void printLongestRepeat();

};

#endif
