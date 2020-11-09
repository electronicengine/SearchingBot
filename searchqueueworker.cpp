#include <iostream>
#include "searchwindow.h"
#include "searchqueueworker.h"
#include "loging.h"




SearchQueueWorker::SearchQueueWorker(int QueueNumber, std::vector<QString> &Search, SearchWindow *ReturnObj) :
                    Queue_Number(QueueNumber), Search_(Search), Return_Object(ReturnObj){}



void SearchQueueWorker::run()
{

    Loging::printAll(Loging::white, "The worker: ", Queue_Number," is working ");
    Http_Request.makeRequest(Search_, Search_Result);

    Return_Object->searchResultCallBackFunction(Search_Result, Queue_Number);


}
