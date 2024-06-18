#include "TablaIntString.h"
#include "Definiciones.h"

#ifdef TABLA_INT_STRING_IMP
struct NodoListaIntString
{
	int dato1;
	const char* dato2;
	NodoListaIntString* sig;
};
struct _cabezalTablaIntString {
	int cantidad;
	NodoListaIntString** hashArray;
	unsigned int esperados;
};



TablaIntString crearTablaIntString(unsigned int esperados) {
	_cabezalTablaIntString* res = new _cabezalTablaIntString;
	res->hashArray = new NodoListaIntString* [esperados];
	res->cantidad = 0;
	res->esperados = esperados;
	for (unsigned int i = 0; i < esperados; i++) {
		res->hashArray[i] = NULL;
	}
	return res;
}

//PRE: --
//POS: devuelve la posicion del hash a ingresar en el array
int hashFunctionTablaString(int e, int esperados) {
	int retorno = e % esperados;
	return abs(retorno);
}

void agregar(TablaIntString& t, int d, const char* r) {
	int pos = hashFunctionTablaString(d, t->esperados);
	NodoListaIntString* iter = t->hashArray[pos];
	while (iter != NULL && iter->dato1 != d)
		iter = iter->sig;
	if (iter == NULL) {
		NodoListaIntString* nuevo = new NodoListaIntString;
		nuevo->dato1 = d;
		nuevo->dato2 = r;
		nuevo->sig = t->hashArray[pos];
		t->hashArray[pos] = nuevo;
		t->cantidad++;
	}
	else iter->dato2 = r;
}

bool estaDefinida(TablaIntString t, int d) {
	int pos = hashFunctionTablaString(d, t->esperados);
	NodoListaIntString* iter = t->hashArray[pos];
	while (iter != NULL && iter->dato1 != d)
		iter = iter->sig;
	return iter != NULL;
}

const char* recuperar(TablaIntString t, int d) {
	assert(estaDefinida(t, d));
	int pos = hashFunctionTablaString(d, t->esperados);
	NodoListaIntString* lista = t->hashArray[pos];
	while (lista->dato1 != d)
		lista = lista->sig;
	return lista->dato2;
}

void borrar(TablaIntString& t, int d) {
	int pos = hashFunctionTablaString(d, t->esperados);
	NodoListaIntString* iter = t->hashArray[pos];
	while (iter != NULL && iter->dato1 != d)
		iter = iter->sig;
	if (iter != NULL) {
		NodoListaIntString* aBorrar = iter;
		iter = iter->sig;
		delete aBorrar;
		aBorrar = NULL;
		t->cantidad--;
	}
}

int elemento(TablaIntString t) {
	assert(!esVacia(t));
	for (unsigned int i = 0; i < t->esperados; i++) {
		if (t->hashArray[i] != NULL) {
			return t->hashArray[i]->dato1;
		}
	}
	return NULL;
}

bool esVacia(TablaIntString t) {
	return t->cantidad == 0;
}

unsigned int cantidadElementos(TablaIntString t) {
	return t->cantidad;
}

void destruir(TablaIntString& t) {
	for (unsigned int i = 0; i < t->esperados; i++) {
		while (t->hashArray[i] != NULL) {
			NodoListaIntString* aBorrar = t->hashArray[i];
			t->hashArray[i] = t->hashArray[i]->sig;
			delete aBorrar;
			aBorrar = NULL;
		}
	}
	delete t;
	t = NULL;
}

TablaIntString clon(TablaIntString t) {
	_cabezalTablaIntString* tabla = crearTablaIntString(t->esperados);
	for (unsigned int i = 0; i < t->esperados; i++) {
		NodoListaIntString* iter = t->hashArray[i];
		while (iter != NULL) {
			agregar(tabla, t->hashArray[i]->dato1, t->hashArray[i]->dato2);
			iter = iter->sig;
		}
	}
	return tabla;
}

#endif