#include "TablaIntInt.h"
#include "Definiciones.h"
#ifdef TABLA_INT_INT_IMP

struct _cabezalTablaIntInt {
	int cantidad;
	NodoListaIntDobleDato** hashArray;
	unsigned int esperados;
};

TablaIntInt crearTablaIntInt(unsigned int esperados) {
	_cabezalTablaIntInt* res = new _cabezalTablaIntInt;
	res->hashArray = new NodoListaIntDobleDato * [esperados];
	res->cantidad = 0;
	res->esperados = esperados;
	for (unsigned int i = 0; i < esperados; i++) {
		res->hashArray[i] = NULL;
	}
	return res;
}

//PRE: --
//POS: devuelve la posicion del hash a ingresar en el array
int hashFunctionTabla(int e, int esperados) {
	int retorno = e % esperados;
	return abs(retorno);
}

void agregar(TablaIntInt& t, int d, int r) {
	int pos = hashFunctionTabla(d, t->esperados);
	NodoListaIntDobleDato* iter = t->hashArray[pos];
	while (iter != NULL && iter->dato1 != d)
		iter = iter->sig;
	if (iter == NULL) {
		NodoListaIntDobleDato* nuevo = new NodoListaIntDobleDato;
		nuevo->dato1 = d;
		nuevo->dato2 = r;
		nuevo->sig = t->hashArray[pos];
		t->hashArray[pos] = nuevo;
		t->cantidad++;
	}
	else iter->dato2 = r;
	
}

bool estaDefinida(TablaIntInt t, int d) {
	int pos = hashFunctionTabla(d, t->esperados);
	while (t->hashArray[pos] != NULL && t->hashArray[pos]->dato1 != d)
		t->hashArray[pos] = t->hashArray[pos]->sig;
	return t->hashArray[pos] != NULL;
}

int recuperar(TablaIntInt t, int d) {
	assert(estaDefinida(t,d));
	int pos = hashFunctionTabla(d, t->esperados);
	NodoListaIntDobleDato* lista = t->hashArray[pos];
	while (lista->dato1 != d)
		lista = lista->sig;
	return lista->dato2;

}

void borrar(TablaIntInt& t, int d) {
	int pos = hashFunctionTabla(d, t->esperados);
	NodoListaIntDobleDato* iter = t->hashArray[pos];
	while (iter != NULL && iter->dato1 != d)
		iter = iter->sig;
	if (iter != NULL) {
		NodoListaIntDobleDato* aBorrar = iter;
		iter = iter->sig;
		delete aBorrar;
		aBorrar = NULL;
	}
}

int elemento(TablaIntInt t) {
	assert(!esVacia(t));
	for (unsigned int i = 0; i < t->esperados; i++) {
		if (t->hashArray[i] != NULL) {
			return t->hashArray[i]->dato1;
		}
	}
	return NULL;
}

bool esVacia(TablaIntInt t) {
	return t->cantidad == 0;
}

unsigned int cantidadElementos(TablaIntInt t) {
	return t->cantidad;
}

void destruir(TablaIntInt& t) {
	for (unsigned int i = 0; i < t->esperados; i++) {
		while (t->hashArray[i] != NULL) {
			NodoListaIntDobleDato* aBorrar = t->hashArray[i];
			t->hashArray[i] = t->hashArray[i]->sig;
			delete aBorrar;
			aBorrar = NULL;
		}
	}
	delete t;
	t = NULL;
}

TablaIntInt clon(TablaIntInt t) {
	_cabezalTablaIntInt* tabla = crearTablaIntInt(t->esperados);
	for(unsigned int i = 0;i < t->esperados;i++){
		NodoListaIntDobleDato* iter = t->hashArray[i];
		while (iter != NULL) {
			agregar(tabla, t->hashArray[i]->dato1, t->hashArray[i]->dato2);
			iter = iter->sig;
		}
	}
	return tabla;
}

#endif