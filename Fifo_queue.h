#ifndef FIFO_QUEUE_H
#define FIFO_QUEUE_H


#include <iostream>
#include <conio.h>

#include "Edge.h"


// klasa reprezentujaca kolejke typu first in, first out dla obiektow klasy Edge

class Fifo_queue
{
	// atrybuty
	
	Edge ** ptr; // tablica przechowujaca obiekty Edge
	int capacity; // maksymalny rozmiar kolejki
	int first; // indeks pierwszego elementu
	int last; // indeks ostatniego elementu
	int size; // aktualny rozmiar
	
	
	// metody
	
	public:
		
		// konstruktor
		// args:
		//		int size - rozmiar kolejki
		Fifo_queue(int size);
		
		// dekonstruktor
		~Fifo_queue();
		
		Edge ** get_ptr() { return ptr; };
		
		// metoda zwracaca pierwszy element kolejki ( jesli kolejka nie jest pusta )
		// return:
		//		  Edge first, jesli kolejka nie jest pusta
		//		  NULL jezeli kolejka jest pusta
		Edge * get_first();
		
		// metoda zwracaca ostatni element kolejki ( jesli kolejka nie jest pusta )
		// return:
		//		  Edge last, jesli kolejka nie jest pusta
		//		  NULL jezeli kolejka jest pusta
		Edge * get_last();
		
		int get_size() { return size; }
		
		int get_capacity() {return capacity; }
		
		// metoda okreslajaca czy kolejka jest pusta
		// return:
		//		  bool true, jesli kolejka jest pusta
		//		  bool false, jesli kolejka nie jest pusta
		bool is_empty() { return (get_size() == 0); }
		
		// metoda okreslajaca czy kolejka jest pelna
		// return:
		//		  bool true, jesli kolejka jest pelna
		//		  bool false, jesli kolejka nie jest pelna
		bool is_full() { return (get_size() == get_capacity()); }
		
		// metoda usuwa pierwszy element, jesli istnieje
		void delete_first();
		
		// metoda dodaje element, jesli kolejka nie jest pelna
		// args:
		//		int cost - koszt krawedzi
		//		int v1 - indeks pierwszego wierzcholka krawedzi
		//		int v2 - indeks drugiego wierzcholka krawedzi
		void insert(int cost, int v1, int v2);
		
		// metoda dodaje element, jesli kolejka nie jest pelna
		// args:
		//		Edge * e - krawedz;
		void insert(Edge * e);
};


#endif


