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
/** C Includes **/
/** external includes **/

/** internal includes **/
#include "Parser.h"
#include "Helper.h"

Parser::Parser():cParametersList(container::vector<char*>({}))
{
  /** Définition des Expressions réguilières **/
  rFileTitleFirstLine = regex("^\\% .* \\%\n$");
  rFileTitleSecondLine = regex("^\\~*$");
  rPartTitleFirstLine = regex("^!<[0-9]*>\\[[0-9](.[0-9])*-*\\]");
  rPartTitleSecondLine = regex("^=|-|_$");
  rNote = regex("!>.*<!");
  rComment = regex("");
  rCodeBlock = regex("");
  rBoldStart = regex("!&");
  rBoldEnd = regex("&!");
  rItalicStart = regex("!/");
  rItalicEnd = regex("/!");
  rUnderligneStart = regex("!_");
  rUnderligneEnd = regex("_!");
  rParagraphStart = regex("!\"");
  rParagraphEnd = regex("\"!");
  rDotList = regex("");
  rNumList = regex("");
  rHRule = regex("");
  rEndOfPage = regex("");
  rTable = regex("");
  rURL = regex("");
  rLocalLink = regex("");


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
  bool isFirstPLine = false;
  bool isDrawable = true;
  bool isParagraph = false;
  PdfFont * curFont = NULL;
  container::vector<std::string> storedLines;


  try{
    lOutFile = new IOPdf();

    lOutFile->AddPage(PdfPage::CreateStandardPageSize(ePdfPageSize_A4));
    double cdX = 0;
    double cdY = (lOutFile->GetPageSize().GetHeight()) - 40;
    double nextY = 0;
    inputfile.open(iFileName, std::ios_base::in);
    while(inputfile.read(&curChar, 1)){
      PoDoFo::PdfString curString;
      curLine += curChar;
      if(curChar == 10){
        
        if(isFirstLine){
          isFirstLine = false;
          isDrawable = false;
          if(regex_search(curLine, rFileTitleFirstLine)){
            storedLines.push_back(curLine);
          }
        }
        else if(isParagraph && regex_search(curLine, rParagraphEnd)){
          isDrawable = false;
          smatch m;
          regex_search(curLine, m, rParagraphEnd);
          std::cout << m[1] << std::endl;;
          std::cout << "m 0 : " << m[0] <<  " m 1 : " << m.prefix() << std::endl;
          if(m.prefix().length() != 0){
            curString = PoDoFo::PdfString(curLine);
            curFont = lOutFile->GetParagraphFont();
            curFont->SetFontSize(12);
            nextY = 20;
            isDrawable = true;
            
          }
          isParagraph = false;
        }
        else if(isParagraph){
          std::string formattedString;
          smatch matchBoldStart;
          smatch matchBoldEnd;
          smatch matchItalicStart;
          smatch matchItalicEnd;
          smatch matchUnderlinedStart;
          smatch matchUnderlinedEnd;
          smatch matchLink;
          int boldCount = 0;
          int italicCount = 0;
          int underlinedCount = 0;
          int linkCount = 0;
          bool isBold = false;
          bool isItalic = false;
          bool isUnderlined = false;
          bool isCrossed = false;
          std::string myStr("AA vfBB ,jioAABBgrf AAjp BB jpAAjp");
          // bool resBold = regex_search("", matchBold, rBold);
          int i = 1;
          if(isFirstPLine){
            cdX += 15;
          }
          while(boost::regex_search(myStr, matchBoldStart, boost::regex("AA"))){
            std::cout << "match " << i << " " << matchBoldStart.suffix() << std::endl;
            myStr = matchBoldStart.suffix();
            boldCount++;
          }
          // regex_search("Voici le !_contenu_! du premier !&paragraphe&! de la premiere !&partie&! !!!\n", matchBoldStart, rBoldStart);
          regex_search(curLine, matchBoldEnd, rBoldEnd);
          regex_search(curLine, matchItalicStart, rItalicStart);
          regex_search(curLine, matchItalicEnd, rItalicEnd);
          regex_search(curLine, matchUnderlinedStart, rUnderligneStart);
          regex_search(curLine, matchUnderlinedEnd, rUnderligneEnd);
          regex_search(curLine, matchLink, rLocalLink);
          for(int i = 0 ; i < curLine.length() ; i++){
            if(matchBoldStart[boldCount] == &curLine[i]){
              isBold = true;
              i++;
            }
            else if(matchBoldEnd[boldCount] == &curLine[i]){
              isBold = false;
              boldCount++;
              i++;
            }
            else if(matchItalicStart[italicCount] == &curLine[i]){
              isItalic = true;
              i++;
            }
            else if(matchItalicEnd[italicCount] == &curLine[i]){
              isItalic = false;
              italicCount++;
              i++;
            }
            if(isBold && isItalic){
              // curFont = lOutFile->GetBoldItalicFont();
              // curFont->SetFontSize(12);
            }
            else if(isBold){
              curFont = lOutFile->GetBoldFont();
              curFont->SetFontSize(12);
            }
            else if(isItalic){
              curFont = lOutFile->GetItalicFont();
              curFont->SetFontSize(12);
            }
            else{
              curFont = lOutFile->GetParagraphFont();
              curFont->SetFontSize(12);
            }              
            formattedString = curLine[i];
            curString = PoDoFo::PdfString(formattedString);
            lOutFile->DrawLine(cdX, cdY, curString, curString.GetLength(), curFont);
            cdX+= curFont->GetFontMetrics()->CharWidth(curLine[i]);
          }
          nextY = 20;
          cdY-= nextY;
          isDrawable = false;
          if(isFirstPLine){
            cdX -= 15;
            isFirstPLine = false;
          }

        }
        else if(storedLines.size() > 0 && regex_search(storedLines.at(0), rFileTitleFirstLine) && regex_search(curLine, regex("\\~*"))){
          std::string tmpLine;
          for (int i = 2 ; i < storedLines.at(0).length() - 3 ; i++){
            tmpLine += storedLines.at(0)[i];
          }
          
          curString = PoDoFo::PdfString(tmpLine);
          curFont = lOutFile->GetFileTitleFont();
          curFont->SetFontSize(40);
          curFont->SetUnderlined(true);
          storedLines.pop_back();
          cdX = (lOutFile->GetPageSize().GetWidth())/2;
          cdX -= curFont->GetFontMetrics()->StringWidth(curString)/2;
          nextY = 60;
          isDrawable = true;
        }
        else if(regex_search(curLine, rFileTitleFirstLine) && !isFirstLine){
          std::cout << "[ParseError] Le titre du document doit être à la première ligne du document" << std::endl;
        }
        else if(regex_search(curLine, rParagraphStart)){
          std::cout << "Paragraphe reconnue" << std::endl;
          isDrawable = false;
          smatch m;
          regex_search(curLine, m, rParagraphStart);
          std::cout << "m 0 : " << m[0] <<  " m 1 : " << m.suffix() << std::endl;
          
          if(m.suffix().length() != 0){
            curString = PoDoFo::PdfString(m.suffix());
            curFont = lOutFile->GetParagraphFont();
            curFont->SetFontSize(12);
            nextY = 20;
            isDrawable = true;
            cdX +=15;
            
          }
          isFirstPLine = true;
          isParagraph = true;
        }
        else if(regex_search(curLine, rPartTitleFirstLine)){
          
          curFont = lOutFile->GetPartTitleFont();
          curFont->SetUnderlined(true);
          if(regex_search(curLine, regex("^!<1>"))){
          std::cout << "Partie niveau 1" << std::endl;
            curFont->SetFontSize(30);
            cdX += 10;
          }
          else if(regex_search(curLine, regex("^!<2>"))){
          std::cout << "Partie niveau 2" << std::endl;
            curFont->SetFontSize(25);
            cdX += 30;
          }
          else if(regex_search(curLine, regex("^!<3>"))){
          std::cout << "Partie niveau 3" << std::endl;
            curFont->SetFontSize(20);
          }
          else{
            cdX += 50;
            std::cout << "Partie niveau 4+" << std::endl;
            curFont->SetFontSize(15);
          }
          std::string tmpLine;
          int i = 0;
          while(curLine[i]  != '>'){
            i++;
          }
          i++;
          for (; i < curLine.length() - 1 ; i++){
            tmpLine += curLine[i];
          }

          std::cout << "Partie reconnue" << std::endl;
          curString = PoDoFo::PdfString(tmpLine);
          storedLines.push_back(curLine);
          nextY = 20;
          isDrawable = true;
        }
        else if(storedLines.size() > 0 && regex_search(storedLines.at(0), rPartTitleFirstLine) && regex_search(curLine, rPartTitleSecondLine)){
          std::cout << "Partie optionnelle reconnue" << std::endl;
          storedLines.pop_back();
          isDrawable = false;
        }
        else{
          std::cout << "autre reconnue" << std::endl;
          curString = PoDoFo::PdfString(curLine);
          curFont = lOutFile->GetParagraphFont();
          curFont->SetFontSize(12);
          nextY = 10;
          isDrawable = true;
        }
        if(isDrawable){
          lOutFile->DrawLine(cdX, cdY, curString, curString.GetLength(), curFont);
          cdY-= nextY;
          if(isFirstPLine){
            cdX -= 15;
            isFirstPLine = false;
          }
          if(curFont->IsUnderlined()){
            curFont->SetUnderlined(false);
          }

        }
        cdX = (lOutFile->GetPageSize().GetWidth())/8;
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


