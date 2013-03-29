# *koala*
## What is *koala*?
*koala* is a toolkit for HPC users at NCSU. It is written in C-Shell language or C++. *koala* assists users in some common works so that users can take a break on a tree like a koala.

- `koala`
    - List all *koala* commands.
- `koala_dire2cart [FILE]`
    - Convert "Direct" to "Cartesian".
    - Input: POSCAR (default) or [FILE]
    - Output: [FILE].cart
- `koala_elec_entro`
    - Calculate electronic entropy.
    - Input: DOSCAR
    - Output: Elec_entropy.dat
- `koala_emto_mur`
    - Fit Murnaghan EOS for EMTO-CPA results.
- `koala_espr_mur`
    - Fit Murnaghan EOS for ESPRESSO results.
- `koala_kill`
    - Kill LSF jobs selected by user.
- `koala_monitor`
    - Save all finished LSF jobs (running in background).
    - Finished jobs saved at ~/.koala
- `koala_plot_dos`
    - Plot Total DOS (Fermi level as zero).
    - Input: DOSCAR
    - Output: TDOS.png
- `koala_plot_mag`
    - Plot animation of magnetic moments.
    - Input: CONTCAR, OUTCAR
    - Output: mag.gif
- `koala_vasp_mur`
    - Fit Murnaghan EOS for VASP calculations.
    - Input: CONTCAR&OSZICAR in all sub-directories
    - Output: mur_fit.out

## Installation
This instruction will guide users to store the source code of *koala* at `$HOME/Apps/koala/koala-master`, executables of *koala* at `$HOME/Apps/koala/bin`, soft links at `$HOME/bin` which point to the executables of *koala*. If user decides to follow exactly this instruction, please make sure `$HOME/bin` is in the `PATH`, that is, add `setenv PATH $HOME/bin:$PATH` to `$HOME/.tcshrc`.

If user prefers other ways, please make suitable changes when following the instruction. It is not difficult.

### 1. Install or update *koala*
Copy the following to run.tcsh, then `tcsh run.tcsh`.
```tcsh
#! /bin/tcsh
mkdir -p $HOME/Apps/koala
cd $HOME/Apps/koala
rm -r koala-master bin master*
wget --no-check-certificate https://github.com/changning/koala/archive/master.zip
unzip master
cd koala-master
vi Install
./Install
```

### 2. Install necessary softwares
Some *koala* executables need additional softwares in order to work properly. Check whether you need to install additional softwares.

- `koala`
    - None
- `koala_dire2cart`
    - None
- `koala_elec_entro`
    - None
- `koala_emto_mur`
    - mur_fit.f by Andrei Postnikov
- `koala_espr_mur`
    - mur_fit.f by Andrei Postnikov
- `koala_kill`
    - None
- `koala_monitor`
    - None
- `koala_plot_dos`
    - Gnuplot 4.6.2
- `koala_plot_mag`
    - Gnuplot 4.6.2
- `koala_vasp_mur`
    - mur_fit.f by Andrei Postnikov

#### 2.1 Install Gnuplot 4.6.2:
```tcsh
mkdir ~/Apps/Gnuplot
cd ~/Apps/Gnuplot
wget --no-check-certificate http://downloads.sourceforge.net/project/gnuplot/gnuplot/4.6.2/gnuplot-4.6.2.tar.gz
tar xzf gnuplot-4.6.2.tar.gz
cd gnuplot-4.6.2
./configure --prefix=$HOME/Apps/Gnuplot
make
make install
ln -s $HOME/Apps/Gnuplot/bin/gnuplot $HOME/bin/gnuplot
```

#### 2.2 Install mur_fit.f
```tcsh
mkdir ~/Apps/mur_fit
cd ~/Apps/mur_fit
wget http://www.home.uni-osnabrueck.de/apostnik/Software/mur_fit.f
gfortran mur_fit.f -o mur_fit
ln -s $HOME/Apps/mur_fit/mur_fit $HOME/bin/mur_fit
```

## Usage
### koala
Synopsis: `koala`

Anytime you want to use a *koala* command but forget the exact name, type `koala`. It will display all the *koala* commands.

### koala_dire2cart
Synopsis: `koala_dire2cart [FILE]`

It converts the file given by user (POSCAR if not given) from *direct* to *Cartesian*. The file must follow the format of POSCAR in VASP. The Cartesian-formated file is saved as `[FILE].cart`.

### koala_elec_entro
Synopsis: `koala_elec_entro`

Make sure a DOSCAR is in the present working directory. It will calculate the electronic entropy as S = -k_B * integral(n * (f*ln(f)+(1-f)*ln(1-f))dE), where f is the Fermi distribution function, n is the density of states. The electronic entropy as a function of temperature will be saved as `Elec_entropy.dat`.

### koala_emto_mur
Synopsis: `koala_emto_mur`

This code works with EMTO-CPA calculations.

### koala_espr_mur
Synopsis: `koala_espr_mur`

This code works with ESPRESSO (pwscf) calculations.

### koala_kill
Synopsis: `koala_kill`

After typing this command, a VIM file that shows all running jobs will pop up. Edit this file and leave only jobs to kill and quit VIM. The left jobs will be automatically killed after confirmation.

### koala_monitor
Synopsis: `koala_monitor`

You only need to run this command once. After typing this command, close the current terminal (otherwise it will keep popping up disturbing messages) and start a new one. It runs `bjobs -d` every hour and saves your finished jobs at `$HOME/.koala/finished.jobs`. It also saves more details about the finished jobs (`bjobs -l -d`) at `$HOME/.koala/finished.details`. Users can check whether it is running by checking whether `$HOME/.koala/running` exists. To stop the monitor, type `touch $HOME/.koala/stop` and wait for an hour. If it is stopped, `$HOME/.koala/stopped` will show up.

### koala_plot_dos
Synopsis: `koala_plot_dos`

Make sure a DOSCAR is in the present working directory. Make sure Gnuplot 4.6.2 has been installed. It re-calculates energies by setting the Fermi level as zero. Then it generates TDOS.png using gnuplot. It is expected that this command cannot generate TODS.png as user wants. Try ``vim `which koala_plot_dos` `` and change the gnuplot settings.

### koala_plot_mag
Synopsis: `koala_plot_mag`

Make sure a CONTCAR and an OUTCAR is in the present working directory. Make sure Gnuplot 4.6.2 has been installed. It draws arrows that represent magnetic moments in both direction and magnitude on each atom. It plots 36 static images with viewing angle shifted by 10 degree using gnuplot. Then it uses ImageMagick (already installed on HPC) to convert these images to an animation gif named `mag.gif`. Try ``vim `which koala_plot_mag` `` and change the gnuplot settings for you needs.

### koala_vasp_mur
Synopsis: `koala_vasp_mur`

This command is only useful in such situation: each sub-directory is an individual VASP calculation with a changing volume. It finds volume and energy from CONTCAR and OSZICAR from all sub-directories, and fits these data to the Murnaghan EOS. The fitting results will be saved as `mur_fit.out`. The fitting is done by mur_fit.f which is written by Andrei Postnikov.
