
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
      if(argc < (i+1) || CheckIsParameter(argv[i+1]))
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
      if(argc < (i+1) || CheckIsParameter(argv[i+1]))
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
      if(argc < (i+1) || CheckIsParameter(argv[i+1]))
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
    smatch matchExt;
    regex fileExtension = regex("\\.[a-zA-Z0-9]{1,3}$");
    if(regex_search(lParametres.GetInputFileName(), matchExt, fileExtension)){
      lParametres.SetOutputFileName(matchExt.prefix().str()+ ".pdf");
    }
    else{
      lParametres.SetOutputFileName(lParametres.GetInputFileName()+ ".pdf");
    }

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
    cPdfMargin = (lOutFile->GetPageSize().GetWidth())/8;
    double cdX = 0;
    double cdY = (lOutFile->GetPageSize().GetHeight()) - 40;
    double nextY = 0;
    inputfile.open(iFileName, std::ios_base::in);
    while(inputfile.read(&curChar, 1)){
      PoDoFo::PdfString curString;
      PoDoFo::PdfString curStringTest;
      curStringTest = PoDoFo::PdfString(curLine);
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
          bool boldFound = false;
          bool italicFound = false;
          bool underlinedFound = false;
          bool linkFound = false;
          bool isBold = false;
          bool isItalic = false;
          bool isUnderlined = false;
          bool isCrossed = false;
          int i = 1;
          if(isFirstPLine){
            cdX += 20;
          }
          boldFound = regex_search(curLine, matchBoldStart, rBoldStart);
          regex_search(curLine, matchBoldEnd, rBoldEnd);
          italicFound = regex_search(curLine, matchItalicStart, rItalicStart);
          regex_search(curLine, matchItalicEnd, rItalicEnd);
          underlinedFound = regex_search(curLine, matchUnderlinedStart, rUnderligneStart);
          regex_search(curLine, matchUnderlinedEnd, rUnderligneEnd);
          linkFound = regex_search(curLine, matchLink, rLocalLink);
          for(int i = 0 ; i < curLine.length() ; i++){
            if(boldFound && matchBoldStart.prefix().length() == i){
              isBold = true;
              i+=2;
            }
            else if(boldFound && matchBoldEnd.prefix().length() == i){
              isBold = false;
              curLine = matchBoldEnd.suffix().str();
              boldFound = regex_search(curLine, matchBoldStart, rBoldStart);
              regex_search(curLine, matchBoldEnd, rBoldEnd);
              i=0;
            }
            if(italicFound && matchItalicStart.prefix().length() == i){
              isItalic = true;
              i+=2;
            }
            else if(italicFound && matchItalicEnd.prefix().length() == i){
              isItalic = false;
              curLine = matchItalicEnd.suffix().str();
              italicFound = regex_search(curLine, matchItalicStart, rItalicEnd);
              regex_search(curLine, matchItalicEnd, rItalicEnd);
              i=0;
            }
            if(underlinedFound && matchUnderlinedStart.prefix().length() == i){
              isUnderlined = true;
              i+=2;
            }
            else if(underlinedFound && matchUnderlinedEnd.prefix().length() == i){
              isUnderlined = false;
              curLine = matchUnderlinedEnd.suffix().str();
              underlinedFound = regex_search(curLine, matchUnderlinedStart, rUnderligneStart);
              regex_search(curLine, matchUnderlinedEnd, rUnderligneEnd);
              i=0;
            }
            if(isBold && isItalic){
              curFont = lOutFile->GetBoldItalicFont();
              curFont->SetFontSize(8);
            }
            else if(isBold){
              curFont = lOutFile->GetBoldFont();
              curFont->SetFontSize(8);
            }
            else if(isItalic){
              curFont = lOutFile->GetItalicFont();
              curFont->SetFontSize(8);
            }
            else{
              curFont = lOutFile->GetParagraphFont();
              curFont->SetFontSize(12);
            }              
            if(isUnderlined){
              curFont->SetUnderlined(true);
            }
            else if(!isUnderlined){
              curFont->SetUnderlined(false);
            }
            formattedString = curLine[i];
            curString = PoDoFo::PdfString(formattedString);
            if(cdX >= (lOutFile->GetPageSize().GetWidth() - cPdfMargin)){
              cdX= cPdfMargin;
              cdY-= 20;
            }
            if(cdY <= 40){
              lOutFile->AddPage(PdfPage::CreateStandardPageSize(ePdfPageSize_A4));
              cdY = lOutFile->GetPageSize().GetHeight() - 40;
            }
    
            lOutFile->DrawLine(cdX, cdY, curString, curString.GetLength(), curFont);
            cdX+= curFont->GetFontMetrics()->CharWidth(curLine[i]);
            if(isBold || isItalic){
              cdX +=3;
            }
          }
          nextY = 20;
          cdY-= nextY;
          isDrawable = false;
          if(isFirstPLine){
            cdX -= 20;
            isFirstPLine = false;
          }

        }
        else if(storedLines.size() > 0 && regex_search(storedLines.at(0), rFileTitleFirstLine) && regex_search(curLine, regex("\\~*"))){
          std::string tmpLine;
          for (int i = 2 ; i < storedLines.at(0).length() - 3 ; i++){
            tmpLine += storedLines.at(0)[i];
          }
          
          curString = PoDoFo::PdfString(tmpLine);
          std::cout << curString.GetStringUtf8() << std::endl;
          std::cout << curString.GetUnicode() << std::endl;
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
          isDrawable = false;
          smatch m;
          regex_search(curLine, m, rParagraphStart);
          
          if(m.suffix().length() != 1){
            curString = PoDoFo::PdfString(m.suffix());
            curFont = lOutFile->GetParagraphFont();
            curFont->SetFontSize(12);
            nextY = 20;
            isDrawable = true;
            cdX +=20;
            
          }
          isFirstPLine = true;
          isParagraph = true;
        }
        else if(regex_search(curLine, rPartTitleFirstLine)){
          
          curFont = lOutFile->GetPartTitleFont();
          curFont->SetUnderlined(true);
          if(regex_search(curLine, regex("^!<1>"))){
            curFont->SetFontSize(25);
          }
          else if(regex_search(curLine, regex("^!<2>"))){
            curFont->SetFontSize(20);
            cdX += 20;
          }
          else if(regex_search(curLine, regex("^!<3>"))){
            curFont->SetFontSize(18);
            cdX += 40;
          }
          else{
            cdX += 40;
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
            curString = PoDoFo::PdfString(tmpLine);
            if(curFont->GetFontMetrics()->StringWidth(curString) > (lOutFile->GetPageSize().GetWidth() - 2*cPdfMargin)){
              if(cdY <= 40){
                lOutFile->AddPage(PdfPage::CreateStandardPageSize(ePdfPageSize_A4));
                cdY = lOutFile->GetPageSize().GetHeight() - 40;
              }
              lOutFile->DrawLine(cdX, cdY, curString, curString.GetLength(), curFont);
              cdY-= nextY*2;
              tmpLine = "";
            }
          }

          storedLines.push_back(curLine);
          nextY = 20;
          isDrawable = true;
        }
        else if(storedLines.size() > 0 && regex_search(storedLines.at(0), rPartTitleFirstLine) && regex_search(curLine, rPartTitleSecondLine)){
          storedLines.pop_back();
          isDrawable = false;
        }
        else{
          curString = PoDoFo::PdfString(curLine);
          curFont = lOutFile->GetParagraphFont();
          curFont->SetFontSize(12);
          nextY = 10;
          isDrawable = true;
        }
        if(isDrawable){
          if(cdY <= 40){
            lOutFile->AddPage(PdfPage::CreateStandardPageSize(ePdfPageSize_A4));
            cdY = lOutFile->GetPageSize().GetHeight() - 40;
          }
          lOutFile->DrawLine(cdX, cdY, curString, curString.GetLength(), curFont);
          cdY-= nextY;
          if(isFirstPLine){
            cdX -= 20;
            isFirstPLine = false;
          }
          if(curFont->IsUnderlined()){
            curFont->SetUnderlined(false);
          }

        }
        cdX = cPdfMargin;
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


