#ifndef COLA_H
#define COLA_H

#include <queue>
#include "Proceso.h"

class Cola {
private:
    int tipo;     // 1 = RR(3), 2 = RR(5), 3 = FCFS
    int quantum;
    queue<Proceso*> procesos;

public:
    Cola(int tipo_, int quantum_);
    void agregar(Proceso* p);
    bool vacia() const;
    Proceso* frente();
    void quitar();
    int getTipo() const;
    int getQuantum() const;
};

#endif
