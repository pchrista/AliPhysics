#ifndef AliAnalysisTaskSEHFTreeCreator_H
#define AliAnalysisTaskSEHFTreeCreator_H

/* Copyright(c) 1998-2009, ALICE Experiment at CERN, All rights reserved. *
 * See cxx source for full Copyright notice                               */

/* $Id$ */

///*************************************************************************
/// \class AliAnalysisTaskSEHFTreeCreator
/// 
// \authors:
// F. Catalano, fabio.catalano@cern.ch
// A. Festanti, andrea.festanti@cern.ch
// F. Grosa, fabrizio.grosa@cern.ch
// G. Innocenti, gian.michele.innocenti@cern.ch
// F. Prino, prino@to.infn.it
// L. Vermunt, luuk.vermunt@cern.ch
// L. van Doremalen, lennart.van.doremalen@cern.ch
// J. Norman, jaime.norman@cern.ch
// G. Luparello, grazia.luparello@cern.ch
///*************************************************************************

#include <TROOT.h>
#include <TSystem.h>
#include <TNtuple.h>
#include <TTree.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TH3F.h>

#include "AliAnalysisTaskSE.h"
#include "AliRDHFCutsD0toKpi.h"
#include "AliRDHFCutsDstoKKpi.h"
#include "AliRDHFCutsDplustoKpipi.h"
#include "AliRDHFCutsLctopKpi.h"
#include "AliRDHFCutsBPlustoD0Pi.h"
#include "AliRDHFCutsDStartoKpipi.h"
#include "AliNormalizationCounter.h"
#include "AliHFTreeHandler.h"
#include "AliHFTreeHandlerD0toKpi.h"
#include "AliHFTreeHandlerDplustoKpipi.h"
#include "AliHFTreeHandlerDstoKKpi.h"
#include "AliHFTreeHandlerLctopKpi.h"
#include "AliHFTreeHandlerBplustoD0pi.h"
#include "AliHFTreeHandlerDstartoKpipi.h"

class AliAODEvent;

class AliAnalysisTaskSEHFTreeCreator : public AliAnalysisTaskSE
{
public:


    
    AliAnalysisTaskSEHFTreeCreator();
    AliAnalysisTaskSEHFTreeCreator(const char *name,TList *cutsList);
    virtual ~AliAnalysisTaskSEHFTreeCreator();
    
    
    /// Implementation of interface methods
    virtual void UserCreateOutputObjects();
    virtual void Init();
    virtual void LocalInit() {Init();}
    virtual void UserExec(Option_t *option);
    virtual void Terminate(Option_t *option);
    
    
    void SetReadMC(Bool_t opt=kFALSE){fReadMC=opt;}
    void SetSystem(Int_t opt){fSys=opt;}
    void SetAODMismatchProtection(Int_t opt=1) {fAODProtection=opt;}
    void SetWriteOnlySignalTree(Bool_t opt){fWriteOnlySignal=opt;}
    void SetFillD0Tree(Int_t opt){fWriteVariableTreeD0=opt;}
    void SetFillDsTree(Int_t opt){fWriteVariableTreeDs=opt;}
    void SetFillDplusTree(Int_t opt){fWriteVariableTreeDplus=opt;}
    void SetFillLctopKpiTree(Int_t opt){fWriteVariableTreeLctopKpi=opt;}
    void SetFillBplusTree(Int_t opt){fWriteVariableTreeBplus=opt;}
    void SetFillDstarTree(Int_t opt){fWriteVariableTreeDstar=opt;}
    void SetPIDoptD0Tree(Int_t opt){fPIDoptD0=opt;}
    void SetPIDoptDsTree(Int_t opt){fPIDoptDs=opt;}
    void SetPIDoptDplusTree(Int_t opt){fPIDoptDplus=opt;}
    void SetPIDoptLctopKpiTree(Int_t opt){fPIDoptLctopKpi=opt;}
    void SetPIDoptBplusTree(Int_t opt){fPIDoptBplus=opt;}
    void SetPIDoptDstarTree(Int_t opt){fPIDoptDstar=opt;}
    void SetFillMCGenTrees(Bool_t fillMCgen) {fFillMCGenTrees=fillMCgen;}
    
