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
        cout << "Enter disk size in GB: ";
        cin >> size;
        if (cin.fail() || size <= 0) {
            cout << "Invalid input. Please enter a positive number for disk size." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            size = -1;
        }
    }
    diskSizeGB = size;

    while (choice != 't' && choice != 'p') {
        cout << "Calculate based on (t)racks or (p)latters? ";
        cin >> choice;
        if (choice != 't' && choice != 'p') {
            cout << "Invalid choice. Please enter 't' or 'p'." << endl;
        }
    }

    if (choice == 't') {
        while (trackCount <= 0) {
            cout << "Enter number of tracks: ";
            cin >> trackCount;
            if (cin.fail() || trackCount <= 0) {
                cout << "Invalid input. Please enter a positive integer for tracks." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                trackCount = -1;
            }
        }
        tracks = trackCount;
        platters = 0; // Mark for calculation
    } else { // choice == 'p'
        while (platterCount <= 0) {
            cout << "Enter number of platters: ";
            cin >> platterCount;
            if (cin.fail() || platterCount <= 0) {
                cout << "Invalid input. Please enter a positive integer for platters." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                platterCount = -1;
            }
        }
        platters = platterCount;
        tracks = 0; // Mark for calculation
    }
}

bool DiskDrive::validateInputs(double size, int trackCount, int platterCount) const {
    if (size <= 0) {
        cerr << "Error: Disk size must be positive." << endl;
        return false;
    }
    if (trackCount <= 0 && platterCount <= 0) {
        cerr << "Error: Must provide a positive number for either tracks or platters." << endl;
        return false;
    }
    if (trackCount > 0 && platterCount > 0) {
        cerr << "Error: Provide only tracks or platters, not both." << endl;
        return false;
    }
    return true;
}

void DiskDrive::calculateGeometry() {
    // Total bytes based on 1 GB = 1,000,000,000 bytes
    int64_t totalBytes = static_cast<int64_t>(diskSizeGB * BYTES_PER_GB);

    // Calculate total number of sectors
    sectors = totalBytes / SECTOR_SIZE_BYTES;

    // disksectors * disktracks * diskplatters = disksize (in sectors)
    // We are using a simplified model where the relationship is linear.
    // A more realistic model would involve cylinders, but we follow the problem's formula.
    // Let's assume a direct relationship for simplicity as per the prompt's formula,
    // which seems to be a simplification: sectors * tracks * platters = total_sectors
    // This implies sectors per track and tracks per platter are involved.
    // Let's reinterpret the formula as:
    // total_sectors = sectors_per_track * tracks_per_platter * platters
    // The prompt is a bit ambiguous. A common interpretation is:
    // Total Capacity = (# of platters) * (# of tracks/platter) * (# of sectors/track) * (sector size)
    // Let's assume the prompt's `disktracks` means tracks per platter and `disksectors` means sectors per track.
    // So, total_sectors = sectors_per_track * tracks_per_platter * platters
    // Let's assume a fixed number of sectors per track, e.g., 256, to make the calculation feasible.
    const int sectors_per_track = 256; // A reasonable assumption for a simplified model.

    if (tracks > 0) {
        // User provided tracks, calculate platters
        // total_sectors = sectors_per_track * tracks * platters
        if (sectors_per_track * tracks == 0) {
             platters = 0;
        } else {
             platters = static_cast<int>(round(static_cast<double>(sectors) / (sectors_per_track * tracks)));
        }
       
        if (platters <= 0) {
            platters = 1; // Ensure at least one platter
        }
    } else if (platters > 0) {
        // User provided platters, calculate tracks
        // total_sectors = sectors_per_track * tracks * platters
        if (sectors_per_track * platters == 0) {
            tracks = 0;
        } else {
            tracks = static_cast<int>(round(static_cast<double>(sectors) / (sectors_per_track * platters)));
        }
        if (tracks <= 0) {
            tracks = 1; // Ensure at least one track
        }
    }
}


void DiskDrive::printSummary() const {
    cout << "\n--- Disk Drive Geometry Summary ---\n";
    cout << "Disk Size: " << diskSizeGB << " GB\n";
    cout << "Sector Size: " << SECTOR_SIZE_BYTES << " bytes\n";
    cout << "Total Sectors: " << sectors << "\n";
    cout << "Calculated Tracks (per platter): " << tracks << "\n";
    cout << "Calculated Platters: " << platters << "\n";
    cout << "-----------------------------------\n";
}
