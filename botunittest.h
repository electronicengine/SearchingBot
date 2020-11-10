#ifndef BOTUNITTEST_H
#define BOTUNITTEST_H


#include "bot.h"

class BotUnitTest
{

    Bot Bot_;

    QString readInputTest();

public:
    BotUnitTest();



    QStringList Search_Prefixes;
    QStringList Ban_List;
    QStringList Test_Content;
    std::vector<QStringList> Result_List;

};

#endif // BOTUNITTEST_H
