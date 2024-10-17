//wx_gui.hpp
#ifndef __WX_GUI_HPP__
#define __WX_GUI_HPP__

#include <cstdlib>
#include <ctime>

#include <wx-3.2/wx/wx.h>
#include <wx/generic/calctrlg.h>

#include "leang.hpp"
#include "database.hpp"


///////////////////////////////////////////////LOGIN_FRAME_CLASS//////////////////////////////////////////////////
///////////////////////////////////////////////LOGIN_FRAME_CLASS//////////////////////////////////////////////////
///////////////////////////////////////////////LOGIN_FRAME_CLASS//////////////////////////////////////////////////

class login_frame : public wxFrame{
public:
    login_frame(const wxString &tittle);
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

    std::string leangVersion;    

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
    //tablo icindekiler makro olarak baslangic ve son arasina yazilir
};



///////////////////////////////////////////////HOME_FRAME_CLASS//////////////////////////////////////////////////
///////////////////////////////////////////////HOME_FRAME_CLASS//////////////////////////////////////////////////
///////////////////////////////////////////////HOME_FRAME_CLASS//////////////////////////////////////////////////

class home_frame : public wxFrame , public leangEngine{
public:
    //constructor ve wxframeden turedigi icin o classinda constructorini baslatma
    home_frame(const wxString &yeniPencere_Baslik);

private:

//GUI BILESENLERI HOME_FRAME
    wxMenuBar *menuBarHome;

    wxMenu *menuSettings; //settings: ozellestirme , bildirim , program_dili
    wxMenu *menuSupport;  //support : github contributes
    wxMenu *menuLeang;    //leang   : kelime_tabani , ogrenilmek_istenen_diller , kelime_setleri , export , import , user_notes
    
    wxButton *leang_baslat; //leang.cpp'ye bagli fonksiyonlari calistirmali
    
    wxButton *sorulanKelime;
    wxButton *istenenKelime_1;
    wxButton *istenenKelime_2;
    wxButton *istenenKelime_3;
    wxButton *istenenKelime_4;

    std::string str_sorulanKelime;
    std::string str_istenenKelime_1;
    std::string str_istenenKelime_2;
    std::string str_istenenKelime_3;
    std::string str_istenenKelime_4;

//LEANG VIRTUAL DECLERATION//LEANG VIRTUAL DECLERATION//LEANG VIRTUAL DECLERATION//LEANG VIRTUAL DECLERATION
//LEANG VIRTUAL DECLERATION//LEANG VIRTUAL DECLERATION//LEANG VIRTUAL DECLERATION//LEANG VIRTUAL DECLERATION
//LEANG VIRTUAL DECLERATION//LEANG VIRTUAL DECLERATION//LEANG VIRTUAL DECLERATION//LEANG VIRTUAL DECLERATION
    void addWord(const std::string &dil_1 , const std::string &dil_2,const std::string &kelime1 , const std::string &kelime1_anlam) override;
    void getWord(const std::string &istenenDil , int istenenID) override;
    int randomizeID(int database_record_count) override;
    std::string& getRandomWord() override;
//LEANG VIRTUAL DECLERATION//LEANG VIRTUAL DECLERATION//LEANG VIRTUAL DECLERATION//LEANG VIRTUAL DECLERATION
//LEANG VIRTUAL DECLERATION//LEANG VIRTUAL DECLERATION//LEANG VIRTUAL DECLERATION//LEANG VIRTUAL DECLERATION
//LEANG VIRTUAL DECLERATION//LEANG VIRTUAL DECLERATION//LEANG VIRTUAL DECLERATION//LEANG VIRTUAL DECLERATION





    //SLOTLAR HOME_FRAME KOMPONENT SLOTLARI
    void slotHomeFrameBaslatButton(wxCommandEvent &e);


    //SLOTLAR-MENU SLOTLARI
    void slotSettingsTercihler(wxCommandEvent &e);
    void slotSettingsBildirim(wxCommandEvent &e);
    void slotSettingsProgramDili(wxCommandEvent &e);

    
    void slotSupportGithub(wxCommandEvent &e);
    
    
    void slotLeangKelimeTabani(wxCommandEvent &e);
    void slotLeangBaslatici(wxCommandEvent &e);
    void slotLeangKullaniciNotlari(wxCommandEvent &e);
    void slotLeangKelimeSetleri(wxCommandEvent &e);
    void slotLeangExport(wxCommandEvent &e);
    void slotLeangImport(wxCommandEvent &e);


protected:
    //SLOTLAR-KOMPONENT SLOTLARI (LEANG MOTORUNDAN GELECEK)


    //home_frame'ye ozel event_table deklerasyonu
    wxDECLARE_EVENT_TABLE();
};






/////////////////////////////////////////////////MENU PENCERELERI

/////////////////////////////////////////////////MENU PENCERELERI

/////////////////////////////////////////////////MENU PENCERELERI

/////////////////////////////////////////////////MENU PENCERELERI

/////////////////////////////////////////////////MENU PENCERELERI

/////////////////////////////////////////////////MENU PENCERELERI

/////////////////////////////////////////////////MENU PENCERELERI

/////////////////////////////////////////////////MENU PENCERELERI





///////////////////////////////////////////////settings_CLASS-SETTINGS//////////////////////////////////////////////////
///////////////////////////////////////////////settings_CLASS-SETTINGS//////////////////////////////////////////////////
///////////////////////////////////////////////settings_CLASS-SETTINGS//////////////////////////////////////////////////

class settings_frame : public wxFrame{
public:
    static bool pencereAcikMi;
    
    //alt pencere 1'den baslar bir menuBar icinde kac adet menu varsa oraya kadar gider
    settings_frame(const wxString &tittle);

private:

////TERCIHLER = PREFERENCES////
    bool isUserWantUpdate;
    wxString minSizeLogin;
    wxString minSizeHome;
    
    wxCheckBox *checkBox_autoUpdate;
    wxCheckBox *checkBox_loginGuiActive;
    wxCheckBox *checkBox_homeGuiActive;
    
    
    wxTextCtrl *textCTRL_loginSize;
    wxTextCtrl *textCTRL_homeSize;

    wxButton *button_kaydetTercih;

    //PREFERENCES-SLOTLAR//
    //SLOTLAR BURAYA    
    //YAZILACAK
    //PREFERENCES-SLOTLAR//

////TERCIHLER = PREFERENCES////


    void  OnSettingsClose(wxCloseEvent &e);
};


///////////////////////////////////////////////leang_CLASS-SETTINGS//////////////////////////////////////////////////
///////////////////////////////////////////////leang_CLASS-SETTINGS//////////////////////////////////////////////////
///////////////////////////////////////////////leang_CLASS-SETTINGS//////////////////////////////////////////////////
class leang_frame : public wxFrame{
public:
    leang_frame(const wxString &tittle);

private:
    
/*
1-KELIME TABANI
2-KELIME SETLERI
3-BASLATICI
4-IMPORT
5-EXPORT
6-KULLANICI NOTLARI
*/

};

#endif 