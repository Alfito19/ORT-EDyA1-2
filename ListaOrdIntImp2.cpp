#include "ListaOrdInt.h"
#include "Definiciones.h"
#ifdef LISTA_ORD_INT_IMP_2

struct _cabezalListaOrdInt {
	NodoABInt* ab;
	int cantidad;
	int max;
	int min;
};

ListaOrdInt crearListaOrdInt() {
	ListaOrdInt nuevo = new _cabezalListaOrdInt;
	nuevo->ab = NULL;
	nuevo->cantidad = 0;
	nuevo->max = INT_MIN;
	nuevo->min = INT_MAX;
	return nuevo;
}

//PRE
//POS
void agregarABB(NodoABInt*& abb, int dato) {
	if (abb == NULL) {
		abb = new NodoABInt;
		abb->dato = dato;
		abb->izq = abb->der = NULL;
	}
	else if (dato < abb->dato) {
		agregarABB(abb->izq, dato);
	}
	else {
		agregarABB(abb->der, dato);
	}
}

void agregar(ListaOrdInt& l, int e) {
	agregarABB(l->ab, e);
	l->cantidad++;
	if (e > l->max) l->max = e;
	if (e < l->min) l->min = e;
}



void borrarMinimo(ListaOrdInt& l) {
	borrar(l, l->min);
}

void borrarMaximo(ListaOrdInt& l) {
	borrar(l, l->max);
}

//PRE
//POS
void borrarABB(NodoABInt*& abb, int dato) {
	if (abb == NULL) return;
	if (dato < abb->dato) {
		borrarABB(abb->izq, dato);
	}
	else if (dato > abb->dato) {
		borrarABB(abb->der, dato);
	}
	else {
		NodoABInt* aBorrar = abb;
		if (abb->izq == NULL) {
			abb = abb->der;
		}
		else if (abb->der == NULL) {
			abb = abb->izq;
		}
		else {
			NodoABInt* reemplazo = abb->izq;
			NodoABInt* padreReemplazo = abb;
			while (reemplazo->der != NULL) {
				padreReemplazo = reemplazo;
				reemplazo = reemplazo->der;
			}
			if (padreReemplazo != abb) {
				padreReemplazo->der = reemplazo->izq;
				reemplazo->izq = abb->izq;
			}
			reemplazo->der = abb->der;
			abb = reemplazo;
		}
		delete aBorrar;
	}
}

void borrar(ListaOrdInt& l, int e) {
	if (existe(l, e)) {
		borrarABB(l->ab, e);
		l->cantidad--;
		if (l->ab != NULL) {
			if (e == l->max) {
				NodoABInt* iter = l->ab;
				while (iter->der != NULL) {
					iter = iter->der;
				}
				l->max = iter->dato;
			}
			if (e == l->min) {
				NodoABInt* iter = l->ab;
				while (iter->izq != NULL) {
					iter = iter->izq;
				}
				l->min = iter->dato;
			}
		}
		else {
			l->max = INT_MIN;
			l->min = INT_MAX;
		}
	}
}

int minimo(ListaOrdInt l) {
	return l->min;
}

int maximo(ListaOrdInt l) {
	return l->max;
}

//PRE
//POS
bool buscarEnABB(NodoABInt* nodo, int e) {
	if (nodo == NULL) return false;
	if (nodo->dato == e) return true;
	if (e < nodo->dato) return buscarEnABB(nodo->izq, e);
	return buscarEnABB(nodo->der, e);
}

bool existe(ListaOrdInt l, int e) {
	return buscarEnABB(l->ab,e);
}



bool esVacia(ListaOrdInt l) {
	return l->cantidad == 0;
}

unsigned int cantidadElementos(ListaOrdInt l) {
	return l->cantidad;
}

//PRE
//POS
NodoABInt* clonarABB(NodoABInt* nodo) {
	if (nodo == NULL) return NULL;

	NodoABInt* nuevoNodo = new NodoABInt;
	nuevoNodo->dato = nodo->dato;
	nuevoNodo->izq = clonarABB(nodo->izq);
	nuevoNodo->der = clonarABB(nodo->der);
	return nuevoNodo;
}

ListaOrdInt clon(ListaOrdInt l) {
	if (l == NULL) return NULL;

	ListaOrdInt nuevaLista = new _cabezalListaOrdInt;
	nuevaLista->cantidad = l->cantidad;
	nuevaLista->max = l->max;
	nuevaLista->min = l->min;
	nuevaLista->ab = clonarABB(l->ab);

	return nuevaLista;
}

void destruirABB(NodoABInt* nodo) {
	if (nodo == NULL) return;

	destruirABB(nodo->izq);
	destruirABB(nodo->der);
	delete nodo;
}

void destruir(ListaOrdInt& l) {
	if (l == NULL) return;

	destruirABB(l->ab);
	delete l;
	l = NULL;
}



#endif