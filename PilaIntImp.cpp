#include "PilaInt.h"

#ifdef PILA_INT_IMP

struct _cabezalPilaInt {
	unsigned int dato;
	_cabezalPilaInt* sig;
};


PilaInt crearPilaInt(){
	_cabezalPilaInt* res = NULL;
	return res;
}

void push(PilaInt& p, int e) {
	_cabezalPilaInt* nuevo = new _cabezalPilaInt;
	nuevo->dato = e;
	nuevo->sig = p;
	p = nuevo;
}

int top(PilaInt p) {
	return p->dato;
}

void pop(PilaInt& p) {
	_cabezalPilaInt* aBorrar = p;
	p = p->sig;
	delete aBorrar;
	aBorrar = NULL;
}

unsigned int cantidadElementos(PilaInt p) {
	int count = 0;
	while (p != NULL) {
		count++;
		p = p->sig;
	}
	return count;
}

bool esVacia(PilaInt p) {
	return p == NULL;
}

PilaInt clon(PilaInt p) {
	_cabezalPilaInt* res = NULL;
	_cabezalPilaInt* ultimo = res;
	while (p != NULL) {
		push(ultimo, p->dato);
		ultimo = ultimo->sig;
		p = p->sig;
	}
	return res;
}

void destruir(PilaInt& p) {
	while (p != NULL) {
		_cabezalPilaInt* aBorrar = p;
		p = p->sig;
		delete aBorrar;
		aBorrar = NULL;
	}
}


#endif