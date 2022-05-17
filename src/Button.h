#include <Arduino.h>

#ifndef BUTTON_H
#define BUTTON_H

class Button
{
private:
  uint32_t lastMillis;

public:
  /* data */
  uint8_t PIN;
  uint32_t numberKeyPresses;
  bool actionne;
  bool relache;
  uint32_t dureeAction;
  int etatHaut = HIGH;

  Button(uint8_t _PIN);
  Button(uint8_t _PIN, bool modePullUp);
  void Presse(); 
  void MAJ();
  uint32_t DureeEtatEnCours();
};

Button::Button(uint8_t _PIN)
{
  PIN = _PIN;
  numberKeyPresses = 0;
  actionne = false;
  relache = true;
  pinMode(PIN, INPUT_PULLUP);
  dureeAction = 0;
}

Button::Button(uint8_t _PIN, bool modePullUp)
{
  PIN = _PIN;
  numberKeyPresses = 0;
  actionne = false;
  relache = true;
  pinMode(PIN, INPUT_PULLUP);
  if (modePullUp == true)
   // pinMode(PIN, INPUT_PULLUP);
   etatHaut = HIGH;
  else
    etatHaut = 0x0;
    //pinMode(PIN, INPUT_PULLDOWN);
  dureeAction = 0;
}

void Button::MAJ()
{
  int etatBouton = digitalRead(PIN);
  
  if (etatBouton == etatHaut) // test si le bouton a un niveau logique HAUT
  {
    if (actionne == false)
    {
      actionne = true;
      relache = false;
      numberKeyPresses++;

      lastMillis = millis();
    }
    //Serial.printf("etatBouton %d\n", etatBouton);
  }
  else // test si le bouton a un niveau logique différent de HAUT (donc BAS)
  {
    if (actionne == true)
    {
      actionne = false;
      dureeAction = DureeEtatEnCours();

      lastMillis = millis();
      if (dureeAction > 10)
        relache = true;
      else
        numberKeyPresses--;
    }
    else
      relache = false;
  }
}

uint32_t Button::DureeEtatEnCours()
{
  return millis() - lastMillis;
}

#endif