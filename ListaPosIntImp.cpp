#include "ListaPosInt.h"

#ifdef LISTA_POS_INT_IMP

struct _cabezalListaPosInt {
	int* listaPos;
	int cantidad;
	int maxPos;
};

ListaPosInt crearListaPosInt()
{
	_cabezalListaPosInt* nuevo = new _cabezalListaPosInt;
	nuevo->listaPos = new int[1];
	for(int i = 0; i < 1; i++){
		nuevo->listaPos[i] = NULL;
	}
	nuevo->maxPos = 0;
	nuevo->cantidad = 0;
	return nuevo;
}

void agregar(ListaPosInt& l, int e, unsigned int pos)
{

}

void borrar(ListaPosInt& l, unsigned int pos)
{
	l->listaPos[pos] = 0;
	l->cantidad--;
}

int elemento(ListaPosInt l, unsigned int pos)
{
	return l->listaPos[pos];
}

bool esVacia(ListaPosInt l)
{
	return l->cantidad == 0;
}

unsigned int cantidadElementos(ListaPosInt l)
{
	return l->cantidad;
}

ListaPosInt clon(ListaPosInt l)
{
	_cabezalListaPosInt* clon = crearListaPosInt();
	for (int i = 0; i < l->maxPos; i++) {
		agregar(clon, l->listaPos[i], i);
	}
	return clon;
}

void destruir(ListaPosInt& l)
{
	delete[] l->listaPos;
	delete l;
}


#endif