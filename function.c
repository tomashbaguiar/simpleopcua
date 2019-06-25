#include "function.h"
#include "open62541.h"

//  Variável globais   //
UA_Boolean running = true;

//  Procedimento para finalizar o servidor  //
void 
signalHandler(int sig)
{
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "received ctrl-c");               //Mostra no log que foi recebido comando de fechamento.
    running = false;                                                                    //Coloca false na variável booleana de execução.
}