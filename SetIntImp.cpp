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
	}
	else {
		NodoListaInt* iter = s->elemento;
		while (iter->dato > e || iter->sig != NULL) {
			if (iter->dato == e){
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

void borrar(SetInt& s, int e) {
	NodoListaInt* iter = s->elemento;
	while (iter->dato > e || iter->sig != NULL) {
		if (iter->dato == e) {
			NodoListaInt* aBorrar = iter;
			iter = iter->sig;
			delete aBorrar;
			aBorrar = NULL;
			s->cantidad--;
		}
		iter = iter->sig;
	}
}

bool pertenece(SetInt s, int e) {
	while (s->elemento != NULL) {
		if (s->elemento->dato == e) {
			return true;
		}
		s->elemento = s->elemento->sig;
	}
	return false;
}

SetInt unionConjuntos(SetInt s1, SetInt s2) {
	_cabezalSetInt* res = crearSetInt();
	while (s1->elemento != NULL) {
		agregar(res, s1->elemento->dato);
		s1->elemento = s1->elemento->sig;
	}
	while (s2->elemento != NULL) {
		agregar(res, s2->elemento->dato);
		s2->elemento = s2->elemento->sig;
	}
	return res;
}

SetInt interseccionConjuntos(SetInt s1, SetInt s2) {
	_cabezalSetInt* res = crearSetInt();
	while (s1->elemento != NULL && s2->elemento != NULL) {
		if (s1->elemento->dato == s2->elemento->dato) {
			agregar(res, s1->elemento->dato);
			s1->elemento = s1->elemento->sig;
			s2->elemento = s2->elemento->sig;
		}
		else if (s1->elemento->dato > s2->elemento->dato) {
			s2->elemento = s2->elemento->sig;
		}
		else if (s1->elemento->dato < s2->elemento->dato) {
			s1->elemento = s1->elemento->sig;
		}
	}
	return res;
}

SetInt diferenciaConjuntos(SetInt s1, SetInt s2) {
	_cabezalSetInt* res = crearSetInt();
	while (s1->elemento != NULL && s2->elemento != NULL) {
		if (s1->elemento->dato == s2->elemento->dato) {
			s1->elemento = s1->elemento->sig;
			s2->elemento = s2->elemento->sig;
		}
		else if (s1->elemento->dato > s2->elemento->dato) {
			s2->elemento = s2->elemento->sig;
		}
		else if (s1->elemento->dato < s2->elemento->dato) {
			agregar(res, s1->elemento->dato);
			s1->elemento = s1->elemento->sig;
		}
	}
	while (s1->elemento != NULL) {
		agregar(res, s1->elemento->dato);
		s1->elemento = s1->elemento->sig;
	}
	while (s2->elemento != NULL) {
		s2->elemento = s2->elemento->sig;
	}
	return res;
}

bool contenidoEn(SetInt s1, SetInt s2) {
	while (s1->elemento != NULL && s2->elemento != NULL && s1->elemento->dato == s2->elemento->dato) {
		s1->elemento = s1->elemento->sig;
		s2->elemento = s2->elemento->sig;
	}
	return s1->elemento == NULL && s2->elemento == NULL;
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
	while (s->elemento != NULL) {
		agregar(res, s->elemento->dato);
		s->elemento = s->elemento->sig;
	}
	return res;
}

#endif