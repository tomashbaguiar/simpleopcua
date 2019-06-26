#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

#include "function.h"
#include "open62541.h"

int
main(int argc, char **argv)
{
    //  Verifica a quantidade de nós a serem criados    //
    if(argc != 2)
    {
        fprintf(stderr, "Invalid number of arguments.\n");
        fprintf(stdout, "Usage:\t./servidor <num_of_nodes>\n");
        return EXIT_FAILURE;
    }
    int num_var = atoi(argv[1]);                                                    // Recebe a quantidade.

    //  Verifica recebimento de sinais de fechamento //
    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);

    //  Cria o endpoint do servidor //
    UA_ServerConfig *config = UA_ServerConfig_new_default();                        // Cria o padrão de configuração do endpoint.
    UA_Server *server = UA_Server_new(config);                                      // Cria o endpoint.

    //  Adiciona nós de variáveis  //
    int qtdVar = 0;
    char *name = malloc(10 * sizeof(char));
    for(int i = 1; i <= num_var; i++)
    {
        sprintf(name, "proVar %d", i);
        addVariable(server, (UA_Int32) i, name, (UA_Int32) ++qtdVar);               // Adiciona nós.
        //free(name);
		clearName(name);
    }

    //  Escreve nos nós //
    for(int i = 0; i <= num_var; i++)
    {
        sprintf(name, "proVar %d", i);
        writeVariable(server, (UA_Int32)i, name, (UA_Int32)qtdVar);                 // Escreve nos nós.
		memset(name, 0, strlen(name) * sizeof(char));
    }

    //  Executa o loop do servidor  //
    UA_StatusCode status = UA_Server_run(server, &running);
    if(status != UA_STATUSCODE_GOOD)
        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "Impossible to run server.");//Mostra no log erro na execução.

    //  Encerra o servidor  //
    UA_Server_delete(server);

    return (status == UA_STATUSCODE_GOOD) ? EXIT_SUCCESS : EXIT_FAILURE;
}
