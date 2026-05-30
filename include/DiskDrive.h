#ifndef DISKDRIVE_H
#define DISKDRIVE_H

#include <cstdint>

class DiskDrive {
public:
    // Constants
    static const int SECTOR_SIZE_BYTES;
    static const int64_t BYTES_PER_GB;

    // Constructor
    DiskDrive();

    // Public interface
    void run();

private:
    // Attributes
    double diskSizeGB;
    int64_t sectors;
    int tracks;
    int platters;

    // Private methods
    void readInputs();
    bool validateInputs(double size, int trackCount, int platterCount) const;
    void calculateGeometry();
    void printSummary() const;
};

#endif // DISKDRIVE_H
