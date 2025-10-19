#include "Cola.h"

//Crea una cola con un tipo y quantum
Cola::Cola(int tipo_, int quantum_) : tipo(tipo_), quantum(quantum_) {}

//Agrega proceso a la cola
void Cola::agregar(Proceso* p) {procesos.push(p);}

//Verifica si hay procesos
bool Cola::vacia() const {return procesos.empty();}

//Devuelve proceso al frente
Proceso* Cola::frente() {return procesos.front();}

//Saca proceso al frente
void Cola::quitar() {procesos.pop();}

//Devuelve tipo de la cola
int Cola::getTipo() const { return tipo; }

//Devuelve quantum de la cola
int Cola::getQuantum() const { return quantum; }
