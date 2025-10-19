#ifndef PROCESO_H
#define PROCESO_H

#include <string>
using namespace std;

class Proceso {
private:
    string id;
    int burstTime;
    int arrivalTime;
    int queue;
    int priority;
    int remainingTime;
    int completionTime;
    int waitingTime;
    int responseTime;
    int turnAroundTime;
    bool started;

public:
    Proceso(string, int, int, int, int);

    // Métodos Get
    string getId() const;
    int getBurstTime() const;
    int getArrivalTime() const;
    int getQueue() const;
    int getPriority() const;
    int getRemainingTime() const;
    int getCompletionTime() const;
    int getWaitingTime() const;
    int getResponseTime() const;
    int getTurnAroundTime() const;
    bool isStarted() const;

    // Métodos Set
    void setRemainingTime(int);
    void setCompletionTime(int);
    void setWaitingTime(int);
    void setResponseTime(int);
    void setTurnAroundTime(int);
    void setStarted(bool);

    // Otros
    void reset();
};

#endif
