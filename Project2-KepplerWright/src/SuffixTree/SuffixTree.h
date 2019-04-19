//Patrick Keppler and Connor Wright, 2019
#ifndef SUFFIXTREE_H
#define SUFFIXTREE_H

#include "SuffixTreeNode.h"
#include "STData.h"

class SuffixTree {

private:

//***********data*****************
SuffixTreeNode * root, * lastInserted;
unsigned int lastInternalId;

string * fullString;

//******private methods***********

//TODO: Write findPath
//findPath navigates the (sub)tree from the starting node parameter. Returns the created leaf node that was inserted
SuffixTreeNode * findPath(SuffixTreeNode * start, unsigned int suffix);

//slInsert handles the 4 cases for inserting a suffix using suffix links. Ultimately calls findPath.
SuffixTreeNode * slInsert(SuffixTreeNode * last, unsigned int suffix);

//TODO: Write nodeHop
//helper function for the node hop operation. Called by slInsert.
//Either locates the correct node (v) that already exists, or creates it.
//Returns the node v
SuffixTreeNode * nodeHop(SuffixTreeNode * start, const Label & beta);

//private recursive DFS function. Called by public DFS
void DFS(SuffixTreeNode * currentNode);

public:

//********constructors*************

SuffixTree();

//*******public methods*************

//naive suffix tree insertion.
//Invokes FindPath on every suffix of the parameter string, but only uses root
//returns true if all suffixes inserted successfully
bool basicInsert(string  * str);

//McCreight's suffix tree insertion.
//Invokes FindPath on every suffix of the parameter string, and uses suffix links
//returns true if all suffixes inserted successfully
bool McCreightInsert(string * str);

//Depth-first search. Used for gathering data and constructing the BWT
void DFS();

};

#endif
