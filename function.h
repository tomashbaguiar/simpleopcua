#ifndef FUNCTION_H
    #define FUNCTION_H

    #include <open62541/plugin/log_stdout.h>
    #include <open62541/server.h>
    #include <open62541/client.h>
    #include <open62541/server_config_default.h>
    #include <open62541/client_config_default.h>

    UA_Boolean running = true;                                              // Variável global de execução do servidor.

    void signalHandler(int);                                                // Procedimento que recebe sinais de terminação.

#endif
