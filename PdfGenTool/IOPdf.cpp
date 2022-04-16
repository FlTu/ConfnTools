/********************************************************************************
 **********                                                            **********
 **********     Nom du fichier                : IOPdf.cpp              **********
 **********     Auteur                        : Florent TURRI          **********
 **********     Date de création              : 13/04/2022             **********
 **********     Date de dernière modification : 13/04/2022             **********
 **********                                                            **********
 ********************************************************************************/
/** CPP Includes **/

/** C Includes **/

/** external includes **/


/** internal includes **/
#include "IOPdf.h"

IOPdf::IOPdf(): pcEncoding(NULL), pcMemDocument(NULL), pcPage(NULL), cPainter(), cPageSize(PoDoFo::PdfRect()), pcPdfContent(std::vector<PdfString>()), cdX(0), cdY(0)
{
  try{
    pcMemDocument = new PdfMemDocument();
    pcEncoding = new PdfIdentityEncoding();
    pcOutputDocumentName = "";

    pcFontFileTitleLine = pcMemDocument->CreateFont("Liberation Serif", false, pcEncoding);
    pcFontPartTitleLine = pcMemDocument->CreateFont("Liberation Serif", false, pcEncoding);
    pcFontNote = pcMemDocument->CreateFont("Liberation Serif", false, pcEncoding);
    pcFontComment = pcMemDocument->CreateFont("Liberation Serif", false, pcEncoding);
    pcFontCodeBlock = pcMemDocument->CreateFont("Liberation Serif", false, pcEncoding);
    pcFontBold = pcMemDocument->CreateFont("Liberation Serif", false, pcEncoding);
    pcFontItalic = pcMemDocument->CreateFont("Liberation Serif", false, pcEncoding);
    pcFontUnderligne = pcMemDocument->CreateFont("Liberation Serif", false, pcEncoding);
    pcFontParagraph = pcMemDocument->CreateFont("Liberation Serif", false, pcEncoding);
    pcFontDotList = pcMemDocument->CreateFont("Liberation Serif", false, pcEncoding);
    pcFontNumList = pcMemDocument->CreateFont("Liberation Serif", false, pcEncoding);
    pcFontHRule = pcMemDocument->CreateFont("Liberation Serif", false, pcEncoding);
    pcFontEndOfPage = pcMemDocument->CreateFont("Liberation Serif", false, pcEncoding);
    pcFontTable = pcMemDocument->CreateFont("Liberation Serif", false, pcEncoding);
    pcFontURL = pcMemDocument->CreateFont("Liberation Serif", false, pcEncoding);
    pcFontLocalLink = pcMemDocument->CreateFont("Liberation Serif", false, pcEncoding);
    pcFontFileTitleLine->SetFontSize(10);
    pcFontPartTitleLine->SetFontSize(16);
    pcFontNote->SetFontSize(16);
    pcFontComment->SetFontSize(16);
    pcFontCodeBlock->SetFontSize(16);
    pcFontBold->SetFontSize(16);
    pcFontItalic->SetFontSize(16);
    pcFontUnderligne->SetFontSize(16);
    pcFontUnderligne->SetFontSize(16);

  }catch(const std::exception e){
    std::cout << "[Erreur] Constructeur IOPdf : " << e.what() << std::endl;
  }
}
IOPdf::~IOPdf()
{
  free(pcEncoding);
  free(pcMemDocument);
  free(pcPage);

  free(pcFontFileTitleLine);
  free(pcFontPartTitleLine);
  free(pcFontNote);
  free(pcFontComment);
  free(pcFontCodeBlock);
  free(pcFontBold);
  free(pcFontItalic);
  free(pcFontUnderligne);
  free(pcFontUnderligne);
}

void IOPdf::WriteToFile()
{
  try{
    // cSize = PdfPage::CreateStandardPageSize(ePdfPageSize_A4);
    // pcPage = pcMemDocument->CreatePage(cSize);
    // pcPainter.SetPage(pcPage);
    // cdY = 500;
    // for(PoDoFo::PdfString cur : pcPdfContent){
    //   pcPainter.DrawText(cdX, cdY, cur, cur.GetLength());
    //   // cdY-= pcFont->GetFontSize() + 5;
    // }
    //    cPainter.FinishPage();
    
    char * file = new char[pcOutputDocumentName.length() +1];
    std::copy(pcOutputDocumentName.begin(), pcOutputDocumentName.end(), file);
    std::cout << file << std::endl; 
    pcMemDocument->Write(file);
  }catch(const std::exception e){
    std::cout << "[Erreur] Ecriture du fichier impossible : " << e.what() << std::endl;
  }
}

