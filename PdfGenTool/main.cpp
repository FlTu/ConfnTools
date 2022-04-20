/********************************************************************************
 **********                                                            **********
 **********     Auteur                        : Florent TURRI          **********
 **********     Date de création              : 11/04/2022             **********
 **********     Date de dernière modification : 13/04/2022             **********
 **********                                                            **********
 ********************************************************************************/
/** CPP Includes **/

#include <fstream>
#include <iostream>
#include <filesystem>
#include <string>
/** C Includes **/

#include <podofo-base.h>
#include <podofo.h>

/** external includes **/
#include <regex.hpp> // boost lib

/** internal includes **/
#include "Parametres.h"
#include "Parser.h"
#include "IOPdf.h"

/** Namespace **/
using namespace PoDoFo;


/** Headers **/

int parse_input(int numArg, char ** args);


/** Functions **/

int parse_input(int numArg, char ** args)
{
  return 0;
}

/** MAIN **/



/**
 * @Func Main
 *  
 **/
int main(int argc, char ** argv)
{
  Parser * mParser = new Parser();
  try{
    Parametres mParameters = Parser::ParseParameters(argc, argv);
    IOPdf * mOutputPdf = mParser->ParseInputFile(mParameters.GetInputFileName());
    std::fstream inputFile(mParameters.GetInputFileName(), inputFile.in);
    try{
      if(mParameters.GetOutputFileName() != ""){
        mOutputPdf->SetOutputDocumentName(mParameters.GetOutputFileName());
      }
      else{
        mOutputPdf->SetOutputDocumentName(mParameters.GetInputFileName());
      }
    }catch(const std::exception e){
      std::cout << "[Erreur] " << e.what() << "Impossible de définir le nom du document de sortie" << std::endl;
    }
    try{
      mOutputPdf->WriteToFile();
    }catch(PdfError & e){
      std::cout << "[Erreur]Impossible de créer le fichier pdf : " << e.what() << std::endl;
    }
    
  }catch(const std::exception e){
    std::cout << "[Erreur] Lors de l'initialisation des variables : " << e.what() << std::endl;
  }
  return 0;
}
