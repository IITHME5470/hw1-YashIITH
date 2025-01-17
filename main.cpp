/********************************************************************************************************
* File main.cpp
* Description
* Program : To read the data from input.in file and call the Array Class to generate the ASCII and BINARY
* AUTHOR: Yashwant Singh
* LAST REVISED: 16/01/25
*********************************************************************************************************/


#include <fstream>
#include <vector>
#include <filesystem> 
#include <iomanip>    
#include "array.h"

using namespace std;
namespace fs = std::filesystem;

int main() {
    
    // Read multiple values of n from the input file
    ifstream inputFile("input.in");
    if (!inputFile.is_open()) {
        cerr << "Error: Unable to open input file.\n";
        return 1;
    }

    vector<int> sizes;
    int n;
    while (inputFile >> n) {
        if (n > 0) {
            sizes.push_back(n);
        } else {
            cerr << "Warning: Invalid matrix size " << n << " ignored.\n";
        }
    }
    inputFile.close();

    // Open CSV files for recording file sizes
    ofstream asciiFileSizeCSV("ascii_file_sizes.csv");
    ofstream binaryFileSizeCSV("binary_file_sizes.csv");

    if (!asciiFileSizeCSV.is_open() || !binaryFileSizeCSV.is_open()) {
        cerr << "Error: Unable to open CSV files for writing.\n";
        return 1;
    }

    // Write headers for the CSV files
    asciiFileSizeCSV << "Matrix Size,ASCII File Size (MB)\n";
    binaryFileSizeCSV << "Matrix Size,Binary File Size (MB)\n";

    // Process each size and write outputs
    for (int size : sizes) {
        cout << "Processing size " << size << "...\n";
        Array array(size);

        // Write ASCII file and get its size
        array.printToFile(0); // ASCII format
        string asciiFileName = "array_" + string(6 - to_string(size).length(), '0') + to_string(size) + "_asc.out";
        if (fs::exists(asciiFileName)) {
            size_t asciiFileSizeBytes = fs::file_size(asciiFileName);
            double asciiFileSizeMB = static_cast<double>(asciiFileSizeBytes) / (1024 * 1024);
            asciiFileSizeCSV << size << "," << fixed << setprecision(6) << asciiFileSizeMB << "\n";
        } else {
            cerr << "Warning: ASCII file " << asciiFileName << " does not exist.\n";
        }

        // Write Binary file and get its size
        array.printToFile(1); // Binary format
        string binaryFileName = "array_" + string(6 - to_string(size).length(), '0') + to_string(size) + "_bin.out";
        if (fs::exists(binaryFileName)) {
            size_t binaryFileSizeBytes = fs::file_size(binaryFileName);
            double binaryFileSizeMB = static_cast<double>(binaryFileSizeBytes) / (1024 * 1024);
            binaryFileSizeCSV << size << "," << fixed << setprecision(6) << binaryFileSizeMB << "\n";
        } else {
            cerr << "Warning: Binary file " << binaryFileName << " does not exist.\n";
        }
    }

    // Close CSV files
    asciiFileSizeCSV.close();
    binaryFileSizeCSV.close();

    return 0;
}

