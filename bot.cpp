#include "bot.h"
#include "loging.h"
#include <iostream>

Bot::Bot()
{
}




void Bot::searchPrefix(QString &Content, QString &Prefix, QStringList &ResultList)
{

    Founded_Words = &ResultList;
    parsePrefix(Prefix);

    if(Mode_ == variable_search)
        makeBeginPrefix(Content);
    else
        makeConstantSearch(Content);

}



int Bot::searchText(QString &Content, QStringList &Prefixes, QStringList &BanPrefix,
                     std::vector<QStringList> &ResultList)
{

    int res;

    if(Prefixes.size() <= 0) return -1;

    QString main_prefix = Prefixes[0];

    res = defineTextVariables(Prefixes);
    if(res < 0) return -1;

    Ban_Prefixes = BanPrefix;

    Current_Prefix_Number = 0;
    makeMainPrefixSearch(Content, main_prefix, ResultList[Current_Prefix_Number]);

    Current_Prefix_Number++;
    Loging::printAll(Loging::white, "Prefix Number: ", Prefixes.size());


    if((int)Prefixes.size() <= 1)
        return 0;

    for(int i=1; i<(int)Prefixes.size(); i++)
    {
        QString temp_prefix = Prefixes[i];
        if(temp_prefix.size() <= 2)
            return -1;


        for(int l=0; l < ResultList[0].size(); l++)
        {

            for(int k=0; k < i; k++)
            {
                temp_prefix.replace(Variable_Prefixes[k], ResultList[k].at(l));
                if(Current_Prefix_Number > k+1)
                    temp_prefix.replace(Variable_Prefixes[k+1], ResultList[k+1].at(l));
                else
                    temp_prefix.replace(Variable_Prefixes[k+1], "#");
            }

            Loging::printAll(Loging::red, "new_prefix: ", temp_prefix.toStdString());

            QString temp_content = Complete_Search_Texts.at(l);

            Prefix_Pieces.clear();
            searchPrefix(temp_content, temp_prefix, ResultList[Current_Prefix_Number]);

            Loging::printAll(Loging::white, "Size: ", ResultList[Current_Prefix_Number].size(), " "
                             ,l);

            if(ResultList[Current_Prefix_Number].size() < (l+1))
            {
                for(int m = 0; m <  (l+1) - ResultList[Current_Prefix_Number].size(); m++)
                {
                    ResultList[Current_Prefix_Number].push_back(QString(""));
                }
            }

            Loging::printAll(Loging::green, "newresult: ", ResultList[Current_Prefix_Number].at(l).toStdString());

            temp_prefix = Prefixes[i];

        }

        Loging::printAll(Loging::green, "new_search results: ");

        foreach (QString var, ResultList[Current_Prefix_Number]) {
            Loging::printAll(Loging::green, var.toStdString());
        }


        Current_Prefix_Number++;


    }

    return 0;
}



