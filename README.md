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

## Installation
This instruction will guide users to store the source code of *koala* at `$HOME/Apps/koala/koala-master`, executables of *koala* at `$HOME/Apps/koala/bin`, soft links at `$HOME/bin` which point to the executables of *koala*. If user decides to follow exactly this instruction, please make sure `$HOME/bin` is in the `PATH`, that is, add `setenv PATH $HOME/bin:$PATH` to `$HOME/.tcshrc`.

If user prefers other ways, please make suitable changes when following the instruction. It is not difficult.

### 1. Install *koala*
```tcsh
mkdir ~/Apps/koala
cd ~/Apps/koala
wget --no-check-certificate https://github.com/changning/koala/archive/master.zip
unzip master
cd koala-master
vi Install
./Install
```

### 2. Install necessary softwares
Some *koala* executables need newer versions of some softwares on the HPC@NCSU in order to work properly. Check the following list and decide whether you need to install additional softwares.

- `koala`
    - None
- `koala_dire2cart`
    - None
- `koala_elec_entro`
    - None
- `koala_kill`
    - None
- `koala_monitor`
    - None
- `koala_plot_dos`
    - Gnuplot 4.6.2
- `koala_plot_mag`
    - Gnuplot 4.6.2
    - ImageMagick 6.8.4-4
- `koala_vasp_mur`
    - mur_fit.f by Andrei Postnikov

Install Gnuplot 4.6.2:
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

```shell
mkdir ~/Apps/ImageMagick
cd ~/Apps/ImageMagick
wget http://www.imagemagick.org/download/ImageMagick.tar.gz
tar xzf ImageMagick.tar.gz
cd ImageMagick*
./configure --prefix=~/Apps/ImageMagick
make
make install
````

2. Install latest Gnuplot

```shell
mkdir ~/Apps/Gnuplot
cd ~/Apps/Gnuplot
wget http://downloads.sourceforge.net/project/gnuplot/gnuplot/4.6.2/gnuplot-4.6.2.tar.gz
tar xzf gnuplot-4.6.2.tar.gz
cd gnuplot-4.6.2
./configure --prefix=~/Apps/Gnuplot
make
make install
```
