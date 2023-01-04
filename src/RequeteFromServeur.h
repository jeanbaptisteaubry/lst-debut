#ifndef RequeteFromServeur_h
#define RequeteFromServeur_h

#include <pgmspace.h>
#include <Arduino.h>

enum TypeRequete
{
  indicationServeur,
  changerInformation,
  demarrerPartie,
  arreterPartie,
  updateScorePartie
};

class RequeteFromServeur{
    private :
     char* data;

    public : 
        RequeteFromServeur(char* tabData)
        {
            this->data = tabData;
        }

};

#endif
