#include <Arduino.h>
#include "Button.h"
#include "Param.h"

#include <TFT_eSPI.h>
#include <SPI.h>
#include <WiFi.h>
#include "Image.h"
#include "Game_Audio.h"
#include "Arme.h"
#include "Ecran.h"
#include "InputText.h"

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
  ChoixSSIDScan,
  ChoixSSID,
  ChoixMotDePasse,
  ChoixValidationWifi,
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
// TFT_eSPI ecran = TFT_eSPI();
Ecran ecran;
// TFT_eSprite spr = TFT_eSprite(&ecran); // Sprite object graph1

int memoReste = -1;
int nWifi = 0;
int iWifi = 0;
int memoIWifi = 0;
unsigned long memoMillis;

InputText inpTxt("");

Arme laser(&GameAudio);
void setup()
{
  Serial.begin(115200);

  Serial.printf("***** Démarrage *****\n");
  ecran.init();
  randomSeed(140584);
  /* ecran.setRotation(1);
   ecran.fillScreen(TFT_BLACK);
   ecran.setTextColor(TFT_WHITE);*/
  // Charge depuis un fichier
  /*
  if (!SPIFFS.begin(true))
  {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
  */
}

void loop()
{

  btnGachette.MAJ();
  btnMode.MAJ();
  btnReload.MAJ();
  bool btnMode5s = false;
  bool btnGachette5s = false;
  bool btnReload5s = false;

  if (btnGachette.relache)
  {
    Serial.printf("Button gachette has been relache %u times %u ms\n", btnGachette.numberKeyPresses, btnGachette.dureeAction);
    if (btnGachette.dureeAction >= 5000)
    {
      btnGachette5s = true;
      Serial.print("BTN Gachette 5s\n");
    }
  }

  if (btnReload.relache)
  {
    Serial.printf("Button relaod has been relache %u times %u ms\n", btnReload.numberKeyPresses, btnReload.dureeAction);
    if (btnReload.dureeAction >= 5000)
    {
      btnReload5s = true;
      Serial.print("BTN Reload 5s\n");
    }
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
#pragma region Initial
    // Position du Setup ou autre
    ecran.effacerEcran();
    ecran.afficherCentrerNormal("Initialisation\n");

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
#pragma endregion
  case EnJeuAutonome:
#pragma region EnJeuAutonome
    laser.setGachette(btnGachette.actionne);
    laser.setChangementModeRelache(btnReload.relache);
    laser.setChangementModeAppuye(btnReload.actionne);
    laser.MAJ();

    if (changementEtat) // On vient de changer l'état
    {
      // ecran.drawBitmap(40,40,testImg,4,7, (uint8_t)TFT_WHITE);
      ecran.afficherEcranJeu(0, 0, laser.chargeur, laser.mode, laser.etat, ((float)laser.getNb10emeSecRestantReload()) / 10);
    }

    if (laser.changement || laser.etat == rechargeChargeur)
    {
      // Un action sur l'arme, on bascule sur un affichage spécifique arme
      ecran.afficherEcranJeuArme(laser.chargeur, laser.mode, laser.etat, ((float)laser.getNb10emeSecRestantReload()) / 10);
    }

    if (!laser.changementAffichageFini)
      if (laser.millisChangement - millis() > ecran.dureeAvantVeille)
      {
        // L'action sur l'arme est finie, on rebascule sur un affichage générique
        ecran.afficherEcranJeu(0, 0, laser.chargeur, laser.mode, laser.etat, ((float)laser.getNb10emeSecRestantReload()) / 10);
        laser.changementAffichageFini = true;
      }

    break;
#pragma endregion
  case MortAutonome:

    break;
  case AttenteWifi:
#pragma region AttenteWifi
    if (changementEtat)
    {
      ecran.effacerEcran();
      ecran.afficherCentrerNormal("Attendre wifi");
      memoMillis = millis();
    }
    else
    {

      unsigned long delta = millis() - memoMillis;
      int reste = int((float)delta / 1000.0f) % 4;
      if (memoReste != reste)
      {
        ecran.effacerEcran();
        Serial.printf("%d\n", reste);
        memoReste = reste;
        switch (reste)
        {
        case 0:
          ecran.afficherCentrerNormal("Attendre wifi");

          break;
        case 1:
          ecran.afficherCentrerNormal("Attendre wifi.");

          break;
        case 2:
          ecran.afficherCentrerNormal("Attendre wifi..");
          break;
        case 3:

          ecran.afficherCentrerNormal("Attendre wifi...");

          break;
        }
      }
    }
    break;
#pragma endregion
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
      ecran.effacerEcran();
      ecran.afficherCentrerGaucheL1("Mode de fonctionnement");

      switch (param.mode)
      {
      case Autonome:
        Serial.print("Mode : Autonome\n");
        ecran.afficherCentrerAlerte("Autonome");
        break; //
      case PiloteWifiDefaut:
        Serial.print("Mode : PiloteWifiDefaut\n");
        ecran.afficherCentrerAlerte("Wifi par Defaut");

        break;
      case PiloteWifiParame:
        Serial.print("Mode : PiloteWifiParame\n");
        ecran.afficherCentrerAlerte("Wifi Parametre");

        break;
      }
    }

    // On a fait un appui simple sur bntMode5s
    if (!btnMode5s && btnMode.relache)
    {
      switch (param.mode)
      {
      case Autonome:
        etat = ChoixEquipe;
        break; //
      case PiloteWifiDefaut:
        etat = ChoixFin;
        param.Wifi_SSID = "LAZERJBA";
        param.Wifi_motDePAsse = "LAZERJBA";
        break;
      case PiloteWifiParame:
        etat = ChoixSSIDScan;

        break;
      }
    }
    break;
  case ChoixSSIDScan:
  {
    ecran.effacerEcran();
    ecran.afficherCentrerGaucheL1("Sélection du wifi\n");
    ecran.afficherCentrerAlerte("Scan en cours\n");

    Serial.println("scan start");

    // WiFi.scanNetworks will return the number of networks found
    nWifi = WiFi.scanNetworks();
    
    iWifi = -1;
    memoIWifi = -2;
    Serial.println("scan done");
    if (nWifi == 0)
    {
      Serial.println("no networks found");
    }
    else
    {
      Serial.print(nWifi);
      Serial.println(" networks found");
    }
    etat = ChoixSSID;
  }
  break;
  case ChoixSSID:
    if (!btnMode5s)
    {
      if (btnGachette.relache && iWifi < nWifi)
        iWifi++;
      if (btnReload.relache && iWifi > -2)
        iWifi--;

      // Il y a un changement à afficher
      if (iWifi != memoIWifi)
      {
        memoIWifi = iWifi;
        ecran.effacerEcran();
        ecran.afficherCentrerGaucheL1("Sélection du wifi\n");
        switch (iWifi)
        {
        case -2:
          ecran.afficherCentrerAlerte("Rescanner");
          break;
        case -1:
        {
          char strTmp[50];
          sprintf(strTmp, "%d trouve(s) \n", nWifi);
          ecran.afficherCentrerAlerte(strTmp);
        }
        break;
        default:
        {
          char strTmp[100];
          sprintf(strTmp, "%d: %d (%d) %c", iWifi + 1, WiFi.SSID(iWifi), WiFi.RSSI(iWifi), (WiFi.encryptionType(iWifi) == WIFI_AUTH_OPEN) ? " " : "*");
          ecran.afficherCentrerAlerte(strTmp);
        }
        break;
        }
      }
    }

    else
    {
      switch (iWifi)
      {
      case -2:
        etat = ChoixSSIDScan;
        break;
      case -1:
      {
      }
      break;
      default:
        {
          param.Wifi_SSID = WiFi.SSID(iWifi);

          etat = ChoixMotDePasse;
          inpTxt.setTexteBase(param.Wifi_motDePAsse);
        }
      }
    }

    // On regarde s'il changer de mode

    break;
  case ChoixMotDePasse:
  {
    // Action      / Gachette / Reload      / mode
    // Fini        / Press    / Press
    // Lettre UP   /          / Relache
    // Letttre D   / Relache  /
    // Lettre Next / Relache5S/
    // Lettre Back /          / Relache5S
    // Valider MDP /          /           / Relache 5S
    if (btnMode5s)
    {
      param.Wifi_motDePAsse = String(inpTxt.donneTexte());
      etat = ChoixValidationWifi;
    }
    else
    {
      bool actSelection = false;
      if (btnGachette.relache)
      {
        inpTxt.CaracterePossibleSuivant();
        actSelection = true;
      }
      if (btnReload.relache)
      {
        inpTxt.CaracterePossiblePrecedent();
        actSelection = true;
      }
      if (btnGachette5s)
      {
        inpTxt.CaractereSelectionSuivant();
        actSelection = true;
      }
      if (btnReload5s)
      {
        inpTxt.CaractereSelectionPrecedent();
        actSelection = true;
      }

      // Il faut afficher !
      if (actSelection)
      {
        ecran.effacerEcran();
      }
    }
  }
  break;
  case ChoixValidationWifi:
  {
    WiFi.mode(WIFI_STA); // Optional
    char *wifi_ssid;
     param.Wifi_SSID.toCharArray(wifi_ssid,param.Wifi_SSID.length(),0);

     char *wifi_pwd;
     param.Wifi_SSID.toCharArray(wifi_pwd,param.Wifi_motDePAsse.length(),0);
    //WiFi.begin(param.Wifi_SSID, param.Wifi_motDePAsse);
    Serial.println("\nConnecting");

    int countWaiting = 0;
    int waitingMax = 50 ;
    while (WiFi.status() != WL_CONNECTED && countWaiting < waitingMax)
    {
      Serial.print(".");
      delay(100);
      countWaiting ++ ;
    }

    if(WiFi.status() == WL_CONNECTED)
    {
      Serial.println("\nConnected to the WiFi network");
      Serial.print("Local ESP32 IP: ");
      Serial.println(WiFi.localIP());
      etat = ChoixFin;
    }
    else
    {
      Serial.print("Echec wifi ");
      etat = ChoixSSIDScan;
    }
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
      ecran.effacerEcran();
      ecran.afficherCentrerGaucheL1("Choix de l'equipe\n");
      if (param.team == 0)
      {
        Serial.printf("Equipe : solo\n");
        ecran.afficherCentrerAlerte("En solitaire\n");
      }
      else
      {
        Serial.printf("Equipe %d\n", param.team);
        char str[50];
        sprintf(str, "Equipe n°%d\n", param.team);
        ecran.afficherCentrerAlerte(str);
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
      ecran.effacerEcran();
      ecran.afficherCentrerGaucheL1("Sélection de l'arme");

      ecran.afficherCentrerAlerte("Arme : not yet!");
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
      ecran.effacerEcran();

      ecran.afficherCentrerNormal("Terminer le paramétrage ?\n");

      if (bChoixFin)
      {
        Serial.printf("Retour : Oui\n");
        ecran.afficherCentrerAlerte("Oui (et sauvegarder)\n");
      }
      else
      {
        Serial.printf("Retour : Non\n");
        ecran.afficherCentrerAlerte("Non \n");
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

  ecran.checkVeille();
  if (ecran.veilleEnCours)
    ecran.drawVeille();
  // Detach Interrupt after 1 Minute
  /*static uint32_t lastMillis = 0;
  if (millis() - lastMillis > 60000) {
    lastMillis = millis();
    detachInterrupt(btnGachette.PIN);
  Serial.println("Interrupt Detached!");
  }*/
}
