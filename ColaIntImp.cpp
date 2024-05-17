#include "ColaInt.h"

#ifdef COLA_INT_IMP

struct _cabezalColaInt {
	unsigned int dato;
	_cabezalColaInt* sig;
};

ColaInt crearColaInt() {
	_cabezalColaInt* res = NULL;
	return res;
}

void encolar(ColaInt& c, int e) {
	_cabezalColaInt* nuevo = new _cabezalColaInt;
	if (c == NULL) {
		nuevo->dato = e;
		nuevo->sig = NULL;
		c = nuevo;
	}
	else {
		_cabezalColaInt* aux = c;
		while (aux->sig != NULL) {
			aux = aux->sig;
		}
		aux->sig = nuevo;
		nuevo->dato = e;
		nuevo->sig = NULL;
	}
}

int principio(ColaInt c) {
	assert(!esVacia(c));
	return c->dato;
}

void desencolar(ColaInt& c) {
	assert(!esVacia(c));
	_cabezalColaInt* aBorrar = c;
	c = c->sig;
	delete aBorrar;
	aBorrar = NULL;
}

bool esVacia(ColaInt c) {	
	return c == NULL;
}

unsigned int cantidadElementos(ColaInt c) {
	int count = 0;
	while (c != NULL) {
		count++; 
		c = c->sig;
	}
	return count;
}

ColaInt clon(ColaInt c) {
	_cabezalColaInt* res = NULL;
	while (c != NULL) {
		encolar(res, c->dato);
		c = c->sig;
	}
	return res;
}

void destruir(ColaInt& c) {
	while (c != NULL) {
		_cabezalColaInt* aBorrar = c;
		c = c->sig;
		delete aBorrar;
		aBorrar = NULL;
	}
}

#endif