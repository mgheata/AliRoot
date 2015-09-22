//-*- Mode: C++ -*-
// $Id$
#ifndef ALIHLTLUMIREGCOMPONENT_H
#define ALIHLTLUMIREGCOMPONENT_H
/* This file is property of and copyright by the ALICE HLT Project        *
 * ALICE Experiment at CERN, All rights reserved.                         *
 * See cxx source for full Copyright notice                               */

/**
 * Class for Luminous Region determination in the HLT
 *
 * @file   AliHLTLumiRegComponent.h
 * @author Davide Caffarri <davide.caffarri@cern.ch> 
 * @date   January 2015
 * @brief  Luminous Region calculation component
 */


#include "AliHLTProcessor.h"
//#include "AliHLTCalibrationProcessor.h"
#include "TH1F.h"
#include "AliVEvent.h"
#include "AliCDBEntry.h"
#include "AliGRPObject.h"
#include "AliCDBManager.h"
#include "AliFlatESDEvent.h"
#include "TF1.h"

class AliHLTLumiRegComponent : public AliHLTProcessor
{

public:
  /** standard constructor*/
  AliHLTLumiRegComponent();
  /** standard descructor */
  virtual ~AliHLTLumiRegComponent();
  
  // Public functions to implement AliHLTComponent's interface.
  // These functions are required for the registration process
  
  /** @see component interface @ref AliHLTComponent::GetComponentID */
  const char* GetComponentID() {return "LumiRegComponent";}
  /** @see component interface @ref AliHLTComponent::GetInputDataTypes */
  void GetInputDataTypes( vector<AliHLTComponentDataType>& list )  ;
  /** @see component interface @ref AliHLTComponent::GetOutputDataType */
  AliHLTComponentDataType GetOutputDataType() ;
  
  /** @see component interface @ref AliHLTComponent::GetOutputDataSize */
  virtual void GetOutputDataSize( unsigned long& constBase, double& inputMultiplier ) ;
  
  //not sure i need it for the moment
  //void GetOCDBObjectDescription(TMap *const targetMap);
  
  /** @see component interface @ref AliHLTComponent::Spawn */
  AliHLTComponent* Spawn();
  
  Int_t ReadInput(AliVEvent *& vEvent);

  enum eventSpecie {kpp, kpPb, kPbPb};
  
protected:
  int DoInit(int argc, const char** argv);
  int DoDeinit();
  
  int DoEvent(int argc, const char **argv);
  
  
  using AliHLTProcessor::DoEvent;
 
  Int_t FitPositions(TH1F *histos[], Float_t* mean, Float_t* sigma);
  Int_t LuminousRegionExtraction(TH1F *histos[], Float_t* meanLR, Float_t* sigmaLR);
  Int_t FitHistos(TH1F *hVtx, Float_t &mean,  Float_t &sigma, Float_t rangelow = -1 , Float_t rangeup = 1);
  
private:
  /** copy constructor */
  AliHLTLumiRegComponent( const AliHLTLumiRegComponent& );
  /** dummy assignment op */
  AliHLTLumiRegComponent& operator=( const AliHLTLumiRegComponent& );
  
  Int_t fPushBackPeriodLHC;
  Int_t fPushBackPeriodDQM;
  Int_t fLastPushBackTime;
  
 // TH1F *fPrimaryX[2];
 // TH1F *fPrimaryY[2];
 // TH1F *fPrimaryZ[2];
  
  TH1F *fPrimaryLHC[3];
  TH1F *fPrimaryDQM[3];

  TH1F *fPrimaryDefMultLHC[2];
  TH1F *fPrimaryDefMultDQM[2];
  
  
//  TH1F *fPrimaryXDefMult[2];
//  TH1F *fPrimaryYDefMult[2];
  
  Int_t fEventSpecie;

 
};

#endif /* defined(____AliHLTLumiRegComponent__) */