    Int_t  GetSystem() const {return fSys;}
    Bool_t GetWriteOnlySignalTree() const {return fWriteOnlySignal;}
    
    void Process2Prong(TClonesArray *array2prong, AliAODEvent *aod, TClonesArray *arrMC, Float_t bfield);
    void Process3Prong(TClonesArray *array3Prong, AliAODEvent *aod, TClonesArray *arrMC, Float_t bfield);
    void ProcessCasc(TClonesArray *arrayCasc, AliAODEvent *aod, TClonesArray *arrMC, Float_t bfield);
    void ProcessMCGen(TClonesArray *mcarray);
  
    Bool_t CheckDaugAcc(TClonesArray* arrayMC,Int_t nProng, Int_t *labDau);
    AliAODVertex* ReconstructBplusVertex(const AliVVertex *primary, TObjArray *tracks, Double_t bField, Double_t dispersion);
    
private:
    
    AliAnalysisTaskSEHFTreeCreator(const AliAnalysisTaskSEHFTreeCreator&);
    AliAnalysisTaskSEHFTreeCreator& operator=(const AliAnalysisTaskSEHFTreeCreator&);
    
    
    
    TH1F                    *fNentries;                  //!<!   histogram with number of events on output slot 1
    TH2F                    *fHistoNormCounter;          //!<!   histogram with number of events on output slot 1
    TList                   *fListCuts;                  //      list of cuts sent to output slot 2
    AliRDHFCutsD0toKpi      *fFiltCutsD0toKpi;           //      D0toKpi filtering (or loose) cuts
    AliRDHFCutsDstoKKpi     *fFiltCutsDstoKKpi;          //      DstoKKpi filtering (or loose) cuts
    AliRDHFCutsDplustoKpipi *fFiltCutsDplustoKpipi;      //      DplustoKpipi filtering (or loose) cuts
    AliRDHFCutsLctopKpi     *fFiltCutsLctopKpi    ;      //      LctopKpi filtering (or loose) cuts
    AliRDHFCutsBPlustoD0Pi  *fFiltCutsBplustoD0pi;       //      BplustoD0pi filtering (or loose) cuts
    AliRDHFCutsDStartoKpipi *fFiltCutsDstartoKpipi;      //      DstartoKpipi filtering (or loose) cuts
    AliRDHFCutsD0toKpi      *fCutsD0toKpi;               //      D0toKpi analysis cuts
    AliRDHFCutsDstoKKpi     *fCutsDstoKKpi;              //      DstoKKpi analysis cuts
    AliRDHFCutsDplustoKpipi *fCutsDplustoKpipi;          //      DplustoKpipi analysis cuts
    AliRDHFCutsLctopKpi     *fCutsLctopKpi;              //      LctopKpi analysis cuts
    AliRDHFCutsBPlustoD0Pi  *fCutsBplustoD0pi;           //      BplustoD0pi analysis cuts
    AliRDHFCutsDStartoKpipi *fCutsDstartoKpipi;          //      DstartoKpipi analysis cuts
    Bool_t                  fReadMC;                     //     flag for MC array: kTRUE = read it, kFALSE = do not read it
    TList                   *fListCounter;               //!<!   list for normalization counter on output slot 3
    AliNormalizationCounter *fCounter;                   //!<!   AliNormalizationCounter
    Bool_t                  fUseSelectionBit;
    Int_t                   fSys;                        // fSys=0 -> p-p; fSys=1 ->PbPb
    Int_t                   fAODProtection;              // flag to activate protection against AOD-dAOD mismatch.
                                                         // -1: no protection,  0: check AOD/dAOD nEvents only,  1: check AOD/dAOD nEvents + TProcessID names
    Int_t                   fWriteVariableTreeD0;         // flag to decide whether to write the candidate variables on a tree variables
                                                         // 0 don't fill
    													 // 1 fill standard tree
    Int_t                   fWriteVariableTreeDs;         // flag to decide whether to write the candidate variables on a tree variables
 														 // 0 don't fill
   														 // 1 fill standard tree
    Int_t                   fWriteVariableTreeDplus;      // flag to decide whether to write the candidate variables on a tree variables
    													 // 0 don't fill
                                                         // 1 fill standard tree
    Int_t                   fWriteVariableTreeLctopKpi;      // flag to decide whether to write the candidate variables on a tree variables
    													 // 0 don't fill
                                                         // 1 fill standard tree
    Int_t                    fWriteVariableTreeBplus;    // flag to decide whether to write the candidate variables on a tree variables
                                                          // 0 don't fill
                                                          // 1 fill standard tree

