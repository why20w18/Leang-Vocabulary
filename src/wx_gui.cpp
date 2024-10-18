//wx_gui.cpp
#include "../include/wx_gui.hpp"
#include "../include/leang.hpp"
#include "../include/database.hpp"

//STATIC DEFINE
int login_frame::isLoginButtonDatabaseConnection = 0;


enum ID_ENUM_LOGIN{
   ID_LoginSumbit = 1,
   ID_RegisterSumbit,
};

//EVENT TABLE MAKROLARI - bunun yerine dinamik bind kullanilabilirdi
wxBEGIN_EVENT_TABLE(login_frame,wxFrame)
   EVT_BUTTON(ID_LoginSumbit,login_frame::OnLoginSumbitButton) //func adres
   EVT_BUTTON(ID_RegisterSumbit,login_frame::OnRegisterSumbitButton)
   
wxEND_EVENT_TABLE()


login_frame::login_frame(const wxString &tittle) 
: wxFrame(nullptr,wxID_ANY,tittle,wxDefaultPosition)
{  
   CenterOnScreen();
   this->mevcutPencereTittle = tittle;
   this->leangVersion = "0.1";

   leangEngine::leangConfig("../config.txt");


//CONFIG KONSOL INFO
   std::cout << "MIN_SIZE=" << leangEngine::minSizeArr[0] << "," << leangEngine::minSizeArr[1] << std::endl; 
   SetMinSize(wxSize(leangEngine::minSizeArr[0],leangEngine::minSizeArr[1]));     

   std::string cfgDurum = (leangEngine::loginGuiActive == 1) ? "TRUE" : "FALSE";  
   std::cout << "GUI_ACTIVE=" << cfgDurum << std::endl; 


//GUI ISLEMLERI
   wxPanel *panel = new wxPanel(this,wxID_ANY);
   //LOGIN KISMI
   //-->label(wxstatictext)
   //-->textctrl

   wxStaticText *label_username = new wxStaticText(panel,wxID_ANY,"KULLANICI ADI:",wxPoint(18,85));
   userName = new wxTextCtrl(panel,wxID_ANY,"",wxPoint(135,75),wxSize(200,40));
   //genislik = 134...311 = 177
   //yukseklik = 112..72  = 40

   wxStaticText *label_pass = new wxStaticText(panel,wxID_ANY,"PAROLA :",wxPoint(18,183));
   userPassword = new wxTextCtrl(panel,wxID_ANY,"",wxPoint(135,175),wxSize(200,40),wxTE_PASSWORD);


//BUTONLAR
   buttonGiris = new wxButton(panel,ID_LoginSumbit,"Login",wxPoint(120,281),wxSize(134,36));
   //108,281 = x,y
   //h:317..281 = 36 
   //w:108..242 = 134

   buttonRegister = new wxButton(panel,ID_RegisterSumbit,"Register",wxPoint(146,320),wxSize(80,25));
   
   
   wxStaticText *leangVersionLabel = new wxStaticText(panel,wxID_ANY,"Leang Version : "+this->leangVersion,wxPoint(130,370));   
}

/////////////////////////////////////////////////////////LOGIN_FRAME_SLOT_FONKSIYONLARI////////////////////////////////////
/////////////////////////////////////////////////////////LOGIN_FRAME_SLOT_FONKSIYONLARI////////////////////////////////////
/////////////////////////////////////////////////////////LOGIN_FRAME_SLOT_FONKSIYONLARI////////////////////////////////////
/////////////////////////////////////////////////////////LOGIN_FRAME_SLOT_FONKSIYONLARI////////////////////////////////////
/////////////////////////////////////////////////////////LOGIN_FRAME_SLOT_FONKSIYONLARI////////////////////////////////////
/////////////////////////////////////////////////////////LOGIN_FRAME_SLOT_FONKSIYONLARI////////////////////////////////////
/////////////////////////////////////////////////////////LOGIN_FRAME_SLOT_FONKSIYONLARI////////////////////////////////////

