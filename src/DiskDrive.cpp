#include "../include/DiskDrive.h"
#include <iostream>
#include <cmath>
#include <limits>

using namespace std;

const int DiskDrive::SECTOR_SIZE_BYTES = 512;
const int64_t DiskDrive::BYTES_PER_GB = 1000000000;

DiskDrive::DiskDrive() : diskSizeGB(0), sectors(0), tracks(0), platters(0) {}

void DiskDrive::run() {
    readInputs();
    calculateGeometry();
    printSummary();
}

void DiskDrive::readInputs() {
    double size = -1;
    int trackCount = -1;
    int platterCount = -1;
    char choice = ' ';

    while (size <= 0) {
        cout << "Ingresa el tamano del disco en GB: ";
        cin >> size;
        if (cin.fail() || size <= 0) {
            cout << "Entrada invalida. Ingresa un numero positivo para el tamano del disco." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            size = -1;
        }
    }
    diskSizeGB = size;

    while (choice != 't' && choice != 'p') {
        cout << "Calcular con (t)pistas o (p)platos? ";
        cin >> choice;
        if (choice != 't' && choice != 'p') {
            cout << "Opcion invalida. Ingresa 't' o 'p'." << endl;
        }
    }

    if (choice == 't') {
        while (trackCount <= 0) {
            cout << "Ingresa el numero de pistas: ";
            cin >> trackCount;
            if (cin.fail() || trackCount <= 0) {
                cout << "Entrada invalida. Ingresa un entero positivo para las pistas." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                trackCount = -1;
            }
        }
        tracks = trackCount;
        platters = 0; // Marcar para calculo
    } else { // choice == 'p'
        while (platterCount <= 0) {
            cout << "Ingresa el numero de platos: ";
            cin >> platterCount;
            if (cin.fail() || platterCount <= 0) {
                cout << "Entrada invalida. Ingresa un entero positivo para los platos." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                platterCount = -1;
            }
        }
        platters = platterCount;
        tracks = 0; // Marcar para calculo
    }
}

bool DiskDrive::validateInputs(double size, int trackCount, int platterCount) const {
    if (size <= 0) {
        cerr << "Error: el tamano del disco debe ser positivo." << endl;
        return false;
    }
    if (trackCount <= 0 && platterCount <= 0) {
        cerr << "Error: debes proporcionar un numero positivo de pistas o de platos." << endl;
        return false;
    }
    if (trackCount > 0 && platterCount > 0) {
        cerr << "Error: proporciona solo pistas o platos, no ambos." << endl;
        return false;
    }
    return true;
}

void DiskDrive::calculateGeometry() {
    // Bytes totales con base en 1 GB = 1,000,000,000 bytes
    int64_t totalBytes = static_cast<int64_t>(diskSizeGB * BYTES_PER_GB);

    // Calcular el numero total de sectores
    sectors = totalBytes / SECTOR_SIZE_BYTES;

    // disksectors * disktracks * diskplatters = tamano del disco (en sectores)
    // Se usa un modelo simplificado con una relacion lineal.
    // Un modelo mas realista involucraria cilindros, pero aqui seguimos la formula del problema.
    // Reinterpretamos la formula como:
    // total_sectors = sectores_por_pista * pistas_por_plato * platos
    // Para hacer posible el calculo, se asume un numero fijo de sectores por pista.
    const int sectors_per_track = 256; // Suposicion razonable para un modelo simplificado.

    if (tracks > 0) {
        // El usuario proporciono pistas; calcular platos
        // total_sectors = sectors_per_track * tracks * platters
        if (sectors_per_track * tracks == 0) {
             platters = 0;
        } else {
             platters = static_cast<int>(round(static_cast<double>(sectors) / (sectors_per_track * tracks)));
        }
       
        if (platters <= 0) {
            platters = 1; // Asegurar al menos un plato
        }
    } else if (platters > 0) {
        // El usuario proporciono platos; calcular pistas
        // total_sectors = sectors_per_track * tracks * platters
        if (sectors_per_track * platters == 0) {
            tracks = 0;
        } else {
            tracks = static_cast<int>(round(static_cast<double>(sectors) / (sectors_per_track * platters)));
        }
        if (tracks <= 0) {
            tracks = 1; // Asegurar al menos una pista
        }
    }
}


void DiskDrive::printSummary() const {
    cout << "\n--- Resumen de geometria de la unidad de disco ---\n";
    cout << "Tamano del disco: " << diskSizeGB << " GB\n";
    cout << "Tamano del sector: " << SECTOR_SIZE_BYTES << " bytes\n";
    cout << "Total de sectores: " << sectors << "\n";
    cout << "Pistas calculadas (por plato): " << tracks << "\n";
    cout << "Platos calculados: " << platters << "\n";
    cout << "-----------------------------------------------\n";
}
