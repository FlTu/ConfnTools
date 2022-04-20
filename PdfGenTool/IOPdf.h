/********************************************************************************
 **********                                                            **********
 **********     Nom du fichier                : IOPdf.h                **********
 **********     Auteur                        : Florent TURRI          **********
 **********     Date de création              : 13/04/2022             **********
 **********     Date de dernière modification : 13/04/2022             **********
 **********                                                            **********
 ********************************************************************************/
#ifndef __IOPDF_H__
#define __IOPDF_H__
/** std CPP Includes **/
/** std C Includes **/

/** external includes **/
#include <podofo-base.h>
#include <podofo.h>
#include <container/vector.hpp> // boost lib
/** internal includes **/

/** Namespace **/
using namespace PoDoFo;

class IOPdf
{
private:
  PdfEncoding* pcEncoding;
  PdfMemDocument*    pcMemDocument;
  PdfPage*           pcPage;
  PdfPainter         cPainter;
  PdfRect            cPageSize;
  boost::container::vector<PdfString>  pcPdfContent;
  std::string pcOutputDocumentName;
  double cdX;
  double cdY;
  
  PdfFont  * pcFontFileTitleLine;
  PdfFont  * pcFontPartTitleLine;
  PdfFont  * pcFontNote;
  PdfFont  * pcFontComment;
  PdfFont  * pcFontCodeBlock;
  PdfFont  * pcFontBold;
  PdfFont  * pcFontItalic;
  PdfFont  * pcFontUnderligne;
  PdfFont  * pcFontParagraph;
  PdfFont  * pcFontDotList;
  PdfFont  * pcFontNumList;
  PdfFont  * pcFontHRule;
  PdfFont  * pcFontEndOfPage;
  PdfFont  * pcFontTable;
  PdfFont  * pcFontURL;
  PdfFont  * pcFontLocalLink;

public:
  /** Constructeur **/
  IOPdf();

  ~IOPdf();

  void WriteToFile();
  void AddContent(std::string newLine);
  std::string GetOutputDocumentName();
  void SetOutputDocumentName(std::string docName);

  // int GetFontSize();
  // void SetFontSize(int fontSize);
  // int GetFontSize();
  // void SetFontSize(int fontSize);
  PdfFont * GetPainterFont();
  void      SetPainterFont(PdfFont * font);
  PdfRect GetPageSize();
  void    AddPage(PdfRect pageSize);
  void DrawLine(double xPos, double yPos, PoDoFo::PdfString line, double strLen, PoDoFo::PdfFont * font);
  void FinishPage();
  int  GetFileTitleFontSize();
  void SetFileTitleFontSize(int fontSize);
  int  GetPartTitleFontSize();
  void SetPartTitleFontSize(int fontSize);
  int  GetNoteFontSize();
  void SetNoteFontSize(int fontSize);
  int  GetCommentFontSize();
  void SetCommentFontSize(int fontSize);
  int  GetCodeBLockFontSize();
  void SetCodeBlockFontSize(int fontSize);
  int  GetBoldFontSize();
  void SetBoldFontSize(int fontSize);
  int  GetItalicFontSize();
  void SetItalicFontSize(int fontSize);
  int  GetParagraphFontSize();
  void SetParagraphFontSize(int fontSize);

  PdfFont *  GetFileTitleFont();
  void       SetFileTitleFont(PdfFont * font);
  PdfFont *  GetPartTitleFont();
  void       SetPartTitleFont(PdfFont * font);
  PdfFont *  GetNoteFont();
  void       SetNoteFont(PdfFont * font);
  PdfFont *  GetCommentFont();
  void       SetCommentFont(PdfFont * font);
  PdfFont *  GetCodeBLockFont();
  void       SetCodeBlockFont(PdfFont * font);
  PdfFont *  GetBoldFont();
  void       SetBoldFont(PdfFont * font);
  PdfFont *  GetItalicFont();
  void       SetItalicFont(PdfFont * font);
  PdfFont *  GetParagraphFont();
  void       SetParagraphFont(PdfFont * font);

};
#endif
