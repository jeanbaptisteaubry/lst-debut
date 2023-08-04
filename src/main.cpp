#include <Arduino.h>
#include <AsyncTCP.h>
#include "Button.h"
#include "Param.h" 
#include "FS.h"
#include "SPIFFS.h"
#include <TFT_eSPI.h>
#include <SPI.h>
#include <WiFi.h>

#include "Image.h"
#include "Game_Audio.h"
#include "Arme.h"
#include "Ecran.h"
#include "InputText.h"

#define TCP_SERVEUR_PORT 5000 // Port sur lequel le terminal écoute pour recevoir des requêtes du serveur
enum ModeConnexionServeur
{
  SaisieIp,
  AttenteServeur
};
ModeConnexionServeur modeConnexionServeur = AttenteServeur;
enum EtatFini
{
  Initial,
  EnJeuAutonome,
  MortAutonome,
  AttenteWifi,
  PiloteParWifi_EnAttente,

  ConnecteAttenteOrdre,
  ActionPilote,
  EnJeuPilote,
  MortPilote,
  ChoixModePilotage,
  ChoixSSIDScan,
  ChoixSSID,
  ChoixMotDePasse,
  ChoixValidationWifi,
  ChoixModeSelectionServeur,
  SaisieIpServeur,  // On saisie l'ip du serveur de gestion des armes
  AttenteServeurIn, // On attend sur un port que le serveur vienne s'enregistrer
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
char last_wifissidOK[200] = "\r";
unsigned long memoMillis;

InputText inpTxt("");
AsyncServer *server;
Arme laser(&GameAudio);

bool btnMode1s = false;
bool btnGachette1s = false;
bool btnReload1s = false;
bool btnMode5s = false;
bool btnGachette5s = false;
bool btnReload5s = false;
char datasRecues[1024];

/**
 * @brief Fonction qui gère les données reçues par le serveur. Attention, cela dépend de l'état
 *
 * @param arg
 * @param client
 * @param data
 * @param len
 */
static void handleData(void *arg, AsyncClient *client, void *data, size_t len)
{
  Serial.printf("\n data received from client %s \n", client->remoteIP().toString().c_str());

  Serial.write((uint8_t *)data, len);
  int i;
  for (i = 0; i < len; i++)
  {
    datasRecues[i] = ((char *)data)[i];
  }
  datasRecues[i] = '\r';

  Serial.printf("%s\n", datasRecues);

  // our big json string test
  String jsonString = "{\"etat\":\"OK\"}";
  // reply to client
  if (client->space() > strlen(jsonString.c_str()) && client->canSend())
  {
    client->add(jsonString.c_str(), strlen(jsonString.c_str()));
    client->send();
  }
}

static void handleError(void *arg, AsyncClient *client, int8_t error)
{
  Serial.printf("\n connection error %s from client %s \n", client->errorToString(error), client->remoteIP().toString().c_str());
}

static void handleDisconnect(void *arg, AsyncClient *client)
{
  Serial.printf("\n client %s disconnected \n", client->remoteIP().toString().c_str());
}

static void handleTimeOut(void *arg, AsyncClient *client, uint32_t time)
{
  Serial.printf("\n client ACK timeout ip: %s \n", client->remoteIP().toString().c_str());
}

static void handleConnexionEntrante(void *arg, AsyncClient *client)
{
  Serial.printf("\n new client has been connected to server, ip: %s", client->remoteIP().toString().c_str());
  // register events
  client->onData(&handleData, NULL);
  client->onError(&handleError, NULL);
  client->onDisconnect(&handleDisconnect, NULL);
  client->onTimeout(&handleTimeOut, NULL);
}

void serveur_start()
{
  if (server == NULL)
  {
    server = new AsyncServer(TCP_SERVEUR_PORT); // start listening on tcp port 7050
    server->onClient(&handleConnexionEntrante, server);
    server->begin();
  }
}

void setup()
{
  Serial.begin(115200);

  Serial.printf("***** Démarrage *****\n");
  
  ecran.init();
  randomSeed(140584);
  /* ecran.setRotation(1);
   ecran.fillScreen(TFT_BLACK);
   ecran.setTextColor(TFT_WHITE);*/
   ecran.effacerEcran();
   ecran.afficherCentrerNormal("TEST");

  // Charge depuis un fichier
  
  if (!SPIFFS.begin(true))
  {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
  
}

void loop()
{
  ecran.afficherCentrerNormal("TEST");
  return ;
  btnMode1s = false;
  btnGachette1s = false;
  btnReload1s = false;
  btnMode5s = false;
  btnGachette5s = false;
  btnReload5s = false;

  btnGachette.MAJ();
  btnMode.MAJ();
  btnReload.MAJ();

  if (btnGachette.relache)
  {
    Serial.printf("Button gachette has been relache %u times %u ms\n", btnGachette.numberKeyPresses, btnGachette.dureeAction);
    if (btnGachette.dureeAction >= 5000)
    {
      btnGachette5s = true;
      btnGachette1s = true;
      Serial.print("BTN Gachette 5s\n");
    }
    else if (btnGachette.dureeAction >= 1000)
    {
      btnGachette1s = true;
      Serial.print("BTN Gachette 1s\n");
    }
  }

  if (btnReload.relache)
  {
    Serial.printf("Button relaod has been relache %u times %u ms\n", btnReload.numberKeyPresses, btnReload.dureeAction);
    if (btnReload.dureeAction >= 5000)
    {
      btnReload5s = true;
      btnReload1s = true;
      Serial.print("BTN Reload 5s\n");
    }
    else if (btnReload.dureeAction >= 1000)
    {
      btnReload1s = true;
      Serial.print("BTN Reload 1s\n");
    }
  }

  if (btnMode.relache)
  {
    // Serial.printf("Button 2 has been relache %u times %u ms\n", btnMode.numberKeyPresses, btnMode.dureeAction);
    if (btnMode.dureeAction >= 5000)
    {
      changementEtat = true;
      btnMode5s = true;
      btnMode1s = true;
      if (etat != ChoixMotDePasse)
        etat = ChoixModePilotage;
      Serial.print("BTN MODE 5s\n");
    }
    else if (btnMode.dureeAction >= 1000)
    {
      btnMode1s = true;
      Serial.print("BTN MODE 1s\n");
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
    if (false)
    {
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
    }
    else
    {
      etat = ChoixSSIDScan;
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
      ecran.afficherEcranJeu(0, 0, laser.chargeur, laser.mode, laser.etat, laser.getTempsRestantEnSAAfficher());
    }

    if (laser.changement || laser.etat == rechargeChargeur)
    {
      // Un action sur l'arme, on bascule sur un affichage spécifique arme
      ecran.afficherEcranJeuArme(laser.chargeur, laser.mode, laser.etat, laser.getTempsRestantEnSAAfficher());
    }

    else if (!laser.changementAffichageFini)
    {
      if (millis() - laser.millisChangement > ecran.dureeAvantVeille / 2)
      {
        // L'action sur l'arme est finie, on rebascule sur un affichage générique
        ecran.afficherEcranJeu(0, 0, laser.chargeur, laser.mode, laser.etat, laser.getTempsRestantEnSAAfficher());
        laser.changementAffichageFini = true;
      }
    }
    break;
#pragma endregion
  case MortAutonome:

    break;
  case AttenteWifi:
#pragma region AttenteWifi
    if (changementEtat)
    {
      char wifi_ssid_tmp[500];
      sprintf(wifi_ssid_tmp, "%s", param.Wifi_SSID.c_str());

      if (strcmp(last_wifissidOK, wifi_ssid_tmp) == 1)
      {
        Serial.printf("Déjà connecté à %s\n", wifi_ssid_tmp);
        // etat =
      }
      else
      {
        ecran.effacerEcran();
        ecran.afficherCentrerNormal("Attendre wifi");
        memoMillis = millis();
      }
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
#pragma region ChoixModePilotage
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
      ecran.afficherGaucheL1("Mode de fonctionnement");

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
#pragma endregion ChoixModePilotage
  case ChoixSSIDScan:
#pragma region ChoixSSIDScan
  {
    ecran.effacerEcran();
    ecran.afficherGaucheL1("Sélection du wifi\n");
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
#pragma endregion ChoixSSIDScan
  case ChoixSSID:
#pragma region ChoixSSID
    if (!btnMode.relache)
    {
      if (btnGachette.relache && iWifi < nWifi - 1)
        iWifi++;
      if (btnReload.relache && iWifi > -2)
        iWifi--;

      // Il y a un changement à afficher
      if (iWifi != memoIWifi)
      {
        memoIWifi = iWifi;
        ecran.effacerEcran();
        ecran.afficherGaucheL1("Sélection du wifi\n");
        switch (iWifi)
        {
        case -2:
          ecran.afficherCentrerAlerte("Rescanner");
          Serial.println("Rescanner");
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
          sprintf(strTmp, "%d: %s %c", iWifi + 1, WiFi.SSID(iWifi), (WiFi.encryptionType(iWifi) == WIFI_AUTH_OPEN) ? " " : "*");
          ecran.afficherCentrerAlerte(strTmp);
          Serial.printf("%s \n", strTmp);
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
        Serial.printf("param.Wifi_motDePAsse %s \n", param.Wifi_motDePAsse);

        // inpTxt.setTexteBase(param.Wifi_motDePAsse);
        inpTxt.setTexteBase("523CF66DAF9C23C741137513C6C2FD");

        Serial.printf("inpTxt.setTexteBase %s \n", inpTxt.donneTexte());
      }
      }
    }

    // On regarde s'il changer de mode
#pragma endregion ChoixSSID
    break;
  case ChoixMotDePasse:
#pragma region ChoixMotDePasse
  {
    // Action      / Gachette / Reload      / mode
    // Fini        /          /
    // Lettre UP   /          / Relache
    // Letttre D   / Relache  /
    // Lettre Next / Relache1S/
    // Lettre Back /          / Relache1S
    // Effacer Let /          / Relache5S
    // Valider MDP /          /           / Relache 5S
    if (btnMode5s)
    {
      param.Wifi_motDePAsse = String(inpTxt.donneTexte().c_str());
      Serial.printf("Validation MDP\ninpTxt.donneTexte %s \n", inpTxt.donneTexte());
      etat = ChoixValidationWifi;
    }
    else
    {
      bool actSelection = false;
      if (changementEtat)
      {
        actSelection = true;
      }

      if (btnGachette.relache && !(btnGachette1s || btnGachette5s))
      {
        inpTxt.CaracterePossibleSuivant();
        actSelection = true;
      }
      if (btnReload.relache && !(btnReload1s || btnReload5s))
      {
        inpTxt.CaracterePossiblePrecedent();
        actSelection = true;
      }
      if ((btnGachette1s && !btnGachette5s) || (btnMode.relache && !(btnMode1s || btnMode5s)))
      {
        inpTxt.CaractereSelectionSuivant();
        actSelection = true;
      }
      if (btnReload1s && !btnReload5s)
      {
        inpTxt.CaractereSelectionPrecedent();
        actSelection = true;
      }

      if (btnReload5s)
      {
        inpTxt.SupprimerCharAct();
        actSelection = true;
      }
      // Il faut afficher !
      if (actSelection)
      {
        ecran.EcranAfficherChoixMdPSSID(inpTxt);
        // inpTxt.setTexteBase("putainte debarteojkaergbaergaergaergaerg aervaervaerb");
        char strTmp[500];
        sprintf(strTmp, "inpTxt.donneTexte %s %d\n", inpTxt.donneTexte().c_str(), inpTxt.donneTexte().length()); // Serial.print(strTmp);
        Serial.println(strTmp);
      }
    }
  }
  break;
#pragma endregion ChoixMotDePasse
  case ChoixValidationWifi:
#pragma region ChoixValidationWifi
  {
    Serial.println("Validation Wifi");
    WiFi.mode(WIFI_STA); // Optional
                         // char *wifi_ssid;

    char wifi_ssid[500];
    sprintf(wifi_ssid, "%s", param.Wifi_SSID.c_str());
    Serial.println("1");
    char wifi_pwd[500];
    sprintf(wifi_pwd, "%s", param.Wifi_motDePAsse.c_str());

    // strcpy(wifi_ssid, param.Wifi_SSID.c_str());
    // param.Wifi_SSID.toCharArray(wifi_ssid, param.Wifi_SSID.length(), 0);

    // char *;
    // strcpy(wifi_pwd, param.Wifi_motDePAsse.c_str());
    // wifi_pwd = param.Wifi_SSID.c_str();
    // param.Wifi_SSID.toCharArray(wifi_pwd, param.Wifi_motDePAsse.length(), 0);
    Serial.println("2");
    Serial.printf("SSID : %s pwd : %s", wifi_ssid, wifi_pwd);
    WiFi.mode(WIFI_STA);
    WiFi.begin(wifi_ssid, wifi_pwd);
    Serial.println("\nConnecting");

    int countWaiting = 0;
    int waitingMax = 250;
    while (WiFi.status() != WL_CONNECTED && countWaiting < waitingMax)
    {
      Serial.print(".");
      delay(100);
      countWaiting++;
    }

    if (WiFi.status() == WL_CONNECTED)
    {
      Serial.println("\nConnected to the WiFi network");
      Serial.print("Local ESP32 IP: ");
      Serial.println(WiFi.localIP());
      etat = ChoixModeSelectionServeur,
      sprintf(last_wifissidOK, "%s", wifi_ssid);
    }
    else
    {
      Serial.print("Echec wifi \n");
      etat = ChoixSSIDScan;
    }
  }

  break;
#pragma endregion ChoixValidationWifi
  case ChoixModeSelectionServeur:
#pragma region ChoixModeSelectionServeur
  {
    if (btnGachette.relache)
    {
      switch (modeConnexionServeur)
      {
      case SaisieIp:
        modeConnexionServeur = AttenteServeur;
        break;

      case AttenteServeur:
        modeConnexionServeur = SaisieIp;
        break;
      }
    }

    if (changementEtat || btnGachette.relache)
    {
      ecran.effacerEcran();
      ecran.afficherGaucheL1("Choix du mode de connexion\n");
      if (modeConnexionServeur == SaisieIp)
      {
        ecran.afficherCentrerAlerte("Saisie Ip\n");
      }
      else if (modeConnexionServeur == AttenteServeur)
      {
        ecran.afficherCentrerAlerte("Attente serveur\n");
      }
    }

    if (!btnMode5s && btnMode.relache)
    {
      switch (modeConnexionServeur)
      {
      case SaisieIp:
        etat = SaisieIpServeur;
        break;

      case AttenteServeur:
        etat = AttenteServeurIn;
        break;
      }
    }
  }
#pragma endregion ChoixModeSelectionServeur
  break;

  case SaisieIpServeur:
#pragma region SaisieIpServeur
    if (changementEtat)
    {
      ecran.effacerEcran();
      ecran.afficherGaucheL1("IP du serveur");

      ecran.afficherCentrerAlerte("IP : not yet!");
      Serial.printf("IP : not yet!\n");
    }
    if (!btnMode5s && btnMode.relache)
    {

      etat = ChoixModeSelectionServeur;
    }
#pragma endregion SaisieIpServeur
    break;

  case AttenteServeurIn:
#pragma region AttenteServeurIn
    if (changementEtat)
    {
      Serial.printf("AttenteServeurIn\n");
      ecran.effacerEcran();
      ecran.afficherGaucheL1("Attente serveur");

      serveur_start();
      // ecran.afficherCentrerAlerte("IP : not yet!");
      //
    }
    if (!btnMode5s && btnMode.relache)
    {

      etat = ChoixModeSelectionServeur;
    }
#pragma endregion AttenteServeurIn
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
      ecran.afficherGaucheL1("Choix de l'equipe\n");
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
      ecran.afficherGaucheL1("Sélection de l'arme");

      ecran.afficherCentrerAlerte("Arme : not yet!");
      Serial.printf("Arme : not yet!\n");
    }
    if (!btnMode5s && btnMode.relache)
    {

      etat = ChoixFin;
    }
    break;
  case ChoixFin:
#pragma region ChoixFin
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
#pragma endregion ChoixFin
  }

  if (memoEtat != etat)
    changementEtat = true;
  else
    changementEtat = false;
  
  //On efface le tempon du serveur
  sprintf(datasRecues, "");
  
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
