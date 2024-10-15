//leang.cpp
#include "../include/leang.hpp"
#include <iostream>
#include <fstream>
#include <string>


//STATIK DEFINE
bool leangEngine::loginGuiActive = -1;
bool leangEngine::leangGuiActive = -1;


leangEngine::leangEngine(){
    leangConfig("../config.txt");
}

void leangEngine::addWord(const std::string &dil_1 , const std::string &dil_2){

}

void leangEngine::getWord(const std::string &istenenDil){

}

int leangEngine::randomizeWord(int database_record_count){

}

enum leangConfigEnum{
    LOGIN_MIN_SIZE=1,
    AUTO_UPDATE,
    LOGIN_GUI_ACTIVE,
    LEANG_GUI_ACTIVE,
    LEANG_MENU_MIN_SIZE,
    AUTO_BACKUP
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
       
        short commandStart = satir.find("=");
        
        if (commandStart == std::string::npos) {
            continue; //= yoksa satiri atla
        }

        std::string command(satir.substr(commandStart+1));

        switch(rowNo){
            case LOGIN_MIN_SIZE:{
              size_t commaPos = command.find(",");
            
                if (commaPos != std::string::npos) {
                    std::string x = command.substr(0, commaPos);
                    std::string y = command.substr(commaPos + 1);
                
                    this->minSizeArr[0] = std::stoi(x);
                    this->minSizeArr[1] = std::stoi(y);
                }
                break;
            }
            case AUTO_UPDATE:{
                
                break;
            }
            case LOGIN_GUI_ACTIVE:{
                std::string isGuiActive(satir.substr(commandStart+1));
                
                for(char &c : isGuiActive){
                    c = tolower(c);
                }

                (isGuiActive == "true") ? this->loginGuiActive=true :
                (isGuiActive == "false") ? this->loginGuiActive=false:
                this->loginGuiActive = false;
                
                break;
            }
        }
        rowNo++;
    }

}