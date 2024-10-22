//wx_gui.cpp
#include "../include/wx_gui.hpp"
#include "../include/leang.hpp"
#include "../include/database.hpp"


//STATIC DEFINE
int login_frame::isLoginButtonDatabaseConnection = 0;


enum ID_ENUM_LOGIN_LEANGMENU{
   ID_LoginSumbit = 1,
   ID_RegisterSumbit,
   
   ID_SaveLeangBaslaticiButton,

   ID_LeangKelimeSetleriAddButton,
   ID_LeangKelimeSetleriListButton,
   ID_LeangKelimeSetleriTabaniButton,
   
   ID_LeangKelimeSetleriDuzenle_SetlerimiGoster,
   ID_LeangKelimeSetleriDuzenle_wxListBoxSecilenSet,
   ID_LeangKelimeSetleriDuzenle_setIcerigiGoruntule,
   ID_LeangKelimeSetleriDuzenle_setShownCount,
   ID_LeangKelimeSetleriDuzenle_addWords,

   
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

   leangEngine::leangConfig("../leang.cfg");


//CONFIG KONSOL INFO
   std::cout << "MIN_SIZE=" << leangEngine::minSizeArr[0] << "," << leangEngine::minSizeArr[1] << std::endl; 
   SetMinSize(wxSize(leangEngine::minSizeArr[0],leangEngine::minSizeArr[1]));   
   SetMaxSize(wxSize(leangEngine::minSizeArr[0]+50,leangEngine::minSizeArr[1]+50));

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

enum ID_ENUM_HOME_{
    ID_SETTINGS_OZELLESTIRME = 608,
    ID_SETTINGS_BILDIRIM,
    ID_SETTINGS_PROGRAMDILI,
    ID_SETTINGS_PROFIL,

    ID_SUPPORT_GITHUB,
    
    ID_LEANG_KELIMETABANI,
    ID_LEANG_BASLATICI,
    ID_LEANG_KULLANICINOTLARI,
    ID_LEANG_KELIMESETLERI,
    ID_LEANG_KELIMESETLERI_DUZENLE,
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

   LEANG_MENU_KELIME_SETLERI_DUZENLEME,
   LEANG_MENU_KELIME_SETLERI_DUZENLEME_GET_DATABASE_TABLE,
   
   LEANG_MENU_BASLATICI,
   LEANG_MENU_IMPORT,
   LEANG_MENU_EXPORT,
   LEANG_MENU_KULLANICI_NOTLARI
};

wxBEGIN_EVENT_TABLE(home_frame,wxFrame)
   EVT_MENU(ID_SUPPORT_GITHUB,home_frame::slotSupportGithub)
  
   EVT_MENU(ID_SETTINGS_OZELLESTIRME,home_frame::slotSettingsTercihler)
   EVT_MENU(ID_LEANG_BASLATICI,home_frame::slotLeangBaslatici)
   EVT_MENU(ID_LEANG_KELIMESETLERI,home_frame::slotLeangKelimeSetleri)
   EVT_MENU(ID_LEANG_KELIMESETLERI_DUZENLE,home_frame::slotLeangKelimeSetleriDuzenleyici)
   EVT_MENU(ID_LEANG_KELIMETABANI,home_frame::slotLeangKelimeTabani)
   
   
  
