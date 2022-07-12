#ifndef InputText_H
#define InputText_H
#include <pgmspace.h>
#include <Arduino.h>
#include <string>

using std::string;

/**
 * @brief Classe permettant de gérer la construction d'une chaine de saisie avec un curseur qui se déplace
 *
 */
class InputText
{
private:
    String possible = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890 <";
    String chaine = "";
    int positionAct = 0;
    int length = 0;
    int positionPossible = 0;

    int DonnePositionPossible(char charCherche)
    {
        for (int i = 0; i < possible.length(); i++)
        {
            if (possible[i] == charCherche)
                return i;
        }
        return -1;
    }

public:
    InputText(String texteBase) : chaine(texteBase)
    {

        positionAct = 0;
        length = chaine.length();
        Serial.printf("texteBase : %s \n", texteBase);
    }

    String donneTexte()
    {
        return chaine;
    }
    void setTexteBase(String texteBase)
    {
        if (texteBase.compareTo("") == 0)
        {
            chaine = String("A");
            positionPossible = 0;
        }
        else
        {

            chaine = String(texteBase);
        }
        positionAct = 0;
        positionPossible = DonnePositionPossible(chaine[0]);

        length = chaine.length();
    }

    void CaracterePossibleSuivant()
    {
        if (positionPossible < possible.length() - 1)
            positionPossible++;
        else
            positionPossible = 0;

        chaine[positionAct] = possible[positionPossible];
    }

    void CaracterePossiblePrecedent()
    {
        if (positionPossible > 0)
            positionPossible--;
        else
            positionPossible = possible.length() - 1;

        chaine[positionAct] = possible[positionPossible];
    }

    void CaractereSelectionPrecedent()
    {
        if (positionAct > 0)
            positionAct--;
        else
            positionAct = chaine.length() - 1;
        positionPossible = DonnePositionPossible(chaine[positionAct]);
    }

    void CaractereSelectionSuivant()
    {

        if (positionAct < chaine.length() - 1)
        {
            positionAct++;
            positionPossible = DonnePositionPossible(chaine[positionAct]);
        }
        if (positionAct == chaine.length()-1)
        {
            chaine += possible[positionPossible];
            positionAct++;
        }
    }

    String DonneChaineAvantAct()
    {
        return chaine.substring(0, positionAct);
    }

    char DonneCharAct()
    {
        return chaine[positionAct];
    }

    String DonneChaineApres()
    {
        if (chaine.length() - positionAct == 1)
            return "";
        return chaine.substring(positionAct + 1, chaine.length() - 1 - positionAct);
    }
};

#endif