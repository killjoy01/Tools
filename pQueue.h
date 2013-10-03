#include "Helpers.h"
#include <iostream>
using namespace std;

template<typename TYPE>
class pQueue{
private:
	//the heap
	TYPE * heap;

	//size of the priority queue
	int size;

	//current maximum size of the heap array
	int maxSize;


public:

	pQueue()
		:size(0), heap(0), maxSize(0)
	{}

	~pQueue(){
		makeEmpty();
	}

	pQueue(const pQueue & pq)
		:size(0), heap(0), maxSize(0)
	{
		copy(pq);
	}


	void push(TYPE toAdd){
		if(size==maxSize){
			maxSize+=100;
			TYPE *tempheap = new TYPE[maxSize];

			for(int i = 0; i < size; ++i)
				tempheap[i]=heap[i];

			delete [] heap;
			heap=tempheap;
		}
		heap[size++] = toAdd;
		reheapUp(size-1);
	}

	bool pop(TYPE & toRemove){
		if(size){
			toRemove = heap[0];
			swapVals(heap[0], heap[size-1]);
			size--;
			reheapDown(0);
			return true;
		}
		return false;
	}

	int size(){
		return size;
	}

	void makeEmpty(){
		if(heap){
			delete[] heap;
		}
		heap = NULL;
		size = 0;
		maxSize = 0;
	}

	void printPQueue(){
		for(int i = 0; i < size; ++i)
			cout << heap[i] << endl;
	}


	pQueue & operator=(const pQueue & pq){
		if(this!=&pq){
			makeEmpty();
			copy(pq);
		}
	}

private:
		//HELPERS

	//recursive heap up
	void reheapUp(int toHeap){
		//if there is a heap
		if(toHeap>0){
			//init the parent to the (passed value-1)/2.
			int parent = (toHeap-1)/2;
			//if the heap at the passed index is less than the heap at the parent index
			if(heap[toHeap]<heap[parent]){
				//swap them
				swapVals(heap[toHeap], heap[parent]);
				//then check again.
				reheapUp(parent);
			}
		}
	}

	//recursive heap down
	void reheapDown(int toHeap){
		//init the first daughter node to the passed number * 2, then add 1.
		int left = (toHeap*2)+1;
		//init the second daughter node to the passed number * 2, then add 2.
		int right = (toHeap*2)+2;
		//check to see if the heap needs to be big enough to hold the number to heap.
		if(size > left && size > right){
			// if the heap at the first index is less than the heap at the second index, 
			//and if the heap at the first is less than the heap at the passed index
			if(heap[left] < heap[right] && heap[left] < heap[toHeap]){
				//swap them
				swapVals(heap[left], heap[toHeap]);
				//then check again
				reheapDown(left);
			}
			//or if heap[left] is more than heap[right] and heap at the passed index is greater than heap[right]
			else if(heap[left] >= heap[right] && heap[right] < heap[toHeap]){
				//swap them
				swapVals(heap[right], heap[toHeap]);
				//check again
				reheapDown(right);
			}
		}
		//if only left child
		else if(size > left){
			//and heap[passed index] is less than heap[left]
			if(heap[left] > heap[toHeap]){
				//swap them
				swapVals(heap[left], heap[toHeap]);
				//check again
				reheapDown(left);
			}
		}
	}


	//copies this->everything to the passed pq objects everything
	void copy(const pQueue & pq){
		//copy size
		size = pq.size;
		//copy maxSize
		maxSize = pq.maxSize;
		//
		if(pq.heap){
			heap = new TYPE[maxSize];
			for(int i = 0; i < size; ++i)
				heap[i] = pq.heap[i];
		}
		else
			printf("pQueue.copy() cannot copy the heap\n");
	}

};