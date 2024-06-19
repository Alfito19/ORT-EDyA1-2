#include "SetInt.h"
#include "Definiciones.h"

#ifdef SET_INT_IMP

struct _cabezalSetInt {
	int cantidad;
	NodoListaInt* elemento;
};


SetInt crearSetInt(){
	_cabezalSetInt* res = new _cabezalSetInt;
	res->cantidad = 0;
	res->elemento = NULL;
	return res;
}

void agregar(SetInt& s, int e) {
	NodoListaInt* nuevo = new NodoListaInt;
	nuevo->dato = e;
	nuevo->sig = NULL;
	bool yaIngresado = false;
	if (s->elemento == NULL) {
		s->elemento = nuevo;
		s->cantidad++;
	}
	else {
		NodoListaInt* iter = s->elemento;
		NodoListaInt* anterior = NULL;
		while (iter != NULL) {
			if (iter->dato == e){
				yaIngresado = true;
			}
			anterior = iter;
			iter = iter->sig;
		}
		if (!yaIngresado) {
			anterior->sig = nuevo;
			s->cantidad++;
		}
		else delete nuevo;
	}
}

void borrar(SetInt& s, int e) {
	NodoListaInt* iter = s->elemento;
	NodoListaInt* anterior = NULL;

	while (iter != NULL) {
		if (iter->dato == e) {
			if (anterior == NULL) {
				s->elemento = iter->sig;
			}
			else {
				anterior->sig = iter->sig;
			}
			delete iter;
			s->cantidad--;
			return;
		}
		anterior = iter;
		iter = iter->sig;
	}
}

bool pertenece(SetInt s, int e) {
	NodoListaInt* iter = s->elemento;
	while (iter != NULL) {
		if (iter->dato == e) {
			return true;
		}
		iter = iter->sig;
	}
	return false;
}

SetInt unionConjuntos(SetInt s1, SetInt s2) {
	SetInt res = crearSetInt();
	NodoListaInt* iter = s1->elemento;
	while (iter != NULL) {
		agregar(res, iter->dato);
		iter = iter->sig;
	}
	iter = s2->elemento;
	while (iter != NULL) {
		agregar(res, iter->dato);
		iter = iter->sig;
	}
	return res;
}

SetInt interseccionConjuntos(SetInt s1, SetInt s2) {
	SetInt res = crearSetInt();
	NodoListaInt* iter = s1->elemento;
	while (iter != NULL) {
		if (pertenece(s2, iter->dato)) {
			agregar(res, iter->dato);
		}
		iter = iter->sig;
	}
	return res;
}

SetInt diferenciaConjuntos(SetInt s1, SetInt s2) {
	SetInt res = crearSetInt();
	NodoListaInt* iter = s1->elemento;
	while (iter != NULL) {
		if (!pertenece(s2, iter->dato)) {
			agregar(res, iter->dato);
		}
		iter = iter->sig;
	}
	return res;
}

bool contenidoEn(SetInt s1, SetInt s2) {
	NodoListaInt* iter = s1->elemento;
	while (iter != NULL) {
		if (!pertenece(s2, iter->dato)) {
			return false;
		}
		iter = iter->sig;
	}
	return true;
}

int elemento(SetInt s) {
	return s->elemento->dato;
}

bool esVacio(SetInt s) {
	return s->elemento == NULL;
}

unsigned int cantidadElementos(SetInt s) {
	return s->cantidad;
}

void destruir(SetInt& s) {
	while (s->elemento != NULL) {
		NodoListaInt* aBorrar = s->elemento;
		s->elemento = s->elemento->sig;
		delete aBorrar;
		aBorrar = NULL;
	}
	delete s;
	s = NULL;
}

SetInt clon(SetInt s) {
	_cabezalSetInt* res = crearSetInt();
	NodoListaInt* iter = s->elemento;
	while (iter != NULL) {
		agregar(res, iter->dato);
		iter = iter->sig;
	}
	return res;
}

#endif