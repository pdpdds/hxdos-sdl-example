#include "Queue.h"

template<class T>
T Queue<T>::GetFirstPair()
{
	return data[noOfElements - 2];
}



template<class T>
Queue<T>::Queue()
{
	rear = front = noOfElements = 0;
	capacity = 1;
	data = new T[capacity];
}

template<class T>
Queue<T>::~Queue()
{
	if (data)
	{
		return;
	}
	delete[]data;
	data = 0;
}

template<class T>
bool Queue<T>::isFull()
{
	return noOfElements == capacity;
}

template<class T>
bool Queue<T>::isEmpty()
{
	return noOfElements == 0;
}

template<class T>
int Queue<T>::getCapacity()
{
	return capacity;
}

template<class T>
int Queue<T>::getNoOfElements()
{
	return noOfElements;
}

template<class T>
void Queue<T>::enQueue(T val)
{
	if (isFull())
		reSize(capacity * 2);

	data[rear] = val;
	rear = (rear + 1) % capacity;
	noOfElements++;
}

template<class T>
T Queue<T>::deQueue()
{
	if (isEmpty())
		exit(0);

	T val = data[front];
	front = (front + 1) % capacity;
	noOfElements--;

	if (noOfElements > 0 && noOfElements == capacity / 4)
		reSize(capacity / 2);

	return val;
}

template<class T>
T Queue<T>::getElementAtFront()
{
	if (isEmpty())
		exit(0);
	return data[front];
}

template<class T>
void Queue<T>::reSize(int newSize)
{
	T * temp = new T[newSize];

	for (int j = 0, i = front; j < noOfElements; j++)
	{
		temp[j] = data[i];
		i = (i + 1) % capacity;
	}

	this->~Queue();
	data = temp;

	capacity = newSize;
	rear = noOfElements;
	front = 0;
}
