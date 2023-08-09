#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

// Templated Node class
// Normal node except that each node can hold a pair <T,int>
// where the first value is templated and the second value is the frequency
// (or quantity) of the first
// For example, if T was a string then it would hold string,int
template <class T>
class Node {
public:
  Node( const T& data ); //Node Constructor - Assume each quan
  pair<T,int>& GetData(); //Node Data Getter
  void SetData( const pair<T,int>& ); //Node Data Setter
  Node<T>* GetNext(); //Node m_next getter
  void SetNext( Node<T>* next ); //Node m_next setter
private:
  pair <T,int> m_data; //Holds templated data
  Node<T>* m_next; //Pointer to next node
};

template <class T>
Node<T>::Node( const T& data ) {
  m_data = make_pair(data,1);
  m_next = nullptr;
}

template <class T>
pair<T,int>& Node<T>::GetData() {
   return m_data;
}

template <class T>
void Node<T>::SetData( const pair<T,int>& data ) {
   m_data = data;
}

template <class T>
Node<T>* Node<T>::GetNext() {
   return m_next;
}

template <class T>
void Node<T>::SetNext( Node<T>* next ) {
   m_next = next;
}

//Templated Linked List class
template <class T>
class LL {
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
  LL(const LL&);
  // Name: operator= (Overloaded Assignment Operator)
  // Desc: Makes two LL of the same type have identical number of nodes and values
  // Preconditions: Requires two linked lists of the same templated type
  //                REQUIRED to be implemented even if not used
  // Postconditions: Two idenetical LL
  LL<T>& operator= (const LL&);
  // Name: Find
  // Desc: Iterates through LL and returns node if data found
  // Preconditions: LL Populated
  // Postconditions: Returns nullptr if not found OR Node pointer if found
  Node<T>* Find(const T& data);
  // Name: Insert
  // Desc: Either inserts a node to the linked list OR increments frequency of first
  //       Takes in data. If "first" (of pair) NOT in list, adds node
  //       If "first" (of pair) is already in list, increments quantity
  //       Inserts "first" in order with no duplicates
  // Preconditions: Requires a LL.
  // Postconditions: Node inserted in LL based on first value (or quantity incremented)
  void Insert(const T&);
  // Name: RemoveAt
  // Desc: Removes a node at a particular position based on data passed (matches first)
  // Preconditions: LL with at least one node. 
  // Postconditions: Removes first node with passed value (in first)
  void RemoveAt(const T&);
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
  friend ostream& operator<<(ostream& output, const LL<U>&);
  // Name: Overloaded [] operator
  // Desc: When passed an integer, returns the data at that location
  // Precondition: Existing LL
  // Postcondition: Returns pair from LL using []
  pair<T,int>& operator[] (int x);//Overloaded [] operator to pull data from LL
private:
  Node <T> *m_head; //Node pointer for the head
  int m_size; //Number of nodes in queue
};
//*****************************************************************
//Implement LL here


// Default constructor
template <class T>
LL<T>::LL()
{
  m_head = nullptr;
  m_size = 0;
}

// LL - Destructor
template<class T>
LL<T>::~LL()
{
  Node<T> *current = m_head;
  // Iterate through the list to delete Nodes
  while (current != nullptr)
  {
    m_head  = current;
    current = current->GetNext();
    delete m_head;
    m_size--;
  }

  // resets
  m_head = nullptr;
  m_size = 0;
}

// Copy constructor
template <class T>
LL<T>::LL(const LL& source)
{
  // Initialize values
  Node<T> *current = source.m_head;
  m_head = nullptr;
  m_size = 0;
  
  // Iterate through the list copying source
  for (int i = 0; i < source.m_size; i++)
  {
    for (int i = 0; i < current->GetData().second; i++)
    {
      Insert(current->GetData().first);
    }
    current = current->GetNext();
  }
}

// Overloaded assignment operator
template <class T>
LL<T>& LL<T>::operator=(const LL& source)
{
  if (this != &source)
  {
    Node<T> *temp = m_head;
    // Iterate through the list to delete Nodes
    // if not empty
    while (temp != nullptr)
    {
      m_head = temp;
      temp   = temp->GetNext();
      delete m_head;
    }

    // Resets
    m_head = nullptr;
    m_size = 0;
    
    Node<T> *current = source.m_head;
    
    // Iterate through the list copying source
    for (int i = 0; i < source.m_size; i++)
    {
      for (int i = 0; i < current->GetData().second; i++)
      {
	Insert(current->GetData().first);
      }
      current = current->GetNext();
    }
  }
  return *this;
}

// Find - Iterates through LL and returns node if data found
template <class T>
Node<T>* LL<T>::Find(const T& data)
{
  Node<T> *current = m_head;
  Node<T> *temp = nullptr;
  while (current != nullptr)
  {
    if (current->GetData().first == data)
    {
      temp = current;
    }
    current = current->GetNext();
  }
  return temp;
}

