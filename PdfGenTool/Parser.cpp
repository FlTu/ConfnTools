/********************************************************************************
 **********                                                            **********
 **********     Nom du fichier                : Parser.cpp             **********
 **********     Auteur                        : Florent TURRI          **********
 **********     Date de création              : 13/04/2022             **********
 **********     Date de dernière modification : 13/04/2022             **********
 **********                                                            **********
 ********************************************************************************/
/** CPP Includes **/
#include <cstring>
#include <iostream>
#include <fstream>
#include <regex>
/** C Includes **/
/** external includes **/

/** internal includes **/
#include "Parser.h"
#include "Helper.h"

Parser::Parser():cParametersList(vector<char*>({}))
{
  /** Définition des Expressions réguilières **/
  rFileTitleFirstLine = regex("^\\% .* \\%\n$");
  rFileTitleSecondLine = regex("^\\~*$", std::regex_constants::ECMAScript);
  rPartTitleFirstLine = regex("\\!\\<[0-9]*\\>\\[([0-9]*\\.)*\\]- .*", std::regex_constants::ECMAScript);
  rPartTitleSecondLine = regex("", std::regex_constants::ECMAScript);
  rNote = regex("!>.*<!", std::regex_constants::ECMAScript);
  rComment = regex("", std::regex_constants::ECMAScript);
  rCodeBlock = regex("", std::regex_constants::ECMAScript);
  rBold = regex("", std::regex_constants::ECMAScript);
  rItalic = regex("", std::regex_constants::ECMAScript);
  rUnderligne = regex("", std::regex_constants::ECMAScript);
  rParagraph = regex("", std::regex_constants::ECMAScript);
  rDotList = regex("", std::regex_constants::ECMAScript);
  rNumList = regex("", std::regex_constants::ECMAScript);
  rHRule = regex("", std::regex_constants::ECMAScript);
  rEndOfPage = regex("", std::regex_constants::ECMAScript);
  rTable = regex("", std::regex_constants::ECMAScript);
  rURL = regex("", std::regex_constants::ECMAScript);
  rLocalLink = regex("", std::regex_constants::ECMAScript);


}
Parser::~Parser()
{

}

bool CheckIsParameter(std::string param);
  
Parametres Parser::ParseParameters(int argc, char ** argv)
{
  Parametres lParametres;
  for (int i = 1 ; i < argc ; i++)
  {
    if( (0 == strcmp(argv[i], "-i")) || (0 == strcmp(argv[i], "--input")) )
    {
      if(CheckIsParameter(argv[i+1]))
      {
        std::cout << "[Erreur] Le paramètre " << argv[i] << " attends un argument" << std::endl;
        Helper::ShowHelp(true);
        break;
      }
      i++;
      lParametres.SetInputFileName(argv[i]);
    }
    else if( (0 == strcmp(argv[i], "-o")) || (0 == strcmp(argv[i], "--output")) )
    {
      if(CheckIsParameter(argv[i+1]))
      {
        std::cout << "[Erreur] Le paramètre " << argv[i] << " attends un argument" << std::endl;
        Helper::ShowHelp(true);
        break;
      }
      i++;
      lParametres.SetOutputFileName(argv[i]);
    }
    else if( (0 == strcmp(argv[i], "-f")) || (0 == strcmp(argv[i], "--fontname")) )
    {
      if(CheckIsParameter(argv[i+1]))
      {
        std::cout << "[Erreur] Le paramètre " << argv[i] << " attends un argument" << std::endl;
        Helper::ShowHelp(true);
        break;
      }
      i++;
      lParametres.SetFontName(argv[i]);
    }
    else if( (0 == strcmp(argv[i], "-e")) || (0 == strcmp(argv[i], "--encoding")) )
    {
      if(CheckIsParameter(argv[i+1]))
      {
        std::cout << "[Erreur] Le paramètre " << argv[i] << " attends un argument" << std::endl;
        Helper::ShowHelp(true);
        break;
      }
      i++;
      lParametres.SetEncoding(argv[i]);
    }
    else if( (0 == strcmp(argv[i], "-t")) || (0 == strcmp(argv[i], "--template")) )
    {
      if(CheckIsParameter(argv[i+1]))
      {
        std::cout << "[Erreur] Le paramètre " << argv[i] << " attends un argument" << std::endl;
        Helper::ShowHelp(true);
        break;
      }
      i++;
      lParametres.SetTemplateFileName(argv[i]);
    }
    else if( (0 == strcmp(argv[i], "-h")) || (0 == strcmp(argv[i], "--help")) )
    {
        Helper::ShowHelp(true);
    }
    else
    {
      std::cout << "[Erreur] Le parametre " << argv[i] << " n'est pas reconnu." << std::endl;
      std::cout << "Veuillez entrer une commande en respectant les paramètres suivants :" << std::endl;
        Helper::ShowHelp(false);
    }
  }
  if(lParametres.GetOutputFileName() == ""){
    std::cout << "Pourquoi??? " << lParametres.GetOutputFileName() << std::endl;
    lParametres.SetOutputFileName(lParametres.GetInputFileName()+ ".pdf");

  }
  return lParametres;
}

IOPdf * Parser::ParseInputFile(std::string iFileName)
{
  IOPdf * lOutFile = NULL;
  std::string curLine;
  char curChar;
  fstream inputfile;
  bool isFirstLine = true;
  std::vector<std::string> storedLines;


  try{
    lOutFile = new IOPdf();

    lOutFile->AddPage(PdfPage::CreateStandardPageSize(ePdfPageSize_A4));
    double cdX = 20;
    double cdY = 500;
  
    inputfile.open(iFileName, std::ios_base::in);
    while(inputfile.read(&curChar, 1)){
      curLine += curChar;
      if(curChar == 10){
        
        if(isFirstLine){
          isFirstLine = false;
          if(regex_search(curLine, rFileTitleFirstLine)){
            storedLines.push_back(curLine);
            curLine = "";
          }
        }
        else if(storedLines.size() > 0 && regex_search(storedLines.at(0), rFileTitleFirstLine) && regex_search(curLine, regex("\\~*"))){
            std::cout << "Titre de fichier reconnu" << std::endl;
            PoDoFo::PdfString curString(storedLines.at(0));
            lOutFile->SetFileTitleFontSize(20);
            lOutFile->DrawLine(cdX, cdY, curString, curString.GetLength(), lOutFile->GetFileTitleFont());
            storedLines.pop_back();
            cdY-= 40;
            curLine = "";
        }
        else if(regex_search(curLine, rFileTitleFirstLine) && !isFirstLine){
          std::cout << "[ParseError] Le titre du document doit être à la première ligne du document" << std::endl;
        }
        else{
        }
        PoDoFo::PdfString curString(curLine);
        lOutFile->SetParagraphFontSize(10);
        lOutFile->DrawLine(cdX, cdY, curString, curString.GetLength(), lOutFile->GetParagraphFont());
        cdY-= 20;
        curLine = "";
      }
    }
    lOutFile->FinishPage();
    inputfile.close();
  }catch(const std::exception e){
    std::cout << "[Erreur] Traitement du fichier d'entrée impossible : " << e.what() << std::endl;
  }
    return lOutFile;
}

bool CheckIsParameter(std::string param)
{
  bool isParam = false;
  if((param == "-i") ||
     (param == "--input") ||
     (param == "-o") ||
     (param == "-output") ||
     (param == "-h") ||
     (param == "--help") ||
     (param == "-t") ||
     (param == "--template") ||
     (param == "-e") ||
     (param == "-f") ||
     (param == "--fontname")
     )
  {
    isParam = true;
  }
  return isParam;
}


