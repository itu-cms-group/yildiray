// -*- C++ -*-
//
// Package:    AllAn/AllAnalyzer
// Class:      AllAnalyzer
// 
/**\class AllAnalyzer AllAnalyzer.cc AllAn/AllAnalyzer/plugins/AllAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Yildiray Komurcu
//         Created:  Wed, 07 Sep 2016 10:50:07 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TH1.h"

#include "DataFormats/JetReco/interface/PFJet.h"
#include "DataFormats/JetReco/interface/PFJetCollection.h"

#include "DataFormats/METReco/interface/PFMET.h"
#include "DataFormats/METReco/interface/PFMETCollection.h"

#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"

#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h"


//
// class declaration
//

class AllAnalyzer : public edm::EDAnalyzer {
   public:
      explicit AllAnalyzer(const edm::ParameterSet&);
      ~AllAnalyzer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
      //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

      // ----------member data ---------------------------
      TH1F *histojet1, *histojet2, *histojet3;
      TH1F *histomet1, *histomet2, *histomet3; 
      TH1F *histomuon1, *histomuon2, *histomuon3;
      TH1F *histogsfE1, *histogsfE2, *histogsfE3;  
      double pt, eta, phi;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
AllAnalyzer::AllAnalyzer(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed
   edm::Service<TFileService> abc;
   histojet1 = abc->make<TH1F>("Jet_pt" , "p_{t}" , 100 , 0 , 400 );
   histojet2 = abc->make<TH1F>( "Jet_eta", "#eta", 100, -6, 6 );  
   histojet3 = abc->make<TH1F>( "Jet_phi", "#phi", 100, -4, 4);

   edm::Service<TFileService> def;
   histomet1 = def->make<TH1F>("MET_pt" , "p_{t}" , 100 , 0 , 200 );
   histomet2 = def->make<TH1F>( "MET_eta", "#eta", 100, -1, 1 );
   histomet3 = def->make<TH1F>( "MET_phi", "#phi", 100, -4, 4);

   edm::Service<TFileService> gh;
   histomuon1 = gh->make<TH1F>("Muon_pt" , "p_{t}" , 100 , 0 , 280 );
   histomuon2 = gh->make<TH1F>( "Muon_eta", "#eta", 100, -3, 3 );  
   histomuon3 = gh->make<TH1F>( "Muon_phi", "#phi", 100, -3.6, 3.6);

   edm::Service<TFileService> ijk;
   histogsfE1 = ijk->make<TH1F>("GsfElectron_pt" , "p_{t}" , 100 , 0 , 300 );
   histogsfE2 = ijk->make<TH1F>( "GsfElectron_eta", "#eta", 100, -3, 3 );
   histogsfE3 = ijk->make<TH1F>( "GsfElectron_phi", "#phi", 100, -3.6, 3.6);

}



AllAnalyzer::~AllAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
AllAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   edm::Handle<reco::PFJetCollection> pfjet;
   iEvent.getByLabel("kt4PFJets", pfjet);
   

   for ( reco::PFJetCollection::const_iterator jet = pfjet->begin(); jet != pfjet->end(); ++jet ) {
   pt = jet->pt();
   eta = jet->eta();
   phi = jet->phi();
   histojet1->Fill(jet->pt());
   histojet2->Fill(jet->eta());
   histojet3->Fill(jet->phi());

}  

   edm::Handle<reco::PFMETCollection> pfmet;
   iEvent.getByLabel("pfMet", pfmet);

   for ( reco::PFMETCollection::const_iterator met = pfmet->begin(); met != pfmet->end(); ++met ) {
   pt = met->pt();
   eta = met->eta();
   phi = met->phi();
   histomet1->Fill(met->pt());
   histomet2->Fill(met->eta());
   histomet3->Fill(met->phi());

}

   edm::Handle<reco::MuonCollection> mu;
   iEvent.getByLabel("muons", mu);

   for ( reco::MuonCollection::const_iterator muon = mu->begin(); muon != mu->end(); ++muon ) {
   pt = muon->pt();
   eta = muon->eta();
   phi = muon->phi();
   histomuon1->Fill(muon->pt());
   histomuon2->Fill(muon->eta());
   histomuon3->Fill(muon->phi());
}

   edm::Handle<reco::GsfElectronCollection> gsfelec;
   iEvent.getByLabel("gsfElectrons", gsfelec);

   for ( reco::GsfElectronCollection::const_iterator elec  = gsfelec->begin(); elec != gsfelec->end(); ++elec ) {
   pt = elec->pt();
   eta = elec->eta();
   phi = elec->phi();
   histogsfE1->Fill(elec->pt());
   histogsfE2->Fill(elec->eta());
   histogsfE3->Fill(elec->phi());

}
#ifdef THIS_IS_AN_EVENT_EXAMPE
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif
   
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
}


// ------------ method called once each job just before starting event loop  ------------
void 
AllAnalyzer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
AllAnalyzer::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
/*
void 
AllAnalyzer::beginRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a run  ------------
/*
void 
AllAnalyzer::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when starting to processes a luminosity block  ------------
/*
void 
AllAnalyzer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a luminosity block  ------------
/*
void 
AllAnalyzer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
AllAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(AllAnalyzer);
