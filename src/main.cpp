#include <Arduino.h>
#include "Button.h"
#include "Param.h"
#include "eSprite_TDM.h"
#include "eSprite_SHD.h"
#include "eSprite_balleX1.h"
#include "eSprite_balleX3.h"
#include "eSprite_balleX5.h"
#include <TFT_eSPI.h>
#include <SPI.h>
#include "Image.h"
#include "Game_Audio.h"
#include "Arme.h"

enum EtatFini
{
  Initial,
  EnJeuAutonome,
  MortAutonome,
  AttenteWifi,
  ConnecteAttenteOrdre,
  ActionPilote,
  EnJeuPilote,
  MortPilote,
  ChoixModePilotage,
  ChoixEquipe,
  ChoixArme,
  ChoixFin,
};

Button btnGachette(18);
Button btnMode(5, false);
Button btnReload(21, false);
Game_Audio_Class GameAudio(25, 0);

EtatFini etat = Initial;
Param param;
bool changementEtat = true;
bool bChoixFin = false;
TFT_eSPI ecran = TFT_eSPI();
// TFT_eSprite spr = TFT_eSprite(&ecran); // Sprite object graph1
eSprite_TDM spr_tdm = eSprite_TDM(&ecran);
eSprite_SHD spr_shd = eSprite_SHD(&ecran);
eSprite_balleX1 spr_balleX1 = eSprite_balleX1(&ecran);
eSprite_balleX3 spr_balleX3 = eSprite_balleX3(&ecran);
eSprite_balleX5 spr_balleX5 = eSprite_balleX5(&ecran);
int memoReste = -1;
unsigned long memoMillis;

