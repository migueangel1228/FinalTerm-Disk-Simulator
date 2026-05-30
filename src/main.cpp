#include "../include/DiskDrive.h"
#include "../include/DiskScheduler.h"
#include <iostream>
#include <limits>
#include <stdexcept>

using namespace std;

void showMenu() {
    cout << "\n===== Final Term - Disk Simulator =====\n";
    cout << "1. Problem 1: Disk Drive Geometry Simulation\n";
    cout << "2. Problem 2: Disk Scheduling Algorithms\n";
    cout << "3. Run Both\n";
    cout << "4. Exit\n";
    cout << "=======================================\n";
    cout << "Enter your choice: ";
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
            cerr << "Invalid command line argument for head position. Using interactive mode." << endl;
        }
    }

    while (choice != 4) {
        showMenu();
        cin >> choice;

        if (cin.fail()) {
            cout << "Invalid input. Please enter a number." << endl;
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
                    cout << "Enter initial head position (0-4999): ";
                    cin >> headPosition;
                     if (cin.fail() || headPosition < 0 || headPosition >= DiskScheduler::TOTAL_CYLINDERS) {
                        cout << "Invalid head position. Please try again." << endl;
                        headPosition = -1;
                        break;
                    }
                }
                runDiskSchedulingSimulator(headPosition);
                headPosition = -1; // Reset for next run
                break;
            case 3:
                runDiskDriveSimulator();
                if (headPosition == -1) {
                    cout << "\nEnter initial head position for scheduling (0-4999): ";
                    cin >> headPosition;
                    if (cin.fail() || headPosition < 0 || headPosition >= DiskScheduler::TOTAL_CYLINDERS) {
                        cout << "Invalid head position. Please try again." << endl;
                        headPosition = -1;
                        break;
                    }
                }
                runDiskSchedulingSimulator(headPosition);
                headPosition = -1; // Reset for next run
                break;
            case 4:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please select a valid option." << endl;
                break;
        }
    }

    return 0;
}
