#include "TablaIntInt.h"
#include "Definiciones.h"
#ifdef TABLA_INT_INT_IMP

struct _cabezalTablaIntInt {
	int cantidad;
	NodoListaIntDobleDato** hashArray;
	int esperados;
};

TablaIntInt crearTablaIntInt(unsigned int esperados) {
	_cabezalTablaIntInt* res = new _cabezalTablaIntInt;
	res->hashArray = new NodoListaIntDobleDato * [esperados];
	res->cantidad = 0;
	res->esperados = esperados;
	for (int i = 0; i < esperados; i++) {
		res->hashArray[i] = NULL;
	}
	return res;
}

//PRE: --
//POS: devuelve la posicion del hash a ingresar en el array
int hashFunction(int e, int esperados) {
	int retorno = e % esperados;
	return abs(retorno);
}

void agregar(TablaIntInt& t, int d, int r) {
	int pos = hashFunction(d, t->esperados);
	while (t->hashArray[pos] != NULL && t->hashArray[pos]->dom != d)
		t->hashArray[pos] = t->hashArray[pos]->sig;
	if (t->hashArray[pos] == NULL) {
		NodoListaIntDobleDato* nuevo = new NodoListaIntDobleDato;
		nuevo->dato1 = d;
		nuevo->dato2 = r;
		nuevo->sig = t->hashArray[pos];
		t->hashArray[pos] = nuevo;
		t->cantidad++;
	}
	else t->hashArray[pos]->dato2= r;
	
}

bool estaDefinida(TablaIntInt t, int d) {
	int pos = hashFunction(d, t->esperados);
	while (t->hashArray[pos] != NULL && t->hashArray[pos]->dato1 != d)
		t->hashArray[pos] = t->hashArray[pos]->sig;
	return t->hashArray[pos] != NULL;
}

int recuperar(TablaIntInt t, int d) {
	assert(estaDefinida(d, t));
	int posicion = hash(d) % (t->cota);
	nodoHash* lista = t->tabla[posicion];
	while (lista->dom != d)
		lista = lista->sig;
	return lista->ran;

}

void borrar(TablaIntInt& t, int d) {
	// NO IMPLEMENTADO
}

int elemento(TablaIntInt t) {
	// NO IMPLEMENTADO
	return 0;
}

bool esVacia(TablaIntInt t) {
	return t->cantidad == 0
}

unsigned int cantidadElementos(TablaIntInt t) {
	// NO IMPLEMENTADO
	return 0;
}

void destruir(TablaIntInt& t) {
	// NO IMPLEMENTADO
}

TablaIntInt clon(TablaIntInt t) {
	// NO IMPLEMENTADO
	return NULL;
}

#endif