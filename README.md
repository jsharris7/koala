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

### 1. Install Github
```shell
mkdir ~/Apps/Github
cd ~/Apps/Github
wget --no-check-certificate https://github.com/git/git/archive/master.zip
unzip master
cd git-master
make configure
./configure --prefix=$HOME/Apps/Github
make all
make install
```

### koala_plot_mag
1. Install latest ImageMagick.

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
