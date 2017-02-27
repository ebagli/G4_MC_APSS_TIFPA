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

#include "SensitiveDetector.hh"
#include "SensitiveDetectorHit.hh"
#include "G4HCofThisEvent.hh"
#include "G4TouchableHistory.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"
#include "G4Navigator.hh"
#include "G4ios.hh"

SensitiveDetector::SensitiveDetector(G4String name):
G4VSensitiveDetector(name){
    G4String HCname;
    collectionName.insert(HCname="collection");
    fHCID = -1;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

SensitiveDetector::~SensitiveDetector(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void SensitiveDetector::Initialize(G4HCofThisEvent*HCE){
    fHitsCollection =
        new SensitiveDetectorHitsCollection(SensitiveDetectorName,
                                                        collectionName[0]);
    if(fHCID<0){
        fHCID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);
    }
    HCE->AddHitsCollection(fHCID,fHitsCollection);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4bool SensitiveDetector::ProcessHits(G4Step*aStep,
                                                  G4TouchableHistory*){
    
    // Save only the first step of the particle in the detector
    G4StepPoint* preStepPoint = aStep->GetPreStepPoint();
    if(!(preStepPoint->GetStepStatus() == fGeomBoundary)) return true;

    // Get the copyNo of the detector, if we have more than one detector
    G4TouchableHistory* theTouchable = (G4TouchableHistory*)(preStepPoint->GetTouchable());
    G4int copyNo = (theTouchable->GetVolume(0))->GetCopyNo();;
    
    // Save the hit position and the particle ID, i.e. if it is primary or secondary
    SensitiveDetectorHit* aHit = new SensitiveDetectorHit(copyNo);
    aHit->SetTrackID(aStep->GetTrack()->GetTrackID());
    aHit->SetParticleID(aStep->GetTrack()->GetParticleDefinition()->GetPDGEncoding());
    aHit->SetWorldPos(preStepPoint->GetPosition());
    
    fHitsCollection->insert(aHit);
    return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void SensitiveDetector::EndOfEvent(G4HCofThisEvent* /*HCE*/){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
