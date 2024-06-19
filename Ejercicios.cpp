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
	if (cantidadElementos(p1) > cantidadElementos(p2)) {
		return false;
	}
	PilaInt p1Aux = clon(p1);
	PilaInt p2Aux = clon(p2);
	PilaInt pilaElems = crearPilaInt();

	while (!esVacia(p1Aux)) {
		bool esta = false;
		while ((!esta) && !esVacia(p2Aux)) {
			if (top(p1Aux) == top(p2Aux)) {
				pop(p1Aux);
				pop(p2Aux);
				esta = true;
			}
			else {
				push(pilaElems, top(p2Aux));
				pop(p2Aux);
			}
		}
		if (esVacia(p2Aux) && !esta) {
			destruir(p2Aux);
			destruir(pilaElems);
			destruir(p1Aux);
			return false;
		}
		else {
			while (!esVacia(pilaElems)) {
				push(p2Aux, top(pilaElems));
				pop(pilaElems);
			}
		}
	}
	return true;
}


ListaOrdInt ObtenerRepetidos(MultisetInt m) 
{
	ListaOrdInt res = crearListaOrdInt();
	MultisetInt multiClon = clon(m);
	while (!esVacio(multiClon)) {
		int elem = elemento(multiClon);
		borrar(multiClon, elem);
		if (pertenece(multiClon, elem) && !existe(res,elem)) agregar(res, elem);
	}
	return res;
}

MultisetInt Xor(MultisetInt m1, MultisetInt m2)
{
	MultisetInt res = crearMultisetInt();
	MultisetInt m1Menosm2 = diferenciaConjuntos(m1, m2);
	MultisetInt m2Menosm1 = diferenciaConjuntos(m2, m1);
	res = unionConjuntos(m1Menosm2, m2Menosm1);
	return res;
}

ColaPrioridadInt MenorPrioridad(ColaPrioridadInt c) {
	if (esVacia(c)) return crearColaPrioridadInt(0);
	ColaPrioridadInt clonColaPrio = clon(c);
	int minimoPrio = principioPrioridad(clonColaPrio);
	while (!esVacia(clonColaPrio)) {
		if (principioPrioridad(clonColaPrio) < minimoPrio) {
			minimoPrio = principioPrioridad(clonColaPrio);
		}
		desencolar(clonColaPrio);
	}

	destruir(clonColaPrio);
	clonColaPrio = clon(c);
	int countMinimoPrio = 0;
	while (!esVacia(clonColaPrio)) {
		if (principioPrioridad(clonColaPrio) == minimoPrio) {
			countMinimoPrio++;
		}
		desencolar(clonColaPrio);
	}

	destruir(clonColaPrio);
	ColaPrioridadInt res = crearColaPrioridadInt(countMinimoPrio);
	clonColaPrio = clon(c);
	while (!esVacia(clonColaPrio)) {
		if (principioPrioridad(clonColaPrio) == minimoPrio) {
			encolar(res, principio(clonColaPrio), principioPrioridad(clonColaPrio));
		}
		desencolar(clonColaPrio);
	}
	destruir(clonColaPrio);

	return res;
}

