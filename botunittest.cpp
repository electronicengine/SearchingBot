#include "botunittest.h"
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <loging.h>


BotUnitTest::BotUnitTest()
{

    Search_Prefixes.push_back("<a href=\"/diseases-conditions*syc*>#1</a>");
    Search_Prefixes.push_back("<a href=\"#2>#1</a>");
    Search_Prefixes.push_back("<a#3=\"#2>#1</a>");


    Ban_List.push_back("<span*</span>");

    Test_Content.push_back(readInputTest());

    Result_List.push_back(QStringList());
    Result_List.push_back(QStringList());
    Result_List.push_back(QStringList());

    QString content = Test_Content.at(0);

    Bot_.searchText(content, Search_Prefixes, Ban_List, Result_List);

    Loging::printAll(Loging::magenta, "Total Result Table: ");

    for(int i=0; Result_List[0].size(); i++)
    {

            Loging::printAll(Loging::magenta, Result_List[0].at(i).toStdString(), "\t\t",
                    Result_List[1].at(i).toStdString(),"\t\t",
                    Result_List[2].at(i).toStdString());

    }



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
