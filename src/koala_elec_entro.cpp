// This code calculates electronic entropy from DOSCAR.
// This function is:
// S = - k_B * int(n * (f*ln(f) + (1 - f) * ln(1 - f))dE)
// where
//  f is the Fermi distribution function
//      f = 1 / (exp((E - E_f) / k_B * T) + 1)
//  n is the density of states.
//
// Changning Niu, March 15, 2013.

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>
using namespace std;
int main() {
    // Variables
    ifstream inFile;    // to open DOSCAR
    string line;        // to read a line from file
    istringstream iss;  // to process a string
    string dummy;       // string trash
    int nStates;        // number of states
    double fermi;       // fermi energy
    int maxT = 300;     // max temperature in K
    double step = 0.5;     // step of temperature points
    int nT = int(maxT / step);  // # temperature points
    double T;           // temperature points
    double k = 1.3806503E-23;   // Boltzmann constant
    double M;           // = exp((E - E_f) / (k * T))
    ofstream outFile;   // to write to file
    // Open DOSCAR
    inFile.open("DOSCAR");
    if (!inFile) {
        cerr << "Cannot open DOSCAR! Quitting...\n";
        exit(1);
    }
    // Read #states and Fermi energy from line 6
    for (int i = 0; i < 6; i++)
        getline(inFile, line); // ignore first 5 lines
    iss.str(line);
    for (int i = 0; i < 2; i++)
        iss >> dummy;   // ignore first two numbers
    iss >> nStates >> fermi;
    // Read energy and DOS, then convert wrt fermi
    double arr1 [nStates][2];   // store energy & DOS
    for (int i = 0; i < nStates; i++) {
        getline(inFile, line);
        iss.str(line);
        iss >> arr1[i][0] >> arr1[i][1];
        arr1[i][0] -= fermi;    // use fermi energy as 0
        arr1[i][0] *= 1.60217646E-19; // convert to J
    }
    // Calculate electronic entropy T*S
    double arr2[nT][2];         // store T & S
    for (int i = 0; i < nT; i++) {
        T = step * (i + 1);  // temperature points
        arr2[i][0] = T;
        // This part calculates S(T):
        arr2[i][1] = 0;         // initiate S
        for (int j = 0; j < nStates-1; j++) {
            M = exp(arr1[j][0] / k / T);
            if (M != 0 && !isinf(M)) {
                arr2[i][1] += (arr1[j+1][0] - arr1[j][0])
                    * arr1[j][1] * (-1 / (M+1) * log(M+1)
                    + M / (M+1) * log(M/(M+1)) );
            }
        }
        arr2[i][1] *= -k * T / 1.60217646E-19; // T*S in eV
    }
    // Write to Elec_entropy.dat
    outFile.open("Elec_entropy.dat");
    if (!outFile) {
        cerr << "Cannot save to Elec_entropy.dat. Quitting...\n";
        exit(1);
    }
    for (int i = 0; i < nT; i++)
        outFile << arr2[i][0] << "\t" << arr2[i][1] << "\n";
    outFile.close();
    return 0;
}
