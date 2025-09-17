//
// Created by gnolfix on 9/16/2025.
//

#include "Logger.h"
#include <iostream>
#include <chrono>
#include <format>

#ifdef _WIN32
#include <windows.h>

void
enable_ansi_colors ()
{
    HANDLE hOut = GetStdHandle( STD_OUTPUT_HANDLE );
    if ( hOut == INVALID_HANDLE_VALUE )
        return;

    DWORD dwMode = 0;
    if ( !GetConsoleMode( hOut, &dwMode ) )
        return;

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode( hOut, dwMode );
}
#endif

std::string
current_date_time ()
{
    auto now = std::chrono::system_clock::now();
    time_t now_c = std::chrono::system_clock::to_time_t( now );
    std::tm tm{};
#ifdef _WIN32
    localtime_s( &tm, &now_c );
#else
    localtime_r( &now_c, &tm );
#endif
    std::chrono::sys_time< std::chrono::seconds > tp = std::chrono::sys_time<
        std::chrono::seconds >( std::chrono::seconds( now_c ) );
    return std::format( "{:%Y-%m-%d %H:%M:%S}", tp );
}

void
Logger::set_current_log_level ( log_level l_log_level )
{
    current_log_level = l_log_level;
};

void
Logger::INFO ( const std::string &text )
{
    logger( e_INFO, text );
};

void
Logger::logger ( log_level l_log_level, const std::string &text )
{



};



