//main.cpp
#include "../include/wx_gui.hpp"
#include "../include/leang.hpp"
#include "../include/database.hpp"
#include "../include/konsol.hpp"

#include <iostream>

using namespace std;

class le_app : public wxApp{
public:
    bool OnInit() override{
        database db("../databaseDIR/leang.db");
        //leangEngine le;
        
        //gui aktif degilse baslatilmasin
        if(leangEngine::loginGuiActive){
        
        login_frame *login = new login_frame("LEANG | LOGIN");
        login->Show(leangEngine::loginGuiActive);
        

        }
        else{ //KONSOL KISMI
        //konsolInitalize konsol();
        std::cout << "LEANG KONSOL\nMOD:CLI\n>>";
        std::string cmd;

        }

        return true;
    }
};

wxIMPLEMENT_APP(le_app);
