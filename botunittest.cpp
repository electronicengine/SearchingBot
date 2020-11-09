#include "botunittest.h"
#include <QFile>
#include <QTextStream>



BotUnitTest::BotUnitTest()
{


    Search_Prefixes.push_back("<a href=\"/diseases-conditions*syc*>#1</a>");
    Search_Prefixes.push_back("<a href=\"#2>#1</a>");
    Search_Prefixes.push_back("<a#3=\"#2>#1</a>");


    Ban_List.push_back("<span*</span>");

    Test_Content.push_back(readInputTest());

    Result_List.push_back(QStringList());
    Result_List.push_back(QStringList());

    Bot_.searchText(Test_Content.at(0), Search_Prefixes, Ban_List, Result_List);

}



QString BotUnitTest::readInputTest()
{
    QFile inputFile("test");
    QString test_input;

    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
          test_input.append(in.readLine());
       }
       inputFile.close();
    }

    return test_input;

}
