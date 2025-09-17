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

std::string
ansi_colors::color_to_string ( colors_codes code )
{
    std::string s = "\033[" + std::to_string( static_cast<int>(code) ) + "m";
    return s;
}


void
Logger::set_current_log_level ( LogLevel l_log_level )
{
    m_current_log_level = l_log_level;
};

void
Logger::INFO ( const std::string &text )
{
    logger( LogLevel::e_INFO, text );
};

void
Logger::logger ( LogLevel l_log_level, const std::string &text )
{
    if ( l_log_level < m_current_log_level )
        return;

};

std::string
Logger::level_to_string ( LogLevel l_log_level )
{
    switch ( l_log_level )
    {
        case LogLevel::e_DEBUG:
            return m_colors[LogLevel::e_DEBUG] + "DEBUG" + ansi_colors::color_to_string( ansi_colors::e_reset );
        case LogLevel::e_INFO:
            return m_colors[LogLevel::e_INFO] + "INFO" + ansi_colors::color_to_string( ansi_colors::e_reset );
        case LogLevel::e_WARNING:
            return m_colors[LogLevel::e_WARNING] + "WARNING" + ansi_colors::color_to_string( ansi_colors::e_reset );
        case LogLevel::e_ERROR:
            return m_colors[LogLevel::e_ERROR] + "ERROR" + ansi_colors::color_to_string( ansi_colors::e_reset );
        default:
            break;
    }


}


