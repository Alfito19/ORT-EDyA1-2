#include "MultisetInt.h"
#include "Definiciones.h"

#ifdef MULTISET_INT_IMP

struct _cabezalMultisetInt {
	int cantidad;
	NodoListaIntDobleDato* elemento;
};

MultisetInt crearMultisetInt() {
	_cabezalMultisetInt* res = new _cabezalMultisetInt;
	res->cantidad = 0;
	res->elemento = NULL;
	return res;
}


void agregar(MultisetInt& s, int e, unsigned int ocurrencias){
	NodoListaIntDobleDato* iter = s->elemento;
	NodoListaIntDobleDato* anterior = NULL;
	while (iter != NULL) {
		if (iter->dato1 == e) {
			iter->dato2 += ocurrencias;
			s->cantidad += ocurrencias;
			return;
		}
		anterior = iter;
		iter = iter->sig;
	}
	NodoListaIntDobleDato* nuevo = new NodoListaIntDobleDato;
	nuevo->dato1 = e;
	nuevo->dato2 = ocurrencias;
	nuevo->sig = NULL;
	if (anterior == NULL) {
		s->elemento = nuevo;
	}
	else {
		anterior->sig = nuevo;
	}
	s->cantidad += ocurrencias;
}

void borrar(MultisetInt& s, int e) {
	NodoListaIntDobleDato* iter = s->elemento;
	NodoListaIntDobleDato* anterior = NULL;

	while (iter != NULL) {
		if (iter->dato1 == e) {
			if (iter->dato2 > 1) {
				iter->dato2--;
				s->cantidad--;
			}
			else {
				if (anterior == NULL) {
					s->elemento = iter->sig;
				}
				else {
					anterior->sig = iter->sig;
				}
				delete iter;
				s->cantidad--;
			}
			return;
		}
		anterior = iter;
		iter = iter->sig;
	}
}

bool pertenece(MultisetInt s, int e) {
	NodoListaIntDobleDato* iter = s->elemento;
	while (iter != NULL) {
		if (iter->dato1 == e) {
			return true;
		}
		iter = iter->sig;
	}
	return false;
}

MultisetInt unionConjuntos(MultisetInt s1, MultisetInt s2) {
	MultisetInt res = crearMultisetInt();
	NodoListaIntDobleDato* iter = s1->elemento;
	while (iter != NULL) {
		agregar(res, iter->dato1, iter->dato2);
		iter = iter->sig;
	}
	iter = s2->elemento;
	while (iter != NULL) {
		agregar(res, iter->dato1, iter->dato2);
		iter = iter->sig;
	}
	return res;
}

MultisetInt interseccionConjuntos(MultisetInt s1, MultisetInt s2) {
	MultisetInt res = crearMultisetInt();
	NodoListaIntDobleDato* iter1 = s1->elemento;
	NodoListaIntDobleDato* iter2;

	while (iter1 != NULL) {
		iter2 = s2->elemento;
		while (iter2 != NULL) {
			if (iter1->dato1 == iter2->dato1) {
				agregar(res, iter1->dato1, std::min(iter1->dato2, iter2->dato2));
			}
			iter2 = iter2->sig;
		}
		iter1 = iter1->sig;
	}
	return res;
}

MultisetInt diferenciaConjuntos(MultisetInt s1, MultisetInt s2) {
	MultisetInt res = crearMultisetInt();
	NodoListaIntDobleDato* iter1 = s1->elemento;

	while (iter1 != NULL) {
		NodoListaIntDobleDato* iter2 = s2->elemento;
		bool found = false;
		while (iter2 != NULL) {
			if (iter1->dato1 == iter2->dato1) {
				if (iter1->dato2 > iter2->dato2) {
					agregar(res, iter1->dato1, iter1->dato2 - iter2->dato2);
				}
				found = true;
				break;
			}
			iter2 = iter2->sig;
		}
		if (!found) {
			agregar(res, iter1->dato1, iter1->dato2);
		}
		iter1 = iter1->sig;
	}
	return res;
}

bool contenidoEn(MultisetInt s1, MultisetInt s2) {
	NodoListaIntDobleDato* iter1 = s1->elemento;
	NodoListaIntDobleDato* iter2;

	while (iter1 != NULL) {
		iter2 = s2->elemento;
		bool found = false;
		while (iter2 != NULL) {
			if (iter1->dato1 == iter2->dato1 && iter1->dato2 <= iter2->dato2) {
				found = true;
				break;
			}
			iter2 = iter2->sig;
		}
		if (!found) {
			return false;
		}
		iter1 = iter1->sig;
	}
	return true;
}

int elemento(MultisetInt s) {
	return s->elemento->dato1;
}

bool esVacio(MultisetInt s) {
	return s->elemento == NULL;
}

unsigned int cantidadElementos(MultisetInt s) {
	return s->cantidad;
}

void destruir(MultisetInt& s) {
	while (s->elemento != NULL) {
		NodoListaIntDobleDato* aBorrar = s->elemento;
		s->elemento = s->elemento->sig;
		delete aBorrar;
		aBorrar = NULL;
	}
	delete s;
	s = NULL;
}

MultisetInt clon(MultisetInt s) {
	_cabezalMultisetInt* res = crearMultisetInt();
	NodoListaIntDobleDato* iter = s->elemento;
	while (iter != NULL) {
		agregar(res, iter->dato1, iter->dato2);
		iter = iter->sig;
	}
	return res;
}

#endif