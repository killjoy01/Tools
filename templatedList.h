#pragma once
#include <stdio.h>
#include <conio.h>

#define LIST 0
#define QUEUE 1
#define STACK 2


template<typename TYPE>
struct Node{
	Node * m_next;
	Node* m_previous;
	TYPE m_data;
	unsigned nodeID;

	Node()
		:m_next(NULL), m_previous(NULL)
	{

	}

	Node(TYPE a_data)
		:m_next(NULL), m_previous(NULL), m_data(a_data)
	{

	}
};

template<typename TYPE>
class tlist{
private:
	Node<TYPE>* head;
	Node<TYPE>* tail;
	unsigned m_size;
	unsigned m_state;
public:

	//cotr
	tlist()
		:head(NULL), tail(NULL), m_size(0), m_state(SINGLE)
	{
	}

	//cotr
	tlist(unsigned state)
		:head(NULL), tail(NULL), m_size(0), m_state(state)
	{
	}

	//dcotr
	~tlist()
	{
		empty();
	}

	//copy cotr
	tlist(const tlist& other)
	{
		Node<TYPE>* temp = other.head;

		while(temp)
		{
			push(temp->m_data);
			temp = temp->m_next;
		}
	}

	/*sets the state of the list.
	0 is LIST
	1 is QUEUE
	2 is STACK
	*/
	void setState(int a_state)
	{
		m_state = a_state;
	}

	//inserts a new node onto the back of the list
	void push_back(TYPE a_data)
	{
		//if there is no list
		if(!m_size)
		{
			//initialize the list with data
			h_startList(a_data);
		}
		else
		{
			//make a new node
			Node<TYPE>* newNode = new Node<TYPE>(a_data);

			//set the former last node's next to this
			getNode(m_size-1)->m_next = newNode;

			//set the new node's previous to the former node;
			newNode->m_previous = getNode(m_size-1);

			//sets the new node's ID
			//newNode->nodeID=m_size++;
			newNode->nodeID = m_size;

			//increments the size
			m_size++;


			//set the new node's next to null
			newNode->m_next = NULL;
		}
	}

	//inserts a new node onto the back of the list
	void push_front(TYPE a_data)
	{
		//if there is no list
		if(!m_size)
		{
			//initialize the list with data
			h_startList(a_data);
		}
		else
		{
			//save the old head's position
			Node<TYPE>* oldHead = head;
			//make a new node
			Node<TYPE>* newHead = new Node<TYPE>(a_data);
			//set the head's previous pointer to the new node
			head->m_previous = newHead;
			//set the new node's previous to the former node;
			head = newHead;
			//sets the head's next to the old head's position
			head->m_next = oldHead;
			//increases the size of the list
			m_size++;
			//redoes all the IDs
			h_setIDs();


		}
	}

	//returns the node at ID
	Node<TYPE>* getNode(int ID)
	{
		return h_getNode(head,ID);
	}

	//returns the data at the given node
	TYPE getData(int ID)
	{
		return getNode(ID)->m_data;
	}

	//removes a node from the list
	void pop()
	{
		if(m_state == STACK || m_state == LIST)
		{
			//set all relevent pointers to NULL
			getNode(m_size-2)->m_next = NULL;

			//delete the back node
			delete getNode(m_size-1);

			//decrement size
			m_size--;

			//reset the IDS
			//h_setIDs();
		}
		else if(m_state == QUEUE)
		{
			//store location of old head
			Node<TYPE> * oldHead = head;

			//move head to next location
			head = head->m_next;

			//set all relevent pointers to NULL
			oldHead->m_next = NULL;
			head->m_previous = NULL;

			//delete the old head;
			delete oldHead;

			//decrement size
			m_size--;

			//reset the IDS
			h_setIDs();
		}
	}

	//returns the size of the list
	unsigned size()
	{
		return m_size;
	}

	//empties the list, nullifies all pointers
	void empty()
	{
		if(m_size)
			h_empty(head);
	}

	//removes the node containing the data from the list
	void remove(TYPE a_data)
	{
		if(m_size)
			h_remove(head,a_data);
	}

	void setData(int ID, TYPE a_data)
	{
		getNode(ID)->m_data = a_data;
	}



private:
	//starts a new list at index 0 with data
	void h_startList(TYPE a_data)
	{
		//makes a new node to work with
		Node<TYPE>* newNode = new Node<TYPE>(a_data);
		//starts the head there
		head = newNode;
		//sets the ID to size
		newNode->nodeID = m_size;
		//let the list know that head's next doesn't point to anything
		head->m_next = NULL;
		//incriment the size
		m_size++;
	}

	//recursive function that checks the node's ID againt the passed ID, then goes down the line from front to back
	Node<TYPE>* h_getNode(Node<TYPE>* toFind, int ID)
	{
		if(toFind && toFind->nodeID == ID)
			return toFind;
		else if(toFind && toFind->nodeID != ID)
			return h_getNode(toFind->m_next, ID);
		else
		{
			if(!toFind)
				printf("Node is null\n");
			else
				printf("Node not found\n");

			return 0;

		}
	}

	//sets the head to ID 0 and goes down the line from front to back
	void h_setIDs()
	{
		Node<TYPE>*node = head;

		for(int i = 0 ; i < m_size; ++i)
		{
			node->nodeID=i;
			node=node->m_next;
		}
	}

	//empties the list empty from back to front
	void h_empty(Node<TYPE>* start)
	{
		//sets the node we're operating on to the passed node
		Node<TYPE>* node = start;
		//if it's there
		if(node)
		{
			//keep moving till we find a node that doesn't exist
			h_empty(node->m_next);
		}
		//set the size to 0
		m_size = 0;

		//delete the node
		delete node;
	}

	//recursively removes the node containing the data passed
	void h_remove(Node<TYPE>* node, TYPE a_data)
	{
		//if data is found
		if(node->m_data == a_data)
		{
			//if the data is in the head and the list is a queue
			if(node == head && m_state == QUEUE)
				//pop the first node off
				pop();
			//if you want to remove the head and the list is not a queue
			else if(node == head && m_state != QUEUE)
			{
				if(m_size > 1)
				{
					//make a pointer for the new head
					Node<TYPE>* newHead = head->m_next;
					//delete the old head
					delete head;
					//reset the new head
					head = newHead;
					//decrement size
					m_size--;
					//reset the IDs
					h_setIDs();
				}
				//if the removed element if the last element in the list
				else
					empty();
			}
			//if you want to remove data from a node that's not the head
			else
			{
				//if the node is the last node and we don't pop off the front
				if(node == getNode(m_size) && m_state !=QUEUE)
				{
					pop();
				}
				else
				{
					//find the addresses of the nodes around the target node
					Node<TYPE>*a = getNode(node->nodeID -1);
					Node<TYPE>*b = getNode(node->nodeID +1);

					//delete the node that as the data
					delete node;

					//connect the two surrounding nodes
					a -> m_next = b;
					b -> m_previous = a;

					//decrement size
					m_size--;
					//reset the IDs
					h_setIDs();
				}

			}

		}
		else if(node)
			h_remove(node->m_next, a_data);
		else
			printf("Node not found");

	}
};

