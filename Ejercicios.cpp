#include "Ejercicios.h"

//PRE
//POS
void EnListarAux(ListaOrdInt& res, NodoABInt* a) {
	if (a != NULL) {
		agregar(res, a->dato);
		EnListarAux(res, a->der);
		EnListarAux(res, a->izq);
	}
	
}

ListaOrdInt Enlistar(NodoABInt* a)
{
	ListaOrdInt res = crearListaOrdInt();
	EnListarAux(res, a);
	return res;
}

ListaOrdInt UnionListaOrd(ListaOrdInt l1, ListaOrdInt l2)
{
	ListaOrdInt res = crearListaOrdInt();
	while (!esVacia(l1)) {
		int minVal = minimo(l1);
		agregar(res, minVal);
		borrarMinimo(l1);
	}
	while (!esVacia(l2)) {
		int minVal = minimo(l2);
		agregar(res, minVal);
		borrarMinimo(l2);
	}
	return res;
}

bool EstaContenida(PilaInt p1, PilaInt p2)
{
	if (esVacia(p2)) return esVacia(p1);
	if(cantidadElementos(p1) < cantidadElementos(p2)){
		return false;
	}
	PilaInt p1Aux = p1;
	while (!esVacia(p1Aux)) {
		PilaInt p2Aux = p2;
		bool esta = false;
		while (!esta || !esVacia(p2Aux)) {
			if (top(p1Aux) == top(p2Aux)) {
				pop(p1Aux);
				esta = true;
			}
			else pop(p2Aux);
		}
		pop(p1Aux);
		if (esVacia(p2Aux)) {
			delete p2Aux;
			delete p1Aux;
			return false;
		}
	}
	return true;
}


ListaOrdInt ObtenerRepetidos(MultisetInt m) 
{
	//IMPLEMENTAR SOLUCION
	return NULL;
}

MultisetInt Xor(MultisetInt m1, MultisetInt m2)
{
	//IMPLEMENTAR SOLUCION
	return NULL;
}

ColaPrioridadInt MenorPrioridad(ColaPrioridadInt c) {
	//IMPLEMENTAR SOLUCION
	return NULL;
}

