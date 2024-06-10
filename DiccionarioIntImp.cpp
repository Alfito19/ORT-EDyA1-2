#include "DiccionarioInt.h"
#include "Definiciones.h"
#ifdef DICCIONARIO_INT_IMP

struct _cabezalDiccionarioInt {
	int cantidad;
	NodoABInt* elem;
};

DiccionarioInt crearDiccionarioInt(unsigned int esperados) {
	_cabezalDiccionarioInt* res = new _cabezalDiccionarioInt;
	res->cantidad = 0;
	res->elem = NULL;
	return res;
}

void agregar(DiccionarioInt& d, int e) {
	if (d->elem != NULL) {
		agregarABB(d->elem, e, d);
	}
	else{
		NodoABInt* nuevo = new NodoABInt;
		nuevo->dato = e;
		nuevo->izq = nuevo->der = NULL;
		d->elem = nuevo;
		d->cantidad++;
	}
}

// PRE: -
// POS: agrega el elemento e en el ABB
void agregarABB(NodoABInt*& abb, int e, DiccionarioInt& d) {
	if (abb == NULL) {
		NodoABInt* nuevo = new NodoABInt;
		nuevo->dato = e;
		nuevo->izq = nuevo->der = NULL;
		d->cantidad++;
	}
	else if (e < abb->dato) {
		agregarABB(abb->izq, e, d);
	}
	else if (e > abb->dato) {
		agregarABB(abb->der, e, d);
	}
}

void borrar(DiccionarioInt& d, int e) {
	if (d->elem != NULL) {
		borrarABB(d->elem, e, d);
	}
}

// PRE: -
// POS: borra el elemento del diccionario
//        Si no encuentra no tiene efecto
void borrarABB(NodoABInt* abb, int e, DiccionarioInt& d) {
	if(abb != NULL){
		if (e < abb->dato) {
			borrarABB(abb->izq, e, d);
		}
		else if (e > abb->dato) {
			borrarABB(abb->der, e, d);
		}
		else{
			if (abb->der == NULL) {
				NodoABInt* aBorrar = abb;
				abb = abb->izq;
				delete aBorrar;
				aBorrar = NULL;
				d->cantidad--;
			}
			else if (abb->izq == NULL) {
				NodoABInt* aBorrar = abb;
				abb = abb->der;
				delete aBorrar;
				aBorrar = NULL;
				d->cantidad--;
			}
			else {
				NodoABInt* aBorrar = abb;
				NodoABInt* derecha = abb->der;
				abb = abb->izq;
				NodoABInt* iter = abb;
				while (iter->der != NULL) {
					iter = iter->der;
				}
				iter->der = derecha;
				delete aBorrar;
				aBorrar = NULL;
				d->cantidad--;
			}
		}
	}
}

bool pertenece(DiccionarioInt d, int e) {
	bool res = false;
	if (d != NULL) {
		if (e == d->elem->dato) {
			res = true;
		}
		else {
			if (d->elem->dato > e) {
				res = perteneceABB(d->elem->izq, e);
			}
			else {
				res = perteneceABB(d->elem->der, e);
			}
		}
	}
	return res;
}

// PRE: -
// POS: retorna true si el elemento e se encuentra en el ABB
bool perteneceABB(NodoABInt* abb, int e) {
	bool res = false;
	if (abb != NULL) {
		if (e == abb->dato) {
			res = true;
		}
		else {
			if (abb->dato > e) {
				res = perteneceABB(abb->izq, e);
			}
			else {
				res = perteneceABB(abb->der, e);
			}
		}
	}
	return res;
}

int elemento(DiccionarioInt d) {
	return d->elem->dato;
}

bool esVacio(DiccionarioInt d) {
	return d->cantidad == 0;
}

unsigned int cantidadElementos(DiccionarioInt d) {
	return d->cantidad;
}

DiccionarioInt clon(DiccionarioInt d) {
	_cabezalDiccionarioInt* res = crearDiccionarioInt(0);
	res->cantidad = 0;
	res->elem = clonABB(d->elem, res);
	return NULL;
}

// PRE: -
// POS: retorna una copia del ABB sin compartir memoria
NodoABInt* clonABB(NodoABInt*& abb, DiccionarioInt clon) {
	if(abb->izq != NULL && abb->der != NULL){
		clonABB(abb->der, clon);
		clonABB(abb->izq, clon);
	}
	else if(abb->izq != NULL && abb->der == NULL){
		clonABB(abb->izq, clon);
	}
	else if (abb->izq == NULL && abb->der != NULL) {
		clonABB(abb->der, clon);
	}
	agregarABB(abb, abb->dato, clon);
}

void destruir(DiccionarioInt& d) {
	if (d->elem != NULL) {
		borrarTodoABB(d->elem);
	}
	delete d;
	d = NULL;
}

// PRE: -
// POS: borra todo el ABB
void borrarTodoABB(NodoABInt*& e) {
	if (e != NULL) {
		borrarTodoABB(e->der);
		borrarTodoABB(e->izq);
	}
	delete e;
	e = NULL;
}

#endif