Arme laser(&GameAudio);
void setup()
{
  Serial.begin(115200);

  Serial.printf("***** Démarrage *****\n");
  ecran.init();
  ecran.setRotation(1);
  ecran.fillScreen(TFT_BLACK);

  // Charge depuis un fichier
  if (!SPIFFS.begin(true))
  {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  spr_tdm.init();
  spr_shd.init();
}

void loop()
{

  btnGachette.MAJ();
  btnMode.MAJ();
  btnReload.MAJ();
  bool btnMode5s = false;
  if (btnGachette.relache)
  {
    Serial.printf("Button gachette has been relache %u times %u ms\n", btnGachette.numberKeyPresses, btnGachette.dureeAction);
  }

  if (btnReload.relache)
  {
    Serial.printf("Button relaod has been relache %u times %u ms\n", btnReload.numberKeyPresses, btnReload.dureeAction);
  }

  if (btnMode.relache)
  {
    // Serial.printf("Button 2 has been relache %u times %u ms\n", btnMode.numberKeyPresses, btnMode.dureeAction);
    if (btnMode.dureeAction >= 5000)
    {
      changementEtat = true;
      btnMode5s = true;
      etat = ChoixModePilotage;
      Serial.print("BTN MODE 5s\n");
    }
    else
    {
      Serial.printf("Mode : %u times %u ms\n", btnMode.numberKeyPresses, btnMode.dureeAction);
    }
  }

  EtatFini memoEtat = etat;
  switch (etat)
  {
  case Initial:
    // Position du Setup ou autre
    ecran.fillScreen(TFT_BLACK);
    ecran.drawCentreString("Initialisation", 80, 30, 2);
    param.Load();
    param.Print();
    delay(1000);
    // On charge le fichier
    switch (param.mode)
    {
    case Autonome:
      etat = EnJeuAutonome;
      break; //
    case PiloteWifiDefaut:
      etat = AttenteWifi;
      break;
    case PiloteWifiParame:
      etat = AttenteWifi;
      break;
    }

    // Chargement du fichier
    break;
  case EnJeuAutonome:

    laser.setGachette(btnGachette.actionne);
    laser.setChangementModeRelache(btnReload.relache);
    laser.setChangementModeAppuye(btnReload.actionne);
    laser.MAJ();

    if (changementEtat || laser.changement)
    {
      ecran.fillScreen(TFT_BLACK);
      // ecran.drawBitmap(40,40,testImg,4,7, (uint8_t)TFT_WHITE);
      spr_tdm.pushSprite(0, 0);
      spr_shd.pushSprite(0, 40);

      switch (laser.mode)
      {
      case simple:
        spr_balleX1.pushSprite(80, 0);
        break;
      case rafale:
        spr_balleX3.pushSprite(80, 0);
        break;
      case automatique:
        spr_balleX5.pushSprite(80, 0);
        break;
      }
      // Sprite spr = new Sprite
      // ecran.pushImage
      // ecran.drawCentreString("IN GAME", 80, 30, 2);
      Serial.printf("IN GAME\n", btnMode.numberKeyPresses, btnMode.dureeAction);
    }
    break;
  case MortAutonome:

    break;
  case AttenteWifi:
    if (changementEtat)
    {
      ecran.fillScreen(TFT_BLACK);
      ecran.drawCentreString("Attendre wifi", 80, 30, 2);
      memoMillis = millis();
    }
    else
    {

      unsigned long delta = millis() - memoMillis;
      int reste = int((float)delta / 1000.0f) % 4;
      if (memoReste != reste)
      {
        ecran.fillScreen(TFT_BLACK);
        Serial.printf("%d\n", reste);
        memoReste = reste;
        switch (reste)
        {
        case 0:
          ecran.drawCentreString("Attendre wifi", 80, 30, 2);

          break;
        case 1:
          ecran.drawCentreString("Attendre wifi.", 80, 30, 2);

          break;
        case 2:
          ecran.drawCentreString("Attendre wifi..", 80, 30, 2);
          break;
        case 3:

          ecran.drawCentreString("Attendre wifi...", 80, 30, 2);

          break;
        }
      }
    }
    break;
  case ConnecteAttenteOrdre:
    break;
  case ActionPilote:
    break;
  case EnJeuPilote:
    break;
  case MortPilote:
    break;
  case ChoixModePilotage:

    // Changement de valeur si gachette
    if (btnGachette.relache)
      switch (param.mode)
      {
      case Autonome:
        param.mode = PiloteWifiDefaut;
        break; //
      case PiloteWifiDefaut:
        param.mode = PiloteWifiParame;
        break;
      case PiloteWifiParame:
        param.mode = Autonome;
        break;
      }

    // Affichage situation actuelle
    if (changementEtat || btnGachette.relache)
    {
      ecran.fillScreen(TFT_BLACK);
      ecran.setTextColor(TFT_WHITE);
      ecran.drawString("Mode de fonctionnement", 0, 10, 2);
      ecran.setTextColor(TFT_RED);
      switch (param.mode)
      {
      case Autonome:
        Serial.print("Mode : Autonome\n");
        ecran.drawCentreString("Autonome", 80, 40, 2);
        break; //
      case PiloteWifiDefaut:
        Serial.print("Mode : PiloteWifiDefaut\n");
        ecran.drawCentreString("Wifi par Defaut", 80, 40, 2);

        break;
      case PiloteWifiParame:
        Serial.print("Mode : PiloteWifiParame\n");
        ecran.drawCentreString("Wifi Parametre", 80, 40, 2);

        break;
      }
    }

    // On a fait un appui simple sur bntMode5s
    if (!btnMode5s && btnMode.relache)
    {
      if (param.mode == PiloteWifiDefaut || param.mode == PiloteWifiParame)
        etat = ChoixFin;
      else
        etat = ChoixEquipe;
    }

    break;
  case ChoixEquipe:
    // Changement de valeur si gachette
    if (btnGachette.relache)
    {
      param.team++;
      if (param.team > 20)
        param.team = 0;
    }

    if (changementEtat || btnGachette.relache)
    {
      ecran.fillScreen(TFT_BLACK);
      ecran.setTextColor(TFT_WHITE);
      ecran.drawString("Choix de l'equipe", 0, 10, 2);
      ecran.setTextColor(TFT_RED);
      if (param.team == 0)
      {
        Serial.printf("Equipe : solo\n");
        ecran.drawCentreString("En solitaire", 80, 40, 2);
      }
      else
      {
        Serial.printf("Equipe %d\n", param.team);
        char str[50];
        sprintf(str, "Equipe n°%d\n", param.team);
        ecran.drawCentreString(str, 80, 40, 2);
      }
    }
    if (!btnMode5s && btnMode.relache)
    {

      etat = ChoixArme;
    }
    break;
  case ChoixArme:
    if (changementEtat)
    {
      ecran.fillScreen(TFT_BLACK);
      ecran.setTextColor(TFT_WHITE);
      ecran.drawString("Sélection de l'arme", 0, 10, 2);
      ecran.setTextColor(TFT_RED);
      ecran.drawCentreString("Arme : not yet!", 80, 40, 2);
      Serial.printf("Arme : not yet!\n");
    }
    if (!btnMode5s && btnMode.relache)
    {

      etat = ChoixFin;
    }
    break;
  case ChoixFin:
    if (btnGachette.relache)
    {
      bChoixFin = !bChoixFin;
    }

    if (changementEtat || btnGachette.relache)
    {
      ecran.fillScreen(TFT_BLACK);
      ecran.setTextColor(TFT_WHITE);
      ecran.drawString("Terminer le paramétrage ?", 0, 10, 2);
      ecran.setTextColor(TFT_RED);
      if (bChoixFin)
      {
        Serial.printf("Retour : Oui\n");
        ecran.drawCentreString("Oui (et sauvegarder)", 80, 40, 2);
      }
      else
      {
        Serial.printf("Retour : Non\n");
        ecran.drawCentreString("Non", 80, 40, 2);
      }
    }

    if (!btnMode5s && btnMode.relache)
    {

      if (bChoixFin)
      {
        etat = Initial;
        param.Save();
      }
      else
        etat = ChoixModePilotage;
    }
    break;
  }

  if (memoEtat != etat)
    changementEtat = true;
  else
    changementEtat = false;
  // Detach Interrupt after 1 Minute
  /*static uint32_t lastMillis = 0;
  if (millis() - lastMillis > 60000) {
    lastMillis = millis();
    detachInterrupt(btnGachette.PIN);
  Serial.println("Interrupt Detached!");
  }*/
}