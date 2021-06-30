#ifndef MATRIX_REP_H
#define MATRIX_REP_H


#include <iostream>
#include <math.h>
#include <conio.h>
#include <cstdlib>
#include <time.h>
#include <iomanip>

#include "Fifo_queue.h"

// Klasa reprezentujaca graf w postaci macierzy sasiedztwa za pomoca dwuwymiarowej tablicy

class Matrix_rep
{
	// atrybuty:
	
	int ** ptr; // tablica reprezentujaca macierz sasiedztwa
	int v; // liczba wierzcholkow
	int max_edges; // maksymalna liczba krawedzi
	int max_edge_cost; // maksymalny koszt krawedzi
	int edges; // liczba krawedzi
	int v_start; // wierzcholek startowy ( z pliku )
	
	// metody:
	
	public:
		
		// konstruktor tworz¹cy tablicê dla v wierzcho³ków bez krawedzi
 		// przypisuj¹cy v, oraz ustawiajacy edge_max_cost na INT_MAX
		// args:
		// 		int v - liczba wierzcholkow
		Matrix_rep(int v);
		
		// konstruktor tworz¹cy tablicê dla v wierzcho³ków
		// obliczajacy ilosc krawedzi z podanej gestosci
		// oraz dodajac odpowiednia ilosc losowych krawedzi
		// jezeli jest to konstruktor uzyty w ramach testow
		// tworzony jest graf spojny
		// args:
		// 		int v - liczba wierzcholkow
		//		int d - procent gestosci
		//		int r - maksymalny koszt krawedzi
		Matrix_rep(int v, int d, int r, bool test);
		
		// dekonstruktor
		~Matrix_rep();
	
		// funkcja przypisuje do pola max_edges maksymalna luczbe krawedzi w grafie
		// return:
		//		int, maksymalna ilosc krawedzi w grafie
		int calc_max_edges() { return int(v * (v - 1) / 2); }
		
		// gettery
		
		int ** get_ptr() { return this -> ptr; }
		
		int get_v() { return this -> v; }
		
		int get_edges() { return this -> edges; }
		
		int get_max_edges() { return this -> max_edges; }
	
		int get_max_edge_cost() { return this -> max_edge_cost; }
		
		int get_v_start() { return this -> v_start; }
		
		void set_v_start(int v_start) { this -> v_start = v_start; }
		
		// funkcja wypisuje w konsoli graf w postaci macierzy sasiedztwa
		void print(Matrix_rep * matrix_rep);
		
		// funkcja dodajaca krawedz o losowej wartosci laczaca dwa losowe wierzcholki
		// jesli jest taka mozliwosc ( wszystkie wierzcholki nie sa polaczone )
		void add_random_edge();
		
		// funkcja dodajaca krawedz o wartosci v laczaca wierzcholek v1 z wierzcholkiem v2,
		// jesli nie sa juz polaczone, jesli sa polaczone zmienia koszt na v
		void add_edge(int v1, int v2, int v);
		
		// funkcja dodajaca krawedz e do zbioru lub modyfikuajca ja
		// ( uzycie add_edge(int v1, int v2, int v) )
		void add_edge(Edge * e);
		
		// funkcja wyznacza minimalne drzewo rozpinajace algorytmem prima
		// args:
		//		bool test - czy wyswietlic wyniki
		void prim(bool test);

		// funkcja wyznacza minimalne drzewo rozpinajace algorytmem kruskala
		// args:
		//		bool test - czy wyswietlic wyniki
		void kruskal(bool test);
		
		// pomocnicza funkcja do algorytmu kruskala
		// sprawdza czy las "set" jest drzewem rozpinajacym
		// args:
		//		int * set - zbior do sprawdzenia
		//		int size - jego rozmiar
		// return:
		// 		bool true jesli jest
		///		bool false jestli nie jest
		bool kruskal_is_set_ok(int * set, int size);

		// funkcja obliczajaca koszt polaczenia z wierzchlolkami danego wierzcholka startowego
		// korzystajac z algorytmu Djkstry
		// args;
		//		int v1 - indeks startowego wierzcholka
		//		bool test - czy wyswietlic wyniki
		void djkstra(int v1, bool test);
		
		// funkcja obliczajaca koszt polaczenia z wierzchlolkami danego wierzcholka startowego
		// korzystajac z algorytmu Forda_Bellmamna
		// args;
		//		int v1 - indeks startowego wierzcholka
		//		bool test - czy wyswietlic wyniki
		void ford_bellman(int v1, bool test);
		
		// funkcja sprawdzajaca czy graf jest polaczony
		bool check_if_connected();
		
		// funkcja pomocnicza sprawdzajaca czy graf jest polaczony		
		void check_if_connected_traverse(int v0, bool set[]);
		
		// pomocnicza funkcja do sortowaniq
		void quick_sort(Edge ** arr, int p, int r);
		
		// pomocnicza funkcja do quick_sort
		// dzieli tablice na dwie czesci zgodnie z porownaniem do x ( wartosc arr[p] )
		int quick_sort_part(Edge ** arr, int p, int r);
};


#endif