void login_frame::OnLoginSumbitButton(wxCommandEvent &e){
   //buton verileri class icine cekmemizi saglayacak attributeslari alacagiz
   this->log_username = userName->GetValue();
   this->log_password = userPassword->GetValue();

   std::cout << "input_username : " << log_username << "\ninput_password : " << log_password << "\n";
   //veritabanina baglanti kuracagiz eger bilgiler dogrulanirsa le_framede yeni bir frame baslatacagiz LEANG | MENU olarak
   
   if(log_username == "" || log_password == ""){
      errMessage(1,"KULLANICI ADI YADA PAROLA BOS BIRAKILAMAZ !");
      return;
   }

    database db("../databaseDIR/leang.db");

    if (db.userLogin(log_username, log_password) == 1) {
        std::cout << "KULLANICI ADI VE PAROLA DOGRUDUR!" << std::endl;
        this->Close();
        isLoginButtonDatabaseConnection = 1;

         home_frame *mainMenu = new home_frame("LEANG | HOME | USER: "+getLogUsername());
         mainMenu->Show(true);

    } 
    else {
        errMessage(1, "KAYITSIZ KULLANICI !");
         isLoginButtonDatabaseConnection = 0;
    }
}

void login_frame::OnRegisterSumbitButton(wxCommandEvent &e){

      std::cout << "register" << std::endl;   

      this->reg_username = userName->GetValue();
      this->reg_password = userPassword->GetValue();

      if(reg_password == "" || reg_username == ""){
         errMessage(3,"KAYIT ICIN KULLANICI ADI VE PAROLA GIRMELISINIZ !");
         return;
      }

      database db("../databaseDIR/leang.db");
      
      int donus = db.userRegister(reg_username,reg_password);
      std::cout << "donus : " << donus << std::endl;
      
      if(donus == 1){
         wxMessageBox("BASARIYLA KAYIT OLDUNUZ\nGIRIS YAPABILIRSINIZ","KAYIT BILGISI", wxOK | wxICON_INFORMATION);
         return;
      }
      else{
         errMessage(2,"KAYIT SIRASINDA PROBLEM YASANDI !");
         return;
      }
}

//private memberlari getter ile database logine yolla
std::string& login_frame::getLogUsername(){
   return this->log_username;
}

std::string& login_frame::getLogPassword(){
   return this->log_password;
}

enum{
   LOGIN_HATASI = 1,
   REGISTER_HATASI,
   VERITABANI_HATASI
};


std::string login_frame::getPencereTittle(){
   return this->mevcutPencereTittle;
}


//STATIC FONKSIYON GEREKTIGI YERDE CLASS ADI ILE CAGIRACAGIZ
void login_frame::errMessage(int hataTip,const std::string &m){
   if(leangEngine::loginGuiActive == false){
      //gui kapaliysa metin olarak
   
   }
   else if(leangEngine::loginGuiActive == true){
      //gui aciksa grafik olarak

      switch(hataTip){
         case LOGIN_HATASI:{
            wxMessageBox("KULLANICI ADI YADA PAROLA PROBLEMI !\n\n"+m,"LOGIN_HATASI",wxOK | wxICON_INFORMATION);
            break;
         }

         case REGISTER_HATASI:{
             wxMessageBox("KAYIT SIRASINDA HATA OLUSTU !\n\n"+m,"REGISTER_HATASI",wxOK | wxICON_INFORMATION);
            break;
         }

         case VERITABANI_HATASI:{
             wxMessageBox("VERITABANI BAGLANTISI SAGLANAMADI !\n\n"+m,"VERITABANI_HATASI",wxOK | wxICON_INFORMATION);
            break;
         }
      }
   }
}
















/////////////////////////////////////////////HOME_FRAME_CLASS_DEFINE///////////////////////////////////////////////////
/////////////////////////////////////////////HOME_FRAME_CLASS_DEFINE///////////////////////////////////////////////////
/////////////////////////////////////////////HOME_FRAME_CLASS_DEFINE///////////////////////////////////////////////////
/////////////////////////////////////////////HOME_FRAME_CLASS_DEFINE///////////////////////////////////////////////////
/////////////////////////////////////////////HOME_FRAME_CLASS_DEFINE///////////////////////////////////////////////////
/////////////////////////////////////////////HOME_FRAME_CLASS_DEFINE///////////////////////////////////////////////////

