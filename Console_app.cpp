#include "Console_app.h"


Console_app::Console_app()
{
	this -> v_start = -1;
	this -> matrix_rep = nullptr;
	this -> n_list_rep = nullptr;
	this -> input = 0;
	this -> run = true;
	this -> run_app();	
}


Console_app::~Console_app() {

    delete matrix_rep;
    delete n_list_rep;
}


void Console_app::run_app()
{
	do
	{
		// czyszcze konsole
		system("CLS");
		// wypisuje menu
		std::cout << "Menu: " << std::endl << std::endl;
		std::cout << "Wybierz: " << std::endl << std::endl;
		std::cout << "1.   Wczytaj graf " << std::endl;
		std::cout << "2.   Stworz losowy graf " << std::endl;
		std::cout << "3.   Prim" << std::endl;
		std::cout << "4.   Kruskal " << std::endl;
		std::cout << "5.   Djkstra " << std::endl;
		std::cout << "6.   Ford Bellman" << std::endl;
		std::cout << "7.   Test" << std::endl;
		std::cout << "8.   readme" << std::endl;
		std::cout << "ESC. back " << std::endl << std::endl;
		std::cout << "Postac macierzowa: " << std::endl;
		if(matrix_rep != nullptr)
		{
			matrix_rep -> print(matrix_rep);
		}
		std::cout << std::endl << std::endl;
		std::cout << "Postac listowa: " << std::endl;
		if(n_list_rep != nullptr)
		{
			n_list_rep -> print(n_list_rep);
		}
		std::cout << std::endl << std::endl;
		input = _getch();
		switch(input)
		{
			// wczytywanie grafu
			case 49:
				{
					auto * reader = new Reader();
					std::cout << "Jezeli plik zawiera wierzcholek startowy nacisnij 't':" << std::endl;
					v0 = _getch();
					matrix_rep = reader -> load(v0);
						if(matrix_rep != nullptr)
						{
							n_list_rep = new N_list_rep(matrix_rep);	
							n_list_rep -> set_v_start(matrix_rep -> get_v_start());	
						}			
					delete reader;
				}
			break;
			
			// tworzenie losowego grafu
			case 50:
				{
					std::cout << "Podaj liczbe wierzcholkow " << std::endl;
					std::cin >> v;
					std::cout << "Podaj gestosc grafu w %" << std::endl;
					std::cin >> d;
					std::cout << "Podaj maksymalny koszt krawedzi" << std::endl;
					std::cin >> r;
					this -> matrix_rep = new Matrix_rep(v, d, r, false);
					this -> n_list_rep = new N_list_rep(matrix_rep);	
				}
			break;
			
			// algorytm prima
			case 51:
				if(matrix_rep != nullptr && matrix_rep -> check_if_connected())
				{
					std::cout << "Prim:" << std::endl;
					matrix_rep -> prim(false);
					n_list_rep -> prim(false);	
				}
				else
				{
					std::cout << "Graf nie jest polaczony, " << std::endl;
				}
				std::cout << "Wcisnij przycisk: " << std::endl;
				_getch();
			break;
				
			// algorytm kruskala
			case 52:
				if(matrix_rep != nullptr && matrix_rep -> check_if_connected())
				{
					std::cout << "Kruskal:" << std::endl;
					matrix_rep -> kruskal(false);
					n_list_rep -> kruskal(false);	
				}
				else
				{
					std::cout << "Graf nie jest polaczony, " << std::endl;
				}
				std::cout << "Wcisnij przycisk: " << std::endl;
				_getch();
			break;
			
			// algorytm djkstry
			case 53:
				if(matrix_rep != nullptr && matrix_rep -> check_if_connected() && v0 != 116)
				{
					std::cout << "Podaj wierzcholek startowy: " << std::endl;
					std::cin >> v0;
					std::cout << "Djkstra:" << std::endl;
					matrix_rep -> djkstra(v0, false);
					n_list_rep -> djkstra(v0, false);
				}
				else if(matrix_rep != nullptr && matrix_rep -> check_if_connected() && v0 == 116)
				{
					std::cout << "Djkstra:" << std::endl;
					matrix_rep -> djkstra(matrix_rep -> get_v_start(), false);
					n_list_rep -> djkstra(n_list_rep -> get_v_start(), false);
				}
				else
				{
					std::cout << "Graf nie jest polaczony, " << std::endl;
				}
				std::cout << "Wcisnij przycisk: " << std::endl;
				_getch();
			break;
			
			// algorytm forda bellmana
			case 54:
				if(matrix_rep != nullptr && matrix_rep -> check_if_connected() && v0 != 116)
				{
					std::cout << "Podaj wierzcholek startowy: " << std::endl;
					std::cin >> v0;
					std::cout << "Ford Bellman:" << std::endl;
					matrix_rep -> ford_bellman(v0, false);
					n_list_rep -> ford_bellman(v0, false);
				}
				else if(matrix_rep != nullptr && matrix_rep -> check_if_connected() && v0 == 116)
				{
					std::cout << "Ford Bellman:" << std::endl;
					matrix_rep -> ford_bellman(matrix_rep -> get_v_start(), false);
					n_list_rep -> ford_bellman(n_list_rep -> get_v_start(), false);
				}
				else
				{
					std::cout << "Graf nie jest polaczony, " << std::endl;
				}
				std::cout << "Wcisnij przycisk: " << std::endl;
				_getch();
			break;
			
			// przeprowadzenie testu
			case 55:
				this -> run_test();
			break;
			
			// readme
			case 56:
				std::cout << "W momencie wczytania z pliku trzeba wybrac czy w pliku znajduje sie\n";
				std::cout << "wierzcholek startowy, jezeli sie znajduje, algorytm djkstry oraz\n";
				std::cout << "Forda-Bellmana zostana wywolane dla podanego wierzcholka\n";
				std::cout << "Funkcja testu zapisuje wyniki do pliku txt. Nacisnij przycisk:\n";
				_getch();
			break;
			
			// koniec
			case 27:
				this -> run = false;
			break;
		}
	}while(run);
}

	
void Console_app::run_test()
{
	PCFreq = 0.0;
	CounterStart = 0;
	std::ofstream myfile;
	myfile.open ("results.txt", std::ios_base::app);
	Matrix_rep * m;
	N_list_rep * l;
	for(int i = 25; i < 176; i += 25)
	{
		m = new Matrix_rep(i, 20, i * 4, 1);
		
		l = new N_list_rep(m);
		
		
		myfile << "Postac macierzowa: " << std::endl << std::endl;
		
		startCounter();
		m -> prim(true);
		time = getCounter();	
  		myfile << "Prim: " << "i: " << i << " d: " << "20" << " czas: " << time << std::endl;
  		
		startCounter();
		m -> kruskal(true);
		time = getCounter();
		myfile << "Kruskal: " << "i: " << i << " d: " << "20" << " czas: " << time << std::endl;
		
		startCounter();
		m -> djkstra(0, true);
		time = getCounter();
		myfile << "Djkstra: " << "i: " << i << " d: " << "20" << " czas: " << time << std::endl;
		
		startCounter();
		m -> ford_bellman(0, true);
		time = getCounter();
		myfile << "Ford bellman: " << "i: " << i << " d: " << "20" << " czas: " << time << std::endl;
		
		
		myfile << std::endl << std::endl << "Postac listowa: " << std::endl << std::endl;
		
		startCounter();
		l -> prim(true);
		time = getCounter();	
  		myfile << "Prim: " << "i: " << i << " d: " << "20" << " czas: " << time << std::endl;
  		
		startCounter();
		l -> kruskal(true);
		time = getCounter();
		myfile << "Kruskal: " << "i: " << i << " d: " << "20" << " czas: " << time << std::endl;
		
		startCounter();
		l -> djkstra(0, true);
		time = getCounter();
		myfile << "Djkstra: " << "i: " << i << " d: " << "20" << " czas: " << time << std::endl;
		
		startCounter();
		l -> ford_bellman(0, true);
		time = getCounter();
		myfile << "Ford bellman: " << "i: " << i << " d: " << "20" << " czas: " << time << std::endl;
		

		delete m;
		delete l;
		m = new Matrix_rep(i, 60, i * 4, 1);
		l = new N_list_rep(m);

		
		myfile << std::endl << std::endl << "Postac macierzowa: " << std::endl << std::endl;
		
		startCounter();
		m -> prim(true);
		time = getCounter();	
  		myfile << "Prim: " << "i: " << i << " d: " << "60" << " czas: " << time << std::endl;
  		
		startCounter();
		m -> kruskal(true);
		time = getCounter();
		myfile << "Kruskal: " << "i: " << i << " d: " << "60" << " czas: " << time << std::endl;
		
		startCounter();
		m -> djkstra(0, true);
		time = getCounter();
		myfile << "Djkstra: " << "i: " << i << " d: " << "60" << " czas: " << time << std::endl;
		
		startCounter();
		m -> ford_bellman(0, true);
		time = getCounter();
		myfile << "Ford bellman: " << "i: " << i << " d: " << "60" << " czas: " << time << std::endl;
		
		
		myfile << std::endl << std::endl << "Postac listowa: " << std::endl << std::endl;
		
		
		startCounter();
		l -> prim(true);
		time = getCounter();	
  		myfile << "Prim: " << "i: " << i << " d: " << "60" << " czas: " << time << std::endl;
  		
		startCounter();
		l -> kruskal(true);
		time = getCounter();
		myfile << "Kruskal: " << "i: " << i << " d: " << "60" << " czas: " << time << std::endl;
		
		startCounter();
		l -> djkstra(0, true);
		time = getCounter();
		myfile << "Djkstra: " << "i: " << i << " d: " << "60" << " czas: " << time << std::endl;
		
		startCounter();
		l -> ford_bellman(0, true);
		time = getCounter();
		myfile << "Ford bellman: " << "i: " << i << " d: " << "60" << " czas: " << time << std::endl;
		

		delete m;
		delete l;
		m = new Matrix_rep(i, 99, i * 4, true);
		l = new N_list_rep(m);
		
		
		myfile << std::endl << std::endl << "Postac macierzowa: " << std::endl << std::endl;
		
		
		startCounter();
		m -> prim(true);
		time = getCounter();	
  		myfile << "Prim: " << "i: " << i << " d: " << "99" << " czas: " << time << std::endl;
  		
		startCounter();
		m -> kruskal(true);
		time = getCounter();
		myfile << "Kruskal: " << "i: " << i << " d: " << "99" << " czas: " << time << std::endl;
		
		startCounter();
		m -> djkstra(0, true);
		time = getCounter();
		myfile << "Djkstra: " << "i: " << i << " d: " << "99" << " czas: " << time << std::endl;
		
		startCounter();
		m -> ford_bellman(0, true);
		time = getCounter();
		myfile << "Ford bellman: " << "i: " << i << " d: " << "99" << " czas: " << time << std::endl;
		
		
		myfile << std::endl << std::endl << "Postac listowa: " << std::endl << std::endl;
		
		
		startCounter();
		l -> prim(true);
		time = getCounter();	
  		myfile << "Prim: " << "i: " << i << " d: " << "99" << " czas: " << time << std::endl;
  		
		startCounter();
		l -> kruskal(true);
		time = getCounter();
		myfile << "Kruskal: " << "i: " << i << " d: " << "99" << " czas: " << time << std::endl;
		
		startCounter();
		l -> djkstra(0, true);
		time = getCounter();
		myfile << "Djkstra: " << "i: " << i << " d: " << "99" << " czas: " << time << std::endl;
		
		startCounter();
		l -> ford_bellman(0, true);
		time = getCounter();
		myfile << "Ford bellman: " << "i: " << i << " d: " << "99" << " czas: " << time << std::endl;
		
		
		delete m;
		delete l;
	}	
	std::cout << "udalo sie" << std::endl;
	_getch();
	myfile.close();
}


void Console_app::startCounter(){

    LARGE_INTEGER li;
    if(!QueryPerformanceFrequency(&li)){
    
         std::cout << "QueryPerformanceFrequency failed!";
         _getch();
         return;
	}
   
    PCFreq = double( li.QuadPart ) / 1000.0;
    QueryPerformanceCounter( & li );
    CounterStart = li.QuadPart;
}


double Console_app::getCounter() const{
	
    LARGE_INTEGER li;
    QueryPerformanceCounter( & li );
    return double( li.QuadPart - CounterStart ) / PCFreq;
}
