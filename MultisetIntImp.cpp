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
	NodoListaIntDobleDato* nuevo = new NodoListaIntDobleDato;
	nuevo->dato1 = e;
	nuevo->dato2 = ocurrencias;
	nuevo->sig = NULL;
	bool yaIngresado = false;
	if (s->elemento == NULL) {
		s->elemento = nuevo;
	}
	else {
		NodoListaIntDobleDato* iter = s->elemento;
		while (!yaIngresado && (iter->dato1 > e || iter->sig != NULL)) {
			if (iter->dato1 == e) {
				iter->dato2 += ocurrencias; // no me queda claro si le suma las ocurrencias, las reemplaza o suma uno
				yaIngresado = true;
			}
			iter = iter->sig;
		}
		if (!yaIngresado) {
			nuevo->sig = iter->sig;
			iter->sig = nuevo;
			s->cantidad++;
		}
		else delete nuevo;
	}
}

void borrar(MultisetInt& s, int e) {
	NodoListaIntDobleDato* iter = s->elemento;
	while (iter->dato1 > e || iter->sig != NULL) {
		if (iter->dato1 == e) {
			NodoListaIntDobleDato* aBorrar = iter;
			iter = iter->sig;
			delete aBorrar;
			aBorrar = NULL;
			s->cantidad--;
		}
		iter = iter->sig;
	}
}

bool pertenece(MultisetInt s, int e) {
	while (s->elemento != NULL) {
		if (s->elemento->dato1 == e) {
			return true;
		}
		s->elemento = s->elemento->sig;
	}
	return false;
}

MultisetInt unionConjuntos(MultisetInt s1, MultisetInt s2) {
	_cabezalMultisetInt* res = crearMultisetInt();
	while (s1->elemento != NULL) {
		agregar(res, s1->elemento->dato1, s1->elemento->dato2);
		s1->elemento = s1->elemento->sig;
	}
	while (s2->elemento != NULL) {
		agregar(res, s2->elemento->dato1, s2->elemento->dato2);
		s2->elemento = s2->elemento->sig;
	}
	return res;
}

MultisetInt interseccionConjuntos(MultisetInt s1, MultisetInt s2) {
	_cabezalMultisetInt* res = crearMultisetInt();
	while (s1->elemento != NULL && s2->elemento != NULL) {
		if (s1->elemento->dato1 == s2->elemento->dato1) {
			agregar(res, s1->elemento->dato1, s1->elemento->dato2);
			s1->elemento = s1->elemento->sig;
			s2->elemento = s2->elemento->sig;
		}
		else if (s1->elemento->dato1 > s2->elemento->dato1) {
			s2->elemento = s2->elemento->sig;
		}
		else if (s1->elemento->dato1 < s2->elemento->dato1) {
			s1->elemento = s1->elemento->sig;
		}
	}
	return res;
}

MultisetInt diferenciaConjuntos(MultisetInt s1, MultisetInt s2) {
	_cabezalMultisetInt* res = crearMultisetInt();
	while (s1->elemento != NULL && s2->elemento != NULL) {
		if (s1->elemento->dato1 == s2->elemento->dato1) {
			s1->elemento = s1->elemento->sig;
			s2->elemento = s2->elemento->sig;
		}
		else if (s1->elemento->dato1 > s2->elemento->dato1) {
			s2->elemento = s2->elemento->sig;
		}
		else if (s1->elemento->dato1 < s2->elemento->dato1) {
			agregar(res, s1->elemento->dato1, s1->elemento->dato2);
			s1->elemento = s1->elemento->sig;
		}
	}
	while (s1->elemento != NULL) {
		agregar(res, s1->elemento->dato1, s1->elemento->dato2);
		s1->elemento = s1->elemento->sig;
	}
	while (s2->elemento != NULL) {
		s2->elemento = s2->elemento->sig;
	}
	return res;
}

bool contenidoEn(MultisetInt s1, MultisetInt s2) {
	while (s1->elemento != NULL && s2->elemento != NULL && s1->elemento->dato1 == s2->elemento->dato1) {
		s1->elemento = s1->elemento->sig;
		s2->elemento = s2->elemento->sig;
	}
	return s1->elemento == NULL && s2->elemento == NULL;
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
	while (s->elemento != NULL) {
		agregar(res, s->elemento->dato1, s->elemento->dato2);
		s->elemento = s->elemento->sig;
	}
	return res;
}

#endif