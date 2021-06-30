#ifndef EDGE_H
#define EDGE_H


// klasa pomocnicza reprezentujaca krawedz

class Edge
{
	public:
	
	// atrybuty
	
	int cost; // koszt krawedzi
	int v1; // indeks pierwszego wierzcholka
	int v2; // indeks drugiego wierzcholka
	
	
	// metody
	
	// domyslny konstruktor
	Edge() { cost = -1; v1 = -1; v2 = -1; }
	
	// konstruktor
	Edge(int cost, int v1, int v2) { this -> cost = cost; this -> v1 = v1; this -> v2 = v2; }
};


#endif


