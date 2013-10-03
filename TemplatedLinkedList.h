#pragma once

template<typename TYPE>
struct Node{
	TYPE data;
	int ID;
	Node<TYPE> * next;
};

template<typename TYPE>
class tlist{
private:
	Node<TYPE> * head;
	unsigned size;

	/*helper functions*/

	//HELPER initializes the list
	void initList(){
		if(!size){
			Node<TYPE> * node = new Node<TYPE>;
			head=node;
			node->ID=size;
			head->next = 0;
			size++;
		}
	}



	//HELPER recursively returns the node with the ID
	Node<TYPE> * getNode(Node<TYPE>* node, int ID){
		if(node && node->ID == ID)
			return node;
		else if(node && node->ID != ID)
			return getNode(node->next, ID);
		else
			return 0;
	}

	//HELPER finds the data passed
	TYPE find(Node<TYPE> * node, TYPE a_data){
		if(size){
			if(node->data==a_data)
				return a_data;
			else
				find(node->next,a_data);
		}
	}

	//HELPER removes the node with a_data in it from the list, then resets all the IDs to numerical order
	void remove(Node<TYPE> * node, TYPE a_data){
		if(node && node->data == a_data){
			if(node->ID==0){
				if(node->next){
					Node<TYPE> * newHead = head->next;
					delete head;
					head = newHead;
					size--;
					resetIDs();
				}
				else{
					delete head;
					size--;
					head=NULL;
				}	
			}
			else{
				int ID1, ID2;
				Node<TYPE> * a; Node<TYPE> * b;
				if(node->data==a_data){
					ID1 = node->ID-1;
					ID2 = node->ID+1;
					a = getNode(ID1);
					b = getNode(ID2);
					delete node;
					a->next = b;
					size--;
					resetIDs();
				}
			}
		}
		else if(node)
		remove(node->next, a_data);
		else
		printf(" There is no node to remove.\n");
	}

	//HELPER resets the IDs of all nodes after a delete
	void resetIDs(){
		Node<TYPE> * temp = head;

		for(int i = 0; i < size; ++i){
			temp->ID = i;
			temp=temp->next;
		}
	}

	//HELPER empties the list
	void makeEmpty(Node<TYPE> * node){
		if (size){
			Node<TYPE> * temp = node;
			if(temp){
				makeEmpty(temp->next);
			}
			if(size)
				size=0;

			delete temp;
		}
	}

	//HELPER copies one list to another listi
	void copy(const tlist<TYPE> & list){
		Node<TYPE>* temp = list.head;

		while(temp){
			insert(temp->data);
			temp=temp->next;
		}

	}


public:

	tlist()
		:head(0), size(0)
	{

	}
	~tlist(){
		makeEmpty(head);
	}

	tlist(const tlist & list)
		:head(0), size(0)
	{
		copy(list);
	}

	//Insert into the list
	void insert(TYPE a_data){
		if(!size){
			initList();
			setData(0,a_data);
		}
		else{
			Node<TYPE> * newNode = new Node<TYPE>;
			newNode->data = a_data;
			getNode(size-1)->next = newNode;
			newNode->ID=size++;
			newNode->next=0;
		}
	}

	//adds a node to the list
	void addNode(TYPE a_data){
		insert(a_data);
	}

	//push onto the list
	void push(TYPE a_data){
		insert(a_data);
	}

	//Remove from the list
	void remove(TYPE a_data){
		remove(head, a_data);
	}

	//remove the last node from the list
	void pop(){
		Node<TYPE> * temp = head;
		for(int i = 0; i < size; ++i)
			temp=temp->next;

			delete temp;
	}


	//finds the data inputted
	TYPE find(TYPE a_data){
		find(head,a_data);
	}

	//checks to see if the list is empty
	bool isEmpty(){
		if(!size)
			return true;
		else
			return false;
	}

	//counts the size of the list
	int count(){
		return size;
	}

	//empties the list
	void makeEmpty(){
		makeEmpty(head);
	}

	//returns the node with the ID
	Node<TYPE> * getNode(int ID){
		if(size)
			return getNode(head, ID);
		else 
			return 0;
	}

	//prints the list
	void print(bool newline){
		Node<TYPE> * node = head;
		while(node){
			cout << node->data;
			if(newline)
				cout << endl;

			node=node->next;
		}
	}

	//sets the data of the node with ID passed to data
	void setData(int ID, TYPE a_data){
		getNode(ID)->data = a_data;
	}


	tlist<TYPE> &	operator=(const tlist<TYPE> & list){
		if(this != &list)
			copy(list);
		return *this;
	}
};