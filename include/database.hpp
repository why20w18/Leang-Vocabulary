//database.hpp
#ifndef __DATABASE_HPP__
#define __DATABASE_HPP__

//https://www.sqlite.org/cintro.html
#include <sqlite3.h> //sqlite ile beraber tasinacak ilerleyen zamanda drive backup ekle
#include <string>
#include <vector>

#define MAX_WORD_SET_SIZE 10

class database{
public:
    //CONSTRUCTOR VE DESTRUCTORLAR
    database(const std::string &databasePath);
    ~database();

    //veritabani
    sqlite3 *db;

    void databaseBaglantiBaslat();


    //VERITABANI ISLEMLERI
    //eger login dogruysa geriye deger cevir
    int userLogin(const std::string &name , const std::string &password);
    
    
    int userRegister(const std::string &name , const std::string &password);
    int deleteRegister(const std::string &name , const std::string &password);
    
    int createTable(const std::string &tableName,const std::string &dil_1 , const std::string &dil_2,const std::string &olusturanKullanici);
    void addColumns(const std::string &columnsName);
    
    void sendWord(const std::string &dil_1 , const std::string &dil_2 ,const std::string &col1,const std::string &col2, const std::string &kelimeSetiAdi);
    void getWord(const std::string &istenenDil , const std::string &kelimeSetiAdi);
    int getRecordCount(const std::string &kelimesetiAdi);
    
    void getTableName(const std::string &kullanicininKelimeSetleri);

    int getUserID(std::string &username);
    std::string& getDatabasePath();
    int getDatabaseCount();
    
    std::vector<std::string> getListColumnsContainsUser(const std::string &username);

    //grid ile wxListBox secili tablolari birbirine bagla temel ozellikleri ekle
    std::vector<std::vector<std::string>> loadGridWordSet(const std::string &tablo_adi);
    void updateGridWordSet();

    std::vector<std::string> getColumnsName(const std::string &tablo_adi);



private:
    int currentUserID;
    int DatabaseCount;
    std::string databasePath;
    void databasePasswordCrypter();
};

#endif