int Bot::parsePrefix(QString &Prefix)
{
    Loging::printAll(Loging::yellow, "parsePrefix");
    int invalid_prefix_index = 0;
    int valid_prefix_index = 0;
    int index = 0;

    if(Prefix.size() <= 2)
        return -1;

    //divide prefixes into an pair array to examine pieces
    while(1)
    {
        invalid_prefix_index = Prefix.indexOf('*');
        valid_prefix_index = Prefix.indexOf('#');

        if(valid_prefix_index >= 0 || invalid_prefix_index >= 0)
        {

            if(valid_prefix_index < invalid_prefix_index)
            {
                if(valid_prefix_index >= 0)
                    index = valid_prefix_index;
                else
                    index = invalid_prefix_index;
            }
            else if(invalid_prefix_index < valid_prefix_index)
            {
                if(invalid_prefix_index >= 0)
                    index = invalid_prefix_index;
                else
                    index = valid_prefix_index;
            }
            else
            {
                break;
            }

            Loging::printAll(Loging::yellow, "piece: " , Prefix.left(index).toStdString());
            if(index == valid_prefix_index)
            {
                Prefix_Pieces.push_back(std::make_pair(Prefix.left(index), '#'));
            }
            if(index == invalid_prefix_index)
            {
                if(index == 0) // if there is nothing before *
                {
                   Prefix_Pieces.push_back(std::make_pair(" ", '*'));
                }
                else
                {
                    Prefix_Pieces.push_back(std::make_pair(Prefix.left(index), '*'));
                }

            }

            Prefix = Prefix.mid(index + 1);

        }
        else
        {
            Prefix_Pieces.push_back(std::make_pair(Prefix, '-'));

            Loging::printAll(Loging::yellow, "last: " , Prefix.toStdString());
            break;
        }
    }

    Mode_ = constant_search;

    Loging::printAll(Loging::yellow, "Prefix Pieces:");

    for(int i=0; i<(int)Prefix_Pieces.size(); i++)
    {
        if(Prefix_Pieces[i].second == '#')
            Mode_ = variable_search;

        Loging::printAll(Loging::yellow, Prefix_Pieces[i].first.toStdString());

    }

    if(Mode_ == variable_search)
        Loging::printAll(Loging::magenta, "This search is variable_search");
    else
        Loging::printAll(Loging::magenta, "This search is constant_search");


    return 0;

}



int Bot::makeBeginPrefix(QString &Content)
{
    QString begin_prefix;
    int begin_prefix_index;
    int initial_search_index;

    while(1)
    {

        //search first prefix
        initial_search_index = Content.indexOf(Prefix_Pieces[0].first);
        if(initial_search_index < 0)
            return 0;

        for(int i=0; i< (int)Prefix_Pieces.size(); i++)
        {
            //create begin prefix until variable prefix
             if(Prefix_Pieces[i].second == '*')
             {
                 //to Do if there is noting before *

                 begin_prefix += Prefix_Pieces[i].first;
                 begin_prefix += findInvalidPrefixText(i, Content);


                //if next prefix is the variable, then include the known part of variable prefix to the begin prefix
                if(Prefix_Pieces[i + 1].second == '#')
                {

                    begin_prefix += Prefix_Pieces[i + 1].first;
                }
             }
             else if(Prefix_Pieces[i].second == '#')
             {
                if(i == 0) // if there is no * before #, include the first known prefix to the begin prefix
                {
                    if(Prefix_Pieces[0].first == "")
                        Prefix_Pieces[0].first = " ";

                    begin_prefix = Prefix_Pieces[0].first;

                }

                break;

             }
        }

        for(int i=0; i< (int)Prefix_Pieces.size(); i++)
        {
            Loging::printAll(Loging::cyan, "");
        }
        Loging::printAll(Loging::cyan, " ************************");
        Loging::printAll(Loging::cyan, "Begin Prefix: " , begin_prefix.toStdString());
        Loging::printAll(Loging::cyan, " ************************");
        Current_Search_Text = begin_prefix;

        //cut off content until known valid begin prefix
        begin_prefix_index = Content.indexOf(begin_prefix);
        Content = Content.mid(begin_prefix_index + begin_prefix.size());

        Loging::printAll(Loging::white, "Cont: " , Content.toStdString());

        //find the end prefix
        makeEndPrefix(Content);

        begin_prefix.clear();

    }

    return 0;
}



