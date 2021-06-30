#include "Matrix_rep.h"

		
Matrix_rep::Matrix_rep(int v)
{
	this -> ptr = new int * [v];
	this -> v = v;
	this -> edges = 0;
	max_edge_cost = INT_MAX;
	max_edges = calc_max_edges();
	for(int i = 0; i < v; i++)
	{
		this -> ptr[i] = new int[v];
		for(int j = 0; j < v; j++)
		{
			this -> ptr[i][j] = 0;
		}
	}
}
		
	
Matrix_rep::Matrix_rep(int v, int d, int r, bool test)
{
	if(d < 0 || d > 100)
	{
		std::cout << "Bledna gestosc, nacisnij przycisk" << std::endl;
		_getch();
		return;
	}
	if(r < 0)
	{
		std::cout << "Bledny maksymalny koszt, nacisnij przycisk" << std::endl;
		_getch();
		return;
	}
	if(!test)
	{
		this -> ptr = new int * [v];
		int temp_edges = 0;
		this -> v = v;
		this -> edges = 0;
		this -> max_edge_cost = r;
		this -> max_edges = calc_max_edges();
		ptr = new int * [v];
		for(int i = 0; i < v; i++)
		{
			this -> ptr[i] = new int[v];
			for(int j = 0; j < v; j++)
			{
				this -> ptr[i][j] = 0;
			}
		}
		temp_edges = floor(float(float(d) / 100) * max_edges);
		for(int i = 0; i < temp_edges; i++)
		{
			add_random_edge();
		}
	}
	else
	{
		this -> ptr = new int * [v];
		int temp_edges = 0;
		this -> v = v;
		this -> edges = 0;
		this -> max_edge_cost = r;
		this -> max_edges = calc_max_edges();
		ptr = new int * [v];
		for(int i = 0; i < v; i++)
		{
			this -> ptr[i] = new int[v];
			for(int j = 0; j < v; j++)
			{
				this -> ptr[i][j] = 0;
			}
		}
		temp_edges = floor(float(float(d) / 100) * max_edges);
		for(int i = 0; i < v - 1; i++)
		{
			add_edge(i, v - 1, rand() % r + 1);
		}
		for(int i = 0; i < temp_edges - (v - 1); i++)
		{
			add_random_edge();
		}
	}
}
		
		
Matrix_rep::~Matrix_rep()
{
	for(int i = 0; i < v; i++)
	{
		delete[] this -> ptr[i];
	}
	delete [] this -> ptr; 
}
	

