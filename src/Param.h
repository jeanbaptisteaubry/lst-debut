#include <Arduino.h>
#include "FS.h"
#include "SPIFFS.h"
#ifndef PARAM_H
#define PARAM_H
enum ModeFonctionnement
{
    Autonome = 0,         //
    PiloteWifiDefaut = 1, //
    PiloteWifiParame = 2,
};

class Param
{

public:
    ModeFonctionnement mode;
    String Wifi_SSID;
    String Wifi_motDePAsse;
    int team;
    String nomJoueur;

    Param()
    {

        
    }

    void Load(){
        LoadDefault();
        File fileSvg = SPIFFS.open("/svg.txt");
        if (!fileSvg)
        {
            Serial.println("Failed to open fileSvg for reading");

            return;
        }
        char buffer[64];
        int i = 0;
        Serial.println("Param : Chargement depuis fichier");
        while (fileSvg.available())
        {
            int l = fileSvg.readBytesUntil('\n', buffer, sizeof(buffer));
            buffer[l] = 0;
            switch (i)
            {
            case 0:
            {
                String num = buffer;
                int value = num.toInt();
                mode = static_cast<ModeFonctionnement>(value);
                Serial.printf("  mode %s\n",String(mode));
            }
            break;
            case 1:

                Wifi_SSID = buffer;
                Serial.printf("  Wifi_SSID %s\n",Wifi_SSID);
                break;
            case 2:
                Wifi_motDePAsse = buffer;
                break;
            case 3:
             {
                String num = buffer;
                int value = num.toInt();
                team = static_cast<ModeFonctionnement>(value);
                Serial.printf("  team %d\n",team);
            }
                break;
            case 4:
                nomJoueur = buffer;
                Serial.printf("  nomJoueur %s\n",nomJoueur);
                break;
            }
            i++;
        }
        Serial.println("Param : Chargement fini");
        fileSvg.close();
    }

    void LoadDefault()
    {
        mode = Autonome;
        Wifi_SSID = "LazerGame";
        Wifi_motDePAsse = "0123456789";
        team = 1;
        nomJoueur = "Gamer";
    }

    void Save()
    {

        File fileSvg = SPIFFS.open("/svg.txt", "w");
        if (!fileSvg)
        {
            Serial.println("Failed to open fileSvg for reading");

            return;
        }
        fileSvg.printf("%s\n", String(mode));
        fileSvg.printf("%s\n", Wifi_SSID);
        fileSvg.printf("%s\n", Wifi_motDePAsse);
        fileSvg.printf("%d\n", team);
        fileSvg.printf("%s\n", nomJoueur);
        Serial.println("Param : Sauvegarde");
        fileSvg.close();
    }

    void Print()
    {
        Serial.printf("Configuration\n");
        Serial.printf("  mode %s\n",String(mode));
        Serial.printf("  Wifi_SSID %s\n",Wifi_SSID);
        Serial.printf("  Wifi_motDePAsse %s\n",Wifi_motDePAsse);
        Serial.printf("  team %d\n",team);
        Serial.printf("  nomJoueur %s\n",nomJoueur);
    }

};
#endif