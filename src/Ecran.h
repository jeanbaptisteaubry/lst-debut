#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SPI.h>

#include "eSprite_TDM.h"
#include "eSprite_SHD.h"
#include "eSprite_balleX1.h"
#include "eSprite_balleX3.h"
#include "eSprite_balleX5.h"
#include "eSprite_balleXAuto.h"
#include "eSprite_reload.h"
#include "Arme.h"

#define _RGB16BIT565(r, g, b) ((b % 32) + ((g % 64) << 6) + ((r % 32) << 11))

class Ecran
{
private:
    eSprite_TDM spr_tdm;
    eSprite_SHD spr_shd;
    eSprite_balleX1 spr_balleX1;
    eSprite_balleX3 spr_balleX3;
    eSprite_balleX5 spr_balleX5;
    eSprite_balleXAuto spr_balleXAuto;
    eSprite_Reload spr_reload;

public:
    int lastChange;
    TFT_eSPI ecran;
    int memoRestant = -1; // Temps restant dans le compte à rebour
    int positionScanVeille;
    bool veilleEnCours = false;
    int dureeAvantVeille = 5000; // 5s
    Ecran() : ecran(),
              spr_tdm(&ecran),
              spr_shd(&ecran),
              spr_balleX1(&ecran),
              spr_balleX3(&ecran),
              spr_balleX5(&ecran),
              spr_balleXAuto(&ecran),
              spr_reload(&ecran)
    {
    }

    void setChange()
    {
        lastChange = millis();
        veilleEnCours = false;
    }

    int lastDrawVeille = 0;
    int dureeDrawVeille = 100;
    void checkVeille()
    {
        if (veilleEnCours == false)
            if (millis() - lastChange >= dureeAvantVeille)
            {
                veilleEnCours = true;
                positionScanVeille = 0;
                lastDrawVeille = millis();
                Serial.println("Veille en cours");
            }
    }

    uint8_t veilleR;
    uint8_t veilleG;
    uint8_t veilleB;
    uint16_t colorVeilleN;
    uint16_t colorVeilleNm1;
    uint16_t colorVeilleNm2;
    void veille_initColor()
    {
        veilleR = random(2, 255);
        veilleG = random(2, 255);
        veilleB = random(2, 255);
        colorVeilleN =  ecran.color565(veilleR, veilleG, veilleB);
        colorVeilleNm1 = ecran.color565(veilleR - 1, veilleG - 1, veilleB - 1);
        colorVeilleNm2 = ecran.color565(veilleR - 2, veilleG - 2, veilleB - 2);
        Serial.printf("%d %d %d \n",colorVeilleN, colorVeilleNm1, colorVeilleNm2);
    }

    void drawVeille()
    {
        if (veilleEnCours && millis() - lastDrawVeille >= dureeDrawVeille)
        {
            lastDrawVeille = millis();
            Serial.printf("Position %d\n", positionScanVeille);
            switch (positionScanVeille)
            {

            case 0:
                veille_initColor();
                effacerEcran();
                ecran.drawLine(0, 0, 0, 80, colorVeilleN);
                positionScanVeille++;
                break;
            case 1:
                ecran.drawLine(0, 0, 80, 0, colorVeilleNm1);
                ecran.drawLine(1, 0, 1, 80, colorVeilleN);
                positionScanVeille++;
                break;
            case 182:
                veille_initColor();
                ecran.drawLine(0, 0, 0, 80, colorVeilleN);
                positionScanVeille = 1;
                break;
            default:
                ecran.drawLine(positionScanVeille - 2, 0, positionScanVeille - 2, 80, colorVeilleNm2);
                ecran.drawLine(positionScanVeille - 1, 0, positionScanVeille - 1, 80, colorVeilleNm1);
                ecran.drawLine(positionScanVeille, 0, positionScanVeille, 80, colorVeilleN);
                positionScanVeille++;
                break;
            }
        }
    }

    void init()
    {
        ecran.init();
        ecran.setRotation(1); // réglage de l'écran en mode paysage (0 pour mode portrait)
        ecran.fillScreen(TFT_BLACK);
        ecran.setTextColor(TFT_WHITE);
        // Charge depuis un fichier
        if (!SPIFFS.begin(true))
        {
            Serial.println("An Error has occurred while mounting SPIFFS");
            return;
        }

        spr_tdm.init();
        spr_shd.init();
        spr_balleX1.init();
        spr_balleX3.init();
        spr_balleX5.init();
        spr_balleXAuto.init();
        spr_reload.init();
    }

    void effacerEcran()
    {
        ecran.fillScreen(TFT_BLACK);
        // setChange();
    }
    void afficherCentrerNormal(char *str)
    {
        ecran.setTextColor(TFT_WHITE);
        ecran.drawCentreString(str, 80, 40, 2);
        setChange();
    }

    void afficherCentrerGaucheL1(char *str)
    {
        ecran.setTextColor(TFT_WHITE);
        ecran.drawCentreString(str, 0, 10, 2);
        setChange();
    }

    void afficherCentrerAlerte(char *str)
    {
        ecran.setTextColor(TFT_RED);
        ecran.drawCentreString(str, 80, 40, 2);
        setChange();
    }

    void afficherEcranJeu(int armure, int vie, int munition, modeTire mode, etatArme etat, float tempsRestantReload)
    {
        effacerEcran();
        spr_tdm.pushSprite(0, 0);
        spr_shd.pushSprite(0, 40);

        if (etat != rechargeChargeur)
        {

            switch (mode)
            {
            case simple:
                spr_balleX1.pushSprite(80, 0);
                Serial.println("Simple");
                break;
            case rafale:
                spr_balleX3.pushSprite(80, 0);
                Serial.println("Rafale");
                break;
            case automatique:
                spr_balleXAuto.pushSprite(80, 0);
                Serial.println("Automatique");
                break;
            }

            char str[2];
            if (munition <= 9)
                sprintf(str, "0%d\n", munition);
            else if (munition <= 99)
                sprintf(str, "%d\n", munition);
            else
                sprintf(str, "++\n");
            // Sprite spr = new Sprite
            // ecran.pushImage

            ecran.drawCentreString(str, 135, 10, 4);
        }
        else
            afficher_tempsReload(tempsRestantReload);
        //  Serial.printf("IN GAME\n", btnMode.numberKeyPresses, btnMode.dureeAction);
        setChange();
    }

    void afficher_tempsReload(float restantS)
    {

        if (restantS != memoRestant)
        {
            memoRestant = restantS;
            spr_reload.pushSprite(80, 0);
            ecran.drawRect(113, 0, 50, 35, TFT_BLACK);
            char str[2];

            sprintf(str, "%d\n", restantS);

            // Sprite spr = new Sprite
            // ecran.pushImage
            ecran.setTextColor(TFT_RED);
            ecran.drawCentreString(str, 135, 10, 4);
            ecran.setTextColor(TFT_WHITE);
            Serial.printf("Reload %d\n", restantS);
            setChange();
        }
    }
};