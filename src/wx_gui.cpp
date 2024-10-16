//wx_gui.cpp
#include "../include/wx_gui.hpp"
#include "../include/leang.hpp"
#include "../include/database.hpp"

//STATIC DEFINE
int login_frame::isLoginButtonDatabaseConnection = 0;


enum ID_ENUM_LOGIN{
   ID_LoginSumbit = 1,
   ID_RegisterSumbit
};

//EVENT TABLE MAKROLARI - bunun yerine dinamik bind kullanilabilirdi
wxBEGIN_EVENT_TABLE(login_frame,wxFrame)
   EVT_BUTTON(ID_LoginSumbit,login_frame::OnLoginSumbitButton) //func adres
   EVT_BUTTON(ID_RegisterSumbit,login_frame::OnRegisterSumbitButton) 
   
wxEND_EVENT_TABLE()


login_frame::login_frame(const wxString &tittle ,leangEngine &leTransfer) 
: wxFrame(nullptr,wxID_ANY,tittle,wxDefaultPosition)
{  
   this->mevcutPencereTittle = tittle;

   //CONFIG KONSOL INFO
   std::cout << "MIN_SIZE=" << leTransfer.minSizeArr[0] << "," << leTransfer.minSizeArr[1] << std::endl; 
   SetMinSize(wxSize(leTransfer.minSizeArr[0],leTransfer.minSizeArr[1]));     

   std::string cfgDurum = (leTransfer.loginGuiActive == 1) ? "TRUE" : "FALSE";  
   std::cout << "GUI_ACTIVE=" << cfgDurum << std::endl; 

   //GUI ISLEMLERI
   wxPanel *panel = new wxPanel(this,wxID_ANY);
   //LOGIN KISMI
   //-->label(wxstatictext)
   //-->textctrl
   
   //KULLANICI_ADI
   wxStaticText *label_username = new wxStaticText(panel,wxID_ANY,"KULLANICI ADI:",wxPoint(18,85));
   userName = new wxTextCtrl(panel,wxID_ANY,"",wxPoint(135,75),wxSize(200,40));
   //genislik = 134...311 = 177
   //yukseklik = 112..72  = 40

   wxStaticText *label_pass = new wxStaticText(panel,wxID_ANY,"PAROLA :",wxPoint(18,183));
   userPassword = new wxTextCtrl(panel,wxID_ANY,"",wxPoint(135,175),wxSize(200,40),wxTE_PASSWORD);

   buttonGiris = new wxButton(panel,ID_LoginSumbit,"Login",wxPoint(120,281),wxSize(134,36));
   //108,281 = x,y
   //h:317..281 = 36 
   //w:108..242 = 134

   buttonRegister = new wxButton(panel,ID_RegisterSumbit,"Register",wxPoint(146,320),wxSize(80,25));
}

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

enum ID_ENUM_HOME{
    ID_SETTINGS_OZELLESTIRME = 11,
    ID_SETTINGS_BILDIRIM,
    ID_SETTINGS_PROGRAMDILI,
    ID_SETTINGS_PROFIL,

    ID_SUPPORT_GITHUB,
    
    ID_LEANG_KELIMETABANI,
    ID_LEANG_ISTEKDIL,
    ID_LEANG_KULLANICINOTLARI,
    ID_LEANG_KELIMESETLERI,
    ID_LEANG_EXPORT,
    ID_LEANG_IMPORT
};

wxBEGIN_EVENT_TABLE(home_frame,wxFrame)
   //EVT_MENU()
wxEND_EVENT_TABLE()

home_frame::home_frame(const wxString &title) : wxFrame(nullptr,wxID_ANY,title,wxDefaultPosition)
{  
   std::cout << "HOME PENCERESI BASLATILDI !\n"; 
   SetMinSize(wxSize(750,500));
   SetMaxSize(wxSize(1000,750));

   //ayri bir dosyada program icinde gecen metinlerin ingilizcesi ve almancasi yer alacak menu metinleri
   //istek dile gore oradan cekilecek 3.parametre olarak simdilik statik olarak ayarlandi
   
   //gui elemanlarini nesne ile beraber baslatma
   menuSettings = new wxMenu;
   menuSupport = new wxMenu;
   menuLeang = new wxMenu;

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

   menuLeang->Append(ID_LEANG_ISTEKDIL,"&Istek Diller","uzerine calismak istediginiz dilleri ekleyin");
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

}


