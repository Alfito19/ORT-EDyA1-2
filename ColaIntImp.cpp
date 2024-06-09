#include "ColaInt.h"
#include "Definiciones.h"

#ifdef COLA_INT_IMP

struct _cabezalColaInt {
	NodoListaInt * primero;
	NodoListaInt * ultimo;
	int cantidad;
};

ColaInt crearColaInt() {
	_cabezalColaInt* res = new _cabezalColaInt;
	res->primero = res->ultimo = NULL;
	res->cantidad = 0;
	return res;
}

void encolar(ColaInt& c, int e) {
	NodoListaInt* nuevo = new NodoListaInt;
	nuevo->dato = e;
	nuevo->sig = NULL;
	if (c->primero == NULL) {
		c->primero = nuevo;
	}
	else {
		c->ultimo->sig = nuevo;
	}
	c->cantidad++;
	c->ultimo = nuevo;
}

int principio(ColaInt c) {
	assert(!esVacia(c));
	return c->primero->dato;
}

void desencolar(ColaInt& c) {
	assert(!esVacia(c));
	NodoListaInt* aBorrar = c->primero;
	c->primero = c->primero->sig;
	delete aBorrar;
	aBorrar = NULL;
}

bool esVacia(ColaInt c) {	
	return c->primero == NULL;
}

unsigned int cantidadElementos(ColaInt c) {
	return c->cantidad;
}

ColaInt clon(ColaInt c) {
	_cabezalColaInt* res = crearColaInt();
	NodoListaInt* iter = c->primero;
	while (iter != NULL) {
		encolar(res, iter->dato);
		iter = iter->sig;
	}
	return res;
}

void destruir(ColaInt& c) {
	while (c->primero != NULL) {
		NodoListaInt* aBorrar = c->primero;
		c->primero = c->primero->sig;
		delete aBorrar;
		aBorrar = NULL;
	}
	delete c;
	c = NULL;
}

#endif