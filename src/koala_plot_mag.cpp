#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main (int argc, char *argv[]) {
    double scale;  // Scale for magnetic moments
    double l2;           // line 2 in CONTCAR
    double l345 [3][3];  // line 3-5 CONTCAR
    vector<string> l6;   // line 6 CONTCAR
    vector<int> l7;      // line 7 CONTCAR
    char l8;             // line 8 CONTCAR
    int nElem;           // # elements
    int nAtom;           // # atoms
    ifstream CONTCAR;    // to open CONTCAR
    string line;         // to read a line
    string word;         // to read a word in a line
    int num;             // to read a number in a line
    istringstream iss;   // to operate a line

    // Read scale from input parameter
    if (argc == 1) // Default scale=0.5
        scale = 0.5;
    else
        scale = atof (argv[1]);

    // Part I. Read CONTCAR
    CONTCAR.open ("CONTCAR");
    if (!CONTCAR) {
        cerr << "Cannot open CONTCAR.\n";
        exit(1);
    }
    getline(CONTCAR, line);    // ignore first line
    getline(CONTCAR, line);    // read line 2: LP
    iss.str(line);
    iss >> l2;
    for (int i = 0; i < 3; i++) { // read lat vectors
        getline(CONTCAR, line);
        iss.str(line);
        iss >> l345[i][0] >> l345[i][1] >> l345[i][2];
    }
    getline(CONTCAR, line);    // read name of elements
    while (iss >> word)
        l6.push_back (word);
    getline(CONTCAR, line);// Read #atom of  each element
    iss.str(line);
    while (iss >> num)     
        l7.push_back (num);
    nElem = l7.size(); // Calculate # of elements
    nAtom = 0;   // Calculate # of all atoms
    for (int i = 0; i < nElem; i++)
        nAtom += l7.at (i);
    getline(CONTCAR, line);    // check D or C: line 8
    l8 = line[0];
    double atoms [nAtom][3];   // read atomic positions
    for (int i = 0; i < nAtom; i++) {
        getline(CONTCAR, line);
        iss.str(line);
        iss >> atoms[i][0] >> atoms[i][1] >> atoms[i][2];
    }
    if (l8 == 'd' || l8 == 'D') { // if "Direct", convert to cart
        double arr[nAtom][3];
        for (int i = 0; i < nAtom; i++) {
            arr[i][0] = atoms[i][0] * l345[0][0]
                      + atoms[i][1] * l345[1][0]
                      + atoms[i][2] * l345[2][0];
            arr[i][1] = atoms[i][0] * l345[0][1]
                      + atoms[i][1] * l345[1][1]
                      + atoms[i][2] * l345[2][1];
            arr[i][2] = atoms[i][0] * l345[0][2]
                      + atoms[i][1] * l345[1][2]
                      + atoms[i][2] * l345[2][2];
            atoms[i][0] = arr[i][0];
            atoms[i][1] = arr[i][1];
            atoms[i][2] = arr[i][2];
        }
    }

    // Part II. Read OUTCAR.
    int para1 = 23 + 3 * nAtom;
    int para2 = para1 + 1;
    stringstream ss;
    ss << "tail -1000 OUTCAR | grep -A " << para1 
       << " \"magnetization (x) \" | tail -" << para2
       << " > mag.tmp";
    char *cmd;
    ss >> *cmd;
    system(cmd);

}
