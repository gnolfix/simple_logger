//
// Created by gnolfix on 9/17/2025.
//

#include <iostream>
#include "Logger.h"
#include "LoggerError.h"

#define TEST( passed ) ( ( passed ) ? "PASSED" : "FAILED" )

bool empty_log_file();
bool cannot_open();

int
main( void )
{


    std::cout << "Tests was run\n";

    std::cout << "First test: " << TEST( empty_log_file() ) << '\n';
    std::cout << "Second test: " << TEST( cannot_open() ) << '\n';
    return 0;
}

bool
cannot_open()
{
    try
    {
        logger_config conf{true, false ,"asdf/asdf/asdf/log.svo"};
        Logger logger( conf );
    }
    catch ( const FileOpenError &e)
    {
       return true;
    }
    return false;
}


bool
empty_log_file()
{
    try
    {
        logger_config conf{true, true ,""};
        Logger logger( conf );
    }
    catch ( const FileNameError &e )
    {
        return true;
    }
    return false;

}