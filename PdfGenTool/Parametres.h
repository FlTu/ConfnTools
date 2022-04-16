/********************************************************************************
 **********                                                            **********
 **********     Nom du fichier                : Parametres.h           **********
 **********     Auteur                        : Florent TURRI          **********
 **********     Date de création              : 13/04/2022             **********
 **********     Date de dernière modification : 13/04/2022             **********
 **********                                                            **********
 ********************************************************************************/
#ifndef __PARAMETRES_H__
#define __PARAMETRES_H__
/** CPP Includes **/
#include <fstream>
#include <vector>
/** C Includes **/


/** external includes **/

/** internal includes **/

class Parametres
{
private:
  std::string pcIFileName;
  std::string pcOFileName;
  char* pcEncoding;
  char* pcTemplateFileName;
  char* pcFontName;
  std::vector<char*> cRawLinesInput;

public:
  /** Constructeur **/
  Parametres();

  /** Destructeur **/
  ~Parametres();

  /** Fonctions de traitement du fichier d'entrée **/
  
  std::string GetInputFileName();
  int    SetInputFileName(std::string fileName);

  /** Fonctions de traitement du fichier de sortie **/
  
  std::string GetOutputFileName();
  int    SetOutputFileName(std::string fileName);

  /** Fonctions de traitement du mode d'encodage du fichier de sortie **/
  
  char * GetEncoding();
  int    SetEncoding(char * encoding);

  /** Fonctions traitement du fichier template pour l'analyse du texte d'entrée **/
  
  char * GetTemplateFileName();
  int    SetTemplateFileName(char * fileName);

  /** Fonctions de traitement de la police de caractères **/
  
  char * GetFontName();
  int    SetFontName(char * fontName);

};
#endif 
