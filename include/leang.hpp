#ifndef __WX_APP_HPP__
#define __WX_APP_HPP__

#include <string>

class leangEngine{
public:
    static int minSizeArr[2];
    static bool loginGuiActive;
    static bool leangGuiActive;
    static void leangConfig(const std::string &configPath);


protected: //INTERFACE VE STATIC DECLARATION

    virtual void addWord(const std::string &dil_1 , 
                         const std::string &dil_2 ,
                         const std::string &kelime1 ,
                         const std::string &kelime1_anlam,
                         int kelimesetiID) = 0;
    
    virtual void getWord(const std::string &istenenDil , int istenenRecord , int kelimesetiID) = 0;
    
    virtual int randomizeID(const std::string &kelimeSetiAdi) = 0;
 //   virtual std::string& getRandomWord() = 0;
};
#endif 

/*
1-wx_gui uzerinden verileri alacak          wx_gui.hpp
2-alinan veriler leang moturuna gelecek     leang.hpp --> motor sadece kelimelerle alakali kisimlari db gonderir
3-kelimelerle alakali alinana veriler dogrudan leang uzerinden databaseye gonderilecek

4-wx_gui uzerinden kullanici tablosu ile ilgili islemler dogrudan database classa gonderilecek
*/