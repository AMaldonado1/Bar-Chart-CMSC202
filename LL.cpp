/***********************************************************
 ** File:    LL.cpp
 ** Project: CMSC 202 - Project 5
 ** Author:  Started by Jeremy Dixon Finished by Adrian Maldonado
 ** Email:   amaldon1@umbc.edu
 ** Date     4/25/2023
 ** Section: 11
 ** This file contains the definition cpp file of the Linked List
 **********************************************************/
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

// DO NOT ADD ANY CONSTANTS OR FUNCTIONS TO ANY CLASS

// Templated Node class
// Normal node except that each node can hold a pair <T,int>
// where the first value is templated and the second value is the frequency
// (or quantity) of the first
// For example, if T was a string then it would hold string,int
template <class T>
class Node
{
public:
  Node(const T &data);                // Node Constructor - Assume each quantity
  pair<T, int> &GetData();            // Node Data Getter
  void SetData(const pair<T, int> &); // Node Data Setter
  Node<T> *GetNext();                 // Node m_next getter
  void SetNext(Node<T> *next);        // Node m_next setter
private:
  pair<T, int> m_data; // Holds templated data
  Node<T> *m_next;     // Pointer to next node
};

template <class T>
Node<T>::Node(const T &data)
{
  m_data = make_pair(data, 1);
  m_next = nullptr;
}

template <class T>
pair<T, int> &Node<T>::GetData()
{
  return m_data;
}

template <class T>
void Node<T>::SetData(const pair<T, int> &data)
{
  m_data = data;
}

template <class T>
Node<T> *Node<T>::GetNext()
{
  return m_next;
}

template <class T>
void Node<T>::SetNext(Node<T> *next)
{
  m_next = next;
}

// Templated Linked List class
template <class T>
class LL
{
public:
  // Name: LL() (Linked List) - Default Constructor
  // Desc: Used to build a new linked list
  // Preconditions: None
  // Postconditions: Creates a new linked list where m_head points to nullptr
  LL();
  // Name: ~LL() - Destructor
  // Desc: Used to destruct a LL
  // Preconditions: There is an existing LL with at least one node
  // Postconditions: A LL is deallocated (including dynamically allocated nodes)
  //                 to have no memory leaks!
  ~LL();
  // Name: LL (Copy Constructor)
  // Desc: Creates a copy of existing LL
  //       Requires a LL - REQUIRED to be implemented even if not used
  // Preconditions: Source LL exists
  // Postconditions: Copy of source LL
  LL(const LL &);
  // Name: operator= (Overloaded Assignment Operator)
  // Desc: Makes two LL of the same type have identical number of nodes and values
  // Preconditions: Requires two linked lists of the same templated type
  //                REQUIRED to be implemented even if not used
  // Postconditions: Two idenetical LL
  LL<T> &operator=(const LL &);
  // Name: Find
  // Desc: Iterates through LL and returns node if data found
  // Preconditions: LL Populated
  // Postconditions: Returns nullptr if not found OR Node pointer if found
  Node<T> *Find(const T &data);
  // Name: Insert
  // Desc: Either inserts a node to the linked list OR increments frequency of first
  //       Takes in data. If "first" (of pair) NOT in list, adds node
  //       If "first" (of pair) is already in list, increments quantity
  //       Inserts "first" in order with no duplicates
  // Preconditions: Requires a LL.
  // Postconditions: Node inserted in LL based on first value (or quantity incremented)
  void Insert(const T &);
  // Name: RemoveAt
  // Desc: Removes a node at a particular position based on data passed (matches first)
  // Preconditions: LL with at least one node.
  // Postconditions: Removes first node with passed value (in first)
  void RemoveAt(const T &);
  // Name: Display
  // Desc: Display all nodes in linked list
  // Preconditions: Outputs the LL
  // Postconditions: Displays the pair in each node of LL
  void Display();
  // Name: GetSize
  // Desc: Returns the size of the LL
  // Preconditions: Requires a LL
  // Postconditions: Returns m_size
  int GetSize();
  // Name: operator<< (Overloaded << operator)
  // Desc: Returns the ostream of the data in each node
  // Preconditions: Requires a LL
  // Postconditions: Returns an ostream with the data from each node on different line
  template <class U>
  friend ostream &operator<<(ostream &output, const LL<U> &);
  // Name: Overloaded [] operator
  // Desc: When passed an integer, returns the data at that location
  // Precondition: Existing LL
  // Postcondition: Returns pair from LL using []
  pair<T, int> &operator[](int x); // Overloaded [] operator to pull data from LL
private:
  Node<T> *m_head; // Node pointer for the head
  int m_size;      // Number of nodes in queue
};
//*****************************************************************
// Implement LL here

