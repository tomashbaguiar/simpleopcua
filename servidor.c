#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

//#include "function.h"
#include "open62541.h"

UA_Boolean running = true;                                              // Variável global de execução do servidor.

void signalHandler(int);                                                // Procedimento que recebe sinais de terminação.

int
main(int argc, char **argv)
{
    //  Verifica recebimento de sinais de fechamento //
    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);

    //  Cria o endpoint do servidor //
    UA_ServerConfig *config = UA_ServerConfig_new_default();                        // Cria o padrão de configuração do endpoint.
    UA_Server *server = UA_Server_new(config);                                      // Cria o endpoint.
    //UA_ServerConfig_setDefault(UA_Server_getConfig(server));                        // Determina configurações padrões (porta 4840).

    //  Adiciona um nó de variável  //
    //  Define os atributos do nó   //
    UA_VariableAttributes attr = UA_VariableAttributes_default;                     // Atributos padrão.
    attr.displayName = UA_LOCALIZEDTEXT("pt-BR", "resposta");                       // Identificador do nó.
    UA_Int32 myInteger = 42;
    //int retval;
    UA_Variant_setScalar(&attr.value, &myInteger, &UA_TYPES[UA_TYPES_INT32]);       // Atribui ao variante um escalar.
    //  Define ondeo nó será adicionado e seu nome de descobrimento //
    UA_NodeId newNodeId = UA_NODEID_STRING(1, "response");
    UA_NodeId parentNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);
    UA_NodeId variableType = UA_NODEID_NULL;                                        // Recebe o tipo padrão.
    UA_QualifiedName browseName = UA_QUALIFIEDNAME(1, "resposta");
    //  Adiciona o nó   //
    UA_Server_addVariableNode(server, newNodeId, parentNodeId, parentReferenceNodeId,
                                browseName, variableType, attr, NULL, NULL);

    //  Executa o loop do servidor  //
    //UA_StatusCode status = UA_Server_run(server, &running);
    UA_Server_run(server, &running);

    //  Encerra o servidor  //
    UA_Server_delete(server);

    return EXIT_SUCCESS;
}

//  Procedimento para finalizar o servidor  //
void 
signalHandler(int signo)
{
    //  Verifica o tipo de sinal recebido   //
    if(signo == SIGINT)
        //UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "received ctrl-c");           //Mostra no log que foi recebido comando de fechamento.
        fprintf(stderr, "Recebido ctrl-c\n");
    else if(signo == SIGTERM)
        //UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "received termination");      //Mostra no log que foi recebido comando de terminação.
        fprintf(stderr, "Recebido SIGTERM\n");
    else
        return;                                                                         //Finaliza o procedimento sem fechamento.

    running = false;                                                                    //Coloca false na variável booleana de execução.
}
