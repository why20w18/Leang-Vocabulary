#ifndef __WX_APP_HPP__
#define __WX_APP_HPP__

#include <string>

class leangEngine{
public:
    //default constructor
    leangEngine();
    int minSizeArr[2] = {750,750};
    static bool loginGuiActive;
    static bool leangGuiActive;


protected: //sadece home_frameden erisilecek kisimlar == PROGRAMIN ILERLEYEN KISMINDA INTERFACE OLACAK

    virtual void addWord(const std::string &dil_1 , const std::string &dil_2);
    virtual void getWord(const std::string &istenenDil);
    virtual int randomizeWord(int database_record_count);

private:
    void leangConfig(const std::string &configPath);

};





#endif 

/*
1-wx_gui uzerinden verileri alacak          wx_gui.hpp
2-alinan veriler leang moturuna gelecek     leang.hpp --> motor sadece kelimelerle alakali kisimlari db gonderir
3-kelimelerle alakali alinana veriler dogrudan leang uzerinden databaseye gonderilecek

4-wx_gui uzerinden kullanici tablosu ile ilgili islemler dogrudan database classa gonderilecek
*/