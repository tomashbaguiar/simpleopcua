#include "function.h"
#include "open62541.h"
#include <signal.h>


//  Procedimento para finalizar o servidor  //
void 
signalHandler(int signo)
{
    //  Verifica o tipo de sinal recebido   //
    if(signo == SIGINT)
        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "received ctrl-c");           //Mostra no log que foi recebido comando de fechamento.
        //fprintf(stderr, "Recebido ctrl-c\n");
    else if(signo == SIGTERM)
        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "received termination");      //Mostra no log que foi recebido comando de terminação.
        //fprintf(stderr, "Recebido SIGTERM\n");
    else
        return;                                                                         //Finaliza o procedimento sem fechamento.

    running = false;                                                                    //Coloca false na variável booleana de execução.
}
