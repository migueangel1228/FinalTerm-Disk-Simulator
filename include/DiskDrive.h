#ifndef DISKDRIVE_H
#define DISKDRIVE_H

#include <cstdint>

class DiskDrive {
public:
    // Constantes
    static const int SECTOR_SIZE_BYTES;
    static const int64_t BYTES_PER_GB;

    // Constructor
    DiskDrive();

    // Interfaz publica
    void run();

private:
    // Atributos
    double diskSizeGB;
    int64_t sectors;
    int tracks;
    int platters;

    // Metodos privados
    void readInputs();
    bool validateInputs(double size, int trackCount, int platterCount) const;
    void calculateGeometry();
    void printSummary() const;
};

#endif // DISKDRIVE_H
