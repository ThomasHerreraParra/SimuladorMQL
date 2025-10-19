#include "Proceso.h"

//constructor
Proceso::Proceso(string id_, int bt, int at, int q, int pr)
    : id(id_), burstTime(bt), arrivalTime(at), queue(q), priority(pr),
      remainingTime(bt), completionTime(0), waitingTime(0),
      responseTime(0), turnAroundTime(0), started(false) {}

//Devuelve el id
string Proceso::getId() const { return id; }

//Devuelve el BT
int Proceso::getBurstTime() const { return burstTime; }

//Devuelve el AT
int Proceso::getArrivalTime() const { return arrivalTime; }

//Devuelve el numero de cola al que pertenece
int Proceso::getQueue() const { return queue; }

//Devuelve la prioridad
int Proceso::getPriority() const { return priority; }

//Devuelve el tiempo restante por ejecutar
int Proceso::getRemainingTime() const { return remainingTime; }

//Devuelve el CT
int Proceso::getCompletionTime() const { return completionTime; }

//Devuelve el WT
int Proceso::getWaitingTime() const { return waitingTime; }

//Devuelve el RT
int Proceso::getResponseTime() const { return responseTime; }

//Devuleve el TAT
int Proceso::getTurnAroundTime() const { return turnAroundTime; }

//Indica si el porceso ya inicio
bool Proceso::isStarted() const { return started; }

//Establece el tiempo restante por ejecutar
void Proceso::setRemainingTime(int v) { remainingTime = v; }

//Establece el CT
void Proceso::setCompletionTime(int v) { completionTime = v; }

//Establece el WT
void Proceso::setWaitingTime(int v) { waitingTime = v; }

//Establece el RT
void Proceso::setResponseTime(int v) { responseTime = v; }

//Establece el TAT
void Proceso::setTurnAroundTime(int v) { turnAroundTime = v; }

//Marca si el proceso ya inició su ejecución
void Proceso::setStarted(bool v) { started = v; }

//Esto permite volver a simular desde cero sin recargar datos
void Proceso::reset() {
    remainingTime = burstTime;
    completionTime = waitingTime = responseTime = turnAroundTime = 0;
    started = false;
}
