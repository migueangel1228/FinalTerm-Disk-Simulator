#include "../include/DiskScheduler.h"
#include "../include/Utils.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <fstream>

using namespace std;

const int DiskScheduler::TOTAL_CYLINDERS = 5000;
const int DiskScheduler::MAX_CYLINDER = 4999;
const int DiskScheduler::REQUEST_COUNT = 1000;

DiskScheduler::DiskScheduler(int startHeadPosition, Algorithm selectedAlgorithm, unsigned int requestSeed, Direction startDirection)
    : startHeadPosition(startHeadPosition), selectedAlgorithm(selectedAlgorithm), initialDirection(startDirection), requestSeed(requestSeed) {
    if (startHeadPosition < 0 || startHeadPosition >= TOTAL_CYLINDERS) {
        throw invalid_argument("La posicion inicial de la cabeza esta fuera de rango.");
    }
    loadRandomRequests();
}

void DiskScheduler::loadRandomRequests() {
    requests = Utils::generateRandomRequests(REQUEST_COUNT, 0, MAX_CYLINDER, requestSeed);
}

void DiskScheduler::runAllAlgorithms() {
    results.clear();
    results.push_back(calculateFCFS());
    results.push_back(calculateSCAN());
    results.push_back(calculateCSCAN());
}

void DiskScheduler::runSelectedAlgorithm() {
    results.clear();
    results.push_back(calculateSelectedAlgorithm());
}

ScheduleResult DiskScheduler::calculateSelectedAlgorithm() const {
    switch (selectedAlgorithm) {
        case Algorithm::FCFS:
            return calculateFCFS();
        case Algorithm::SCAN:
            return calculateSCAN();
        case Algorithm::CSCAN:
            return calculateCSCAN();
    }

    throw invalid_argument("Algoritmo de planificacion invalido.");
}

ScheduleResult DiskScheduler::calculateFCFS() const {
    ScheduleResult result;
    result.algorithmName = "FCFS";
    result.servicedRequests = requests; // Se conserva el orden
    result.totalMovement = calculateTotalMovement(result.servicedRequests, startHeadPosition);
    return result;
}

ScheduleResult DiskScheduler::calculateSCAN() const {
    ScheduleResult result;
    result.algorithmName = "SCAN";
    
    vector<int> left, right;
    for (int req : requests) {
        if (req < startHeadPosition) {
            left.push_back(req);
        } else {
            right.push_back(req);
        }
    }

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    if (initialDirection == Direction::DOWN) {
        // Mover hacia abajo primero, atendiendo solicitudes
        for (int i = left.size() - 1; i >= 0; --i) {
            result.servicedRequests.push_back(left[i]);
        }
        // Llegar al inicio del disco
        if (!left.empty() || !right.empty()) {
             result.servicedRequests.push_back(0);
        }
        // Mover hacia arriba, atendiendo solicitudes
        for (int req : right) {
            result.servicedRequests.push_back(req);
        }
    } else { // Direction::UP
        // Mover hacia arriba primero
        for (int req : right) {
            result.servicedRequests.push_back(req);
        }
        // Llegar al final del disco
        if (!left.empty() || !right.empty()) {
            result.servicedRequests.push_back(MAX_CYLINDER);
        }
        // Mover hacia abajo
        for (int i = left.size() - 1; i >= 0; --i) {
            result.servicedRequests.push_back(left[i]);
        }
    }

    result.totalMovement = calculateTotalMovement(result.servicedRequests, startHeadPosition);
    return result;
}

ScheduleResult DiskScheduler::calculateCSCAN() const {
    ScheduleResult result;
    result.algorithmName = "C-SCAN";

    vector<int> left, right;
    for (int req : requests) {
        if (req < startHeadPosition) {
            left.push_back(req);
        } else {
            right.push_back(req);
        }
    }

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    // Siempre se mueve en una sola direccion, por ejemplo hacia arriba
    // Atender solicitudes a la derecha de la cabeza
    for (int req : right) {
        result.servicedRequests.push_back(req);
    }

    // Si hay solicitudes, saltar al final y luego al inicio
    if (!requests.empty()) {
        result.servicedRequests.push_back(MAX_CYLINDER);
        result.servicedRequests.push_back(0);
    }
    
    // Atender solicitudes desde el inicio
    for (int req : left) {
        result.servicedRequests.push_back(req);
    }

    result.totalMovement = calculateTotalMovement(result.servicedRequests, startHeadPosition);
    return result;
}

int DiskScheduler::calculateTotalMovement(const vector<int>& servicedRequests, int initialPosition) const {
    if (servicedRequests.empty()) {
        return 0;
    }
    int totalMovement = 0;
    int currentPosition = initialPosition;
    for (int request : servicedRequests) {
        totalMovement += abs(request - currentPosition);
        currentPosition = request;
    }
    return totalMovement;
}

void DiskScheduler::printAllResults() const {
    cout << "\n--- Simulacion de planificacion de disco ---\n";
    cout << "Posicion inicial de la cabeza: " << startHeadPosition << "\n";
    cout << "Total de solicitudes: " << requests.size() << "\n";
    cout << "------------------------------------\n";

    for (const auto& result : results) {
        printAlgorithmResult(result);
    }
}

void DiskScheduler::printSummary() const {
    cout << "\n--- Resumen de planificacion de disco ---\n";
    cout << "Posicion inicial de la cabeza: " << startHeadPosition << "\n";
    cout << "Total de solicitudes: " << requests.size() << "\n";

    if (results.empty()) {
        cout << "No hay resultados para mostrar.\n";
        cout << "------------------------------------\n";
        return;
    }

    const ScheduleResult& result = results.front();
    cout << "Algoritmo: " << result.algorithmName << "\n";
    cout << "Semilla: " << requestSeed << "\n";
    cout << "Movimiento total de la cabeza: " << result.totalMovement << " cilindros\n";

    if (!result.servicedRequests.empty()) {
        double avgMovement = static_cast<double>(result.totalMovement) / result.servicedRequests.size();
        cout << "Movimiento promedio de la cabeza: " << avgMovement << " cilindros\n";
    }

    cout << "------------------------------------\n";
}

void DiskScheduler::printAlgorithmResult(const ScheduleResult& result) const {
    cout << "\n--- Algoritmo: " << result.algorithmName << " ---\n";
    cout << "Orden de atencion y movimiento:\n";
    
    int lastPos = startHeadPosition;
    for(int req : result.servicedRequests) {
        cout << "  Solicitud: " << req << ", Movimiento: " << abs(req - lastPos) << "\n";
        lastPos = req;
    }

    cout << "Movimiento total de la cabeza: " << result.totalMovement << " cilindros\n";
    if (!result.servicedRequests.empty()) {
        double avgMovement = static_cast<double>(result.totalMovement) / result.servicedRequests.size();
        cout << "Movimiento promedio de la cabeza: " << avgMovement << " cilindros\n";
    }
    cout << "------------------------------------\n";
}

void DiskScheduler::exportResultsToCSV(const string& filename) const {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cerr << "Error: no se pudo abrir el archivo " << filename << " para escritura." << endl;
        return;
    }

    outFile << "Algorithm,TotalMovement,AverageMovement\n";
    for (const auto& result : results) {
        double avgMovement = 0;
        if (!result.servicedRequests.empty()) {
            avgMovement = static_cast<double>(result.totalMovement) / result.servicedRequests.size();
        }
        outFile << result.algorithmName << "," << result.totalMovement << "," << avgMovement << "\n";
    }

    outFile.close();
    cout << "\nResultados exportados a " << filename << endl;
}
