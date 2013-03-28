// This code works for POSCAR-format files.
// It converts Direct to Cartesian.
//
// Author: Changning Niu (cniu@ncsu.edu)
// March 28, 2013.

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
int main( int argc, char* argv[]) {
    // Variables
    ifstream inFile;    // to open Direct file
    ofstream outFile;   // to save Cartesian file
    string line;        // to read a line
    istringstream ss;  // to process a string
    double Vec[3][3];   // store lattice vectors
    int nAtom;          // # of atoms
    
    // Open Direct file
    char* file;
    if (argc == 1)
        file = "POSCAR";
    else if (argc == 2)
        file = argv[1];
    else {
        cerr << "Usage: koala_dire2cart FileName\n";
        exit (1);
    }
    inFile.open(file);
    if (!inFile) {
        cerr << "Cannot open " << file << ".\n";
        exit (1);
    }
    
    // Copy first 2 lines to new file.
    outFile.open(strcat(file,".cart"));
    outFile.precision(15);
    outFile << fixed;
    for (int i = 0; i < 2; i++) {
        getline(inFile, line);
        outFile << line << "\n";
    }
    // Read lattice vectors
    string a,b,c;
    for (int i = 0; i < 3; i++) {
        getline(inFile, line);
        ss.str(line);
        ss >> a >> b >> c;
        ss.clear();
        if (a.length() > 15)
            a = a.substr(0,15);
        if (b.length() > 15)
            b = b.substr(0,15);
        if (c.length() > 15)
            c = c.substr(0,15);
        Vec[i][0] = atof(a.c_str());
        Vec[i][1] = atof(b.c_str());
        Vec[i][2] = atof(c.c_str());
        outFile << Vec[i][0] << " " << Vec[i][1] << " " << Vec[i][2] << "\n";
    }
    getline(inFile, line);  // line 6
    ss.str(line);
    int test;
    if (! (ss >> test)) { // if line 6 starts w/ a non-integer
        outFile << line << "\n"; // Copy element-line to new file
        getline(inFile, line);  // read next line: #elements
    }
    // Calculate how many atoms
    ss.clear();
    ss.str(line);
    nAtom = 0;
    int add;
    while (ss >> add)
        nAtom += add;
    
    outFile << line << "\n"; // Copy # elements to new file
    getline(inFile, line);      // read Direct or Cartesian
    char DorC = line[0];
    if (DorC == 'c' || DorC == 'C') { // if already cartesian
        cerr << "Error: input file is already Cartesian.\n";
        exit (1);
    }
    outFile << "Cartesian";   // add Cartesian to new file
    double x, y, z; // direct coordinates
    double xx,yy,zz;    // cartesian coordinates
    while (getline(inFile, line)) {
        ss.clear();
        ss.str(line);
        if ((ss >> a >> b >> c)) {
            if (a.length() > 15)
                a = a.substr(0,15);
            if (b.length() > 15)
                b = b.substr(0,15);
            if (c.length() > 15)
                c = c.substr(0,15);
            x = atof(a.c_str());
            y = atof(b.c_str());
            z = atof(c.c_str());
            xx = x * Vec[0][0] + y * Vec[1][0] + z * Vec[2][0];
            yy = x * Vec[0][1] + y * Vec[1][1] + z * Vec[2][1];
            zz = x * Vec[0][2] + y * Vec[1][2] + z * Vec[2][2];
            outFile << "\n" << xx << "  " << yy << "  " << zz;
        }
        else {
            outFile.close();
            exit (0);
        }
    }
    outFile.close();
    exit (0);
}
