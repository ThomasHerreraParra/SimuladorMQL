#include <iostream>
#include "PlanificadorMLQ.h"
using namespace std;

int main() {
    PlanificadorMLQ mlq;

    mlq.leerArchivo("mlq004.txt");
    mlq.cargarColas();
    mlq.ejecutar();
    mlq.generarSalida("mlq004_out.txt");

    cout << "Simulación MLQ completada.\n";
    cout << "Archivo generados.\n";
    return 0;
}