    Int_t                  fWriteVariableTreeDstar;      // flag to decide whether to write the candidate variables on a tree variables
    													 // 0 don't fill
                                                         // 1 fill standard tree

    TTree                   *fVariablesTreeD0;           //!<! tree of the candidate variables
    TTree                   *fVariablesTreeDs;           //!<! tree of the candidate variables
    TTree                   *fVariablesTreeDplus;        //!<! tree of the candidate variables
    TTree                   *fVariablesTreeLctopKpi;     //!<! tree of the candidate variables
    TTree                   *fVariablesTreeBplus;        //!<! tree of the candidate variables
    TTree                   *fVariablesTreeDstar;        //!<! tree of the candidate variables
    TTree                   *fGenTreeD0;                 //!<! tree of the gen D0 variables
    TTree                   *fGenTreeDs;                 //!<! tree of the gen Ds variables
    TTree                   *fGenTreeDplus;              //!<! tree of the gen D+ variables
    TTree                   *fGenTreeLctopKpi;           //!<! tree of the gen LctopKpi variables
    TTree                   *fGenTreeBplus;              //!<! tree of the gen B+ variables
    TTree                   *fGenTreeDstar;              //!<! tree of the gen Dstar variables
    TTree                   *fTreeEvChar;                //!<!
    bool                    fWriteOnlySignal;
    AliHFTreeHandlerD0toKpi        *fTreeHandlerD0;             //!<! handler object for the tree with topological variables
    AliHFTreeHandlerDstoKKpi       *fTreeHandlerDs;             //!<! handler object for the tree with topological variables
    AliHFTreeHandlerDplustoKpipi   *fTreeHandlerDplus;          //!<! handler object for the tree with topological variables
    AliHFTreeHandlerLctopKpi       *fTreeHandlerLctopKpi;       //!<! handler object for the tree with topological variables
    AliHFTreeHandlerBplustoD0pi    *fTreeHandlerBplus;          //!<! handler object for the tree with topological variables
    AliHFTreeHandlerDstartoKpipi   *fTreeHandlerDstar;          //!<! handler object for the tree with topological variables
    AliHFTreeHandlerD0toKpi        *fTreeHandlerGenD0;             //!<! handler object for the tree with topological variables
    AliHFTreeHandlerDstoKKpi       *fTreeHandlerGenDs;             //!<! handler object for the tree with topological variables
    AliHFTreeHandlerDplustoKpipi   *fTreeHandlerGenDplus;          //!<! handler object for the tree with topological variables
    AliHFTreeHandlerLctopKpi       *fTreeHandlerGenLctopKpi;       //!<! handler object for the tree with topological variables
    AliHFTreeHandlerBplustoD0pi    *fTreeHandlerGenBplus;          //!<! handler object for the tree with topological variables
    AliHFTreeHandlerDstartoKpipi   *fTreeHandlerGenDstar;          //!<! handler object for the tree with topological variables
    int                     fPIDoptD0;
    int                     fPIDoptDs;
    int                     fPIDoptDplus;
    int                     fPIDoptLctopKpi;
    int                     fPIDoptBplus;
    int                     fPIDoptDstar;
    Float_t                 fCentrality;
    Float_t                 fzVtxReco;
    Float_t                 fzVtxGen;
    Int_t                   fNcontributors;
    Int_t                   fNtracks;
    Int_t                   fIsEvRej;
    Int_t                   fRunNumber;

    Bool_t                  fFillMCGenTrees;
    
    
    /// \cond CLASSIMP
    ClassDef(AliAnalysisTaskSEHFTreeCreator,3);
    /// \endcond
};

#endif

