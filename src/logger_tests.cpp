//
// Created by gnolfix on 9/17/2025.
//
#include <sstream>
#include <iostream>

#include "Logger.h"
#include "LoggerError.h"

#define TEST( passed ) ( ( passed ) ? "PASSED" : "FAILED" )

bool empty_log_file();
bool cannot_open();
bool formatter_test();
bool log_test_one();
bool log_test_two();

int
main( void )
{

    std::cout << "Tests was run\n";

    std::cout << "First test: " << TEST( empty_log_file() ) << '\n';
    std::cout << "Second test: " << TEST( cannot_open() ) << '\n';
    std::cout << "Third test: " << TEST( formatter_test() ) << '\n';
    std::cout << "Fourth test: " << TEST( log_test_one() ) << '\n';
    std::cout << "Fifth test: " << TEST( log_test_two() ) << '\n';

    return 0;
}

bool
log_test_two()
{
    try
    {
        logger_config conf{false, true, ""};
        Logger logger( conf );
        logger.set_log_format( "%s" );

        std::ostringstream buffer;

        std::streambuf* old_buffer = std::cerr.rdbuf();

        std::cerr.rdbuf(buffer.rdbuf());

        logger.WARNING( "test" );

        std::cerr.rdbuf(old_buffer);

        std::string log = buffer.str();
        std::string test = "test\n";
        if ( log == test ) return true;
    }
    catch ( const std::exception &e )
    {
        return false;
    }
    return false;


}

bool
log_test_one()
{
    try
    {
        logger_config conf{false, true, ""};
        Logger logger( conf );
        logger.set_log_format( "%s" );

        std::ostringstream buffer;

        std::streambuf* old_buffer = std::cout.rdbuf();

        std::cout.rdbuf(buffer.rdbuf());

        logger.INFO( "test" );

        std::cout.rdbuf(old_buffer);

        std::string log = buffer.str();
        std::string test = "test\n";
        if ( log == test ) return true;
    }
    catch ( const std::exception &e )
    {
        return false;
    }
    return false;
}

bool
formatter_test()
{
    try
    {
        logger_config conf{false, false, ""};
        Logger logger( conf );
        logger.set_log_format( "sdfsddfasdf%esdf%d" );
    }
    catch ( const InvalidMacro &e )
    {
        return true;
    }
    return false;
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