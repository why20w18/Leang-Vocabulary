//database.cpp
#include "../include/database.hpp"
#include "../include/wx_gui.hpp"

database::database(const std::string &databasePath){
    this->currentUserID = -1;
    this->databasePath = databasePath;
    databaseBaglantiBaslat();
   // this->userWordSets = new char* [MAX_WORD_SET_SIZE];

}

database::~database(){
 //  if(count != 0)
 //   deleterWordSet();
}

/*
USER WORD SET
{
{"SET_1"},
{"SET_2"},
{"SET_3"},
}

*/
/*
void database::deleterWordSet(){
    for(int i = 0 ; i <= count ; i++){
        delete[] userWordSets[i];
    }
   
    delete[] userWordSets;
    userWordSets = nullptr;
}

void database::addUserWordSet(const char *kelimeSetiAdi) {
    if(count < MAX_WORD_SET_SIZE){
        userWordSets[count] = new char[strlen(kelimeSetiAdi) + 1];
        strcpy(userWordSets[count],kelimeSetiAdi);
        count++;
    }
    std::cout << "add_user_word_set finished\n";
}

int database::getCountSet(){
    return count;
}
*/


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
    std::string sqlSorgu = "SELECT COUNT (*) FROM "+kelimeSetiAd+";";
    sqlite3_stmt *stmt;
    if(sqlite3_prepare_v2(db,sqlSorgu.c_str(),-1,&stmt,nullptr) != SQLITE_OK){
        login_frame::errMessage(3,"prepare_v2");
        
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        
        return -1;
    }

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
                          "username_"+olusturanKullanici+" TEXT);"; //username_test : test kullanıcısı
                          //bu sutun adi sadece kontrol icin eklendi not null olmasina gerek yoktur
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

std::vector<std::string> database::getListColumnsContainsUser(const std::string &username) {
    std::vector<std::string> vec_TabloAdlari;

    const char *sqlFindAllTables = "SELECT name FROM sqlite_master WHERE type='table';";
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db,sqlFindAllTables,-1,&stmt,nullptr);

    while (sqlite3_step(stmt) == SQLITE_ROW){
        std::string tabloAdi = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
        std::string sqlGetColumns = "PRAGMA table_info ("+tabloAdi+");";
        
        sqlite3_stmt *pragma_stmt;
        sqlite3_prepare_v2(db, sqlGetColumns.c_str(), -1, &pragma_stmt, nullptr);

        while (sqlite3_step(pragma_stmt) == SQLITE_ROW){//SORGU YAZARKEN 1.INDEX VS. SORGUDAKI YAZIM SIRASIDIR
            std::string kolonAdi = reinterpret_cast<const char*>(sqlite3_column_text(pragma_stmt, 1));

            if (kolonAdi == "username_"+username){
                vec_TabloAdlari.push_back(tabloAdi);
                break;
            }
        }
        sqlite3_finalize(pragma_stmt);
    }

    sqlite3_finalize(stmt);
    return vec_TabloAdlari;
}

std::vector<std::vector<std::string>> database::loadGridWordSet(const std::string &tablo_adi){
    std::vector<std::vector<std::string>> vec2D_Tablo;
    std::cout << "DATABASE LOADGRIDWORDSET(&TABLO_ADI="+tablo_adi+")\n";
    //tablo adi bind edilemez
    std::string sqlSorgu = "SELECT * FROM "+tablo_adi+";"; 
    
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db,sqlSorgu.c_str(),-1,&stmt,nullptr);

    while(sqlite3_step(stmt) == SQLITE_ROW){
        std::vector<std::string> vec_satir;

        for(int col = 0 ; col < sqlite3_column_count(stmt) ; col++){
            const char *satirVerisi = reinterpret_cast<const char*>(sqlite3_column_text(stmt,col));
            vec_satir.push_back(satirVerisi ? satirVerisi : ""); //eger satir verisi bos ise "" at degilse kendisini gonder
        }
        vec2D_Tablo.push_back(vec_satir); //vec_satir tum kolonlardaki verileri tutar sonra vec2D_Tablo icine atar
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return vec2D_Tablo;
}


std::vector<std::string> database::getColumnsName(const std::string &tablo_adi){
    std::vector<std::string> vec_KolonAdlari;

    std::string sqlSorgu = "PRAGMA table_info("+tablo_adi+");";
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db,sqlSorgu.c_str(),-1,&stmt,nullptr);
    
    while(sqlite3_step(stmt) == SQLITE_ROW){
        //gelen sonuclardan 1.kolonu cekersek name
        const char *kolonAdi = reinterpret_cast<const char *>(sqlite3_column_text(stmt,1));
        vec_KolonAdlari.push_back(kolonAdi);
    }

    return vec_KolonAdlari;
}