// Name: LL() (Linked List) - Default Constructor
// Desc: Used to build a new linked list
// Preconditions: None
// Postconditions: Creates a new linked list where m_head points to nullptr
template <class T>
LL<T>::LL()
{
  m_head = nullptr;
  m_size = 0;
}

// Name: ~LL() - Destructor
// Desc: Used to destruct a LL
// Preconditions: There is an existing LL with at least one node
// Postconditions: A LL is deallocated (including dynamically allocated nodes)
//                 to have no memory leaks!
template <class T>
LL<T>::~LL()
{
  // Makes the new node and a temporary node pointer to travel through the linked list
  Node<T> *traverse = m_head;
  while (traverse != nullptr)
  {
    // The head pointer is now changed to what the temporary pointer points to
    m_head = traverse;
    // The temporary pointer is now the next node in the linked list
    traverse = traverse->GetNext();
    // Deletes the pointer, head, located before the temporary node
    delete m_head;
  }
  // Sets the values back to the originals, null pointer head and tail and size of zero
  m_head = nullptr;
  m_size = 0;
}

// Name: LL (Copy Constructor)
// Desc: Creates a copy of existing LL
//       Requires a LL - REQUIRED to be implemented even if not used
// Preconditions: Source LL exists
// Postconditions: Copy of source LL
template <class T>
LL<T>::LL(const LL &copiedList)
{
  // Normal construction of the linked list
  m_head = nullptr;
  m_size = 0;
  // If the linked list being copied is not empty
  if (copiedList.m_head != nullptr)
  {
    // Makes a node pointer to the list that will be copied and a traveral pointer of the new list
    Node<T> *copiedNode = copiedList.m_head;
    Node<T> *traverse = m_head;
    // Loop through the copied list while it still has a nodes
    while (copiedNode != nullptr)
    {
      // Makes the new node and sets it's data to be the same as the copied node
      Node<T> *newNode = new Node<T>(copiedNode->GetData().first);
      newNode->SetData(copiedNode->GetData());
      // Moves the copied node to the next node in the list
      copiedNode = copiedNode->GetNext();
      // The first iteration, it sets the head to the first node being copied, only happens once
      if (m_size == 0)
      {
        // Traversal node now points to the first node and will start there
        m_head = newNode;
        traverse = newNode;
        m_size++;
      }
      else
      {
        // Sets node that the traversal node is pointing to point at the new node copied

        traverse->SetNext(newNode);
        // Moves the traversal node to that new node just added to the linked list before
        traverse = traverse->GetNext();
        // Increases the size of the linked list
        m_size++;
      }
    }
  }
}

// Name: operator= (Overloaded Assignment Operator)
// Desc: Makes two LL of the same type have identical number of nodes and values
// Preconditions: Requires two linked lists of the same templated type
//                REQUIRED to be implemented even if not used
// Postconditions: Two idenetical LL

template <class T>
LL<T> &LL<T>::operator=(const LL &copiedList)
{
  // Makes the new node and a temporary node pointer to travel through the linked list
  Node<T> *traverse = m_head;
  while (traverse != nullptr)
  {
    // The head pointer is now changed to what the temporary pointer points to (current node)
    m_head = traverse;
    // The temporary pointer is now the next node in the linked list
    traverse = traverse->GetNext();
    // Deletes the pointer, head, located before the temporary node
    delete m_head;
  }
  // Sets the values back to the originals, null pointer head and tail and size of zero
  m_head = nullptr;
  m_size = 0;
  // If the linked list being copied is the same memory address
  if (this == &copiedList)
  {
    return *this;
  }
  // If the linked list being copied is not empty
  if (copiedList.m_head != nullptr)
  {
    // Makes a node pointer to the list that will be copied and a traveral pointer of the new list
    Node<T> *copiedNode = copiedList.m_head;
    Node<T> *traverse = m_head;
    // Loop through the copied list while it still has a nodes
    while (copiedNode != nullptr)
    {
      // Makes the new node and sets it's data to be the same as the copied node
      Node<T> *newNode = new Node<T>(copiedNode->GetData().first);
      newNode->SetData(copiedNode->GetData());
      // Moves the copied node to the next node in the list
      copiedNode = copiedNode->GetNext();
      // The first iteration, it sets the head to the first node being copied, only happens once
      if (m_size == 0)
      {
        // Traversal node now points to the first node and will start there
        m_head = newNode;
        traverse = newNode;
        m_size++;
      }
      else
      {
        // Sets node that the traversal node is pointing to point at the new node copied
        traverse->SetNext(newNode);
        // Moves the traversal node to that new node just added to the linked list before
        traverse = traverse->GetNext();
        // Increases the size of the linked list
        m_size++;
      }
    }
  }
  // Returns the copied linked list newly made
  return *this;
}

