# include "N_list_rep.h"


N_list_rep::N_list_rep(int v)
{
	this -> v = v;
	arr = new N_list_el * [v];
	for(int i = 0; i < v; i++)
	{
		arr[i] = nullptr;
	}
	this -> edges = 0;
	this -> max_edges = calc_max_edges();
}
		
		
N_list_rep::N_list_rep(int v, int d, int r, bool test)
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
		int temp_edges = 0;
		this -> v = v;
		this -> edges = 0;
		this -> max_edge_cost = r;
		this -> max_edges = calc_max_edges();
		arr = new N_list_el * [v];
		for(int i = 0; i < v; i++)
		{
			arr[i] = nullptr;
		}
		temp_edges = floor(float(float(d) / 100) * max_edges);
		for(int i = 0; i < temp_edges; i ++)
		{
			add_random_edge();
		}
	}
	else
	{
		int temp_edges = 0;
		this -> v = v;
		this -> edges = 0;
		this -> max_edge_cost = r;
		this -> max_edges = calc_max_edges();
		arr = new N_list_el * [v];
		for(int i = 0; i < v; i++)
		{
			arr[i] = nullptr;
		}
		temp_edges = floor(float(float(d) / 100) * max_edges);
		for(int i = 0; i < v - 1; i ++)
		{
			add_edge(rand() % r + 1, i, v - 1);
		}
		for(int i = 0; i < temp_edges - (v - 1); i++)
		{
			add_random_edge();
		}
	}
}


N_list_rep::N_list_rep(Matrix_rep * g)
{
	int temp_edges = 0;
	this -> v = g -> get_v();
	this -> edges = 0;
	this -> max_edge_cost = g -> get_max_edge_cost();
	this -> max_edges = calc_max_edges();
	arr = new N_list_el * [v];
	for(int i = 0; i < v; i++)
	{
		arr[i] = nullptr;
	}
	int helper = 0;
	for(int i = 0; i < v - 1; i++)
	{
		helper++;
		for(int j = helper; j < v; j++)
		{
			if(g -> get_ptr()[i][j] != 0)
			{
				this -> add_edge(i, j, g -> get_ptr()[i][j]);	
			}
		}
	}
}


N_list_rep::~N_list_rep()
{
	N_list_el * temp;
	N_list_el * to_delete = nullptr;
	for(int i = 0; i < v; i++)
	{
		temp = arr[i];
		while(temp)
		{
			to_delete = temp;
			temp = temp -> next;
			delete to_delete;
		}	
	}
	delete [] arr;
}


void N_list_rep::add_random_edge()
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
	}while(v1 == v2 || find_edge(v1, v2) != nullptr);
	add_edge(v1, v2, val);
}
		

void N_list_rep::add_edge(int v1, int v2, int v)
{
	// tworze obiekt do dodania w liscie wierzcholka v1
	// ustawiam jego nastepny wierzcholek na ten ktory obecnie znajduje sie jako poczatek listy
	// ustawiam jego indeks na v2
	// ustawiam koszt polaczenia z nim na v
	auto el_v1 = new N_list_el(arr[v1], v2, v);
	arr[v1] = el_v1;
	edges++;
}
		

void N_list_rep::add_edge(Edge * e)
{
	add_edge(e -> v1, e -> v2, e -> cost);
}
		

N_list_el * N_list_rep::find_edge(int v1, int v2)
{
	N_list_el * el = arr[v1];
	if(el != nullptr)
	{
		if(el -> v == v2)
		{
			return el;
		}
		while(el -> next)
		{
			el = el -> next;
			if(el -> v == v2)
			{
				return el;
			}
		}	
	}
	el = arr[v2];
	if(el != nullptr)
	{
		if(el -> v == v1)
		{
			return el;
		}
		while(el -> next)
		{
			el = el -> next;
			if(el -> v == v1)
			{
				return el;
			}
		}	
	}
	return nullptr;
}
	
		
void N_list_rep::print(N_list_rep * g) const
{
	N_list_el * temp = nullptr;
	for(int i = 0; i < v; i++ )
  	{
    	std::cout << "A [ " << i << " ] =";
    	if(g -> arr[i] != nullptr)
    	{
    		temp = g -> arr[i];
    	}
		while(temp != nullptr)
    	{
    		std::cout << std::setw(3) << temp -> v << " ";
			std::cout << std::setw(3) << "cost: " << temp -> cost << " ";
			temp = temp -> next;
  	}
    	std::cout << std::endl;
  	}
}


void N_list_rep::prim(bool test)
{
	// graf ktory posluzy jako odpowiedz
	auto * ans = new N_list_rep(v);
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
					if(!proccessed[k] && find_edge(j, k) != nullptr && find_edge(j, k) -> cost != 0)
					{
						if(min > find_edge(j, k) -> cost)
						{
							min = find_edge(j, k) -> cost;
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
		

void N_list_rep::kruskal(bool test)
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
	auto * ans = new N_list_rep(v);
	// kolejka krawedzi
	auto * q = new Fifo_queue(edges);
	// las wierzcholkow
	int *l = new int[v];
	for(int i = 0; i < v; i++)
	{
		l[i] = i;
	}
	// pomocnicza zmienna do stworzenia kolejki
	int helper = 0;
	// tworzenie kolejki
	N_list_el * el;
	for(int i = 0; i < v; i++)
	{
		if(arr[i] != nullptr)
		{
			el = arr[i];
			q -> insert(new Edge(el -> cost, i, el -> v));
			while(el -> next != nullptr)
			{
				el  = el -> next;
				q -> insert(new Edge(el -> cost, i, el -> v));
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


bool N_list_rep::kruskal_is_set_ok(const int * set, int size)
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


void N_list_rep::quick_sort(Edge ** arr, int p, int r)
{
	int d;
	if(p < r)
	{
		d = quick_sort_part(arr, p, r);
		quick_sort(arr, p, d);
		quick_sort(arr, (d + 1), r);
	}
}


int N_list_rep::quick_sort_part(Edge ** arr, int p, int r)
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
	delete temp;
}


void N_list_rep::djkstra(int v1, bool test)
{
	if(v1 >= v || v1 < 0)
	{
		std::cout << "Podano zly wierzcholek startowy, nacisnij przycisk" << std::endl;
		_getch();
		return;
	}
	// indeks rozpatrywanego wierzcholka
	int temp;
	// zmienna pomocnicza do przechowywania elementu listy
	N_list_el * el;
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
			el = find_edge(temp, j);	
			if(el != nullptr && el -> cost > 0)
			{
				if(cost[j] > cost[temp] + el -> cost)
				{
					cost[j] = cost[temp] + el -> cost;
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
	delete[] parent;
	delete[] cost;
	delete[] is_proccessed;
}


void N_list_rep::ford_bellman(int v1, bool test)
{
	if(v1 < 0 || v1 >= v)
	{
		std::cout << "Podano zly wierzcholek startowy, nacisnij przycisk";
		_getch();
		return;
	}
	// zmienna do przechowywania przegladanego elementu
	N_list_el * el;
	// koszt polaczenia wierzcholka startowego z danym wierzcholkiem
	int *cost = new int[v];
	// ostatni wierzcholek na drodze z wierzcholka startowego to danego wierzcholka
    int *parent = new int[v];;
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
				el =find_edge(j, k);
				if(el != nullptr && el -> cost > 0 && cost[k] > cost[j] + el -> cost)
				{
					cost[k] = cost[j] + el -> cost;
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
	delete[] cost;
	delete[] parent;
}