   EVT_BUTTON(ID_LEANG_BASLAT_BUTTON,home_frame::slotHomeFrameBaslatButton)
wxEND_EVENT_TABLE()

home_frame::home_frame(const wxString &title) : wxFrame(nullptr,wxID_ANY,title,wxDefaultPosition)
{  

   CenterOnScreen();
   std::cout << "HOME PENCERESI BASLATILDI !\n"; 
   SetMinSize(wxSize(750,520));
   SetMaxSize(wxSize(750,520));
   olusturucu_username = this->GetTitle().substr(this->GetTitle().ToStdString().find(":")+2);

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
   leang_baslat->Enable(false);

   leang_durdur = new wxButton(panel,ID_LEANG_DURDUR_BUTTON,"LEANG DURDUR",wxPoint(575,75),wxSize(120,50));
   leang_durdur->Enable(false);


   istenenKelime_1 = new wxButton(panel,ID_LEANG_ISTENEN_1_BUTTON,this->str_istenenKelime_1,wxPoint(575,150),wxSize(150,50));
   istenenKelime_1->Enable(false);
   
   istenenKelime_2 = new wxButton(panel,ID_LEANG_ISTENEN_2_BUTTON,this->str_istenenKelime_2,wxPoint(575,220),wxSize(150,50));
   istenenKelime_2->Enable(false);
   
   istenenKelime_3 = new wxButton(panel,ID_LEANG_ISTENEN_3_BUTTON,this->str_istenenKelime_3,wxPoint(575,290),wxSize(150,50));
   istenenKelime_3->Enable(false);
   
   istenenKelime_4 = new wxButton(panel,ID_LEANG_ISTENEN_4_BUTTON,this->str_istenenKelime_4,wxPoint(575,360),wxSize(150,50));
   istenenKelime_4->Enable(false);


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

   menuLeang->Append(ID_LEANG_KELIMESETLERI_DUZENLE,"&Kelime Setleri Duzenleyici\tCTRL+E","Kelime setlerinize kelime ekleyin yada silin");
   menuLeang->AppendSeparator();

   menuLeang->Append(ID_LEANG_KELIMESETLERI,"&Kelime Setleri\tCTRL+C","olusturdugunuz kategorik kelime setlerini inceleyin");
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


   if(leang_frame::mem_secenekSayisi == 0){
      login_frame::errMessage(3,"LUTFEN LEANG SEKMESINDEN BASLATICI AYARLARINI YAPIN !");
      return;
   }




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
////////////////////////////////////////////////HOME_FRAME_METODLARI///////////////////////////////////////////////////
////////////////////////////////////////////////HOME_FRAME_METODLARI///////////////////////////////////////////////////
////////////////////////////////////////////////HOME_FRAME_METODLARI///////////////////////////////////////////////////
////////////////////////////////////////////////HOME_FRAME_METODLARI///////////////////////////////////////////////////
////////////////////////////////////////////////HOME_FRAME_METODLARI///////////////////////////////////////////////////
int home_frame::setEnabledDisabledButton(int activeButtonCount){
   //leang uzerinden bunu cagiracagiz
   leang_baslat->Enable(true);
   
   switch(activeButtonCount){
      case 2:{
         istenenKelime_1->Enable(true);
         istenenKelime_2->Enable(true);
         istenenKelime_3->Enable(false);
         istenenKelime_4->Enable(false);
         return 2;
      }
      case 3:{
         istenenKelime_1->Enable(true);
         istenenKelime_2->Enable(true);
         istenenKelime_3->Enable(true);
         istenenKelime_4->Enable(false);
         return 3;
      }
      case 4:{
         istenenKelime_1->Enable(true);
         istenenKelime_2->Enable(true);
         istenenKelime_3->Enable(true);
         istenenKelime_4->Enable(true);
         return 4;
      }
   }
   std::cout << "setEnabledDisabledButton Func\n";
}


void home_frame::logMessage(const std::string &baslik ,const std::string &textr){
   wxMessageBox(textr,baslik,wxOK | wxICON_INFORMATION);
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
   
   if(!settings_frame::pencereAcikMi){
   
      leang_frame *leang_frame_kelimeTabani = new leang_frame("LEANG | Kelime Tabani",LEANG_MENU_KELIME_TABANI,this);
      leang_frame_kelimeTabani->Show(true);
   }
   
   else 
   wxMessageBox("PENCERE ZATEN ACIKTIR","AMAC DISI KULLANIM",wxOK | wxICON_INFORMATION);



}

void home_frame::slotLeangBaslatici(wxCommandEvent &e){

   if(!settings_frame::pencereAcikMi){
   
      leang_frame *leang_frame_baslatici = new leang_frame("LEANG | Baslatici",LEANG_MENU_BASLATICI,this);
      leang_frame_baslatici->Show(true);
   }
   
   else 
   wxMessageBox("PENCERE ZATEN ACIKTIR","AMAC DISI KULLANIM",wxOK | wxICON_INFORMATION);



   

}

void home_frame::slotLeangKullaniciNotlari(wxCommandEvent &e){}
    
void home_frame::slotLeangKelimeSetleri(wxCommandEvent &e){

     if(!settings_frame::pencereAcikMi){
   
      leang_frame *leang_frame_kelimeSetleri = new leang_frame("LEANG | Kelime Setleri",LEANG_MENU_KELIME_SETLERI,this);
      leang_frame_kelimeSetleri->Show(true);
   }
   
   else 
   wxMessageBox("PENCERE ZATEN ACIKTIR","AMAC DISI KULLANIM",wxOK | wxICON_INFORMATION);
}

void home_frame::slotLeangKelimeSetleriDuzenleyici(wxCommandEvent &e){
    if(!settings_frame::pencereAcikMi){
   
      leang_frame *leang_frame_kelimeSetleriDuzenleyici = new leang_frame("LEANG | Kelime Setleri Duzenleyici",LEANG_MENU_KELIME_SETLERI_DUZENLEME,this);
      leang_frame_kelimeSetleriDuzenleyici->Show(true);
   }
   else 
   wxMessageBox("PENCERE ZATEN ACIKTIR","AMAC DISI KULLANIM",wxOK | wxICON_INFORMATION);
}


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
wxBEGIN_EVENT_TABLE(leang_frame,wxFrame)

   EVT_BUTTON(ID_SaveLeangBaslaticiButton,leang_frame::OnBaslaticiSaveButton)
   EVT_BUTTON(ID_LeangKelimeSetleriAddButton,leang_frame::OnAddButton)
   EVT_BUTTON(ID_LeangKelimeSetleriListButton,leang_frame::OnListButton)
   EVT_BUTTON(ID_LeangKelimeSetleriDuzenle_SetlerimiGoster,leang_frame::OnListed)
   EVT_BUTTON(ID_LeangKelimeSetleriDuzenle_setIcerigiGoruntule,leang_frame::OnSetiDuzenle)
//   EVT_BUTTON(ID_LeangKelimeSetleriDuzenle_setShownCount,leang_frame::OnSetRecordSayisi)
   EVT_BUTTON(ID_LeangKelimeSetleriDuzenle_addWords,leang_frame::OnAddWords)

   
   EVT_LISTBOX(ID_LeangKelimeSetleriDuzenle_wxListBoxSecilenSet,leang_frame::OnUserSelectWordSet)

   //EVT_TEXT_ENTER(ID_LeangKelimeSetleriDuzenle_setShownCount,leang_frame::OnTextCtrlCountShow)
   
wxEND_EVENT_TABLE()

//STATIC VAR DEFINE
int leang_frame::mem_secenekSayisi = 0;
int leang_frame::setSayisi = 0;
std::string leang_frame::secilenSetIsim = "_";
int leang_frame::kelimeSetiGridKayitSayisi = VARSAYILAN_KAYIT_SAYISI;



leang_frame::leang_frame(const wxString &tittle , int menuNO , home_frame *home) 
: wxFrame(nullptr,wxID_ANY,tittle,wxDefaultPosition) , home(home)
{  

   this->Bind(wxEVT_CLOSE_WINDOW,&leang_frame::OnSettingsClose,this);
   settings_frame::pencereAcikMi = true;
   
   if(menuNO == LEANG_MENU_KELIME_SETLERI_DUZENLEME || 
      menuNO == LEANG_MENU_KELIME_SETLERI_DUZENLEME_GET_DATABASE_TABLE){
      
      if(menuNO == LEANG_MENU_KELIME_SETLERI_DUZENLEME)
      SetMaxSize(wxSize(750,600));

      SetMinSize(wxSize(750,600));
   }
   else{
      SetMaxSize(wxSize(500,250));
      SetMinSize(wxSize(500,250));
   }
   this->CenterOnScreen();

   this->textCtrl_leangMenu_1 = 0;
   this->comboBox_leangMenu_1 = 0; 

   switch(menuNO){
      case LEANG_MENU_BASLATICI:{
         this->leang_frame_baslatici();
         break;
      }

      case LEANG_MENU_KELIME_SETLERI:{
         this->leang_frame_kelimeSetleri();
         break;
      }

      case LEANG_MENU_KELIME_SETLERI_DUZENLEME:{
         this->leang_frame_kelimeSetleriDuzenleyici();
         break;
      }
      
      case LEANG_MENU_KELIME_SETLERI_DUZENLEME_GET_DATABASE_TABLE:{
         //DATABASEDEN TABLOLAR BURADA CEKILMELIDIR
         this->leang_frame_kelimeSetleriDuzenleyici_setDuzenle();
         break;
      }

      case LEANG_MENU_KELIME_TABANI:{
         this->leang_frame_kelimeTabani();
         break;
      }

      default:{
         std::cout << "DEFAULT_LEANG_FRAME\n";
         break;
      }
   }
}//CONSTRUCTOR









void  leang_frame::OnSettingsClose(wxCloseEvent &e){
   settings_frame::pencereAcikMi = false;
   e.Skip();
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
/////////////////LEANG_FRAME_MENUSU_DEFINE_ISLEMLERI_BASLANGIC
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void leang_frame::leang_frame_kelimeTabani(){

/*
+textCtrl lazim tablo adini alacagiz
+buton lazim
+buton gridi ekranda baslatacak
+grid icin ek pencere olmayacak
*/


}


void leang_frame::leang_frame_baslatici(){
   wxString secenekler[] = {"2","3","4"};

   label_leangMenu_1 = new wxStaticText(this,wxID_ANY,"GOSTERILECEK SECENEK SAYISI : ",wxPoint(10,100),wxDefaultSize);
   comboBox_leangMenu_1 = new wxComboBox(this,wxID_ANY,"",wxPoint(250,100),wxSize(100,50),3,secenekler,wxCB_READONLY);

   label_leangMenu_2 = new wxStaticText(this,wxID_ANY,"GOSTERILECEK KELIME SAYISI : ",wxPoint(10,25),wxDefaultSize);
   textCtrl_leangMenu_1 = new wxTextCtrl(this,wxID_ANY,"",wxPoint(250,25),wxSize(50,25));
   
   comboBox_leangMenu_1->SetValue("4");
   textCtrl_leangMenu_1->SetValue("0");

   button_leangMenu_1 = new wxButton(this,ID_SaveLeangBaslaticiButton,"KAYDET",wxPoint(370,20),wxSize(100,170));
}

void leang_frame::leang_frame_kelimeSetleri(){
      wxString diller[] = {"English","Turkish","French","Spanish","Arabic","Chinese"};

      //ogrenilecek dil
      label_leangMenu_1 = new wxStaticText(this,wxID_ANY,"OGRENILECEK DIL : ",wxPoint(10,20),wxDefaultSize);
      comboBox_leangMenu_1 = new wxComboBox(this,wxID_ANY,"",wxPoint(150,20),wxSize(110,40),6,diller,wxCB_READONLY);
      comboBox_leangMenu_1->SetValue("English");

      //bilinen dil
      label_leangMenu_2 = new wxStaticText(this,wxID_ANY,"BILINEN DIL : ",wxPoint(10,80),wxDefaultSize);
      comboBox_leangMenu_2 = new wxComboBox(this,wxID_ANY,"",wxPoint(150,80),wxSize(110,40),6,diller,wxCB_READONLY);
      comboBox_leangMenu_2->SetValue("Turkish");   

      //kelimesetinin adi
      label_leangMenu_3 = new wxStaticText(this,wxID_ANY,"KELIME SETI ADI : ",wxPoint(10,140),wxDefaultSize);
      textCtrl_leangMenu_1 = new wxTextCtrl(this,wxID_ANY,"",wxPoint(150,140),wxSize(110,40));

      //girdileri saklamak icin butonun baglandigi eventte isleyecegiz olaylari
      button_leangMenu_1 = new wxButton(this,ID_LeangKelimeSetleriAddButton,"OLUSTUR",wxPoint(350,20),wxSize(100,50));  
      button_leangMenu_2 = new wxButton(this,ID_LeangKelimeSetleriListButton,"GUNCELLE",wxPoint(325,90),wxSize(150,50));
}


void leang_frame::leang_frame_kelimeSetleriDuzenleyici(){ //750x600
   std::cout << "leang_kelimeSetleriDuzenleyici baslatildi\n";

   listBox_SetIsimleriGUI =  new wxListBox(this, ID_LeangKelimeSetleriDuzenle_wxListBoxSecilenSet, wxPoint(15, 50), wxSize(200, 450));
   button_leangMenu_1 = new wxButton(this, ID_LeangKelimeSetleriDuzenle_SetlerimiGoster, "LISTELERIMI GOSTER", wxPoint(250, 50),wxDefaultSize);
   button_leangMenu_2 = new wxButton(this,ID_LeangKelimeSetleriDuzenle_setIcerigiGoruntule,"SETIN ICERIGI",wxPoint(450,50),wxDefaultSize);
   button_leangMenu_2->Enable(false);

   label_leangMenu_1 = new wxStaticText(this,wxID_ANY,"2.SUTUN DILI: ",wxPoint(250,150),wxDefaultSize);
   textCtrl_leangMenu_1 = new wxTextCtrl(this,wxID_ANY,"",wxPoint(380,150),wxSize(200,25));

   label_leangMenu_2 = new wxStaticText(this,wxID_ANY,"3.SUTUN DILI: ",wxPoint(250,220),wxDefaultSize);
   textCtrl_leangMenu_2 = new wxTextCtrl(this,wxID_ANY,"",wxPoint(380,220),wxSize(200,25));


   button_leangMenu_3 = new wxButton(this,ID_LeangKelimeSetleriDuzenle_addWords,"KELIME EKLE",wxPoint(250,260),wxDefaultSize);

}

   /*
      {
         {1,2,3,4},
         {5,6,7,8},
      }
   */
void leang_frame::leang_frame_kelimeSetleriDuzenleyici_setDuzenle(bool pencereAc){
   //sutun isimlerini db uzerinden cek
   database db("../databaseDIR/leang.db");
   database db_2("../databaseDIR/leang.db");
   

   std::vector<std::string> kolonAdlari = db.getColumnsName(secilenSetIsim);
   
   
   std::cout << "secilen tablo adi : " << leang_frame::secilenSetIsim << "\n";
   std::vector<std::vector<std::string>> vec_table_2D = db_2.loadGridWordSet(leang_frame::secilenSetIsim); 
   //TABLOYU OLUSTURACAK VEKTORLER BOS MU


   if(vec_table_2D.empty() || vec_table_2D[0].empty()){
      std::cerr << "gelen tablo bostur , kelime eklemeniz gerekmektedir\n";
      return;
   }
   
   
   //SATIR SUTUN SAYISI KONTROLU
   int satirSayisi = vec_table_2D.size(); //kelimeSetiGridKayitSayisi;
   int sutunSayisi = vec_table_2D[0].size();
      
   if(satirSayisi <= 0 && sutunSayisi <= 0){
      std::cerr << "HATALI SATIR VE SUTUN SAYISI : " << satirSayisi << "," << sutunSayisi << "\n";
      return;
   }



   //GRID OLUSTURULACAK SONRASINDA ISE LABELLAR YERLESTIRILECEK
      wxGrid_WordSetIcerik = new wxGrid(this,LEANG_MENU_KELIME_SETLERI_DUZENLEME_GET_DATABASE_TABLE,wxPoint(0,0),wxSize(400,300));
      wxGrid_WordSetIcerik->CreateGrid(satirSayisi,sutunSayisi);
   

   
   int j = 0;
   for(const auto &i : kolonAdlari){
      std::cout << "secilen kolon adlari ::: " << i << "\n";
      if(j == 3){
         wxGrid_WordSetIcerik->SetColLabelValue(j,"DOGRULAMA_COL");
         wxGrid_WordSetIcerik->SetColSize(j,600);
      }
      else
      wxGrid_WordSetIcerik->SetColLabelValue(j,i);
      if(j > 0)
      wxGrid_WordSetIcerik->SetColSize(j,150);
      j++;
   }
      
   for(int row = 0 ; row < satirSayisi ; row++){
      
      for(int col = 0 ; col < sutunSayisi ; col++){
         wxGrid_WordSetIcerik->SetCellValue(row,col,vec_table_2D[row][col]);
      }
   }
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
/////////////////LEANG_FRAME_MENUSU_DEFINE_ISLEMLERI_SON
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void leang_frame::OnAddWords(wxCommandEvent &e){
   database db("../databaseDIR/leang.db");
   database db_2("../databaseDIR/leang.db");
   

   std::cout << "on add words : interface leang motorundan cekmesi lazim\n";

   this->addWords_sutun2 = this->textCtrl_leangMenu_1->GetValue().ToStdString();
   this->addWords_sutun3 = this->textCtrl_leangMenu_2->GetValue().ToStdString();

   if(addWords_sutun2 == "" || addWords_sutun3 == ""){
      home_frame::logMessage("BOS METIN EKLEME","LUTFEN KELIMELERI GIRIN VE SONRA EKLEYIN");
      return;
   } 

   std::cout << "sutun2 eklenecek kelime : " << addWords_sutun2 << std::endl;
   std::cout << "sutun3 eklenecek kelime : " << addWords_sutun3 << std::endl;

   auto vecKolonAdlari = db_2.getColumnsName(secilenSetIsim);
   db.sendWord(addWords_sutun2,addWords_sutun3,vecKolonAdlari[1],vecKolonAdlari[2],secilenSetIsim);


}



/*
void leang_frame::OnSetRecordSayisi(wxCommandEvent &e){
   std::cout << "kayit sayisi alindi : ";
   std::string maxKayitGosterici = this->textCtrl_leangMenu_1->GetValue().ToStdString();
   leang_frame::kelimeSetiGridKayitSayisi = std::stoi(maxKayitGosterici);
   std::cout << kelimeSetiGridKayitSayisi << "\n";

}
*/

void leang_frame::OnSetiDuzenle(wxCommandEvent &e){
   std::cout << "duzenle buton leang_menu_duzenle\n";

   if(secilenSetIsim == "_"){
      home_frame::logMessage("KELIME SETI SECILMEDI !","LUTFEN ILK ONCE LISTE BUTONUNA TIKLAYARAK DUZENLENECEK KELIME SETINI SECIN");
      return;
   }
   else{
      lf_getDatabaseTable = new leang_frame("LEANG DUZENLEYICI | DUZENLE | KELIME SETI : "
      +secilenSetIsim,LEANG_MENU_KELIME_SETLERI_DUZENLEME_GET_DATABASE_TABLE,home);
      
      lf_getDatabaseTable->Show(true);
   }
   //this->wxGrid_WordSetIcerik->ClearGrid();
}

void leang_frame::OnUserSelectWordSet(wxCommandEvent &e){
   this->secilenSetIndex = listBox_SetIsimleriGUI->GetSelection(); 

   if(secilenSetIndex != wxNOT_FOUND){ //eger bir index secildiyse o indexteki stringi getir
      lf_getDatabaseTable->secilenSetIsim = listBox_SetIsimleriGUI->GetString(secilenSetIndex).ToStdString().c_str();
   }
   
   std::cout << "wxListBox Selected Str : "<< secilenSetIsim << " :: Selected Index : " << secilenSetIndex << "\n";
}

void leang_frame::OnListed(wxCommandEvent& event){ //max 8 set
    leang_frame::OnListButton(event);
    
    listBox_SetIsimleriGUI->Clear(); //eski verileri temizle
    
    int i = 0;
    for (const auto& kelime : this->kelimeSetiIsimleriVec) {
        if(i < 8)
        listBox_SetIsimleriGUI->Append(kelime);
        else login_frame::errMessage(3,"EN FAZLA 8 ADET KELIME SETI LISTELENIR");
      i++;
    }

}

void leang_frame::OnBaslaticiSaveButton(wxCommandEvent &e){
   std::string StrGosterilecekKelimeSayisi = textCtrl_leangMenu_1->GetValue().ToStdString();

   if(StrGosterilecekKelimeSayisi.empty()){
      login_frame::errMessage(3,"GOSTERILECEK KELIME SAYISI BOS BIRAKILAMAZ !");
      return;
   }
   if(StrGosterilecekKelimeSayisi.length() != 2 || StrGosterilecekKelimeSayisi[0] == '0'){
      login_frame::errMessage(3,"EN AZ 10 , EN FAZLA 99 KELIMEYE KADAR IZIN VARDIR");
      return;
   }

   std::string StrSecenekSayisi = comboBox_leangMenu_1->GetValue().ToStdString();
   
   this->mem_gosterilecekKelimeSayisi = std::stoi(StrGosterilecekKelimeSayisi);
   this->mem_secenekSayisi = std::stoi(StrSecenekSayisi);
   
   leangEngine::leang_baslatici_kelime_sayisi = this->mem_gosterilecekKelimeSayisi;
   leangEngine::leang_baslatici_secenek_sayisi = this->mem_secenekSayisi;

   std::cout << "LEANG_BASLATICI KAYIT EDILDI\n";

   std::cout << StrGosterilecekKelimeSayisi+"\n";
   std::cout << StrSecenekSayisi+"\n"; 

   std::cout <<"GOSTERILECEK KELIME_SAYISI : " << this->mem_gosterilecekKelimeSayisi << std::endl;
   std::cout <<"SECENEK_SAYISI             : " << this->mem_secenekSayisi << std::endl; 

   leangEngine::leangConfig("../leang.cfg");

   home->setEnabledDisabledButton(mem_secenekSayisi);
   wxMessageBox("BASLATICI AYARLARINIZ KAYDEDILDI !","KAYDEDILDI",wxOK | wxICON_INFORMATION);
}

void leang_frame::OnAddButton(wxCommandEvent &e){
   
   std::string ogrenilecekDil_CB = comboBox_leangMenu_1->GetValue().ToStdString();
   std::string bilinenDil_CB = comboBox_leangMenu_2->GetValue().ToStdString();
   std::string kelimeSetiAdi_TC = textCtrl_leangMenu_1->GetValue().ToStdString();

   if(kelimeSetiAdi_TC.empty()){
      login_frame::errMessage(3,"KELIME SETI ADI BOS OLAMAZ !");
      return;
   }

   std::cout << "KELIME SETI OLUSTURULDU !\n";
   std::cout << "OGRENILECEK DIL : " << ogrenilecekDil_CB << "\nBILINEN DIL : " << bilinenDil_CB << "\n"; 
   std::cout << "KELIME SETI ADI : " << kelimeSetiAdi_TC << "\n";

   //home frame penceresinden cekecegiz ismi


   std::cout << "MEVCUT KULLANICI : " << home->olusturucu_username << "\n";
   
   database db("../databaseDIR/leang.db");

   if(db.createTable(kelimeSetiAdi_TC,ogrenilecekDil_CB,bilinenDil_CB,home->olusturucu_username) == 1){
      //gorsel olarak eklenen seti goster
   }  

}

void leang_frame::OnListButton(wxCommandEvent &e){
   std::cout << "listeleme butonu\n";
   database db("../databaseDIR/leang.db");

   std::cout << "OLUSTURUCU USERNAME : " << home->olusturucu_username << "\n";
   this->kelimeSetiIsimleriVec = db.getListColumnsContainsUser(home->olusturucu_username);

   for(const auto &i : kelimeSetiIsimleriVec){
      std::cout << i << "\n"; 
   }
   this->setSayisi = kelimeSetiIsimleriVec.size();

}


