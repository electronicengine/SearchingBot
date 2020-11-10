#include <iostream>
#include "searchwindow.h"
#include "searchqueueworker.h"
#include "loging.h"




SearchQueueWorker::SearchQueueWorker(int QueueNumber, std::vector<QStringList> &Search, SearchWindow *ReturnObj) :
                    Queue_Number(QueueNumber), Search_(Search), Return_Object(ReturnObj){}



void SearchQueueWorker::run()
{

    for(int i=0; i<Search_[1].size(); i++)   // as much as search prefix size
        Search_Result.push_back(QStringList());

    Loging::printAll(Loging::white, "The worker: ", Queue_Number," is working ");
    Search_Engine.searchRequest(Search_, Search_Result);

    Return_Object->searchResultCallBackFunction(Search_Result, Queue_Number);

}