// Insert
// Either inserts a node to the linked list OR increments frequency of first
// Takes in data. If "first" (of pair) NOT in list, adds node
// If "first" (of pair) is already in list, increments quantity
// Inserts "first" in order with no duplicates
template <class T>
void LL<T>::Insert(const T& data)
{
  // If the list is empty, add to the front
  if(m_head == nullptr)
  {
    Node<T> *temp = new Node<T>(data);
    m_head = temp;
    m_size = 1;
    //    delete temp;
    // temp = nullptr;
  }
  else
  {
    // Check if data is already in the list
    Node<T> *isAvailable = Find(data);
    Node<T> *current  = m_head;
    Node<T> *previous = m_head;
    int count = 0;

    // if data is not in the list, add it
    // (in ascending order)
    if (isAvailable == nullptr)
    {
      
      Node<T> *temp = new Node<T>(data);
      for (int i = 0; i < m_size; i++)
      {
	if (temp->GetData().first > current->GetData().first)
	{
	  previous = current;
	  current = current->GetNext();
	  count++;
	}
      }
      // If data is the smaller than everything in the list
      // Add it to the start of the list
      if (count == 0)
      {
	temp->SetNext(current);
	m_head = temp;
	m_size++;
      }
      // Else add it to the list
      // at the right position
      else
      {
	temp->SetNext(current);
	previous->SetNext(temp);
	m_size++;
      }

      // delete temp;
      // temp = nullptr;
    }
    // If data already in the list, just increment
    // the amount of the data
    else
    {
      isAvailable->GetData().second++;
    }
  }
}

// RemoveAt() - Removes a node at a particular position based on data passed
// (matches first)
template <class T>
void LL<T>::RemoveAt(const T& data)
{
  // Declare variables
  Node<T> *temp     = m_head;
  Node<T> *current  = m_head;
  Node<T> *previous = m_head;

  // Check if data is not in the list
  Node<T> *isAvailable = Find(data);
  if (isAvailable == nullptr)
  {
    cout << data << " is not part of the list." << endl;
  }
  // If data is in the list, remove it
  else
  {
    int count = 0;
    // Find the location of the node by index
    while (data != current->GetData().first)
    {
      previous = current;
      current = current->GetNext();
      count++;
    }
    // If node is at start of the list remove it
    if (count == 0)
    {
      m_head = temp->GetNext();
      delete temp;
      m_size--;
    }
    // If not at first position, remove it
    else
    {
      previous->SetNext(current->GetNext());
      delete current;
      m_size--;
    }
  }
}


// Display() - Displays all nodes in linked list
template <class T>
void LL<T>::Display()
{
  Node<T> *temp = m_head;
  for (int i = 0; i < m_size; i++)
  {
    cout << temp->GetData().first << ":" << temp->GetData().second << endl;
    temp = temp->GetNext();
  }
}

// GetSize() - Returns the size of the LL
template <class T>
int LL<T>::GetSize()
{
  return m_size;
}


// operator<< - Returns the ostream of the data in each node
template <class U>
ostream& operator<<(ostream& output, const LL<U>& source)
{
  Node<U> *temp = source.m_head;
  for(int i = 0; i < source.m_size; i++)
  {
    output << temp->GetData().first << ":" << temp->GetData().second << endl;
    temp = temp->GetNext();
  }
  return output;
}


// Overloaded [] operator
template <class T>
pair<T,int>& LL<T>::operator[] (int x)
{
  Node<T> *temp = m_head;
  for(int i = 0; i < x; i++)
  {
    temp = temp->GetNext();
  }
  return temp->GetData();
}

//
//****************************************************************
// To test just LL follow these instructions:
//   1.  Uncomment out int main below
//   2.  make LL
//   3.  ./LL (try valgrind too!)
/*

int main () {
  //Test 1 - Default Constructor and Push
  cout << "Test 1 - Default Constructor and Push Running" << endl;
  //Test Default Constructor
  
  LL <int>* newLL1 = new LL<int>();
  
  //Push 4 nodes into LL
  newLL1->Insert(2);
  newLL1->Insert(4);
  newLL1->Insert(6);
  newLL1->Insert(8);
  newLL1->Insert(10);
  newLL1->Insert(12);
  newLL1->Insert(6);
  newLL1->Insert(8);
  newLL1->Insert(2);
  newLL1->Insert(4);
  newLL1->Insert(12);
  newLL1->Insert(6);
  newLL1->Insert(8);
  newLL1->Insert(8);
  newLL1->Insert(2);
  newLL1->Insert(4);
  newLL1->Insert(10);

  newLL1->Display();
    
  //Test 2 - Copy Constructor and Assignment Operator
  cout << "Test 2 - Copy Constructor and Assignment Operator Running" << endl;
  //Test Copy constructor
  LL <int>* newLL2 = new LL<int>(*newLL1);
  cout << "*******Original*********" << endl;
  newLL1->Display();
  cout << "*******Copy*********" << endl;
  newLL2->Display();
 
  //Test Overloaded Assignment Operator
  LL <int>* newLL3 = new LL<int>();
  *newLL3 = *newLL1;
  cout << "*******Assignment*********" << endl;
  newLL3->Display();
  cout << endl;
  
  //Test 3 - Test Display and Overloaded <<
  cout << "Test 3 - Display and Overloaded << Running" << endl;
  cout << "newLL1 Display Function" << endl;
  newLL1->Display();
  cout << "newLL1 Overloaded" << endl;
  cout << *newLL1;
  
  cout << "RemoveAt(10)" << endl;
  newLL1->RemoveAt(10);
  cout << "newLL1 Display Function" << endl;
  newLL1->Display();

  delete newLL1;
  delete newLL2;
  delete newLL3;
  
  return 0;
}

*/
