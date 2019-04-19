//Patrick Keppler and Connor Wright, 2019
#include "SuffixTreeNode.h"


//********constructors*************

//default constructor for root node
SuffixTreeNode::SuffixTreeNode()
{
  id = 0;
  depth = 0;
  parent = this;
  childrenPointer = nullptr;
  sibling = nullptr;
  sl = this;
  label = {0, 0};
}


//constructor with arguments. Requires an id, label string, and a pointer to the parent.
//Optional child and sibling pointers, default to null if not provided. Depth in tree can be passed in, or computed by default.
SuffixTreeNode::SuffixTreeNode(const int & newId, const Label & inLabel, SuffixTreeNode * parentPtr, SuffixTreeNode * childPtr , SuffixTreeNode * siblingPtr, const int & treeDepth)
{
  id = newId;
  label = inLabel;
  parent = parentPtr;
  childrenPointer = childPtr;
  sibling = siblingPtr;
  sl = nullptr;

  //will initalize to zero if no parent provided
  if(parentPtr != nullptr)
  {
    calculateDepth();
  }
  else
  {
    depth = 0;
  }
}




//*******public methods*************

//returns the depth of a node
unsigned int SuffixTreeNode::getDepth() const
{
  return depth;
}

//returns a node's id
unsigned int SuffixTreeNode::getId() const
{
  return id;
}

//return a pointer to this node's parent
SuffixTreeNode * SuffixTreeNode::getParent()
{
  return parent;
}

SuffixTreeNode * SuffixTreeNode::getChildPointer()
{
  return childrenPointer;
}

SuffixTreeNode * SuffixTreeNode::getChild(char firstLabel, const string * fullString)
{
  int compare = 0;
  SuffixTreeNode * indexer = childrenPointer;
  Label indexerLabel;
  if(indexer == nullptr)
  {
    return nullptr;
  }

  while(true)
  {
    indexerLabel = indexer->getLabel();
    //compare = Alphabet::compare(firstLabel, indexer->getLabel()[0]);
    compare = Alphabet::compare(firstLabel, (*fullString)[indexerLabel.startIndex]);
    if(compare == 0)
    {
      //found child
      return indexer;
    }
    if(indexer->getSibling() == nullptr)
    {
      //unable to find child
      return nullptr;
    }
    //increment search
    indexer = indexer->getSibling();
  }
}

SuffixTreeNode * SuffixTreeNode::getSibling()
{
  return sibling;
}

SuffixTreeNode * SuffixTreeNode::getSL()
{
  return sl;
}

Label SuffixTreeNode::getLabel() {
  return label;
}

void SuffixTreeNode::setSibling(SuffixTreeNode * newSibling)
{
  sibling = newSibling;
}

void SuffixTreeNode::setParent(SuffixTreeNode * newParent)
{
  parent = newParent;
}

void SuffixTreeNode::setChildrenPointer(SuffixTreeNode * newChildPointer)
{
  childrenPointer = newChildPointer;
}

void SuffixTreeNode::calculateDepth()
{
  assert(parent != nullptr);
  depth = parent->getDepth() + label.endIndex - label.startIndex;
  //propagate changes throgh tree
  if(sibling != nullptr)
  {
    sibling->calculateDepth();
  }
  if(childrenPointer != nullptr)
  {
    childrenPointer->calculateDepth();
  }
}

void SuffixTreeNode::setDepth(int newDepth)
{
  depth = newDepth;
}

void SuffixTreeNode::setLabel(const Label & newLabel)
{
  label = newLabel;
}

//mutators

//set the suffix link of the node to the input parameter.
void SuffixTreeNode::setSL(SuffixTreeNode * v)
{
  sl = v;
}

SuffixTreeNode * SuffixTreeNode::addChild(SuffixTreeNode * newChild, const string * fullString)
{
  //check the child is valid
  assert(newChild->getLabel().startIndex != newChild->getLabel().endIndex);

  //check if the parent has a child already
  if(childrenPointer == nullptr)
  {
    //easy insertion
    childrenPointer = newChild;
    newChild->setSibling(nullptr);
    newChild->setParent(this);
    newChild->calculateDepth();
  }
  else
  {
    addSibling(newChild, childrenPointer, fullString);
  }

  return newChild;
}

