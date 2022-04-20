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

IOPdf::IOPdf(): pcEncoding(NULL), pcMemDocument(NULL), pcPage(NULL), cPainter(), cPageSize(PoDoFo::PdfRect()), pcPdfContent(boost::container::vector<PdfString>()), cdX(0), cdY(0)
{
  try{
    pcMemDocument = new PdfMemDocument();
    pcEncoding = new PdfIdentityEncoding();
    pcOutputDocumentName = "";

    pcFontFileTitleLine = pcMemDocument->CreateFont("LiberationSerif", false, pcEncoding);
    pcFontPartTitleLine = pcMemDocument->CreateFont("LiberationSerif", false, pcEncoding);
    pcFontNote = pcMemDocument->CreateFont("LiberationSerif", false, pcEncoding);
    pcFontComment = pcMemDocument->CreateFont("LiberationSerif", false, pcEncoding);
    pcFontCodeBlock = pcMemDocument->CreateFont("LiberationSerif", false, pcEncoding);
    pcFontBold = pcMemDocument->CreateFont("Helvetica-Bold", false, pcEncoding);
    pcFontItalic = pcMemDocument->CreateFont("Helvetica-Oblique", false, pcEncoding);
    pcFontUnderligne = pcMemDocument->CreateFont("LiberationSerif", false, pcEncoding);
    pcFontParagraph = pcMemDocument->CreateFont("LiberationSerif", false, pcEncoding);
    pcFontDotList = pcMemDocument->CreateFont("LiberationSerif", false, pcEncoding);
    pcFontNumList = pcMemDocument->CreateFont("LiberationSerif", false, pcEncoding);
    pcFontHRule = pcMemDocument->CreateFont("LiberationSerif", false, pcEncoding);
    pcFontEndOfPage = pcMemDocument->CreateFont("LiberationSerif", false, pcEncoding);
    pcFontTable = pcMemDocument->CreateFont("LiberationSerif", false, pcEncoding);
    pcFontURL = pcMemDocument->CreateFont("LiberationSerif", false, pcEncoding);
    pcFontLocalLink = pcMemDocument->CreateFont("LiberationSerif", false, pcEncoding);
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
    
    char * file = new char[pcOutputDocumentName.length() +1];
    std::copy(pcOutputDocumentName.begin(), pcOutputDocumentName.end(), file);
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
int  IOPdf::GetItalicFontSize()
{
  return pcFontItalic->GetFontSize();
}
void IOPdf::SetItalicFontSize(int fontSize)
{
  pcFontItalic->SetFontSize(fontSize);
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
PdfFont *  IOPdf::GetItalicFont()
{
  return pcFontItalic;
}
void IOPdf::SetItalicFont(PdfFont * font)
{
  pcFontItalic = font;
}
PdfFont *  IOPdf::GetParagraphFont()
{
  return pcFontParagraph;
}
void IOPdf::SetParagraphFont(PdfFont * font)
{
  pcFontParagraph = font;
}
 
