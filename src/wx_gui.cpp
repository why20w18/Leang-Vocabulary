//wx_gui.cpp
#include "../include/wx_gui.hpp"
#include "../include/leang.hpp"
#include "../include/database.hpp"

//STATIC DEFINE
int login_frame::isLoginButtonDatabaseConnection = 0;


enum ID_ENUM_LEANG{
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

   buttonRegister = new wxButton(panel,ID_RegisterSumbit,"Register",wxPoint(150,350),wxSize(67,18));
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

         home_frame *mainMenu = new home_frame("LEANG | HOME");
         mainMenu->Show(true);

    } 
    else {
        errMessage(1, "KAYITSIZ KULLANICI !");
         isLoginButtonDatabaseConnection = 0;
    }
}

void login_frame::OnRegisterSumbitButton(wxCommandEvent &e){

      std::cout << "register" << std::endl;   
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

/////////////////////////////////////////////HOME_FRAME_CLASS///////////////////////////////////////////////////


home_frame::home_frame(const wxString &title) : wxFrame(nullptr,wxID_ANY,title,wxDefaultPosition)
{  
   std::cout << "HOME PENCERESI BASLATILDI !\n"; 
   SetMinSize(wxSize(750,500));
   SetMaxSize(wxSize(1000,750));
}


