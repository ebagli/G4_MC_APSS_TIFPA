# TIFPA Line Geant4 Simulation

## 1. Introduction

Geant4 simulation of the AXIAL INFN-CSNV experiment at the TIFPA line in the [APSS protontherapy facility](https://www.apss.tn.it/protonterapia) in Trento (Italy).

## 2. Experimental Setup

The setup is composed by two collimators after the nozzle, a brick wall to eliminate the particle scattered at high-angle and two pairs of virtual detectors.
The target to be tested is going to be placed after 15 cm from the end of the second collimator, after the break wall.

## 3. Installation

The application requires [Geant4 10.3](www.geant4.org).
Geant4 is a toolkit for the simulation of the passage of particles through matter.
Its areas of application include high energy, nuclear and accelerator physics, as well as studies in medical and space science.
The three main reference papers for Geant4 are:
- [Nuclear Instruments and Methods in Physics Research A 506 (2003) 250-303](http://www.sciencedirect.com/science/article/pii/S0168900203013688)
- [IEEE Transactions on Nuclear Science 53 No. 1 (2006) 270-278](http://ieeexplore.ieee.org/xpls/abs_all.jsp?isnumber=33833&arnumber=1610988&count=33&index=7)
- [Nuclear Instruments and Methods in Physics Research A 835 (2016) 186-225](http://www.sciencedirect.com/science/article/pii/S0168900216306957)

The source code can be found also on [GitHub](https://github.com/Geant4/geant4/tree/geant4-10.3-release).

After the installation of the Geant4 10.3 libraries, the code can be compiled via [CMake](www.cmake.org).

## 4. Usage

The application can be launched via the apsstifpa executable and the macros

`./apsstifpa mac/vacuum.in`

The output of the application is a [ROOT](https://root.cern.ch) file with the hit position on the first and third detector and the particle angle between the first and second detector and between the third and fourth detectors.
