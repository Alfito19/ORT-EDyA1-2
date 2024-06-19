#include "ListaPosInt.h"

#ifdef LISTA_POS_INT_IMP

struct _cabezalListaPosInt {
	int* elem;
	int cantidad;
	int maxPos;
};

ListaPosInt crearListaPosInt()
{
	
}

void agregar(ListaPosInt& l, int e, unsigned int pos)
{
	
}

void borrar(ListaPosInt& l, unsigned int pos)
{
	
}

int elemento(ListaPosInt l, unsigned int pos)
{
	
}

bool esVacia(ListaPosInt l)
{
	
}

unsigned int cantidadElementos(ListaPosInt l)
{
	
}

ListaPosInt clon(ListaPosInt l)
{
	
}

void destruir(ListaPosInt& l)
{
	delete[] l->elem;
	delete l;
}

#endif