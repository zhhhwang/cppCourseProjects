#include<iostream>
#include "LinkedNodeClass.h"
#include "SortedListClass.h"
using namespace std;

// Author: Zhihao Huang
// Date: November 25, 2019
// Purpose: This is the project 5 of EECS 402. This is the 
// implementation of templated doubly sorted linked list class. 

template < class T >
SortedListClass< T >::SortedListClass()
{
  head = 0;
  tail = 0;
}

template < class T >
SortedListClass< T >::SortedListClass(const SortedListClass< T > &rhs)
{
  // Create empty list
  head = 0;
  tail = 0;
  LinkedNodeClass< T >* tempNode = rhs.head;

  // Single node list
  if (rhs.head == rhs.tail && rhs.head != 0)
  {
    LinkedNodeClass< T >* initNode = new LinkedNodeClass< T >(0, 
                                                              tempNode->
                                                              getValue(), 
                                                              0);
    head = initNode;
    tail = initNode;
  }

  // Multiple nodes list
  if (tempNode != 0 && tempNode->getNext() != 0)
  {
    LinkedNodeClass< T >* initNode = new LinkedNodeClass< T >(0, 
                                                              tempNode->
                                                              getValue(), 
                                                              0);
    head = initNode;
    tail = initNode;

    LinkedNodeClass< T >* tempNodeNew = head;
    while (tempNode->getNext() != 0)
    {
      tempNode = tempNode->getNext();
      LinkedNodeClass< T >* newNode = new LinkedNodeClass< T >(tempNodeNew, 
                                                               tempNode->
                                                               getValue(),
                                                               0);
      newNode->setBeforeAndAfterPointers();
      tempNodeNew = tempNodeNew->getNext();
      tail = newNode;
    }
  }
}

template < class T >
SortedListClass< T >::~SortedListClass()
{
  LinkedNodeClass< T >* tempNode = head;
  LinkedNodeClass< T >* nodeToDelete = head;
  
  if (head != 0 && tail != 0)
  {
    while (tempNode->getNext() != 0)
    {
      tempNode = tempNode->getNext();
      nodeToDelete = tempNode->getPrev();
      delete nodeToDelete;
    }
    delete tempNode;
  }
}

template < class T >
void SortedListClass< T >::insertValue(const T &valToInsert)
{
  // Emtpy list
  if (head == 0 && tail == 0)
  {
    LinkedNodeClass< T >* newNode = new LinkedNodeClass< T >(0, 
                                                             valToInsert, 
                                                             0);
    head = newNode;
    tail = newNode;
  }
  // List with multiple nodes
  else
  {
    LinkedNodeClass< T >* tempNode = head;
    while (valToInsert >= tempNode->getValue() && tempNode->getNext() != 0)
    {
      tempNode = tempNode->getNext();
    }

    if (tempNode->getNext() == 0 && valToInsert >= tempNode->getValue())
    {
      LinkedNodeClass< T >* newNode = new LinkedNodeClass< T >(tempNode, 
                                                               valToInsert, 
                                                               0);
      newNode->setBeforeAndAfterPointers();
      tail = newNode;
    }
    else if (tempNode->getPrev() == 0 && 
             !(valToInsert >= tempNode->getValue()))
    {
      LinkedNodeClass< T >* newNode = new LinkedNodeClass< T >(0, 
                                                               valToInsert, 
                                                               tempNode);
      newNode->setBeforeAndAfterPointers();
      head = newNode;
    }
    else
    {
      LinkedNodeClass< T >* newNode = new LinkedNodeClass< T >(tempNode->
                                                               getPrev(), 
                                                               valToInsert, 
                                                               tempNode);
      newNode->setBeforeAndAfterPointers();
    }
  }
}

template < class T >
void SortedListClass< T >::clear()
{
  LinkedNodeClass< T >* tempNode = head;
  LinkedNodeClass< T >* nodeToDelete = head;
  
  while (tempNode->getNext() != 0)
  {
    tempNode = tempNode->getNext();
    nodeToDelete = tempNode->getPrev();
    delete nodeToDelete;
  }
  head = 0;
  tail = 0;
  delete tempNode;
}

template < class T >
void SortedListClass< T >::printForward() const
{
  LinkedNodeClass< T >* tempNode = head;

  cout << "Forward List Contents Follow:" << endl;

  if (head == 0 && tail == 0)
  {
    ;
  }
  else
  {
    cout << "  " << tempNode->getValue() << endl;
    while (tempNode->getNext() != 0)
    {
      tempNode = tempNode->getNext();
      cout << "  " << tempNode->getValue() << endl;
    }
  }

  cout << "End Of List Contents" << endl;
}

template < class T >
void SortedListClass< T >::printBackward() const
{
  LinkedNodeClass< T >* tempNode = tail;

  cout << "Backward List Contents Follow:" << endl;

  if (head == 0 && tail == 0)
  {
    ;
  }
  else
  {
    cout << "  " << tempNode->getValue() << endl;
    while (tempNode->getPrev() != 0)
    {
      tempNode = tempNode->getPrev();
      cout << "  " << tempNode->getValue() << endl;
    }
  }

  cout << "End Of List Contents" << endl;
}

template < class T >
bool SortedListClass< T >::removeFront(T &theVal)
{
  bool rmSuccess = true;

  // If the list is empty
  if (head == 0 && tail == 0)
  {
    rmSuccess = false;
  }
  else
  {
    LinkedNodeClass< T >* tempNode = head;
    theVal = tempNode->getValue();
    // If the list has one node
    if (head == tail)
    {
      delete tempNode;
      head = 0;
      tail = 0;
    }
    else
    {
      head = tempNode->getNext();
      head->setPreviousPointerToNull();
      delete tempNode;
    }
  }

  return rmSuccess;
}

template < class T >
bool SortedListClass< T >::removeLast(T &theVal)
{
  bool rmSuccess = true;

  // If the list is empty
  if (head == 0 && tail == 0)
  {
    rmSuccess = false;
  }
  else
  {
    LinkedNodeClass< T >* tempNode = tail;
    theVal = tempNode->getValue();
    // If the lsit has one node
    if (head == tail)
    {
      delete tempNode;
      head = 0;
      tail = 0;
    }
    else
    {
      tail = tempNode->getPrev();
      tail->setNextPointerToNull();
      delete tempNode;
    }
  }

  return rmSuccess;
}

template < class T >
int SortedListClass< T >::getNumElems() const
{
  int elementNum = 0;

  if (head == 0 && tail == 0)
  {
    elementNum = 0;
  }
  else
  {
    LinkedNodeClass< T >* tempNode = head;
    elementNum = 1;
    if (head != tail)
    {
      while (tempNode->getNext() != 0)
      {
        tempNode = tempNode->getNext();
        elementNum ++;
      }
    }
  }

  return elementNum;
}

template < class T >
bool SortedListClass< T >::getElemAtIndex(const int index, T &outVal) const
{
  bool getSuccess = true;
  int currentIdx = 0;

  if (head == 0 && tail == 0)
  {
    getSuccess = false;
  }
  else
  {
    LinkedNodeClass< T >* tempNode = head;
    for (int i = 0; i < index && tempNode->getNext() != 0; ++i)
    {
      tempNode = tempNode->getNext();
      currentIdx ++;
    }
    if (currentIdx == index)
    {
      outVal = tempNode->getValue();
    }
    else
    {
      getSuccess = false;
    }
  }

  return getSuccess;
}
