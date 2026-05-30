#include "../include/DiskDrive.h"
#include "../include/DiskScheduler.h"
#include <iostream>
#include <limits>
#include <stdexcept>

using namespace std;

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

void runDiskSchedulingSimulator(int headPosition) {
    try {
        DiskScheduler scheduler(headPosition);
        scheduler.runAllAlgorithms();
        scheduler.printAllResults();
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
                runDiskSchedulingSimulator(headPosition);
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
                runDiskSchedulingSimulator(headPosition);
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