enum ID_ENUM_HOME{
    ID_SETTINGS_OZELLESTIRME = 608,
    ID_SETTINGS_BILDIRIM,
    ID_SETTINGS_PROGRAMDILI,
    ID_SETTINGS_PROFIL,

    ID_SUPPORT_GITHUB,
    
    ID_LEANG_KELIMETABANI,
    ID_LEANG_BASLATICI,
    ID_LEANG_KULLANICINOTLARI,
    ID_LEANG_KELIMESETLERI,
    ID_LEANG_EXPORT,
    ID_LEANG_IMPORT,

    ID_LEANG_BASLAT_BUTTON,
    ID_LEANG_DURDUR_BUTTON,
    
    ID_LEANG_SORULAN_BUTTON,

    ID_LEANG_ISTENEN_1_BUTTON,
    ID_LEANG_ISTENEN_2_BUTTON,
    ID_LEANG_ISTENEN_3_BUTTON,
    ID_LEANG_ISTENEN_4_BUTTON
};


enum settings_leang_menuNO{
   SETTINGS_MENU_OZELLESTIRME_TERCIHLER = 1337,
   SETTINGS_MENU_BILDIRIM,
   SETTINGS_MENU_PROGRAM_DILI,
   SETTINGS_MENU_PROFIL,

   LEANG_MENU_KELIME_TABANI,
   LEANG_MENU_KELIME_SETLERI,
   LEANG_MENU_BASLATICI,
   LEANG_MENU_IMPORT,
   LEANG_MENU_EXPORT,
   LEANG_MENU_KULLANICI_NOTLARI
};

wxBEGIN_EVENT_TABLE(home_frame,wxFrame)
   EVT_MENU(ID_SUPPORT_GITHUB,home_frame::slotSupportGithub)
  
   EVT_MENU(ID_SETTINGS_OZELLESTIRME,home_frame::slotSettingsTercihler)
  
   EVT_MENU(ID_LEANG_BASLATICI,home_frame::slotLeangBaslatici)
  
   EVT_BUTTON(ID_LEANG_BASLAT_BUTTON,home_frame::slotHomeFrameBaslatButton)
wxEND_EVENT_TABLE()

