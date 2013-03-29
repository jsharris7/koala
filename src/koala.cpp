// koala.cpp
// It displays all koala commands.
//
// Author: Changning Niu (cniu@ncsu.edu)
// Updated: 03-29-2013

#include <iostream>

using namespace std;

int main (){
    cout << " koala             - Displays all koala commands.\n";
    cout << " koala_dire2cart   - Convert direct to cartesian for VASP.\n";
    cout << " koala_elec_entro  - Calculate electronic entropy from DOSCAR.\n";
    cout << " koala_emto_mur    - Fit murnaghan EOS for EMTO-CPA.\n";
    cout << " koala_espr_mur    - Fit murnaghan EOS for ESPRESSO.\n";
    cout << " koala_kill        - Kill selected LSF jobs.\n";
    cout << " koala_monitor     - Background LSF monitor.\n";
    cout << " koala_plot_dos    - Plot TDOS from DOSCAR.\n";
    cout << " koala_plot_mag    - Plot magnetic moments from CONTCAR&OUTCAR.\n";
    cout << " koala_vasp_mur    - Fit murnaghan EOS for VASP.\n";


    return 0;
}
