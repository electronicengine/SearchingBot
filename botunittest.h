#ifndef BOTUNITTEST_H
#define BOTUNITTEST_H


#include "bot.h"

class BotUnitTest
{

    Bot Bot_;

    QString readInputTest();

public:
    BotUnitTest();



    std::vector<QString> Search_Prefixes;
    std::vector<QString> Ban_List;
    std::vector<QString> Test_Content;
    std::vector<QStringList> Result_List;

};

#endif // BOTUNITTEST_H
