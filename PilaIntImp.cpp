#include "PilaInt.h"
#include "Definiciones.h"

#ifdef PILA_INT_IMP

struct _cabezalPilaInt {
	unsigned int cantidad;
	NodoListaInt * pila;
};

PilaInt crearPilaInt(){
	_cabezalPilaInt* nuevaPila = new _cabezalPilaInt;
	nuevaPila->cantidad = 0;
	nuevaPila->pila = NULL;
	return nuevaPila;
}

void push(PilaInt& p, int e) {
	NodoListaInt* nuevo = new NodoListaInt;
	nuevo->dato = e;
	nuevo->sig = p->pila;
	p->pila = nuevo;
	p->cantidad++;
}

int top(PilaInt p) {
	assert(!esVacia(p));
	return p->pila->dato;
}

void pop(PilaInt& p) {
	assert(!esVacia(p));
	NodoListaInt* aBorrar = p->pila;
	p->pila = p->pila->sig;
	delete aBorrar;
	aBorrar = NULL;
}

unsigned int cantidadElementos(PilaInt p) {
	return p->cantidad;
}

bool esVacia(PilaInt p) {
	return p->cantidad == 0;
}

PilaInt clon(PilaInt p) {
	PilaInt clon = crearPilaInt();
	int elementos = p->cantidad;
	while (elementos > 0) {
		push(clon, p->pila->dato);
		elementos--;
		p->pila = p->pila->sig;
	}
	return clon;
}

void destruir(PilaInt& p) {
	while (p->pila != NULL) {
		NodoListaInt* aBorrar = p->pila;
		p->pila = p->pila->sig;
		delete aBorrar;
		aBorrar = NULL;
	}
	delete p;
	p = NULL;
}


#endif