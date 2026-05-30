#include "../include/DiskDrive.h"
#include "../include/DiskScheduler.h"
#include <iostream>
#include <limits>
#include <stdexcept>

using namespace std;

DiskScheduler::Algorithm promptAlgorithm() {
    int choice = 0;

    while (choice < 1 || choice > 3) {
        cout << "Elige el algoritmo (1-FCFS, 2-SCAN, 3-C-SCAN): ";
        cin >> choice;

        if (cin.fail() || choice < 1 || choice > 3) {
            cout << "Algoritmo invalido. Intenta nuevamente." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = 0;
        }
    }

    switch (choice) {
        case 1:
            return DiskScheduler::Algorithm::FCFS;
        case 2:
            return DiskScheduler::Algorithm::SCAN;
        default:
            return DiskScheduler::Algorithm::CSCAN;
    }
}

unsigned int promptSeed() {
    unsigned int seed = 2023;

    cout << "Ingresa la semilla para las solicitudes aleatorias (0 usa 2023): ";
    cin >> seed;

    if (cin.fail()) {
        cout << "Semilla invalida. Se usara 2023." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return 2023;
    }

    if (seed == 0) {
        seed = 2023;
    }

    return seed;
}

void showMenu() {
    cout << "\n===== Final Term - Disk Simulator =====\n";
    cout << "1. Problema 1: simulacion de geometria de disco\n";
    cout << "2. Problema 2: algoritmos de planificacion de disco\n";
    cout << "3. Ejecutar ambos\n";
    cout << "4. Salir\n";
    cout << "=======================================\n";
    cout << "Ingresa tu opcion: ";
}

void runDiskDriveSimulator() {
    DiskDrive disk;
    disk.run();
}

void runDiskSchedulingSimulator(int headPosition, DiskScheduler::Algorithm algorithm, unsigned int seed) {
    try {
        DiskScheduler scheduler(headPosition, algorithm, seed);
        scheduler.runSelectedAlgorithm();
        scheduler.printSummary();
        scheduler.exportResultsToCSV("data/results.csv");
    } catch (const invalid_argument& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

int main(int argc, char* argv[]) {
    int choice = 0;
    int headPosition = -1;

    if (argc > 1) {
        try {
            headPosition = stoi(argv[1]);
        } catch (const exception& e) {
            cerr << "Argumento de linea de comandos invalido para la posicion de la cabeza. Se usara el modo interactivo." << endl;
        }
    }

    while (choice != 4) {
        showMenu();
        cin >> choice;

        if (cin.fail()) {
            cout << "Entrada invalida. Por favor ingresa un numero." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = 0;
            continue;
        }

        switch (choice) {
            case 1:
                runDiskDriveSimulator();
                break;
            case 2:
                if (headPosition == -1) {
                    cout << "Ingresa la posicion inicial de la cabeza (0-4999): ";
                    cin >> headPosition;
                    if (cin.fail() || headPosition < 0 || headPosition >= DiskScheduler::TOTAL_CYLINDERS) {
                        cout << "Posicion de cabeza invalida. Intenta nuevamente." << endl;
                        headPosition = -1;
                        break;
                    }
                }
                runDiskSchedulingSimulator(headPosition, promptAlgorithm(), promptSeed());
                headPosition = -1; // Reiniciar para la siguiente ejecucion
                break;
            case 3:
                runDiskDriveSimulator();
                if (headPosition == -1) {
                    cout << "\nIngresa la posicion inicial de la cabeza para la planificacion (0-4999): ";
                    cin >> headPosition;
                    if (cin.fail() || headPosition < 0 || headPosition >= DiskScheduler::TOTAL_CYLINDERS) {
                        cout << "Posicion de cabeza invalida. Intenta nuevamente." << endl;
                        headPosition = -1;
                        break;
                    }
                }
                runDiskSchedulingSimulator(headPosition, promptAlgorithm(), promptSeed());
                headPosition = -1; // Reiniciar para la siguiente ejecucion
                break;
            case 4:
                cout << "Saliendo del programa." << endl;
                break;
            default:
                cout << "Opcion invalida. Selecciona una opcion valida." << endl;
                break;
        }
    }

    return 0;
}
