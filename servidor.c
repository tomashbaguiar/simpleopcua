#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "open62541.h"
#include "function.h"


int
main(int argc, char **argv)
{
    //  Verifica recebimento de sinais de fechamento //
    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);

    //  Cria o endpoint do servidor //
    

    return EXIT_SUCCESS;
}