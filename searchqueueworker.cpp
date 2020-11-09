#include <iostream>
#include "searchwindow.h"
#include "searchqueueworker.h"




SearchQueueWorker::SearchQueueWorker(int QueueNumber, std::vector<QString> &Search, SearchWindow *ReturnObj) :
                    Queue_Number(QueueNumber), Search_(Search), Return_Object(ReturnObj){}



void SearchQueueWorker::run()
{

    std::cout << "The worker: " << Queue_Number << " is working " << std::endl;
    Http_Request.makeRequest(Search_, Search_Result);

    Return_Object->searchResultCallBackFunction(Search_Result);


}
