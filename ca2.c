#include <iostream>
#include <vector>
using namespace std;

// Set the number of blocks on the simulated disk
const int disk_size = 1000;

// Initialize the disk with all blocks free
vector<int> disk(disk_size);

bool allocate_file(int file_size) {
    // Find a free contiguous block of the required size
    int start_block = -1;
    int free_blocks = 0;
    for (int i = 0; i < disk_size; i++) {
        if (disk[i] == 0) {
            free_blocks++;
            if (free_blocks == file_size) {
                start_block = i - file_size + 1;
                break;
            }
        } else {
            free_blocks = 0;
        }
    }

    // If a free contiguous block was found, allocate it
    if (start_block != -1) {
        for (int i = start_block; i < start_block + file_size; i++) {
            disk[i] = 1;
        }
        return true;
    } else {
        return false;
    }
}

double calculate_fragmentation() {
    // Calculate and return the average amount of fragmentation on the disk
    int free_blocks = 0;
    int fragments = 0;
    for (int i = 0; i < disk_size; i++) {
        if (disk[i] == 0) {
            free_blocks++;
            if (i == 0 || disk[i-1] == 1) {
                fragments++;
            }
        }
    }

    if (fragments == 0) {
        return 0;
    } else {
        return free_blocks / (double)fragments;
    }
}

int calculate_wasted_blocks() {
    // Calculate and return the number of wasted disk blocks
    int used_blocks = 0;
    for (int i = 0; i < disk_size; i++) {
        if (disk[i] == 1) {
            used_blocks++;
        }
    }
    int allocated_blocks = used_blocks + calculate_fragmentation();
    return disk_size - allocated_blocks;
}

int main() {
    // Set the number of time units to run the simulation
    int time_units;
    cout << "Enter the number of time units to run the simulation: ";
    cin >> time_units;

    // Run the simulation for the specified number of time units
    for (int t = 0; t < time_units; t++) {
        // Allocate space for a random number of files with random sizes
        int num_files;
        cout << "Enter the number of files to allocate: ";
        cin >> num_files;
        for (int i = 0; i < num_files; i++) {
            int file_size;
            cout << "Enter the size of file " << i+1 << ": ";
            cin >> file_size;
            allocate_file(file_size);
        }

        // Calculate and display the average amount of fragmentation and the number of wasted disk blocks
        double avg_fragmentation = calculate_fragmentation();
        int wasted_blocks = calculate_wasted_blocks();
        cout << "Time unit: " << t+1 << endl;
        cout << "Average fragmentation: " << avg_fragmentation << endl;
        cout << "Wasted blocks: " << wasted_blocks << endl;
    }return 0;
}