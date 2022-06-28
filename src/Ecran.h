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
#include "InputText.h"

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


    /**
     * @brief Récommence le compteur pour l'écran de veille
     * 
     */
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
        colorVeilleN = ecran.color565(veilleR, veilleG, veilleB);
        colorVeilleNm1 = ecran.color565(veilleR - 1, veilleG - 1, veilleB - 1);
        colorVeilleNm2 = ecran.color565(veilleR - 2, veilleG - 2, veilleB - 2);
        Serial.printf("%d %d %d \n", colorVeilleN, colorVeilleNm1, colorVeilleNm2);
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
    /**
     * @brief Affichage au centre
     *
     * @param str
     */
    void afficherCentrerNormal(char *str)
    {
        ecran.setTextColor(TFT_WHITE);
        ecran.drawCentreString(str, 80, 40, 2);
        setChange();
    }

    /**
     * @brief Affiche la chaine Titre à gauche en première ligne
     *
     * @param str
     */
    void afficherCentrerGaucheL1(char *str)
    {
        ecran.setTextColor(TFT_WHITE);
        ecran.drawCentreString(str, 0, 10, 2);
        setChange();
    }

    /**
     * @brief Affichage au centre d'un message d'alerte
     *
     * @param str
     */
    void afficherCentrerAlerte(char *str)
    {
        ecran.setTextColor(TFT_RED);
        ecran.drawCentreString(str, 80, 40, 2);
        setChange();
    }

    /**
     * @brief une action de type Arme à mettre en avant
     *
     * @param mode
     * @param etat
     * @param tempsRestantReload
     */
    void afficherEcranJeuArme(int munition, modeTire mode, etatArme etat, int tempsRestantReload)
    {
        if (etat != rechargeChargeur)
        {
            effacerEcran();
            setChange();

            switch (mode)
            {
            case simple:
                spr_balleX1.pushSprite(0, 20);
                Serial.println("Simple");
                break;
            case rafale:
                spr_balleX3.pushSprite(0, 20);
                Serial.println("Rafale");
                break;
            case automatique:
                spr_balleXAuto.pushSprite(0, 20);
                Serial.println("Automatique");
                break;
            }

            char str[4];
            if (munition <= 9)
                sprintf(str, "0%d\n", munition);
            else if (munition <= 99)
                sprintf(str, "%d\n", munition);
            else
                sprintf(str, "++\n");
            // Sprite spr = new Sprite
            // ecran.pushImage

            ecran.drawCentreString(str, 120, 20, 6);
        }
        else
        {
            if (tempsRestantReload != memoRestant)
            {
                //Changement de temps
                effacerEcran();
                setChange();

                memoRestant = tempsRestantReload;
                spr_reload.pushSprite(0, 20);
                char str[4];
                sprintf(str, "%d\n", tempsRestantReload);
                // Sprite spr = new Sprite
                // ecran.pushImage
                ecran.setTextColor(TFT_RED);
                ecran.drawCentreString(str, 120, 20, 6);
                ecran.setTextColor(TFT_WHITE);
                Serial.printf("Reload %d\n", tempsRestantReload);
                
            }
        }
    }

    /**
     * @brief Une action fait évoluer l'armure et/ou la vie du joueur mais pas l'arme
     *
     * @param armure
     * @param vie
     */
    void afficherEcranJeuArmure(int armure, int vie)
    {
        effacerEcran();
        spr_tdm.pushSprite(0, 20);
        spr_shd.pushSprite(80, 20);

        char str[4];
        if (vie <= 9)
            sprintf(str, "00%d\n", vie);
        else if (vie <= 99)
            sprintf(str, "0%d\n", vie);
        else
            sprintf(str, "100\n");
        // Sprite spr = new Sprite
        // ecran.pushImage

        ecran.drawCentreString(str, 60, 20, 5);

        if (armure <= 9)
            sprintf(str, "00%d\n", armure);
        else if (armure <= 99)
            sprintf(str, "0%d\n", armure);
        else
            sprintf(str, "100\n");
        // Sprite spr = new Sprite
        // ecran.pushImage

        ecran.drawCentreString(str, 160, 20, 5);
        setChange();
    }

    /**
     * @brief Affiche l'écran  de jeu sans activité mise en avant
     *
     * @param armure
     * @param vie
     * @param munition
     * @param mode
     * @param etat
     * @param tempsRestantReload
     */
    void afficherEcranJeu(int armure, int vie, int munition, modeTire mode, etatArme etat, float tempsRestantReload)
    {

        if (etat != rechargeChargeur)
        {
            effacerEcran();
            setChange();
            spr_tdm.pushSprite(0, 0);
            spr_shd.pushSprite(0, 40);

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

            char str[4];
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
        {
            if (tempsRestantReload != memoRestant)
            {
                effacerEcran();
                spr_tdm.pushSprite(0, 0);
                spr_shd.pushSprite(0, 40);
                memoRestant = tempsRestantReload;
                spr_reload.pushSprite(80, 0);
                char str[4];

                // Sprite spr = new Sprite
                // ecran.pushImage
                ecran.setTextColor(TFT_RED);
                ecran.drawCentreString(str, 135, 10, 4);
                ecran.setTextColor(TFT_WHITE);
                Serial.printf("Reload %d\n", tempsRestantReload);
                setChange();
            }
        }
        //  Serial.printf("IN GAME\n", btnMode.numberKeyPresses, btnMode.dureeAction);
    }

    /**
     * @brief Affichage de la zone Input pour la sélection du SSID
     *
     * @param inpTxt
     */
    void EcranAfficherChoixMdPSSID(InputText inpTxt)
    {
        effacerEcran();
        afficherCentrerGaucheL1("Mot de passe");

        //Affichage en rouge du caractère en cours :
        ecran.setTextColor(TFT_RED);
        ecran.drawCentreString(""+inpTxt.DonneCharAct(), 80, 40, 2);
        ecran.drawRightString("" + inpTxt.DonneChaineAvantAct(), 75,40,2);
        ecran.drawString("" + inpTxt.DonneChaineApres(), 90,40,2);
    }
};