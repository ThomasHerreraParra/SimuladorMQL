#ifndef PLANIFICADOR_MLQ_H
#define PLANIFICADOR_MLQ_H

#include <vector>
#include <string>
#include "Cola.h"
#include "Proceso.h"

class PlanificadorMLQ {
private:
    std::vector<Proceso*> procesos;     // Procesos leídos del archivo
    std::vector<Proceso*> pendientes;   // Procesos que aún no han llegado (AT > tiempo)
    std::vector<Proceso*> terminados;   // Procesos completados

    Cola cola1; // RR(3)
    Cola cola2; // RR(5)
    Cola cola3; // FCFS
    int tiempo;

    void ejecutarCola(Cola &cola);
    bool todasColasVacias();

    void moverLlegadas(); // 👈 nueva función para mover los que ya llegaron

public:
    PlanificadorMLQ();

    void leerArchivo(const std::string& nombreArchivo);
    void cargarColas();
    void ejecutar();
    void generarSalida(const std::string& nombreArchivo);
};

#endif

