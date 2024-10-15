//database.cpp
#include "../include/database.hpp"
#include "../include/wx_gui.hpp"


database::database(const std::string &databasePath){
    this->databasePath = databasePath;
    databaseBaglantiBaslat();
}

database::~database(){
    
}

void database::databaseBaglantiBaslat(){
    int db_status = sqlite3_open(databasePath.c_str(),&db);
    if(db_status){
        login_frame::errMessage(3,"db_status");
        return;
    }
    std::cout << "VERITABANI BASLATILDI\n";
}

int database::userLogin(const std::string &name , const std::string &password){
    //databaseBaglantiBaslat();
    if(db == nullptr){
        login_frame::errMessage(3,"db nullptr");
        return -1;
    }

    //sorguyu olusturduk
    const char *sqlSorgu = "SELECT * FROM users WHERE name = ? AND password = ?;";
    //const char *sqlSorgu = "SELECT * FROM users WHERE name = '" + name + "' AND password = '" + password + "';";

    //stmt bos pointerini olustur bu nesne ile baglama yapacagiz
    sqlite3_stmt *stmt;


    //bos nesneyi prepare et ve geri donus degerini tut 
    //BASARILIYSA 0 CEVIRIR
    
    if(sqlite3_prepare_v2(db,sqlSorgu,-1,&stmt,nullptr) != SQLITE_OK){
        login_frame::errMessage(3,"prepare_v2");
        sqlite3_close(db);
        return -1;
    }

    //nesne hazirlandiktan sonra sorgumuz ile sorgudaki bosluklari bind et
    
    //name kisminin bind edilmesi
    sqlite3_bind_text(stmt,1,name.c_str(),-1,SQLITE_STATIC);
    
    //password bind edilmesi sql injectiona karsi savunmasiz sorgudan dolayi
    sqlite3_bind_text(stmt,2,password.c_str(),-1,SQLITE_STATIC);

    //exec ile degil adim adim calistiracagiz
    if(sqlite3_step(stmt) == SQLITE_ROW){
        const char *backName = reinterpret_cast<const char *>(sqlite3_column_text(stmt,1));
        const char *backPass = reinterpret_cast<const char *>(sqlite3_column_text(stmt,2));
        
        std::cout << "backName : " << backName << std::endl;
        std::cout << "backPass : " << backPass << std::endl;
        return true;
    }

    return false;
}