#include "DiccionarioInt.h"
#include "Definiciones.h"
#ifdef DICCIONARIO_INT_IMP

struct _cabezalDiccionarioInt {
	int cantidad;
	NodoListaInt** hashArray;
	unsigned int esperados;
};

DiccionarioInt crearDiccionarioInt(unsigned int esperados) {
	_cabezalDiccionarioInt* res = new _cabezalDiccionarioInt;
	res->hashArray = new NodoListaInt*[esperados];
	res->cantidad = 0;
	res->esperados = esperados;
	for (unsigned int i = 0; i < esperados; i++) {
		res->hashArray[i] = NULL;
	}
	return res;
}

//PRE: --
//POS: devuelve la posicion del hash a ingresar en el array
int hashFunctionDicc(int e, int esperados) {
	int retorno = e % esperados;
	return abs(retorno);
}

void agregar(DiccionarioInt& d, int e) {
	int pos = hashFunctionDicc(e, d->esperados);
	if(!(pertenece(d,e))){
		if (d->hashArray[pos] == NULL) {
			NodoListaInt* nuevo = new NodoListaInt;
			nuevo->dato = e;
			nuevo->sig = NULL;
			d->hashArray[pos] = nuevo;
		}
		else{
			NodoListaInt* iter = d->hashArray[pos];
			while (iter->sig != NULL) {
				iter = iter->sig;
			}
			NodoListaInt* nuevo = new NodoListaInt;
			nuevo->dato = e;
			nuevo->sig = NULL;
			iter->sig = nuevo;
		}
		d->cantidad++;
	}
}

void borrar(DiccionarioInt& d, int e) {
	int pos = hashFunctionDicc(e, d->esperados);
	
	if (pertenece(d,e) && d->hashArray[pos] != NULL) {
		NodoListaInt* aBorrar = NULL;
		NodoListaInt* iter = d->hashArray[pos];
		if (d->hashArray[pos]->dato == e) {
			aBorrar = d->hashArray[pos];
			d->hashArray[pos] = d->hashArray[pos]->sig;
		}
		else{
			while (iter->sig != NULL) {
				if (iter->sig->dato == e) {
					aBorrar = iter->sig;
					iter->sig = iter->sig->sig;
				}
				else {
					iter = iter->sig;
				}
			}
		}
		delete aBorrar;
		aBorrar = NULL;
		d->cantidad--;
	}
}

bool pertenece(DiccionarioInt d, int e) {
	bool res = false;
	int pos = hashFunctionDicc(e, d->esperados);
	if (d->hashArray[pos] != NULL) {
		NodoListaInt* iter = d->hashArray[pos];
		while (iter != NULL) {
			if (iter->dato == e) {
				return true;
			}
			else{
				iter = iter->sig;
			}
		}
	}
	return res;
}

int elemento(DiccionarioInt d) {
	assert(!esVacio(d));
	for (unsigned int i = 0; i < d->esperados; i++) {
		if (d->hashArray[i] != NULL) {
			return d->hashArray[i]->dato;
		}
	}
	return NULL;
}

bool esVacio(DiccionarioInt d) {
	return d->cantidad == 0;
}

unsigned int cantidadElementos(DiccionarioInt d) {
	return d->cantidad;
}

DiccionarioInt clon(DiccionarioInt d) {
	_cabezalDiccionarioInt* res = crearDiccionarioInt(d->esperados);
	for (unsigned int i = 0; i < d->esperados; i++) {
		NodoListaInt* iter = d->hashArray[i];
		while (iter != NULL){
			agregar(res, iter->dato);
			iter = iter->sig;
		}
	}
	return res;
}

void destruir(DiccionarioInt& d) {
	for (unsigned int i = 0; i < d->esperados; i++) {
		while (d->hashArray[i] != NULL) {
			NodoListaInt* aBorrar = d->hashArray[i];
			d->hashArray[i] = d->hashArray[i]->sig;
			delete aBorrar;
			aBorrar = NULL;
		}
	}
	delete d;
	d = NULL;
}


#endif