home_frame::home_frame(const wxString &title) : wxFrame(nullptr,wxID_ANY,title,wxDefaultPosition)
{  
   CenterOnScreen();
   std::cout << "HOME PENCERESI BASLATILDI !\n"; 
   SetMinSize(wxSize(750,520));
   SetMaxSize(wxSize(750,520));

   //ayri bir dosyada program icinde gecen metinlerin ingilizcesi ve almancasi yer alacak menu metinleri
   //istek dile gore oradan cekilecek 3.parametre olarak simdilik statik olarak ayarlandi
   
   //gui elemanlarini nesne ile beraber baslatma
   wxPanel* panel = new wxPanel(this);

   menuSettings = new wxMenu;
   menuSupport = new wxMenu;
   menuLeang = new wxMenu;

   sorulanKelime = new wxButton(panel,ID_LEANG_SORULAN_BUTTON,"SORULACAK_KELIME",wxPoint(25,50),wxSize(450,350));
   sorulanKelime->Enable(false);

   leang_baslat = new wxButton(panel,ID_LEANG_BASLAT_BUTTON,"LEANG BASLAT",wxPoint(575,5),wxSize(120,50));
   leang_baslat = new wxButton(panel,ID_LEANG_DURDUR_BUTTON,"LEANG DURDUR",wxPoint(575,75),wxSize(120,50));



   istenenKelime_1 = new wxButton(panel,ID_LEANG_ISTENEN_1_BUTTON,this->str_istenenKelime_1,wxPoint(575,150),wxSize(150,50));
   istenenKelime_2 = new wxButton(panel,ID_LEANG_ISTENEN_2_BUTTON,this->str_istenenKelime_2,wxPoint(575,220),wxSize(150,50));
   istenenKelime_3 = new wxButton(panel,ID_LEANG_ISTENEN_3_BUTTON,this->str_istenenKelime_3,wxPoint(575,290),wxSize(150,50));
   istenenKelime_4 = new wxButton(panel,ID_LEANG_ISTENEN_4_BUTTON,this->str_istenenKelime_4,wxPoint(575,360),wxSize(150,50));



////////////////////////MENU_SETTINGS
   menuSettings->Append(ID_SETTINGS_OZELLESTIRME,"&Ozellestirme (Preferences)\tCTRL+P","pencere boyutu , gui aktifligi vs. ayarlari");
   menuSettings->AppendSeparator();
   
   menuSettings->Append(ID_SETTINGS_BILDIRIM,"&Bildirimler (Repeat)\tCTRL+R","leang'in size bildirim gonderme sikligini ayarlayin");
   menuSettings->AppendSeparator();


   menuSettings->Append(ID_SETTINGS_PROGRAMDILI,"&Program Dili (Language)\tCTRL+L","programi istediginiz dilde kullanin");
   menuSettings->AppendSeparator();

   menuSettings->Append(ID_SETTINGS_PROFIL,"&Profil (Me)\tCTRL+M","kullanici adi , parola degisimi , hesap silme");

   menuBarHome = new wxMenuBar();
////////////////////////MENU_SETTINGS


////////////////////////MENU_SUPPORT
   menuSupport->Append(ID_SUPPORT_GITHUB,"&Github\tCTRL+G","leang'a projesine katkida bulunun");
////////////////////////MENU_SUPPORT



////////////////////////MENU_LEANG
   menuLeang->Append(ID_LEANG_KELIMETABANI,"&Kelime Tabani","tum kullanicilarin tum calisma kelimeleri");
   menuLeang->AppendSeparator();

   menuLeang->Append(ID_LEANG_KELIMESETLERI,"&Kelime Setleri","olusturdugunuz kategorik kelime setlerini inceleyin");
   menuLeang->AppendSeparator();

   menuLeang->Append(ID_LEANG_BASLATICI,"&Baslatici\tCTRL+S","uzerine calismak istediginiz dilleri , kelimeleri ve fazlasini ayarlayin");
   menuLeang->AppendSeparator();


   menuLeang->Append(ID_LEANG_IMPORT,"&Import","Leang icin baskasinin olusturdugu kelime setini ekleyin");
   menuLeang->AppendSeparator();

   menuLeang->Append(ID_LEANG_EXPORT,"&Export","Leang icin kendi kelime setinizi disari aktarip paylasin");
   menuLeang->AppendSeparator();

   menuLeang->Append(ID_LEANG_KULLANICINOTLARI,"&Notlarim\tCTRL+N","ilerlemeni kaydetmek icin not uygulamasi");
////////////////////////MENU_LEANG


   menuBarHome->Append(menuSettings,"&Settings");
   menuBarHome->Append(menuSupport,"&Support");
   menuBarHome->Append(menuLeang,"&Leang");

   SetMenuBar(menuBarHome);
   CreateStatusBar();






}//HOME_FRAME_CONSTRUCTOR

////////////////////////////////////////////////HOME_FRAME_VIRTUAL_LEANG_ENGINE///////////////////////////////////////////////////
////////////////////////////////////////////////HOME_FRAME_VIRTUAL_LEANG_ENGINE///////////////////////////////////////////////////
////////////////////////////////////////////////HOME_FRAME_VIRTUAL_LEANG_ENGINE///////////////////////////////////////////////////
////////////////////////////////////////////////HOME_FRAME_VIRTUAL_LEANG_ENGINE///////////////////////////////////////////////////

void home_frame::addWord(const std::string &dil_1 , const std::string &dil_2,const std::string &kelime1 ,
 const std::string &kelime1_anlam , int kelimesetiID){

}
void home_frame::getWord(const std::string &istenenDil , int istenenRecord ,  int kelimesetiID){
   

}



