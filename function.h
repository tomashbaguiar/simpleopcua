#ifndef FUNCTION_H
    #define FUNCTION_H
  
    #include "open62541.h"

    static volatile UA_Boolean running = true;                              // Variável global de execução do servidor.

    //  Procedimentos auxiliares    //
    void signalHandler(int);                                                // Procedimento que recebe sinais de terminação.
    void changeName(char *);                                                // Procedimento que retira espaços de string.

    //  Procedimentos do servidor   //
    static void addVariable(UA_Server *, UA_Int32, char *, UA_Int32);       // Procedimento para adicionar variáveis ao servidor.
    static void writeVariable(UA_Server *, UA_Int32, char *, UA_Int32);     // Procedimento que escreve em uma variável do servidor.

#endif
