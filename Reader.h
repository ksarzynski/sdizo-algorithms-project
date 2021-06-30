#ifndef READER_H
#define READER_H


#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <cstdlib>
#include <sstream>

#include "Matrix_rep.h"
#include "N_list_rep.h"


class Reader{

	public:
		
		Matrix_rep * load(int v0);
};

 
#endif