int home_frame::randomizeID(const std::string &kelimeSetiAdi){
   database db("../databaseDIR/leang.db");
   int totalRecord = db.getRecordCount(kelimeSetiAdi);
   if(totalRecord <= 1){
      login_frame::errMessage(3,"KELIME SETINDE YETERI KADAR KELIME YOKTUR !");
      return 0;
   }

   srand(time(nullptr)); //seed atama
   
   //1 <= randomize_id <= totalRecord
   int randomize_id = 1 + rand() % totalRecord; 

   return totalRecord;
}


////////////////////////////////////////////////HOME_FRAME_SLOT_FONKSIYONLARI///////////////////////////////////////////////////
////////////////////////////////////////////////HOME_FRAME_SLOT_FONKSIYONLARI///////////////////////////////////////////////////
////////////////////////////////////////////////HOME_FRAME_SLOT_FONKSIYONLARI///////////////////////////////////////////////////
////////////////////////////////////////////////HOME_FRAME_SLOT_FONKSIYONLARI///////////////////////////////////////////////////
////////////////////////////////////////////////HOME_FRAME_SLOT_FONKSIYONLARI///////////////////////////////////////////////////

void home_frame::slotHomeFrameBaslatButton(wxCommandEvent &e){

   std::cout << "buton tiklandi" << std::endl;

   istenenKelime_1->SetLabel("hello");
}



void home_frame::slotSettingsTercihler(wxCommandEvent &e){
   //home_frame *settings = new home_frame("SETTINGS | Ozellestirme");

      if(!settings_frame::pencereAcikMi){
      settings_frame *settings_frame_tercihler = new settings_frame("SETTINGS | Tercihler",SETTINGS_MENU_OZELLESTIRME_TERCIHLER);
      settings_frame_tercihler->Show(true);
      }
      else 
      wxMessageBox("PENCERE ZATEN ACIKTIR","AMAC DISI KULLANIM",wxOK | wxICON_INFORMATION);


      std::cout << "settings baslatildi" << std::endl;
}
void home_frame::slotSettingsBildirim(wxCommandEvent &e){}
void home_frame::slotSettingsProgramDili(wxCommandEvent &e){}

void home_frame::slotSupportGithub(wxCommandEvent &e){
   //mesaj kutusunu ortalayarak cikarttik
   wxMessageDialog(this,"https://github.com/why20w18/Leang-Vocabulary\n\
ADRESINDEN KATKIDA BULUNABILIR PROGRAMDAKI BUGLARI BILDIREBILIRSIN","Support-Github",wxOK | wxCENTRE).ShowModal();
}
    
void home_frame::slotLeangKelimeTabani(wxCommandEvent &e){

}

void home_frame::slotLeangBaslatici(wxCommandEvent &e){

   if(!settings_frame::pencereAcikMi){
   leang_frame *leang_frame_baslatici = new leang_frame("LEANG | Baslatici",LEANG_MENU_BASLATICI);
   leang_frame_baslatici->Show(true);
      }
      else 
      wxMessageBox("PENCERE ZATEN ACIKTIR","AMAC DISI KULLANIM",wxOK | wxICON_INFORMATION);



   

}

void home_frame::slotLeangKullaniciNotlari(wxCommandEvent &e){}
    
void home_frame::slotLeangKelimeSetleri(wxCommandEvent &e){}
void home_frame::slotLeangExport(wxCommandEvent &e){}
void home_frame::slotLeangImport(wxCommandEvent &e){}

















/////////////////////////////////////////////SETTINGS_FRAME_CLASS_DEFINE///////////////////////////////////////////////////
/////////////////////////////////////////////SETTINGS_FRAME_CLASS_DEFINE///////////////////////////////////////////////////
/////////////////////////////////////////////SETTINGS_FRAME_CLASS_DEFINE///////////////////////////////////////////////////
/////////////////////////////////////////////SETTINGS_FRAME_CLASS_DEFINE///////////////////////////////////////////////////
/////////////////////////////////////////////SETTINGS_FRAME_CLASS_DEFINE///////////////////////////////////////////////////
/////////////////////////////////////////////SETTINGS_FRAME_CLASS_DEFINE///////////////////////////////////////////////////


bool settings_frame::pencereAcikMi = false;

