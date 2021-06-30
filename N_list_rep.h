#ifndef N_LIST_REP_H
#define N_LIST_REP_H


#include "N_list_el.h"
#include "Edge.h"
#include "Fifo_queue.h"
#include "Matrix_rep.h"

#include "iostream"
#include "math.h"
#include "conio.h"
#include <iomanip>
#include <stdlib.h>


// Klasa reprezentujaca graf w postaci listy sasiedztwa

class N_list_rep
{
	// atrybuty
	int v; // liczba wierzcholkow
	int edges; // liczba krawedzi
	int max_edges; // maksymalna liczba krawedzi
	int max_edge_cost; // maksymalny koszt krawedzi
	N_list_el ** arr; // tablica list;
	int v_start; // wierzcholek startowy ( z pliku )

	
	// metody
	public:
		
		// konstruktor tworz�cy tablic� dla v wierzcho�k�w bez krawedzi
 		// przypisuj�cy v, oraz ustawiajacy edge_max_cost na kwadrat v
		// args:
		// 		int v - liczba wierzcholkow
		N_list_rep(int v);
		
		// konstruktor
		// args:
		// 		int v - ilosc wierzcholkow
		//		int d - gestosc w procentach
		//		int r - maksymalny koszt krawedzi
		N_list_rep(int v, int d, int r, bool test);
		
		// konstruktor kopiujacy krawedzie z podanego grafu
		// w postaci macierzy sasiedztwa
		// args:
		//		Matrix_rep * g - graf do skopiowania
		N_list_rep(Matrix_rep * g);
		
		// destruktor
		~N_list_rep();
		
		int get_v_start() { return this -> v_start; }
		
		void set_v_start(int v_start) { this -> v_start = v_start; }
		
		// funkcja pomocnicza do obliczania maksymalnej liczby krawedzi
		// ustawia pole klasy max_edges na odpowiednia wartosc
		int calc_max_edges() { return int(v * (v - 1) / 2); }
		
		// funkcja dodajaca krawedz o losowej wartosci laczaca dwa losowe wierzcholki
		// jesli jest taka mozliwosc ( wszystkie wierzcholki nie sa polaczone )
		void add_random_edge();
		
		// funkcja dodajaca krawedz o wartosci v laczaca wierzcholek v1 z wierzcholkiem v2,
		// jesli nie sa juz polaczone, jesli sa polaczone zmienia koszt na v
		// args:
		//		int v1 - pierwszy wierzcholek
		//		int v2 - drugi wierzcholek
		//		int v - koszt polaczenia
		void add_edge(int v1, int v2, int v);
		
		// funkcja dodajaca krawedz e do zbioru lub modyfikuajca ja
		// args:
		//		Edge * e - krawedz do dodania
		void add_edge(Edge * e);
		
		// pomocnicza funkcja wyszukujaca krawedz miedzy v1 i v2
		// args:
		//		int v1 - numer pierwszego wierzcholka
		//		int v2 - numer drugiego wierzcholka
		// return:
		//		N_list_el szukana krawedz lub NULL, jesli nie istnieje
		N_list_el * find_edge(int v1, int v2);
		
		// funkcja wypisuje w konsoli graf w postaci macierzy sasiedztwa
		void print(N_list_rep * g) const;

		// funkcja wyznacza minimalne drzewo rozpinajace algorytmem prima
		// args:
		//		bool test - czy wyswietlic odpowiedz
		void prim(bool test);

		// funkcja wyznacza minimalne drzewo rozpinajace algorytmem kruskala
		// args:
		//		bool test - czy wyswietlic odpowiedz
		void kruskal(bool test);
		
		// pomocnicza funkcja do algorytmu kruskala
		// sprawdza czy las "set" jest drzewem rozpinajacym
		// args:
		//		int * set - zbior do sprawdzenia
		//		int size - jego rozmiar
		// return:
		// 		bool true jesli jest
		///		bool false jestli nie jest
		bool kruskal_is_set_ok(const int * set, int size);
		
		// pomocnicza funkcja do algorytmu kruskala
		// zwraca dwuwymiarowa tablice z indeksem najmniejszej dodatnoiej wartosci 
		// z podanego zbioru jesli zbior nie jest pusty
		// args:
		//		int * set - wskaznik na zbior
		//		int size - rozmiar zbioru
		// return:
		//		int * index - tablica z indeksem najmniejszej wartosci jezeli taka istnieje lub -1
		int * kruskal_get_min(int ** set, int size);
		
		// pomocnicza funkcja do sortowaniq
		// args:
		//		Edge ** arr - tablica krawedzi ktora zostanie posortowana
		//		int p -indeks liczby wedlug ktorej bedziemy porownywac
		//		int r - TODO
		void quick_sort(Edge ** arr, int p, int r);
		
		// pomocnicza funkcja do quick_sort
		// dzieli tablice na dwie czesci zgodnie z porownaniem do x ( wartosc arr[p] )
		// args:
		//		Edge ** arr - tablica krawedzi ktora zostanie posortowana
		//		int p -indeks liczby wedlug ktorej bedziemy porownywac
		//		int r - TODO
		int quick_sort_part(Edge ** arr, int p, int r);

		// funkcja obliczajaca koszt polaczenia z wierzchlolkami danego wierzcholka startowego
		// korzystajac z algorytmu Djkstry
		// args;
		//		int v1 - indeks startowego wierzcholka
		//		bool test - czy wyswietlic odpowiedz
		void djkstra(int v1, bool test);
	
		// funkcja obliczajaca koszt polaczenia z wierzchlolkami danego wierzcholka startowego
		// korzystajac z algorytmu Forda_Bellmamna
		// args;
		//		int v1 - indeks startowego wierzcholka
		//		bool test - czy wyswietlic odpowiedz
		void ford_bellman(int v1, bool test);
};


#endif

