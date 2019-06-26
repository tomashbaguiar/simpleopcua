#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "open62541.h"

//#include <open62541/client.h>
//#include <open62541/client_config_default.h>

int
main(int argc, char **argv)
{
    //  Cria o endpoint do cliente  //
    UA_Client *client = UA_Client_new(UA_ClientConfig_default);
    //UA_ClientConfig_setDefault(UA_Client_getConfig(client));                            // Cria o cliente com configurações padrão.
    UA_StatusCode status = UA_Client_connect(client, "opc.tcp://localhost:4840");       // Conecta-se ao servidor opc local.
    if(status != UA_STATUSCODE_GOOD)                                                    // Verifica sucesso/qualidade na conexão.
    {
        UA_Client_delete(client);                                                       // Caso contrário finaliza o endpoint.
        fprintf(stderr, "UA_Client_connect: %d.\n", status);
        return EXIT_FAILURE;
    }

    //  Lê os valores de atributo do nó (recebe do servidor)    //
    UA_Variant value;
    UA_Variant_init(&value);                                                            // Inicializa a variável de recebimento.
    status = UA_Client_readValueAttribute(client, UA_NODEID_STRING(1, "response"), &value);
    if((status == UA_STATUSCODE_GOOD) && 
       UA_Variant_hasScalarType(&value, &UA_TYPES[UA_TYPES_INT32]))
        fprintf(stdout, "O valor é: %i.\n", *(UA_Int32 *) value.data);

    //  Finaliza o endpoint e a variável    //
    UA_Variant_deleteMembers(&value);
    UA_Client_delete(client);

    return EXIT_SUCCESS;
}