void Matrix_rep::print(Matrix_rep * matrix_rep)
{
	for(int i = 0; i < matrix_rep -> get_v(); i++)
	{
		for(int j = 0; j < matrix_rep -> get_v(); j++)
		{
			std::cout << std::setw(3) << matrix_rep -> get_ptr()[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
		

void Matrix_rep::add_random_edge()
{
	if(this -> edges >= this -> max_edges)
	{
		std::cout << "za duzo krawedzi, nacisnij przycisk" << std::endl;
		std::cout << this -> edges << std::endl;
		std::cout << this -> max_edges << std::endl;
		_getch();
	}
	int v1;
	int v2;
	int val = rand() % max_edge_cost + 1;
	do
	{
		v1 = rand() % v;
		v2 = rand() % v;
	}while(v1 == v2 || ptr[v1][v2] != 0);
	add_edge(v1, v2, val);
}


void Matrix_rep::add_edge(int v1, int v2, int v)
{
	if(v1 != v2 && ptr[v1][v2] == 0)
	{
		edges++;
		ptr[v1][v2] = v;
		ptr[v2][v1] = v;
		return;
	}
	else
	{
		std::cout << "Error1: v1 == v2, press button" << std::endl;
		_getch();
	}
}
		

void Matrix_rep::add_edge(Edge * e)
{
	add_edge(e -> v1, e -> v2, e -> cost);
}
		

void Matrix_rep::prim(bool test)
{
	// graf ktory posluzy do wyswietlenia mst
	auto ans = new Matrix_rep(v);
	// wierzcholki rozpatrzone
	bool *proccessed = new bool[v];
	for(int i = 1; i < v; i++)
	{
		proccessed[i] = false;
	}
	proccessed[0] = true;
	// koszt mst
	int sum = 0;
	// pomocnicza zmienna do porywnywania
	int min = INT_MAX;
	// zmiennie pomocnicze do przechowania indeksow wierzcholkow
	// ktore laczy rozpatrywana krawdz
	int x = 0;
	int y = 0;
	// glowna petla
	for(int i = 0; i < v - 1; i++)
	{
		// resetuje zmiennie pomocnicze
		min = INT_MAX;
		x = 0;
		y = 0;
		// dla kazdego wierzcholka sprawdzam czy jest rozpatrzony
		// jezeli nalezy to szukam krawedzi laczacej ten wierzcholek
		// z wierzcholkiem spoza mst o najnizszym koszcie
		for(int j = 0; j < v; j++)
		{
			if(proccessed[j])
			{
				for(int k = 0; k < v; k++)
				{
					if(!proccessed[k] && ptr[j][k] != 0)
					{
						if(min > ptr[j][k])
						{
							min = ptr[j][k];
							x = j;
							y = k;
						}
					}
				}
			}
		}
		// dodaje wierzcholek do rozpatrzonych
		// aktualizuje odpowiedz
		ans -> add_edge(x, y, min);
		proccessed[y] = true;
		sum += min;
	}
	// odpowiedz
	if(!test)
	{
		print(ans);
		std::cout << "Koszt: " << sum << std::endl << std::endl;
	}
	delete ans;
	delete[] proccessed;
}

	
void Matrix_rep::kruskal(bool test)
{
	// pomocnicza zmienna przechowujaca rozpatrywana krawedz
	Edge * temp;
	// koszt mst
	int sum = 0;
	// licznik rozpatrzonych wierzcholkow
	int counter = 0;
	// zmienna mowiaca o gotowosci mst
	bool is_mst = false;
	// graf ktory bedzie mst
	auto ans = new Matrix_rep(v);
	// kolejka krawedzi
	auto q = new Fifo_queue(edges);
	// las wierzcholkow
	int *l = new int[v];
	for(int i = 0; i < v; i++)
	{
		l[i] = i;
	}
	// pomocnicza zmienna do stworzenia kolejki
	int helper = 0;
	// tworzenie kolejki
	for(int i = 0; i < v; i++)
	{
		helper++;
		for(int j = helper; j < v; j++)
		{
			if(ptr[i][j] != 0)
			{
				q -> insert(new Edge(ptr[i][j], i, j));
			}
		}
	}
	quick_sort(q -> get_ptr(), 0, edges - 1);
	// glowna petla
	// dopoki nie rozpatrze wszystkich wierzcholkow
	// biore kolejne krawedzi o najnizszych kosztach
	// jezeli laczy wierzcholki nienalezace do jednego podgrafu
	// lacze ich podgrafy
	while(counter != v && !is_mst)
	{
		temp = q -> get_first();
		q -> delete_first();
		if(l[temp -> v1] != l[temp -> v2])
		{
			for(int i = 0; i < v; i++)
			{
				if(l[i] == l[temp -> v2] && i != temp -> v2)
				{
					l[i] = l[temp -> v1];
				}
			}
			l[temp -> v2] = l[temp -> v1];
			counter++;
			ans -> add_edge(temp);
			sum += temp -> cost;
			is_mst = kruskal_is_set_ok(l, v);
		}
	}
	if(!test)
	{
		print(ans);
		std::cout << "Koszt: " << sum << std::endl;	
	}
	delete temp;
	delete ans;
	delete q;
}
		
		

bool Matrix_rep::kruskal_is_set_ok(int * set, int size)
{
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			if(set[j] != set[i])
			{
				return false;
			}	
		}
	}
	return true;
}
		

void Matrix_rep::djkstra(int v1, bool test)
{
	if(v1 >= v || v1 < 0)
	{
		std::cout << "Podano zly wierzcholek startowy, nacisnij przycisk" << std::endl;
		_getch();
		return;
	}
	// indeks rozpatrywanego wierzcholka
	int temp;
	// zmienna pomocnicza do porownywania
	int min = INT_MAX;
	// koszt polaczen wierzcholka startowego z danym wierzcholkiem
	int *cost = new int[v];
	// ostatni wierzcholek na drodze z wierzcholka startowego do danego wierzcholka
    int *parent = new int[v];
	// czy wierzcholek jest rozpatrzony
    bool *is_proccessed = new bool[v];
	for(int i = 0; i < v; i++)
	{
		cost[i] = INT_MAX;
		parent[i] = -1;
		is_proccessed[i] = false;
	}
	cost[v1] = 0;
	// glowna petla
	for(int i = 0; i < v; i++)
	{
		// resetuje zmienna do porownywania
		min = INT_MAX;
		// wybieram nierozpatrzony wierzcholek o najniszym koszcie polaczenia
		for(int j = 0; j < v; j++)
		{
			if(!is_proccessed[j])
			{
				if(min >= cost[j])
				{
					temp = j;
					min = cost[j];
				}
			}
		}
		// relaksacja
		for(int j = 0; j < v; j++)
		{
			if(ptr[temp][j] > 0)
			{
				if(cost[j] > cost[temp] + ptr[temp][j])
				{
					cost[j] = cost[temp] + ptr[temp][j];
					parent[j] = temp;
				}
			}
		}
		// dodaje wierzcholek do rozpatrzonych
		is_proccessed[temp] = true;
	}
	// wypisuje wynik
	if(!test)
	{
		std::cout << "Koszty: " << std::endl;
		for(int i = 0; i < v; i++)
		{
			std::cout << cost[i] << " ";
		}
		std::cout << std::endl << std::endl;
		std::cout << "Rodzice: " << std::endl;
		for(int i = 0; i < v; i++)
		{
			std::cout << parent[i] << " ";
		}
		std::cout << std::endl << std::endl;	
	}
	delete[] cost;
	delete[] is_proccessed;
	delete[] parent;
}


void Matrix_rep::ford_bellman(int v1, bool test)
{
	if(v1 < 0 || v1 >= v)
	{
		std::cout << "Podano zly wierzcholek startowy, nacisnij przycisk";
		_getch();
		return;
	}
	// koszt polaczenia wierzcholka startowego z danym wierzcholkiem
    int *cost = new int[v];
	// ostatni wierzcholek na drodze z wierzcholka startowego to danego wierzcholka
    int *parent = new int[v];
	for(int i = 0; i < v; i++)
	{
		cost[i] = 999999;
		parent[i] = -1;
	}
	cost[v1] = 0;
	// zmienna pomocnicza przy znajdywaniu krawedzi
	int helper = 0;
	// glowna funkcja
	for(int i = 0; i < v - 1; i++)
	{
		// dla kazdej krawedzi
		helper++;
		for(int j = 0; j < v ; j++)
		{
			for(int k = 0; k < v; k++)
			{
				if(ptr[j][k] > 0 && cost[k] > cost[j] + ptr[j][k])
				{
					cost[k] = cost[j] + ptr[j][k];
					parent[k] = j;
				}
			}
		}
	}
	if(!test)
	{
		std::cout << "Koszty: " << std::endl;
		for(int i = 0; i < v; i++)
		{
			std::cout << cost[i] << " ";
		}
		std::cout << std::endl << std::endl;
		std::cout << "Rodzice: " << std::endl;
		for(int i = 0; i < v; i++)
		{
			std::cout << parent[i] << " ";
		}
		std::cout << std::endl << std::endl;	
	}
	delete[] parent;
	delete[] cost;
}
		
		
bool Matrix_rep::check_if_connected()
{
    bool *set = new bool[v];
	for(int i = 0; i < v; i++)
	{
		for(int j = 0; j < v; j++)
		{
			set[j] = false;
		}
		this -> check_if_connected_traverse(i, set);
		for(int j = 0; j < v; j++)
		{	
			if(!set[j])
			{
				return false;
			}	
		}
	}
	return true;
}
		
	
void Matrix_rep::check_if_connected_traverse(int v0, bool set[])
{
	set[v0] = true;
	for(int i = 0; i < v; i++)
	{
		if(ptr[v0][i] > 0)
		{
			if(!set[i])
			{
				this -> check_if_connected_traverse(i, set);
			}
		}
	}
}


void Matrix_rep::quick_sort(Edge ** arr, int p, int r)
{
	int d;
	if(p < r)
	{
		d = quick_sort_part(arr, p, r);
		quick_sort(arr, p, d);
		quick_sort(arr, (d + 1), r);
	}
}


int Matrix_rep::quick_sort_part(Edge ** arr, int p, int r)
{
	int v = arr[p] -> cost;
	int i = p;
	int j = r;
	Edge * temp;
	while(true)
	{
		while((arr[j] -> cost) > v)
		{
			j--;
		}
		while((arr[i] -> cost) < v)
		{
			i++;
		}
		if(i < j)
		{
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
			i++;
			j--;
		}
		else
		{
			return j;
		}
	}
}