int Bot::makeEndPrefix(QString &Content)
{

    QString searched_text;
    QString end_prefix;
    int initial_search_index;

    //find the last piece of prefix
    initial_search_index = Content.indexOf(Prefix_Pieces[Prefix_Pieces.size() - 1].first); // last piece of prefix

    if(initial_search_index < 0)
        return 0;

    for(int i=Prefix_Pieces.size() - 1; i >= 0; i--)
    {

        //create end prefix until variable prefix with reverse of prefixes
         if(Prefix_Pieces[i].second == '*')
         {

             //if there is noting after *
             if(i == (int)Prefix_Pieces.size() - 1)
             {
                 Prefix_Pieces[i].first = " ";
                 end_prefix += " ";
                 Loging::printAll(Loging::yellow, "there is noting after *" , end_prefix.toStdString());

             }
             else
             {
                 end_prefix += Prefix_Pieces[i].first;
                 end_prefix += findInvalidPrefixText(i, Content);
             }


         }
         else if(Prefix_Pieces[i].second == '#')
         {
             if(i == (int)Prefix_Pieces.size() - 1) // if there is no * after #, include the last known prefix to the end prefix
             {
                 if(Prefix_Pieces[Prefix_Pieces.size() - 1].first == "")
                     Prefix_Pieces[Prefix_Pieces.size() - 1].first = " ";

                 end_prefix = Prefix_Pieces[Prefix_Pieces.size() - 1].first;

             }
             break;
         }
    }

    end_prefix += Prefix_Pieces[Prefix_Pieces.size() - 1].first;

    Loging::printAll(Loging::cyan, " -----------------------");
    Loging::printAll(Loging::cyan, "End Prefix: " , end_prefix.toStdString());
    Loging::printAll(Loging::cyan, " -----------------------");

    searched_text = Content.left(Content.indexOf(end_prefix));

    Current_Search_Text +=searched_text;
    Current_Search_Text += end_prefix;

    deleteBanPrefix(Current_Search_Text);

    if(Current_Prefix_Number == 0)
        Complete_Search_Texts.push_back(Current_Search_Text);


    if(!Ban_Prefixes.empty())
    {
        deleteBanPrefix(searched_text);
    }

    if(Mode_ == variable_search)
        Founded_Words->append(searched_text);
    else if(Mode_ == constant_search)
        Founded_Words->append(Complete_Search_Texts);


    return 0;
}



int Bot::deleteBanPrefix(QString &Content)
{

    for(int i = 0; i<(int)Ban_Prefixes.size(); i++)
    {

        int prefix_piece = Ban_Prefixes[i].indexOf("*");

        if(prefix_piece < 0)
        {
            QString prefix = Ban_Prefixes[i];

            int prefix_index = Content.indexOf(prefix);

            if(prefix_index > 0)
                Content = Content.replace(prefix, QString(""));

        }
        else
        {
            QStringList prefixes = Ban_Prefixes[i].split("*");

            if(prefixes.size() == 2)
            {
                QString begin_prefix = prefixes.at(0);
                QString end_prefix = prefixes.at(1);

                Loging::printAll(Loging::red,"Ban Prefix start: ",begin_prefix.toStdString(),
                                 " - Ban Prefix end: ", end_prefix.toStdString());
                printAll(Loging::red, "Dirty Content: ",Content.toStdString());

                int begin_index = Content.indexOf(begin_prefix);
                int end_index = Content.indexOf(end_prefix);

                if(end_index >= 0 && begin_index >= 0)
                {
                    printAll(Loging::red, "Begin Index: ", begin_index, " - End Index: ", end_index);
                    QString complete_ban_text = Content.left(end_index + end_prefix.size()).mid(begin_index);
                    printAll(Loging::red, "complete_ban_text", complete_ban_text.toStdString());

                    Content = Content.replace(complete_ban_text, QString(""));
                    printAll(Loging::red, "Cleared:Content: ",Content.toStdString());
                }
            }
        }

    }
    return 0;
}



int Bot::makeConstantSearch(QString &Content)
{

    if(Prefix_Pieces.size() <= 1)
        return -1;

    int longest_prefix_index = 0;
    int prefix_lenght = 0;
    Loging::printAll(Loging::magenta, "Prefix_Pieces;");
    QString begin_prefix = Prefix_Pieces[0].first;
    QString end_prefix = Prefix_Pieces[Prefix_Pieces.size() - 1].first;

    // find longest prefix
    for(int i=0; i< (int)Prefix_Pieces.size(); i++)
    {
        Loging::printAll(Loging::magenta, Prefix_Pieces[i].first.toStdString());

        if(prefix_lenght < Prefix_Pieces[i].first.size())
        {
            prefix_lenght = Prefix_Pieces[i].first.size();
            longest_prefix_index = i;
        }
    }

    Content.indexOf(Prefix_Pieces[longest_prefix_index].first);



}