// Name: Find
// Desc: Iterates through LL and returns node if data found
// Preconditions: LL Populated
// Postconditions: Returns nullptr if not found OR Node pointer if found
template <class T>
Node<T> *LL<T>::Find(const T &data)
{
  // If the linked list is empty (there is no first key value) it returns nullptr
  if (GetSize() == 0)
  {
    return nullptr;
  }
  // If the linked list is not empty it will search it
  else
  {
    // Makes a new node pointer to find the first key value starting at the head
    Node<T> *traverse = m_head;
    // Uses the new node to go through the linked list until it reaches the last element
    while (traverse != nullptr)
    {
      // Checks if the data is the same first key value as the node at that location
      if (traverse->GetData().first == data)
      {
        // Returns the node pointer if it is the same key value
        return traverse;
      }
      // If the data is not the same then it will traverse to the next node
      traverse = traverse->GetNext();
    }
    // If the first key value was not found it returns nullptr
    return nullptr;
  }
}

// Name: Insert
// Desc: Either inserts a node to the linked list OR increments frequency of first
//       Takes in data. If "first" (of pair) NOT in list, adds node
//       If "first" (of pair) is already in list, increments quantity
//       Inserts "first" in order with no duplicates
// Preconditions: Requires a LL.
// Postconditions: Node inserted in LL based on first value (or quantity incremented)
template <class T>
void LL<T>::Insert(const T &data)
{
  // If the node first key data value is not found in the linked list
  if (Find(data) == nullptr)
  {
    // Makes a new node pointer to find the first key value starting at the head
    Node<T> *newNode = new Node<T>(data);
    // Makes a new node pointer to traverse the linked list starting at the head
    Node<T> *traverse = m_head;
    // Makes a new node that is the previous node to the one that will be added
    Node<T> *previousNode = m_head;
    // Makes a loop counter to set the head of the linked list
    int loopCounter = 0;
    // Loop through the linked list until you reach the end
    while (traverse != nullptr)
    {
      // Check to see if the new node is less alphabetically than the current node
      if (traverse->GetData().first > newNode->GetData().first)
      {
        // Make the new node point at the next node
        newNode->SetNext(traverse);
        // If it hasn't looped once that means that it is the smallest alphabetically and is therefore the head
        if (loopCounter == 0)
        {
          m_head = newNode;
          m_size++;
          return;
        }
        // Makes the previous node point at the new node
        previousNode->SetNext(newNode);
        // // Increases the size of the linked list
        m_size++;
        return;
      }
      // If the new node is greater alphabetically than the current node
      else if (traverse->GetData().first < newNode->GetData().first)
      {
        // Makes the previous node the current node
        previousNode = traverse;
        // Moves the current node up one
        traverse = traverse->GetNext();
        // Increases the counter of the linked list looping
        loopCounter++;
      }
    }
    // If the loop reaches the end of the linked list then the new node entered is last alphabetically
    if ((traverse == nullptr) && (m_size > 0))
    {
      // Increases size and sets the previous node pointer to the new node pointer
      previousNode->SetNext(newNode);
      m_size++;
      return;
    }
    // If the linked list is empty it adds the new node right away and makes it the head
    m_head = newNode;
    m_size++;
    return;
  }
  // If the node first key data value is found in the linked list
  else
  {
    // Makes a new node pointer and sets it to the node of the key data value found
    Node<T> *newNode = Find(data);
    // Makes a new pair same as the data of the node except adding one to the value count
    pair<T, int> newPair(data, newNode->GetData().second + 1);
    // Replaces the old pair with the new pair to show incrementing
    newNode->SetData(newPair);
  }
}