void IOPdf::AddContent(std::string newLine)
{
  try{
    PdfString newString(newLine);
    pcPdfContent.push_back(newString);
  }catch(PdfError pe)
  {
    std::cout << "[Erreur] Ajout de contenu impossible : " << pe.what() << std::endl;
  }
  
}

std::string IOPdf::GetOutputDocumentName()
{
  return pcOutputDocumentName;
}

void IOPdf::SetOutputDocumentName(std::string docName)
{
  pcOutputDocumentName = docName;
}



PdfFont * IOPdf::GetPainterFont()
{
  return cPainter.GetFont();
}
void IOPdf::SetPainterFont(PdfFont * font)
{
  cPainter.SetFont(font);
}

PdfRect IOPdf::GetPageSize()
{
  return cPageSize;
}
void IOPdf::AddPage(PdfRect pageSize)
{
  cPageSize = pageSize;
  pcPage = pcMemDocument->CreatePage(cPageSize);
  cPainter.SetPage(pcPage);
}

void IOPdf::DrawLine(double xPos, double yPos, PoDoFo::PdfString line, double strLen, PdfFont * font)
{
  cPainter.SetFont(font);
  cPainter.DrawText(xPos, yPos, line, strLen);
}

void IOPdf::FinishPage()
{
  cPainter.FinishPage();
}

 


int  IOPdf::GetFileTitleFontSize()
{
  return pcFontFileTitleLine->GetFontSize();
}
void IOPdf::SetFileTitleFontSize(int fontSize)
{
  pcFontFileTitleLine->SetFontSize(fontSize);
}
int  IOPdf::GetPartTitleFontSize()
{
  return pcFontPartTitleLine->GetFontSize();
}
void IOPdf::SetPartTitleFontSize(int fontSize)
{
  pcFontPartTitleLine->SetFontSize(fontSize);
}
int  IOPdf::GetNoteFontSize()
{
  return pcFontNote->GetFontSize();
}
void IOPdf::SetNoteFontSize(int fontSize)
{
  pcFontNote->SetFontSize(fontSize);
}
int  IOPdf::GetCommentFontSize()
{
  return pcFontComment->GetFontSize();
}
void IOPdf::SetCommentFontSize(int fontSize)
{
  pcFontComment->SetFontSize(fontSize);
}
int  IOPdf::GetCodeBLockFontSize()
{
  return pcFontCodeBlock->GetFontSize();
}
void IOPdf::SetCodeBlockFontSize(int fontSize)
{
  pcFontCodeBlock->SetFontSize(fontSize);
}
int  IOPdf::GetBoldFontSize()
{
  return pcFontBold->GetFontSize();
}
void IOPdf::SetBoldFontSize(int fontSize)
{
  pcFontBold->SetFontSize(fontSize);
}
 
int  IOPdf::GetParagraphFontSize()
{
  return pcFontParagraph->GetFontSize();
}
void IOPdf::SetParagraphFontSize(int fontSize)
{
  pcFontParagraph->SetFontSize(fontSize);
}
 


PdfFont *  IOPdf::GetFileTitleFont()
{
  return pcFontFileTitleLine;
}
void IOPdf::SetFileTitleFont(PdfFont * font)
{
  pcFontFileTitleLine = font;
}
PdfFont *  IOPdf::GetPartTitleFont()
{
  return pcFontPartTitleLine;
}
void IOPdf::SetPartTitleFont(PdfFont * font)
{
  pcFontPartTitleLine = font;
}
PdfFont *  IOPdf::GetNoteFont()
{
  return pcFontNote;
}
void IOPdf::SetNoteFont(PdfFont * font)
{
  pcFontNote = font;
}
PdfFont *  IOPdf::GetCommentFont()
{
  return pcFontComment;
}
void IOPdf::SetCommentFont(PdfFont * font)
{
  pcFontComment = font;
}
PdfFont *  IOPdf::GetCodeBLockFont()
{
  return pcFontCodeBlock;
}
void IOPdf::SetCodeBlockFont(PdfFont * font)
{
  pcFontCodeBlock = font;
}
PdfFont *  IOPdf::GetBoldFont()
{
  return pcFontBold;
}
void IOPdf::SetBoldFont(PdfFont * font)
{
  pcFontBold = font;
}
 
PdfFont *  IOPdf::GetParagraphFont()
{
  return pcFontParagraph;
}
void IOPdf::SetParagraphFont(PdfFont * font)
{
  pcFontParagraph = font;
}
 
