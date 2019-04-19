//Patrick Keppler and Connor Wright, 2019
#ifndef SUFFIXTREENODE_H
#define SUFFIXTREENODE_H

#include <cstring>
#include <cassert>

#include "../Alphabet.h"


typedef struct label
{
  unsigned int startIndex;
  unsigned int endIndex;
}Label;

//Nodes for use by a Suffix Tree
class SuffixTreeNode {


private:
//***********data*****************
unsigned int id, depth;
SuffixTreeNode * childrenPointer, * sibling, * parent, * sl;
Label label;


//******private methods***********

//adds and returns sibling if possible
SuffixTreeNode *
    addSibling(SuffixTreeNode * newSibling,
               SuffixTreeNode * firstSibling,
               const string * fullString);
public:

//********constructors*************

//default constructor for root node
SuffixTreeNode();

//constructor with arguments. Requires an id, label string, and a pointer to the parent.
//Optional child and sibling pointers, default to null if not provided. Depth in tree can be passed in, or computed by default.
SuffixTreeNode(const int & newId, const Label & inLabel, SuffixTreeNode * parentPtr, SuffixTreeNode * childPtr = nullptr, SuffixTreeNode * siblingPtr = nullptr, const int & treeDepth = 0);


//*******public methods*************

//accessors
unsigned int getDepth() const;
unsigned int getId() const;
SuffixTreeNode * getParent();
SuffixTreeNode * getChildPointer();
SuffixTreeNode * getChild(char firstLabel, const string * fullString);
SuffixTreeNode * getSibling();
SuffixTreeNode * getSL();
Label getLabel();

void setSibling(SuffixTreeNode * newSibling);
void setParent(SuffixTreeNode * newParent);
void setChildrenPointer(SuffixTreeNode * newChildPointer);
//sets calculates and sets depth if possible
//also tells children and siblings to recalculate depth
void calculateDepth();
void setDepth(int newDepth);
void setLabel(const Label & newLabel);

//mutators
void setSL(SuffixTreeNode * v);

//adds a child to the node maintaing lexographic ordering
SuffixTreeNode * addChild(SuffixTreeNode * newChild, const string * fullString);
//removes a child from the node and returns it
SuffixTreeNode * removeChild(SuffixTreeNode * childToRemove);
//adds a new internal node along the edge
//firstLable: char of the label we will break
//indexBreak: index where the break will occure
SuffixTreeNode * addInternalNode(char firstLabel, const string * fullString, int indexBreak, int id);

};

#endif
