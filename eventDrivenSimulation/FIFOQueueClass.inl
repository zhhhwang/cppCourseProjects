#include <iostream>
#include "FIFOQueueClass.h"
#include "LinkedNodeClass.h"
using namespace std;

// Author: Zhihao Huang
// Date: November 25, 2019
// Purpose: This is the project 5 of EECS 402. This is the 
// implementation of templated queue class. 

template < class T >
FIFOQueueClass< T >::FIFOQueueClass()
{
  head = 0;
  tail = 0;
}

template < class T >
FIFOQueueClass< T >::~FIFOQueueClass()
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
void FIFOQueueClass< T >::enqueue(const T &newItem)
{
  // For emplt queue
  if (head == 0 && tail == 0)
  {
    LinkedNodeClass< T >* newNode = new LinkedNodeClass< T >(0, newItem, 0);
    head = newNode;
    tail = newNode;
  }
  else
  {
    LinkedNodeClass< T >* tempNode = head;
    LinkedNodeClass< T >* newNode = new LinkedNodeClass< T >(0,
                                                             newItem, 
                                                             tempNode);
    newNode->setBeforeAndAfterPointers();
    head = newNode;
  }
}

template < class T >
bool FIFOQueueClass< T >::dequeue(T &outItem)
{
  bool dequeueSuccess = true;

  // If the list is empty
  if (head == 0 && tail == 0)
  {
    dequeueSuccess = false;
  }
  else
  {
    LinkedNodeClass< T >* tempNode = tail;
    outItem = tempNode->getValue();
    // If the list has one node
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

  return dequeueSuccess;
}

template < class T >
void FIFOQueueClass< T >::print() const
{
  LinkedNodeClass< T >* tempNode = head;

  if (head == 0 && tail == 0)
  {
    ;
  }
  else
  {
    // For the first node
    if (head == tail)
    {
      cout << tempNode->getValue() << endl;
    }
    else
    {
      cout << tempNode->getValue() << " "; 
    }
    
    while (tempNode->getNext() != 0)
    {
      tempNode = tempNode->getNext();
      if (tempNode->getNext() == 0)
      {
        cout << tempNode->getValue() << endl;
      }
      else
      {
        cout << tempNode->getValue() << " ";
      }
    }
  }
}

template < class T >
int FIFOQueueClass< T >::getNumElems() const
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
void FIFOQueueClass< T >::clear()
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