QString Bot::findInvalidPrefixText(int Index, QString &Content)
{

    QString temp_search_end;
    QString search_end = Prefix_Pieces[Index+1].first;
    QString search_begin = Prefix_Pieces[Index].first;
    int search_end_index;
    int search_begin_index;

    while(1)
    {
        Loging::printAll(Loging::blue, "search begin: " , search_begin.toStdString());
        Loging::printAll(Loging::blue, "search end: " , search_end.toStdString());

        //find the next valid prefix pos
        search_end_index = Content.indexOf(search_end);

        if(search_end_index < 0)
            return QString("");

        //cut the content from end prefix
        temp_search_end = Content.left(search_end_index);
        Loging::printAll(Loging::white, "temp_search_end: " , temp_search_end.toStdString());

        //find the begin prefix in cutted content
        search_begin_index = temp_search_end.indexOf(search_begin);

        //if there is no begin prefix, then cut all off
        if(search_begin_index < 0)
        {
            Loging::printAll(Loging::yellow, "search_begin_index < 0!!! ");

            Content = Content.mid(search_end_index + search_end.size());
            continue;
        }

        // check if there is begin prefix witout end prefix
        int temp_index;

        do
        {
            temp_search_end = temp_search_end.mid(search_begin_index + search_begin.size());

            temp_index = temp_search_end.indexOf(search_begin);
            if(temp_index >= 0)
            {
                search_begin_index += temp_index + search_begin.size();

            }

        }while(temp_index >= 0);


        //extract valid prefix with begin and end prefix
//        search_end = temp_search_end.mid(search_begin_index + search_begin.size());
        Loging::printAll(Loging::white, "search_end: " , temp_search_end.toStdString());

        return temp_search_end;

    }

}



int Bot::defineTextVariables(QStringList Search_Prefixes)
{

    for(int i = 0; i< (int)Search_Prefixes.size(); i++)
    {
        QString temp_prefix = Search_Prefixes[i];

        for(int k = 0; k<9; k++)
        {
            int index = temp_prefix.indexOf("#");
            if(index < 0)
                break;

            if(QString("0123456789").indexOf(QString(temp_prefix[index + 1])) < 0)
            {
                Loging::printAll(Loging::red, "Invalid Prefix!");
                return -1;
            }

            bool exist = false;
            foreach(QString var, Variable_Prefixes)
            {
                if(QString("#" + temp_prefix[index + 1]) == var)
                    exist = true;
            }

            if(exist == false)
                Variable_Prefixes.push_back("#" + temp_prefix[index + 1]);

            temp_prefix = temp_prefix.mid(QString(temp_prefix[index + 1]).toInt()+1);

        }
    }


    Loging::printAll(Loging::green, "Variables; ");

    foreach (QString var, Variable_Prefixes)
    {
        Loging::printAll(Loging::green, var.toStdString() );

    }

    return 0;
}



void Bot::makeMainPrefixSearch(QString &Content, QString &Main_Prefix,QStringList &ResultList)
{
    if(Main_Prefix.indexOf("#") < 0)
        Mode_ = constant_search;
    else
        Main_Prefix.replace(Variable_Prefixes[0], "#");

    Loging::printAll(Loging::yellow, "Main Prefix: " , Main_Prefix.toStdString());
    Loging::printAll(Loging::green, "Content : " , Content.toStdString());

    searchPrefix(Content, Main_Prefix, ResultList);

    Loging::printAll(Loging::green, "ResultList : " );

    foreach (QString var, ResultList) {Loging::printAll(Loging::green, var.toStdString());}

    Loging::printAll(Loging::green, "\nComplete_Search_Texts : ");

    foreach (QString var, Complete_Search_Texts){Loging::printAll(Loging::green, var.toStdString());}



}
