#include "PlanificadorMLQ.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <algorithm>
using namespace std;

//Elimina espacios, saltos de linea, tabulaciones
static inline std::string trim(const std::string &s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) return "";
    size_t end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}

//constructor de colas, cola 1 RR(3), cola 2 RR(5), cola 3 FCFS
PlanificadorMLQ::PlanificadorMLQ()
    : cola1(1, 3), cola2(2, 5), cola3(3, 0), tiempo(0) {}

//Lectura archivo .txt
void PlanificadorMLQ::leerArchivo(const string& nombreArchivo) {
    ifstream file(nombreArchivo);
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo de entrada: " << nombreArchivo << "\n";
        return;
    }

    string linea;
    while (getline(file, linea)) {
        if (linea.empty() || linea[0] == '#') continue; //Ignora los comentarios y las lineas vacias

        vector<string> campos;
        string campo;
        stringstream ss(linea);
        while (getline(ss, campo, ';')) {
            campos.push_back(trim(campo)); //reconoce el campo por medio del punto y coma (;)
        }

        if (campos.size() < 5) continue;

        string id = campos[0];
        int bt = stoi(campos[1]); //Al primer campo le asigan el BT
        int at = stoi(campos[2]); //Al segundo campo le asigan el AT
        int q  = stoi(campos[3]); //Al tercero campo le asigan la cola (q)
        int pr = stoi(campos[4]); //Al cuarto campo le asigan la prioridad

        Proceso* p = new Proceso(id, bt, at, q, pr); //Crea un puntero proceso con cada uno de los campos
        procesos.push_back(p);
    }
    file.close();

    // Ordenar por tiempo de llegada
    sort(procesos.begin(), procesos.end(), [](Proceso* a, Proceso* b) {
        return a->getArrivalTime() < b->getArrivalTime();
    });

    // copiar a pendientes
    pendientes = procesos;
}

// CARGAR COLAS (VACÍO AL INICIO)
void PlanificadorMLQ::cargarColas() {
    // No cargamos de inmediato: se hace dinámicamente
}

// Mueve los procesos desde la lista de pendientes hacia su cola correspondiente cuando su tiempo de llegada (AT) ya ha pasado o es igual al tiempo actual
void PlanificadorMLQ::moverLlegadas() {
    auto it = pendientes.begin();
    while (it != pendientes.end()) {
        Proceso* p = *it;
        if (p->getArrivalTime() <= tiempo) {
            if (p->getQueue() == 1) cola1.agregar(p);
            else if (p->getQueue() == 2) cola2.agregar(p);
            else cola3.agregar(p);
            it = pendientes.erase(it);
        } else {
            ++it;
        }
    }
}

// Verifica si ya no hay procesos en las colas
bool PlanificadorMLQ::todasColasVacias() {
    return cola1.vacia() && cola2.vacia() && cola3.vacia() && pendientes.empty();
}

// Ejecucion del planificador
void PlanificadorMLQ::ejecutar() {
    tiempo = 0;

    while (!todasColasVacias()) { //Se ejecuta mientras las colas no esten vacias
        moverLlegadas();

        // Si no hay mas procesos listos para ejecutar, salta al próximo proceso que llegue
        if (cola1.vacia() && cola2.vacia() && cola3.vacia()) {
            if (!pendientes.empty()) {
                tiempo = pendientes.front()->getArrivalTime();
                moverLlegadas();
            }
        }

        if (!cola1.vacia()) ejecutarCola(cola1); //Mientras la cola 1 no este vacia se ejecuta
        else if (!cola2.vacia()) ejecutarCola(cola2); //Mientras la cola 2 no este vacia se ejecuta
        else if (!cola3.vacia()) ejecutarCola(cola3); //Mientras la cola 3 no este vacia se ejecuta
    }
}

// Ejecuta el proceso de la cola
void PlanificadorMLQ::ejecutarCola(Cola &cola) {
    Proceso* p = cola.frente();
    cola.quitar();

    int quantum = (cola.getTipo() == 3) ? p->getRemainingTime() : cola.getQuantum();
    int ejecutar = min(quantum, p->getRemainingTime());

    // Si el la primera vez que se ejecuta el proceso, guarda ese tiempo como RT (a partir de 0)
    if (!p->isStarted()) {
        p->setResponseTime(tiempo);
        p->setStarted(true);
    }

    // Ejecuta durante el quantum o hasta terminar
    tiempo += ejecutar;
    p->setRemainingTime(p->getRemainingTime() - ejecutar);

    //Mover procesos que hayan llegado durante este quantum
    moverLlegadas();

    // Si terminó
    if (p->getRemainingTime() == 0) {
        p->setCompletionTime(tiempo);
        p->setTurnAroundTime(p->getCompletionTime() - p->getArrivalTime()); // TAT = CT - AT
        p->setWaitingTime(p->getTurnAroundTime() - p->getBurstTime());      // WT = TAT - BT
        terminados.push_back(p);
    } else {
        // Si no terminó, regresa a la cola
        cola.agregar(p);
    }
}

// Genera el archivo .txt de salida
void PlanificadorMLQ::generarSalida(const string& nombreArchivo) {
    //Ordena los procesos por etiqueta
    sort(terminados.begin(), terminados.end(), [](Proceso* a, Proceso* b){
        return a->getId() < b->getId();
    });

    ofstream file(nombreArchivo);
    if (!file.is_open()) {
        cerr << "Error al crear el archivo de salida.\n";
        return;
    }

    //Etiquetas en el archivo de salida .txt
    file << "# archivo: " << nombreArchivo << "\n";
    file << "# etiqueta; BT; AT; Q; Pr; WT; CT; RT; TAT\n";

    double totalWT = 0, totalCT = 0, totalRT = 0, totalTAT = 0;
    int n = terminados.size();

    //Ingresa en el .txt los valores obtenidos de cada puntero del vector (procesos terminados)
    for (auto &p : terminados) {
        file << p->getId() << "; "
             << p->getBurstTime() << "; "
             << p->getArrivalTime() << "; "
             << p->getQueue() << "; "
             << p->getPriority() << "; "
             << p->getWaitingTime() << "; "
             << p->getCompletionTime() << "; "
             << p->getResponseTime() << "; "
             << p->getTurnAroundTime() << "\n";

        totalWT += p->getWaitingTime();
        totalCT += p->getCompletionTime();
        totalRT += p->getResponseTime();
        totalTAT += p->getTurnAroundTime();
    }

    //Ingresa los promedios de los WT, CT, RT y TAT
    file << fixed << setprecision(1);
    if (n > 0) {
        file << "\nWT=" << totalWT / n
             << "; CT=" << totalCT / n
             << "; RT=" << totalRT / n
             << "; TAT=" << totalTAT / n << ";\n";
    }

    file.close();
}
