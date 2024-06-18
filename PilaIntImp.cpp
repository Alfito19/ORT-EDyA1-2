#include "PilaInt.h"
#include "Definiciones.h"

#ifdef PILA_INT_IMP

struct _cabezalPilaInt {
	unsigned int cantidad;
	NodoListaInt * pila;
};

_cabezalPilaInt* crearPilaInt(){
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
	p->cantidad--;
}

unsigned int cantidadElementos(PilaInt p) {
	return p->cantidad;
}

bool esVacia(PilaInt p) {
	return p->cantidad == 0;
}

PilaInt clon(PilaInt p) {
	_cabezalPilaInt* clonPila = crearPilaInt();
	NodoListaInt* iter = p->pila;
	for(int i = 0; i < p->cantidad;i++){
		push(clonPila, iter->dato);
		iter = iter->sig;
	}
	return clonPila;
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