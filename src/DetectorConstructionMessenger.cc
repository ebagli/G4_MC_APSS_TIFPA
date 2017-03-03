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

#include "DetectorConstructionMessenger.hh"
#include "DetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4RunManager.hh"
#include "G4ios.hh"

DetectorConstructionMessenger::
DetectorConstructionMessenger(
        DetectorConstruction* mpga)
:fTarget(mpga){
    fMyDirectory = new G4UIdirectory("/mydet/");
    fMyDirectory->SetGuidance("Setup control commands.");

    fWorldMaterialCmd = new G4UIcmdWithAString("/mydet/setWorldMaterial",this);
    fWorldMaterialCmd->SetGuidance("Set world material.");
    fWorldMaterialCmd->SetParameterName("worldMat",true);
    fWorldMaterialCmd->SetDefaultValue("G4_Galactic");

    fConfiguration = new G4UIcmdWithAString("/mydet/setConfiguration",this);
    fConfiguration->SetGuidance("Set detector configuration.");
    fConfiguration->SetParameterName("config",true);
    fConfiguration->SetDefaultValue("");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

DetectorConstructionMessenger::
~DetectorConstructionMessenger(){
    delete fWorldMaterialCmd;
    delete fConfiguration;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void DetectorConstructionMessenger::SetNewValue(G4UIcommand *command,
                                                G4String newValue){
    if(command==fWorldMaterialCmd ){
        fTarget->SetWorldMaterial(newValue);
    }
    if(command==fConfiguration ){
        fTarget->SetConfiguration(newValue);
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4String DetectorConstructionMessenger::GetCurrentValue(G4UIcommand * command){
    G4String cv;
    
    if( command==fWorldMaterialCmd ){
        cv = fTarget->GetWorldMaterial();
    }
    if( command==fConfiguration ){
        cv = fTarget->GetConfiguration();
    }
    
    return cv;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