//inserts a sibling in lexographic order
//called within parent node
SuffixTreeNode * SuffixTreeNode::addSibling(SuffixTreeNode * newSibling,
                                            SuffixTreeNode * firstSibling,
                                            const string * fullString)
{
  SuffixTreeNode * currentSibling = firstSibling;
  SuffixTreeNode * previousSibling = nullptr;

  bool inserted = false;
  int ordering = 0;

  newSibling->setParent(this);
  newSibling->calculateDepth();

  Label newSiblingLabel = newSibling->getLabel();
  Label currentSiblingLabel;

  while(!inserted)
  {
    currentSiblingLabel = currentSibling->getLabel();
    ordering = Alphabet::compare((*fullString)[newSiblingLabel.startIndex], (*fullString)[currentSiblingLabel.startIndex]);
    //we should not be inserting the same characters
    //assert(ordering != 0 || newSibling->getLabel()[0] != '$');
    assert(ordering != 0 || newSiblingLabel.startIndex != fullString->length() - 1);

    if(ordering < 0)
    {
      //we insert before
      newSibling->setSibling(currentSibling);

      if(currentSibling == firstSibling)
      {
        //first in the list
        this->setChildrenPointer(newSibling);
        inserted = true;
      }
      else
      {
        //inserting in middle or end
        previousSibling->setSibling(newSibling);
        inserted = true;
      }
    }
    else
    {
      //we keep looking
      if(currentSibling->getSibling() == nullptr)
      {
        //insert at the end
        currentSibling->setSibling(newSibling);
        newSibling->setSibling(nullptr);
        inserted = true;
      }
      else
      {
        //increment for search
        previousSibling = currentSibling;
        currentSibling = currentSibling->getSibling();
      }
    }
  }

  return newSibling;
}

//removes a child and returns it
SuffixTreeNode * SuffixTreeNode::removeChild(SuffixTreeNode * childToRemove)
{
  SuffixTreeNode * currentSibling = childrenPointer;
  SuffixTreeNode * previousSibling = nullptr;

  while(true)
  {
    if(childToRemove == currentSibling)
    {
      //found child
      currentSibling->setParent(nullptr);
      currentSibling->setDepth(-1);

      if(childToRemove == childrenPointer)
      {
        //removal from begining of list
        childrenPointer = currentSibling->getSibling();
        currentSibling->setSibling(nullptr);
        return currentSibling;
      }
      else
      {
        //removal from middle or end
        previousSibling->setSibling(currentSibling->getSibling());
        currentSibling->setSibling(nullptr);
        return currentSibling;
      }
    }
    else
    {
      //we continue searching

      if(currentSibling->getSibling() == nullptr)
      {
        //couldnt find child
        return nullptr;
      }
      else
      {
        previousSibling = currentSibling;
        currentSibling = currentSibling->getSibling();
      }
    }
  }
}

SuffixTreeNode * SuffixTreeNode::addInternalNode(char firstLabel, const string * fullString, int indexBreak, int id)
{
  SuffixTreeNode * childAlongEdge = getChild(firstLabel, fullString);
  assert(childAlongEdge != nullptr);

  //remove the child of the edge we want to break
  childAlongEdge = removeChild(childAlongEdge);
  assert(childAlongEdge != nullptr);

  //convert label to string for easy conversion
  //string oldLabelString = string(childAlongEdge->getLabel());
  Label oldLabel = childAlongEdge->getLabel();
  //string childAlongEdgeLabelString = string(oldLabelString.substr(indexBreak));
  Label childAlongEdgeLabel = oldLabel;

  childAlongEdgeLabel.startIndex += indexBreak;
  //string newInternalNodeLabelString= string(oldLabelString.substr(0, indexBreak));
  Label newInternalNodeLabel = oldLabel;
  newInternalNodeLabel.endIndex = oldLabel.startIndex + indexBreak;
  //save memory
  //oldLabelString = "";

  //edge is now broken
  childAlongEdge->setLabel(childAlongEdgeLabel);

  //create new internal node
  SuffixTreeNode * newInternalNode = new SuffixTreeNode(id, newInternalNodeLabel, nullptr);

  //new internal node added
  addChild(newInternalNode, fullString);
  //old child added
  newInternalNode->addChild(childAlongEdge, fullString);

  return newInternalNode;
}
