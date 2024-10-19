//leang.cpp
#include "../include/leang.hpp"

#include <iostream>
#include <fstream>

#include <string>

//STATIK DEFINE
bool leangEngine::loginGuiActive = -1;
bool leangEngine::leangGuiActive = -1;

int leangEngine::minSizeArr[2] = {450,450};

  
int leangEngine::leang_baslatici_kelime_sayisi = 0;
int leangEngine::leang_baslatici_secenek_sayisi = 4;


enum leangConfigEnum{
    LOGIN_MIN_SIZE=1,
    LEANG_MENU_MIN_SIZE,
    LOGIN_GUI_ACTIVE,
    LEANG_GUI_ACTIVE,
    AUTO_UPDATE,
    AUTO_BACKUP,
    
    LEANG_BASLATICI_KELIME_SAYISI,
    LEANG_BASLATICI_SECENEK_SAYISI,
};


void leangEngine::leangConfig(const std::string &configPath){
    std::ifstream cfgIcerik(configPath);

    if(!cfgIcerik){
        //dosya bulunamadiysa
        std::cerr << "LEANG HATA: konfigurasyon dosyasi bulunamadi\nVARSAYILAN AYARLARLA BASLATILDI 750x750" << std::endl;
        return;
    }

    std::string satir;
    short rowNo = 1;

    while(getline(cfgIcerik,satir)){
       
        short commandEqualIndex = satir.find("=");
        
        if (commandEqualIndex == std::string::npos) {
            continue; //= yoksa satiri atla
        }

        std::string command(satir.substr(commandEqualIndex+1));

        switch(rowNo){
            case LOGIN_MIN_SIZE:{
              size_t commaPos = command.find(",");
            
                if (commaPos != std::string::npos) {
                    std::string x = command.substr(0, commaPos);
                    std::string y = command.substr(commaPos + 1);
                
                    minSizeArr[0] = std::stoi(x);
                    minSizeArr[1] = std::stoi(y);
                }
                break;
            }
            
            case LOGIN_GUI_ACTIVE:{
                std::string isGuiActive(satir.substr(commandEqualIndex+1));
                
                for(char &c : isGuiActive){
                    c = tolower(c);
                }

                (isGuiActive == "true") ? loginGuiActive=true :
                (isGuiActive == "false") ? loginGuiActive=false:
                loginGuiActive = false;
                
                break;
            }

            case AUTO_UPDATE:{
                break;
            }

            case AUTO_BACKUP:{
                break;
            }           
            
            case LEANG_BASLATICI_KELIME_SAYISI:{
                std::cout << "gelen kelime_say : " << leang_baslatici_kelime_sayisi << "\n";
                leangConfigYazma(configPath,LEANG_BASLATICI_KELIME_SAYISI,commandEqualIndex+1,leang_baslatici_kelime_sayisi);
                break;
            }
            case LEANG_BASLATICI_SECENEK_SAYISI:{
                std::cout << "gelen baslatici_say : " << leang_baslatici_secenek_sayisi << "\n";
                leangConfigYazma(configPath,LEANG_BASLATICI_SECENEK_SAYISI,commandEqualIndex+1,leang_baslatici_secenek_sayisi);
                break;
            }
       }
        rowNo++;
    }
    cfgIcerik.close();
}

void leangEngine::leangConfigYazma(const std::string &configPath,int yazmaYapilacakSatir,short yazmaYapilacakIndex,int yazilacakVeri){

    std::fstream cfgFile(configPath);
    std::string satir;
    
    //byte cinsinden konum satir.length + "\n"
    std::streampos byteKonum = 0; //streamPosition
    int satirSay = 0;


    while(getline(cfgFile,satir)){
        satirSay++;

        if(satirSay == yazmaYapilacakSatir){
            break;
        }
            byteKonum += satir.length() + 1;
    }

    //konum tespitinden sonra yazma islemi
    cfgFile.seekp(byteKonum+yazmaYapilacakIndex);
    cfgFile << yazilacakVeri;

    cfgFile.close();
}
