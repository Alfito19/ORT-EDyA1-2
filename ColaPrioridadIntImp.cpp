#include "ColaPrioridadInt.h"
#include "Definiciones.h"

#ifdef COLAPRIORIDAD_INT_IMP

struct _cabezalColaPrioridadInt {
	int cota;
	int cantidad;
	NodoListaIntDobleDato* primero;
	NodoListaIntDobleDato* ultimo;
};

ColaPrioridadInt crearColaPrioridadInt(unsigned int cota) {
	_cabezalColaPrioridadInt* res = new _cabezalColaPrioridadInt;
	res->primero = res->ultimo = NULL;
	res->cota = cota;
	res->cantidad = 0;
	return res;
}

void encolar(ColaPrioridadInt& c, int e, int p) {
	assert(!esLlena(c));

	NodoListaIntDobleDato* nuevo = new NodoListaIntDobleDato;
	nuevo->dato1 = e;
	nuevo->dato2 = p;
	nuevo->sig = NULL;

	if (c->primero == NULL || c->primero->dato2 < p) {
		nuevo->sig = c->primero;
		c->primero = nuevo;
	}
	else {
		NodoListaIntDobleDato* iter = c->primero;
		while (iter->sig != NULL && iter->sig->dato2 >= p) {
			iter = iter->sig;
		}
		nuevo->sig = iter->sig;
		iter->sig = nuevo;
	}
	c->cantidad++;
}

int principio(ColaPrioridadInt c) {
	assert(!esVacia(c));
	return c->primero->dato1;
}

int principioPrioridad(ColaPrioridadInt c) {
	assert(!esVacia(c));
	return c->primero->dato2;
}

void desencolar(ColaPrioridadInt& c) {
	assert(!esVacia(c));
	NodoListaIntDobleDato* aBorrar = c->primero;
	c->primero = c->primero->sig;
	delete aBorrar;
	aBorrar = NULL;
	c->cantidad--;
}

bool esVacia(ColaPrioridadInt c) {
	return c->primero == NULL;
}

bool esLlena(ColaPrioridadInt c) {
	return cantidadElementos(c) == c->cota;
}

unsigned int cantidadElementos(ColaPrioridadInt c) {
	return c->cantidad;
}

ColaPrioridadInt clon(ColaPrioridadInt c) {
	_cabezalColaPrioridadInt* res = crearColaPrioridadInt(c->cota);
	NodoListaIntDobleDato* iter = c->primero;
	while (iter != NULL) {
		encolar(res, iter->dato1, iter->dato2);
		iter = iter->sig;
	}
	return res;
}

void destruir(ColaPrioridadInt& c) {
	while (c->primero != NULL) {
		NodoListaIntDobleDato* aBorrar = c->primero;
		c->primero = c->primero->sig;
		delete aBorrar;
		aBorrar = NULL;
	}
	delete c;
	c = NULL;
}

#endif