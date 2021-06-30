#ifndef CONSOLE_APP_H
#define CONSOLE_APP_H


#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <ctime>
#include <time.h>
#include <string>
#include <fstream>

#include "Matrix_rep.h"
#include "N_list_rep.h"
#include "Reader.h"


class Console_app{
	
	// zmienne do pomiarow
	double PCFreq;
	__int64 CounterStart;
	double time;
	// zmienne oznaczajace czy aplikacja jest wlaczona,
	// zmienne na wejscie od uzytkownika
	// zmienne pomocnicze
	bool run;
	int input;
	int v_start;
	int v0;
	int v;
	int e;
	int d;
	int r;
	std::string input_file;
	// zmienna do zapisania wynikow testu
	std::string file_name;
	Matrix_rep * matrix_rep;
	N_list_rep * n_list_rep;	
	public:
	
		// konstruktor
		Console_app();

        // konstruktor
        ~Console_app();

		// funkcja wlaczajaca i obsluugujaca aplikacje
		void run_app();
		
		// funkcja do testowaniq
		void run_test();
		
		// funkcja pomocnicza
		void choice();
		
		// funkcje do przeprowadzania pomiarow
		void startCounter();
		
		double getCounter() const;
};
#endif

