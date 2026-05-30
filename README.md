# FinalTerm-Disk-Simulator

## 1. Overview

This project is a C++ simulation of two key disk-related concepts for a university final term assignment. It covers:
1.  **Disk Drive Geometry**: Simulating the physical characteristics of a Hard Disk Drive (HDD) based on its size.
2.  **Disk Scheduling Algorithms**: Implementing and comparing FCFS, SCAN, and C-SCAN algorithms for servicing disk I/O requests.

The project is built with professional software engineering practices, including a modular structure, clean code, and a clear separation of concerns. It is designed to be compiled and run from the command line.

## 2. Problem 1: Disk Drive Geometry

### Description
This part of the simulator models the physical structure of an HDD. The user provides the disk size in Gigabytes (GB) and either the number of tracks or platters. The program then calculates the remaining parameter based on a simplified formula.

### Key Features
-   Calculates disk geometry (sectors, tracks, platters).
-   Uses a standard sector size of 512 bytes.
-   Defines 1 GB as 1,000,000,000 bytes for calculations.
-   Validates user input to prevent errors.
-   Displays a clear and professional summary of the disk's geometry.

## 3. Problem 2: Disk Scheduling

### Description
This part implements three fundamental disk scheduling algorithms to manage I/O requests efficiently. The simulation runs on a disk with 5,000 cylinders (0-4999) and services 1,000 randomly generated requests.

### Implemented Algorithms
1.  **FCFS (First-Come, First-Served)**: Services requests in the order they arrive. Simple but often inefficient.
2.  **SCAN (Elevator Algorithm)**: The disk head moves in one direction, servicing all requests in its path until it reaches the end of the disk. It then reverses direction.
3.  **C-SCAN (Circular SCAN)**: Similar to SCAN, but the head only services requests in one direction. After reaching the end, it jumps back to the beginning without servicing any requests on the return trip, providing more uniform wait times.

### Key Features
-   Generates 1,000 random cylinder requests.
-   Accepts the initial head position as a command-line argument or interactively.
-   Calculates and reports the total head movement for each algorithm.
-   Displays the sequence of serviced requests for verification.
-   Exports a summary of results to a CSV file.

## 4. Project Structure

The project is organized into the following directories and files:

```
FinalTerm-Disk-Simulator/
├── include/                # Header files
│   ├── DiskDrive.h
│   ├── DiskScheduler.h
│   ├── ScheduleResult.h
│   └── Utils.h
├── src/                    # Source files
│   ├── DiskDrive.cpp
│   ├── DiskScheduler.cpp
│   ├── main.cpp
│   └── Utils.cpp
├── data/                   # Output data
│   └── results.csv
└── README.md               # This file
```

## 5. Build Instructions

**Prerequisites**:
-   A C++17 compatible compiler (e.g., g++).

**Compilation Steps**:
1.  Open a terminal in the project's root directory.
2.  Run the following command to compile the project:
    ```bash
    g++ -std=c++17 -Wall -Wextra -Wpedantic -g -O0 -Iinclude src/*.cpp -o bin/disksim
    ```
3.  The executable will be created at `bin/disksim`.

## 6. Run Instructions

You can run the simulator in two ways:

### Interactive Mode
Run the program without any arguments to see a menu:
```bash
./bin/disksim
```
You will be prompted to choose which simulation to run.

### Command-Line Argument
You can provide the initial head position for the disk scheduling simulation as a command-line argument. This is useful for scripting or quick tests.
```bash
./bin/disksim [initial_head_position]
```
Example:
```bash
./bin/disksim 1234
```
If an argument is provided, the menu will still be shown, but the scheduling simulation will use the provided head position if selected.

## 7. Input and Output Format

### Input
-   **Disk Geometry**: The program will prompt you to enter the disk size (GB) and either the number of tracks or platters.
-   **Disk Scheduling**: The program will prompt for the initial head position if not provided via command line.

### Output
-   **Console**: The results of the simulations are printed to the console in a formatted, human-readable way.
-   **CSV File**: The disk scheduling results (total and average head movement for each algorithm) are saved to `data/results.csv`.

## 8. Algorithm Explanation

-   **FCFS**: The simplest algorithm. It processes requests in the sequence they were received. This can lead to excessive head movement if the requests are scattered across the disk.
-   **SCAN**: Reduces head movement by servicing all requests in one direction before reversing. This is like an elevator that goes all the way to the top floor and then all the way to the bottom, picking up passengers along the way.
-   **C-SCAN**: Improves upon SCAN by providing more uniform wait times. The head moves from one end of the disk to the other, servicing requests. When it reaches the end, it immediately returns to the beginning without servicing requests, and then starts a new sweep.

## 9. Sample Outputs

### DiskDrive Simulation
```
--- Disk Drive Geometry Summary ---
Disk Size: 10 GB
Sector Size: 512 bytes
Total Sectors: 19531250
Calculated Tracks (per platter): 128
Calculated Platters: 60
-----------------------------------
```

### DiskScheduler Simulation
```
--- Algorithm: FCFS ---
Service Order and Movement:
  Request: 1632, Movement: 399
  Request: 4815, Movement: 3183
  ...
Total Head Movement: 1956381 cylinders
Average Head Movement: 1956.38 cylinders
------------------------------------
```

## 10. Assumptions and Limitations

-   **Disk Geometry**: The formula `sectors * tracks * platters = total_sectors` is a simplification. In this model, we assume a fixed number of sectors per track (256) to make the calculation determinate. Real-world HDDs have a more complex structure (e.g., zones, varying sectors per track).
-   **Scheduling**: The simulation does not account for rotational latency or data transfer time, focusing solely on seek time (head movement).

## 11. Author Information

-   **Author**: [Your Name]
-   **Course**: [Your Course Name]
-   **Assignment**: Final Term Project

This project was developed as a solution to the final term assignment, demonstrating an understanding of disk systems and C++ software development principles.