// Name: RemoveAt
// Desc: Removes a node at a particular position based on data passed (matches first)
// Preconditions: LL with at least one node.
// Postconditions: Removes first node with passed value (in first)
template <class T>
void LL<T>::RemoveAt(const T &data)
{
  // If the node first key data value is not found in the linked list
  if (Find(data) == nullptr)
  {
    cout << "Cannot remove \"" << data << "\"" << endl;
  }
  // If we are removing a node that is the only node in the linked list
  else if (GetSize() == 1)
  {
    // Deletes head node and points it to null (like new linked list)
    delete m_head;
    m_head = nullptr;
    m_size = 0;
  }
  else
  {
    int loopCounter = 0;
    // Makes a new node pointer to traverse the linked list starting at the head
    Node<T> *traverse = m_head;
    // Makes a new node pointer that is the target node to remove
    Node<T> *targetNode = Find(data);
    // Makes a new node that is the previous node to the one that will be removed
    Node<T> *previousNode = m_head;
    // Uses the new node to go through the linked list until it reaches the targetNode
    while (traverse != targetNode)
    {
      // If the traverse pointer is not pointing to the target then the previous node pointer will be the current node pointer
      previousNode = traverse;
      // The current node pointer moves to the next node pointer
      traverse = traverse->GetNext();
      loopCounter++;
    }
    // If the node to remove is the first node
    if (loopCounter == 0)
    {
      // Sets head to the node after the first and deletes the first
      m_head = traverse->GetNext();
      delete traverse;
      m_size--;
    }
    else
    {
      // Sets the node pointer previous to the target node to point at the target node's next node pointer
      previousNode->SetNext(traverse->GetNext());
      // Removes the target node from the linked list
      delete traverse;
      m_size--;
    }
  }
}

// Name: Display
// Desc: Display all nodes in linked list
// Preconditions: Outputs the LL
// Postconditions: Displays the pair in each node of LL
template <class T>
void LL<T>::Display()
{
  // Makes a new node pointer to traverse the linked list starting at the head
  Node<T> *traverse = m_head;
  // Goes through the linked list by its size
  for (int i = 0; i < GetSize(); i++)
  {
    // Outputs the data pair and moves on to the next node
    cout << traverse->GetData().first << " : " << traverse->GetData().second << endl;
    traverse = traverse->GetNext();
  }
  // When its done it outputs end and returns the output stream
  cout << "END" << endl;
}

// Name: GetSize
// Desc: Returns the size of the LL
// Preconditions: Requires a LL
// Postconditions: Returns m_size
template <class T>
int LL<T>::GetSize()
{
  return m_size;
}

// Name: operator<< (Overloaded << operator)
// Desc: Returns the ostream of the data in each node
// Preconditions: Requires a LL
// Postconditions: Returns an ostream with the data from each node on different line
template <class U>
ostream &operator<<(ostream &output, const LL<U> &linkedList)
{
  // Makes a new node pointer to traverse the linked list starting at the head
  Node<U> *traverse = linkedList.m_head;
  // Goes through the linked list by its size
  for (int i = 0; i < linkedList.m_size; i++)
  {
    // Outputs the data pair and moves on to the next node
    output << traverse->GetData().first << " : " << traverse->GetData().second << endl;
    traverse = traverse->GetNext();
  }
  // When its done it outputs end and returns the output stream
  output << "END" << endl;
  return output;
}

// Name: Overloaded [] operator
// Desc: When passed an integer, returns the data at that location
// Precondition: Existing LL
// Postcondition: Returns pair from LL using []
template <class T>
pair<T, int> &LL<T>::operator[](int x) // Overloaded [] operator to pull data from LL
{
  // If the size of the index is greater than the number of nodes in the linked list then returns the last node
  if (x > m_size)
  {
    x = m_size;
  }
  // Makes a new node pointer to traverse the linked list starting at the head
  Node<T> *traverse = m_head;
  // Goes through the linked list by how much the index needs
  for (int i = 0; i < x; i++)
  {
    traverse = traverse->GetNext();
  }
  // Returns the pair at that position
  return traverse->GetData();
}
