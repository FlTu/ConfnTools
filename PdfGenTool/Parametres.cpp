/********************************************************************************
 **********                                                            **********
 **********     Nom du fichier                : Parametres.cpp         **********
 **********     Auteur                        : Florent TURRI          **********
 **********     Date de création              : 13/04/2022             **********
 **********     Date de dernière modification : 13/04/2022             **********
 **********                                                            **********
 ********************************************************************************/
/** CPP Includes **/

/** C Includes **/


/** external includes **/

/** internal includes **/
#include "Parametres.h"

/** Constructeur **/
Parametres::Parametres():
  pcIFileName(""),
  pcOFileName(""),
  pcEncoding(NULL),
  pcTemplateFileName(NULL),
  pcFontName(NULL),
  cRawLinesInput(container::vector<char*>({}))
{
}
Parametres::~Parametres()
{}

/** fonctions du nom du fichier d'entrée **/

std::string Parametres::GetInputFileName()
{
  return pcIFileName;
}

int    Parametres::SetInputFileName(std::string fileName)
{
  pcIFileName = fileName;
  return 0;
}

/** fonctions du nom du fichier de sortie **/
  
std::string Parametres::GetOutputFileName()
{
  return pcOFileName;
}
int    Parametres::SetOutputFileName(std::string fileName)
{
  pcOFileName = fileName;
  return 0;
}
  
char * Parametres::GetEncoding()
{
  return pcEncoding;
}
int    Parametres::SetEncoding(char * encoding)
{
  pcEncoding = encoding;
  return 0;
}
  
char * Parametres::GetTemplateFileName()
{
  return pcTemplateFileName;
}
int    Parametres::SetTemplateFileName(char * fileName)
{
  pcTemplateFileName = fileName;
  return 0;
}
  
char * Parametres::GetFontName()
{
  return pcFontName;
}
int    Parametres::SetFontName(char * fontName)
{
  pcFontName = fontName;
  return 0;
}
