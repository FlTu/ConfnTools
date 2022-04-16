/********************************************************************************
 **********                                                            **********
 **********     Nom du fichier                : TemplateClass.h        **********
 **********     Auteur                        : Florent TURRI          **********
 **********     Date de création              : 13/04/2022             **********
 **********     Date de dernière modification : 13/04/2022             **********
 **********                                                            **********
 ********************************************************************************/
#ifndef __TEMPLATECLASS_H__
#define __TEMPLATECLASS_H__
/** std CPP Includes **/

/** std C Includes **/

/** external includes **/

/** internal includes **/


/** Namespace **/
using namespace std;

class TemplateClass : TemplateInerritance
{
private:
  char* cTemplateString = NULL;
  int cTemplateInt;
  
public:
  /** Constructeur **/
  TemplateClass();

  /** Destructeur **/
  ~TemplateClass();
  
  char * GetTemplateString();
  int    SetTemplateString(char * fileName);
  
  int    GetTemplateString();
  int    SetTemplateString(int templateInt);
  
};
#endif
