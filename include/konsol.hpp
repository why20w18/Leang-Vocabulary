#ifndef __KONSOL_HPP__
#define __KONSOL_HPP__

#include "leang.hpp"
#include "database.hpp"

class konsolInitalize{
public:
    konsolInitalize();
    int komutIsleme();
    bool getIsGuiActive();
    
private:
    //dogrulama durumu
    bool isGuiActive; 
    leangEngine *leangMotoru;
    database *konsolVeritabani;
};

#endif 