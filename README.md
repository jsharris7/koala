# *koala*
## What is *koala*?
*koala* is a toolkit for HPC users at NCSU. It is written in C-Shell language or C++. 

Here is a quick look at what *koala* can do.

- koala
    - List all the following commands.
- koala_dire2cart [file]
    - Convert "Direct" to "Cartesian".
    - Input: POSCAR (default)
    - Output: [file].cart
- koala_elec_entro
    - Calculate electronic entropy.
    - Input: DOSCAR
    - Output: Elec_entropy.dat
- koala_kill
    - Kill LSF jobs based on user selection.
- koala_monitor
    - Keep an eye on finished LSF jobs.
    - Runs on background.
    - Finished jobs saved at ~/.koala
- koala_plot_dos
    - Plot Total DOS.
    - Input: DOSCAR
    - Output: TDOS.png
- koala_plot_mag
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