settings_frame::settings_frame(const wxString &tittle,int menuNo)
 : wxFrame(nullptr,wxID_ANY,tittle,wxDefaultPosition)
{     
      //settings_frame construct edildiyse pencere baslamistir

      switch(menuNo){
         case SETTINGS_MENU_OZELLESTIRME_TERCIHLER:{
            this->settings_frame_terchiler();
         break;
         }
      }

      //destructor yaz calisan caseye gore ve hepsini sil ilerleyen zamanda
}

void  settings_frame::OnSettingsClose(wxCloseEvent &e){
   this->pencereAcikMi = false;
   e.Skip();
}

//MENU PENCERELERI GUI FONKSIYONLARI
void settings_frame::settings_frame_terchiler(){
      this->pencereAcikMi = true;

      std::cout << "settings_frame initalize" << std::endl;
      
      //yatay sekilde tutulacak sizer olabilirse kullanilacak
      SetMinSize(wxSize(500,250));
      SetMaxSize(wxSize(500,250));
      CentreOnScreen();


      //bu pencerenin kapanma sinyalini tutacagiz kapandiysa static degiskeni false cekecegiz
      this->Bind(wxEVT_CLOSE_WINDOW,&settings_frame::OnSettingsClose,this);

      //gui bilesenlerini baslatma
      checkBox_autoUpdate = new wxCheckBox(this,wxID_ANY,"Otomatik Guncelleme",wxPoint(15,40),wxDefaultSize);
      checkBox_loginGuiActive = new wxCheckBox(this,wxID_ANY,"Login Grafik Aktifligi",wxPoint(15,80),wxDefaultSize);
      checkBox_homeGuiActive = new wxCheckBox(this,wxID_ANY,"Home Grafik Aktifligi",wxPoint(15,120),wxDefaultSize);

      wxStaticText *label_logsize = new wxStaticText(this,wxID_ANY,"LOGIN GUI AKTIFLIGI:",wxPoint(225,67),wxDefaultSize);
      textCTRL_loginSize = new wxTextCtrl(this,wxID_ANY,"",wxPoint(380,60),wxSize(100,40));

      wxStaticText *label_homesize = new wxStaticText(this,wxID_ANY,"HOME GUI AKTIFLIGI:",wxPoint(225,127),wxDefaultSize);
      textCTRL_homeSize = new wxTextCtrl(this,wxID_ANY,"",wxPoint(380,120),wxSize(100,40));

      button_kaydetTercih = new wxButton(this,wxID_ANY,"KAYDET",wxPoint(395,15),wxSize(75,25)); 
}
















/////////////////////////////////////////////LEANG_FRAME_CLASS_DEFINE///////////////////////////////////////////////////
/////////////////////////////////////////////LEANG_FRAME_CLASS_DEFINE///////////////////////////////////////////////////
/////////////////////////////////////////////LEANG_FRAME_CLASS_DEFINE///////////////////////////////////////////////////
/////////////////////////////////////////////LEANG_FRAME_CLASS_DEFINE///////////////////////////////////////////////////
/////////////////////////////////////////////LEANG_FRAME_CLASS_DEFINE///////////////////////////////////////////////////
/////////////////////////////////////////////LEANG_FRAME_CLASS_DEFINE///////////////////////////////////////////////////

leang_frame::leang_frame(const wxString &tittle , int menuNO) 
: wxFrame(nullptr,wxID_ANY,tittle,wxDefaultPosition,wxSize(500,250))
{  
   this->Bind(wxEVT_CLOSE_WINDOW,&leang_frame::OnSettingsClose,this);
   settings_frame::pencereAcikMi = true;
   SetMaxSize(wxSize(500,250));
   SetMinSize(wxSize(500,250));
   this->CenterOnScreen();

   switch(menuNO){
      case LEANG_MENU_KELIME_TABANI:{
         this->leang_frame_baslatici();
         break;
      }
      default:{
         std::cout << "DEFAULT_LEANG_FRAMA\n";
         break;
      }
   }
}

void  leang_frame::OnSettingsClose(wxCloseEvent &e){
   settings_frame::pencereAcikMi = false;
   e.Skip();
}

void leang_frame::leang_frame_baslatici(){
   


}