#include <iostream>
#include "LinkedNodeClass.h"

using namespace std;

// Author: Zhihao Huang
// Date: November 11, 2019
// Purpose: This is the project 5 of EECS 402. This is the 
// implementation of the templated linked node class. 

template < class T >
LinkedNodeClass< T >::LinkedNodeClass(LinkedNodeClass< T > *inPrev, 
                                      const T &inVal,        
                                      LinkedNodeClass< T > *inNext)
{
  prevNode = inPrev;
  nextNode = inNext;
  nodeVal = inVal;
}

template < class T >
T LinkedNodeClass< T >::getValue() const
{
  return nodeVal;
}

template < class T >
LinkedNodeClass< T >* LinkedNodeClass< T >::getNext() const 
{
  return nextNode;
}

template < class T >
LinkedNodeClass< T >* LinkedNodeClass< T >::getPrev() const
{
  return prevNode;
}

template < class T >
void LinkedNodeClass< T >::setNextPointerToNull()
{
  nextNode = NULL;
}

template < class T >
void LinkedNodeClass< T >::setPreviousPointerToNull()
{
  prevNode = NULL;
}

template < class T >
void LinkedNodeClass< T >::setBeforeAndAfterPointers()
{
  if (prevNode != 0)
  {
    prevNode->nextNode = this;
  }
  if (nextNode != 0)
  {
    nextNode->prevNode = this; 
  }
}

