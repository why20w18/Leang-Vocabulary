//database.hpp
#ifndef __DATABASE_HPP__
#define __DATABASE_HPP__

#include <sqlite3.h> //sqlite ile beraber tasinacak ilerleyen zamanda drive backup ekle
#include <string>

class database{
public:
    int databaseCount = 0;

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
    
    
    void addColumns(const std::string &columnsName);
    void sendWord(const std::string &dil_1 , const std::string &dil_2);
    void getWord(const std::string &istenenDil);
    int getRecordCount();


    //GETTER SETTERLAR
    std::string& getDatabasePath(){
        return databasePath;
    }

private:
    std::string databasePath;
    void databasePasswordCrypter();
};

#endif