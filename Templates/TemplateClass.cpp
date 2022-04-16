/********************************************************************************
 **********                                                            **********
 **********     Nom du fichier                : TemplateClass.cpp      **********
 **********     Auteur                        : Florent TURRI          **********
 **********     Date de création              : 13/04/2022             **********
 **********     Date de dernière modification : 13/04/2022             **********
 **********                                                            **********
 ********************************************************************************/
/** CPP Includes **/

/** C Includes **/

/** external includes **/

/** internal includes **/
#include "TemplateClass.h"

TemplateClass::TemplateClass(): cTemplateString(NULL),cTemplateInt(0)
{
}

char * TemplateClass::GetTemplateString()
{
  return cTemplateString;
}
int    TemplateClass::SetTemplateString(char * fileName)
{
  int statut = 0;
  cTemplateString = fileName;
  return statut;
}

int    TemplateClass::GetTemplateString()
{
  return cTemplateString;
}
int    TemplateClass::SetTemplateString(int templateInt)
{
  int statut = 0;
  this.cTemplateInt = templateInt;
  return statut;
}
