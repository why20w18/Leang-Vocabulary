//database.cpp
#include "../include/database.hpp"
#include "../include/wx_gui.hpp"

database::database(const std::string &databasePath){
    this->currentUserID = -1;
    this->databasePath = databasePath;
    databaseBaglantiBaslat();
}

database::~database(){
    
}



void database::databaseBaglantiBaslat(){
    this->DatabaseCount = 0;
    int db_status = sqlite3_open(databasePath.c_str(),&db);
    if(db_status){
        login_frame::errMessage(3,"db_status");
        return;
    }
    std::cout << "VERITABANI BASLATILDI\n";
}

std::string& database::getDatabasePath(){
        return this->databasePath;
}

int database::getDatabaseCount(){
    return this->DatabaseCount;
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
        
        sqlite3_finalize(stmt);
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
        
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        
        return 1;
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    
    return 0;
}




int database::userRegister(const std::string &name , const std::string &password){
    //sql sorgusu
    //stmt nesnesi
    //prepare
    //sorgu bind
    //step step isle

    if(db == nullptr){
        login_frame::errMessage(3,"db nullptr");
        return -1;
    }

    const char *sqlSorgu = "INSERT INTO users (name,password) VALUES (?,?);";

    sqlite3_stmt *stmt;

    if(sqlite3_prepare_v2(db,sqlSorgu,-1,&stmt,nullptr) != SQLITE_OK){
        login_frame::errMessage(3,"prepare_v2");
        
        sqlite3_finalize(stmt);
        sqlite3_close(db);
    
        return -1;
    }

    //bind
    sqlite3_bind_text(stmt,1,name.c_str(),-1,SQLITE_STATIC);
    sqlite3_bind_text(stmt,2,password.c_str(),-1,SQLITE_STATIC);

    //run
    //DONE 101 DEFINE , if STEP IS SUCCESFUL
    if(sqlite3_step(stmt) == SQLITE_DONE){
    
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 1;
    }
    
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    
    return 0;
}


//statiklestirilecek ilerleyen zamanda
int database::getRecordCount(const std::string &kelimeSetiAd){
    const char *sqlSorgu = "SELECT COUNT (*) FROM ?;";
    sqlite3_stmt *stmt;
    if(sqlite3_prepare_v2(db,sqlSorgu,-1,&stmt,nullptr) != SQLITE_OK){
        login_frame::errMessage(3,"prepare_v2");
        
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        
        return -1;
    }

    sqlite3_bind_text(stmt,1,kelimeSetiAd.c_str(),-1,SQLITE_STATIC);

    if(sqlite3_step(stmt) == SQLITE_ROW){
        this->DatabaseCount = sqlite3_column_int(stmt,0);
        return this->DatabaseCount;
    }
    
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return -1;
}

//PARAMETRELER : 1-TABLO_ADI,2-OGRENILECEK_DIL,3-BILINEN_DIL
int database::createTable(const std::string &tableName,const std::string &dil_1 , 
                          const std::string &dil_2,const std::string &olusturanKullanici)
{
 
   //tabloya ayni degerler eklenebilsin ki bir kelimenin birden fazla manasi eklensin
   std::string sqlSorgu = "CREATE TABLE "+tableName+" ("+
                          "id INTEGER PRIMARY KEY AUTOINCREMENT, "+
                          dil_1+" TEXT NOT NULL, "+
                          dil_2+" TEXT NOT NULL, "+
                          "username_"+olusturanKullanici+" TEXT NOT NULL);"; //username_test : test kullanıcısı
    sqlite3_stmt *stmt;
    
    if(sqlite3_prepare_v2(db,sqlSorgu.c_str(),-1,&stmt,nullptr) != SQLITE_OK){
        login_frame::errMessage(3,"prepare_v2");
        sqlite3_finalize(stmt);
        sqlite3_close(db);

        return -1;
    }

    if(sqlite3_step(stmt) == SQLITE_DONE){
        home_frame::logMessage("YENI KELIME SETI EKLENDI",tableName+" KELIME SETI BASARIYLA OLUSTURULDU !");
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 1;
    }

    login_frame::errMessage(3,"KELIME SETI OLUSTURULAMADI !");
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}

int database::getUserID(std::string &username){
    const char *sqlSorgu = "SELECT id FROM users WHERE username = ?;";

    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db,sqlSorgu,-1,&stmt,nullptr);
    sqlite3_bind_text(stmt,1,username.c_str(),-1,SQLITE_STATIC);

    
    if(sqlite3_step(stmt) == SQLITE_ROW){
            this->currentUserID = sqlite3_column_int(stmt,0);
        if(currentUserID == -1){
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return -1;
        }
    }
    
    return currentUserID;
}

