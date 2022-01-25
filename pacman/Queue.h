#ifndef QUEUE_H
#define QUEUE_H

#include<iostream>
using namespace std;


template<class T>
class Queue
{
private:
	int rear;
	int front;
	int capacity;
	int noOfElements;
	T *data;
	void reSize(int);

public:
	Queue();
	~Queue();
	void enQueue(T);
	T deQueue();
	T getElementAtFront();
	bool isEmpty();
	bool isFull();
	int getNoOfElements();
	int getCapacity();
	T GetFirstPair();
	
};


#endif
