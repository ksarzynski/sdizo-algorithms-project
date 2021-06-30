#include "Fifo_queue.h"


Fifo_queue::Fifo_queue(int size)
{
	capacity = size;
	ptr = new Edge * [size];
	for(int i = 0; i < size; i++)
	{
		ptr[i] = new Edge();
	}
	first = 0;
	last = 0;
	this -> size = 0;
}


Fifo_queue::~Fifo_queue()
{
	delete [] ptr;
}


Edge * Fifo_queue::get_first()
{
	if(!is_empty())
	{
		return ptr[first];
	}
	return nullptr;
}


void Fifo_queue::delete_first()
{
	if(!is_empty())
	{
		first++;
		size--;
		return;
	}
	std::cout << "Kolejka jest pusta, nacisnij przycisk" << std::endl;
	_getch();
}


void Fifo_queue::insert(int cost, int v1, int v2)
{
	if(!is_full())
	{
		ptr[last] = new Edge(cost, v1, v2);
		last++;
		size++;
		return;
	}
	std::cout << "Kolejka jest pelna, nacisnij przycisk" << std::endl;
	_getch();
}


void Fifo_queue::insert(Edge * e)
{
	if(!is_full())
	{
		ptr[last] = e;
		last++;
		size++;
		return;
	}
	std::cout << "Kolejka jest pelna, nacisnij przycisk" << std::endl;
	_getch();
}

