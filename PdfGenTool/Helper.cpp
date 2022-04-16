/********************************************************************************
 **********                                                            **********
 **********     Nom du fichier                : Helper.cpp             **********
 **********     Auteur                        : Florent TURRI          **********
 **********     Date de création              : 14/04/2022             **********
 **********     Date de dernière modification : 14/04/2022             **********
 **********                                                            **********
 ********************************************************************************/
/** CPP Includes **/
#include <iostream>
/** C Includes **/

/** external includes **/

/** internal includes **/
#include "Helper.h"

Helper::Helper()
{
}

void Helper::ShowHelp(bool showHeader)
{
  if(showHeader)
  {
    std::cout <<  "Les paramètres disponibles sont les suivants :" << std::endl;
  }
  std::cout <<  "    -i, --input  NOM_FICHIER" << std::endl;
  std::cout <<  "    -o, --output NOM_FICHIER" << std::endl;
  std::cout <<  "    -h, --help   PARAMETRE"   << std::endl;
}

