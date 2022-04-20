/********************************************************************************
 **********                                                            **********
 **********     Nom du fichier                : Parser.h               **********
 **********     Auteur                        : Florent TURRI          **********
 **********     Date de création              : 13/04/2022             **********
 **********     Date de dernière modification : 13/04/2022             **********
 **********                                                            **********
 ********************************************************************************/
#ifndef __PARSER_H__
#define __PARSER_H__
/** std CPP Includes **/
#include <cstdlib>
/** std C Includes **/

/** external includes **/
#include <boost/regex.hpp> // boost lib
#include <container/vector.hpp> // boost lib
/** internal includes **/
#include "Parametres.h"
#include "IOPdf.h"

/** Namespace **/
using namespace boost;

class Parser
{
private:
  container::vector<char*> cParametersList;

  regex rFileTitleFirstLine;
  regex rFileTitleSecondLine;
  regex rPartTitleFirstLine;
  regex rPartTitleSecondLine;
  regex rNote;
  regex rComment;
  regex rCodeBlock;
  regex rBoldStart;
  regex rBoldEnd;
  regex rItalicStart;
  regex rItalicEnd;
  regex rUnderligneStart;
  regex rUnderligneEnd;
  regex rParagraphStart;
  regex rParagraphEnd;
  regex rDotList;
  regex rNumList;
  regex rHRule;
  regex rEndOfPage;
  regex rTable;
  regex rURL;
  regex rLocalLink;
  
  
public:
  /** Constructeur **/
  Parser();

  /** Destructeur **/
  ~Parser();

  static Parametres ParseParameters(int argc, char ** argv);
  IOPdf * ParseInputFile(std::string iFileName);

};
#endif
