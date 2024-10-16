//wx_gui.hpp
#ifndef __WX_GUI_HPP__
#define __WX_GUI_HPP__

#include <wx-3.2/wx/wx.h>
#include "leang.hpp"
#include "database.hpp"

class login_frame : public wxFrame{
public:
    login_frame(const wxString &tittle,leangEngine &leTransfer);
    //~login_frame();
    
    std::string& getLogUsername();
    std::string& getLogPassword();

//composition implementation //
//database *db;


//STATIC
    //return=1=true,0=false
    static int isLoginButtonDatabaseConnection;

    //LOGIN=1,REGISTER=2,VERITABANI=3
    static void errMessage(int hataTip,const std::string &msg = "");

//pencerelerin adini tittle olarak icindeki komponentlerle tut konsol kismi icin



private:
    std::string mevcutPencereTittle;

    //guiden cekilecek veriler
    std::string log_username;
    std::string log_password;

    std::string reg_username;
    std::string reg_password;
    

    //gui elemanlari
    wxTextCtrl *userName;
    wxTextCtrl *userPassword;

    wxButton *buttonGiris;
    wxButton *buttonRegister;

    //GETTER SETTERLAR
    std::string getPencereTittle();

    //slotlar
    void OnLoginSumbitButton(wxCommandEvent &e); //login sumbit button
    void OnRegisterSumbitButton(wxCommandEvent &e); //register sumbit button

    //makrolar isin icine buton girince event table
    wxDECLARE_EVENT_TABLE();
};

class home_frame : public wxFrame{
public:
    //constructor ve wxframeden turedigi icin o classinda constructorini baslatma 
    home_frame(const wxString &yeniPencere_Baslik);

private:
    
};
//tablo icindekiler makro olarak baslangic ve son arasina yazilir

#endif 