#include "function.h"
#include "open62541.h"
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void 
signalHandler(int signo)
{
    //  Verifica o tipo de sinal recebido   //
    if(signo == SIGINT)
        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "\nreceived ctrl-c");         //Mostra no log que foi recebido comando de fechamento.
    else if(signo == SIGTERM)
        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "\nreceived termination");    //Mostra no log que foi recebido comando de terminação.
    else
        return;                                                                         //Finaliza o procedimento sem fechamento.

    running = false;                                                                    //Coloca false na variável booleana de execução.
}

void
changeName(char *name)
{
    //  Retira espaços  //
    char *aux = malloc(strlen(name) * sizeof(char));
    for(int i = 0; i < strlen(name); i++)
        (name[i] == ' ') ? aux[i] = '.' : aux[i] = name[i];                             // Verifica existência de espaços e os substitui.
    
    free(name);
    name = aux;
    aux = NULL;
}

static void 
addVariable(UA_Server *server, UA_Int32 myInteger, char *name, int qtdVar)
{
    //  Define os atributos do nó   //
    UA_VariableAttributes attr = UA_VariableAttributes_default;                         // Atributos padrão.
    //UA_Int32 myInteger = ;
    UA_Variant_setScalar(&attr.value, &myInteger, &UA_TYPES[UA_TYPES_INT32]);           // Atribui ao variante um escalar.
    attr.displayName = UA_LOCALIZEDTEXT("pt-BR", name);                                 // Identificador do nó.
    attr.description = UA_LOCALIZEDTEXT("pt-BR", name);                                 // Descrição do nó.
    attr.dataType = UA_TYPES[UA_TYPES_INT32].typeId;
    attr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;

    //  Define ondeo nó será adicionado e seu nome de descobrimento //
    changeName(name);                                                                   // Modifica a descrição.
    UA_NodeId newNodeId = UA_NODEID_STRING((qtdVar + 1), name);
    UA_QualifiedName browseName = UA_QUALIFIEDNAME((qtdVar + 1), name);
    UA_NodeId parentNodeId = UA_NODEID_NUMERIC(qtdVar, UA_NS0ID_OBJECTSFOLDER);
    UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);
    UA_NodeId variableType = UA_NODEID_NULL;                                            // Recebe o tipo padrão.

    //  Adiciona o nó   //
    UA_Server_addVariableNode(server, newNodeId, parentNodeId, parentReferenceNodeId,
                              browseName, variableType, attr, NULL, NULL);
}

static void
writeVariable(UA_Server *server, UA_Int32 myInteger, char *name, UA_Int32 qtdVar)
{
    UA_NodeId myIntegerNodeId = UA_NODEID_STRING(qtdVar, name);

    //  Escreve um inteiro diferente na variável    //
    UA_Int32 newInteger = myInteger + 1;
    UA_Variant myVar;
    UA_Variant_init(&myVar);
    UA_Variant_setScalar(&myVar, &newInteger, &UA_TYPES[UA_TYPES_INT32]);
    UA_Server_writeValue(server, myIntegerNodeId, myVar);

    //  Define os valores da variável   //
    UA_WriteValue wv;
    UA_WriteValue_init(&wv);
    wv.nodeId = myIntegerNodeId;
    wv.attributeId = UA_ATTRIBUTEID_VALUE;
    ((qtd % 2) == 0) ? wv.value.status = UA_STATUSCODE_GOOD : wv.value.status = UA_STATUSCODE_BADNOTCONNECTED;
    wv.value.hasStatus = true;
    UA_Server_write(server, &wv);
}