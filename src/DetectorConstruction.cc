//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//

#include "DetectorConstruction.hh"
#include "G4RunManager.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"

#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "SensitiveDetector.hh"
#include "G4SDManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction(){;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

DetectorConstruction::~DetectorConstruction(){;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

void DetectorConstruction::DefineMaterials(){;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct(){
    //** World **//
    //G4Material* Galactic = G4NistManager::Instance()->FindOrBuildMaterial("G4_Galactic");
    G4Material* Air = G4NistManager::Instance()->FindOrBuildMaterial("G4_AIR");
    
    G4Material* worldMaterial  = Air;
    G4double worldSizeXY = 20. * CLHEP::meter;
    G4double worldSizeZ = 20. * CLHEP::meter;
    
    G4Box* worldSolid = new G4Box("world.solid",
                                  worldSizeXY/2.,
                                  worldSizeXY/2.,
                                  worldSizeZ/2.);
    
    G4LogicalVolume* worldLogic = new G4LogicalVolume(worldSolid,
                                                      worldMaterial,
                                                      "world.logic");
    
    G4PVPlacement* worldPhysical = new G4PVPlacement(0,
                                                     G4ThreeVector(),
                                                     worldLogic,
                                                     "world.physic",
                                                     0,
                                                     false,
                                                     0);
    
    
    //** Collimator **//
    G4Material* W     = G4NistManager::Instance()->FindOrBuildMaterial("G4_W");
    G4double collRin   = 0.200 * CLHEP::mm;
    G4double collRout  = 5. * CLHEP::cm;
    G4double collL     = 5. * CLHEP::cm;
    G4double coll2dist = 2. * CLHEP::m + collL;
    
    G4Tubs* collSolid = new G4Tubs("coll.solid",
                                   collRin,
                                   collRout,
                                   collL * 0.5,
                                   0.   * CLHEP::degree,
                                   360. * CLHEP::degree);
    
    G4LogicalVolume* collLogic = new G4LogicalVolume(collSolid,
                                                     W,
                                                     "coll.logic");
    
    
    new G4PVPlacement(0,
                      G4ThreeVector(0.,0.,collL*0.5),
                      collLogic,
                      "coll.physic",
                      worldLogic,
                      false,
                      0);
    
    new G4PVPlacement(0,
                      G4ThreeVector(0.,0.,collL*0.5 + coll2dist),
                      collLogic,
                      "coll.physic",
                      worldLogic,
                      false,
                      1);
    
    //** Lead Bricks instantiation **//
    G4Material* Pb     = G4NistManager::Instance()->FindOrBuildMaterial("G4_Pb");
    G4double lbdist    = coll2dist + collL * 0.5 + 30. * CLHEP::cm;

    G4double lbIntY    = 5. * CLHEP::mm;
    G4double lbIntX    = 5. * CLHEP::mm;
    
    G4double lbX = 60. * CLHEP::cm;
    G4double lbZ = 20. * CLHEP::cm;
    G4double lbY = 60. * CLHEP::cm;

    G4double lbIntXdim = (lbX - lbIntX)/2.;
    

    G4Box* lbSolid = new G4Box("lb.solid",
                               lbX/2.,
                               lbY/2.,
                               lbZ/2.);
    
    G4LogicalVolume* lbLogic = new G4LogicalVolume(lbSolid,
                                                   Pb,
                                                   "lb.logic");
    

    new G4PVPlacement(0,
                      G4ThreeVector(0.,+(lbY+lbIntY)*0.5,lbdist),
                      lbLogic,
                      "lb.physic",
                      worldLogic,
                      false,
                      0);
    
    new G4PVPlacement(0,
                      G4ThreeVector(0.,-(lbY+lbIntY)*0.5,lbdist),
                      lbLogic,
                      "lb.physic",
                      worldLogic,
                      false,
                      1);

    G4Box* lbInterspaceSolid = new G4Box("lbInt.solid",
                                         lbIntXdim/2.,
                                         lbIntY/2.,
                                         lbZ/2.);
    
    G4LogicalVolume* lbInterspaceLogic = new G4LogicalVolume(lbInterspaceSolid,
                                                             worldMaterial,
                                                             "lbInt.logic");
    
    new G4PVPlacement(0,
                      G4ThreeVector(+(lbIntXdim+lbIntX)*0.5,0.,lbdist),
                      lbInterspaceLogic,
                      "lb.physic",
                      worldLogic,
                      false,
                      0);
    
    new G4PVPlacement(0,
                      G4ThreeVector(-(lbIntXdim+lbIntX)*0.5,0.,lbdist),
                      lbInterspaceLogic,
                      "lb.physic",
                      worldLogic,
                      false,
                      1);

    //** Detectors instantiation **//
    G4double ssdSizeXY = 500. * CLHEP::centimeter;
    G4double ssdSizeZ  = 1. * CLHEP::millimeter;
    G4double det1dist  = coll2dist + collL * 0.5 + 15. * CLHEP::cm;
    G4double det2dist  = coll2dist + collL * 0.5 + 3. * CLHEP::m;
    
    G4double detABdist = 1. * CLHEP::centimeter;
    
    G4Box* ssdSolid = new G4Box("ssd.solid",
                                ssdSizeXY/2.,
                                ssdSizeXY/2.,
                                ssdSizeZ/2.);
    
    G4LogicalVolume* ssdLogic = new G4LogicalVolume(ssdSolid,
                                                    worldMaterial,
                                                    "ssd.logic");
    
    
    G4double ssdDist[4] = {
        det1dist + ssdSizeZ * 0.5,
        det1dist + ssdSizeZ * 1.5,
        det2dist + ssdSizeZ * 0.5,
        det2dist + ssdSizeZ * 1.5};
    
    for(size_t i1=0;i1<4;i1++){
        new G4PVPlacement(0,
                          G4ThreeVector(0.,0.,ssdDist[i1]),
                          ssdLogic,
                          "ssd.physic",
                          worldLogic,
                          false,
                          i1);
    }
    
    
    
    
    return worldPhysical;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::ConstructSDandField(){
    G4LogicalVolume* ssdLogic = G4LogicalVolumeStore::GetInstance()->GetVolume("ssd.logic");
    G4VSensitiveDetector* telescope = new SensitiveDetector("/telescope");
    G4SDManager::GetSDMpointer()->AddNewDetector(telescope);
    for(unsigned int i1=0;i1<3;i1++){
        ssdLogic->SetSensitiveDetector(telescope);
    }
    
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

