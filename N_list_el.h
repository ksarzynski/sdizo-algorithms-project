#ifndef N_LIST_EL_H
#define N_LIST_EL_H


// klasa reprezentuje element listy sasiedztwa

class N_list_el
{
	public:
	
		//atrybuty
		
		N_list_el * next;
		int v;
		int cost;
		
		
		// metody
		
			
		N_list_el(N_list_el * next, int v, int cost)
		{
			this -> next = next;
			this -> v = v;
			this -> cost = cost;
		}
};


#endif

