//
// Created by gnolfix on 9/16/2025.
//

#include "Logger.h"
#include <iostream>
#include <chrono>
#include <format>
#include <utility>

#ifdef _WIN32
#include <windows.h>
#undef ERROR
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
Logger::DEBUG ( const std::string &text )
{
    logger( LogLevel::e_DEBUG, text );
};

void
Logger::WARNING ( const std::string &text )
{
    logger( LogLevel::e_WARNING, text );
};

void
Logger::ERROR ( const std::string &text )
{
    logger( LogLevel::e_ERROR, text );
};

void
Logger::logger ( LogLevel l_log_level, const std::string &text )
{
    if ( l_log_level < m_current_log_level )
        return;
    std::string log = m_format.format_to_string( level_to_string( l_log_level ), text );
    if (l_log_level > LogLevel::e_INFO)
        std::cerr << log << "\n";
    else
        std::cout << log << "\n";
    if ( m_log_conf.in_file )
    {
        m_log_file << log;
    }
};

void
Logger::set_log_format ( std::string format )
{
    m_format = LogFormat{std::move(format)};
}


std::string
Logger::level_to_string ( LogLevel l_log_level )
{
    if ( m_log_conf.no_ansi )
    {
        switch ( l_log_level )
        {
            case LogLevel::e_DEBUG:
                return "DEBUG";
            case LogLevel::e_INFO:
                return "INFO";
            case LogLevel::e_WARNING:
                return "WARNING";
            case LogLevel::e_ERROR:
                return "ERROR";
            default:
                break;
        }
    }
    else
        switch ( l_log_level )
        {
            case LogLevel::e_DEBUG:
                return m_colors[LogLevel::e_DEBUG] + "DEBUG" +
                       ansi_colors::color_to_string( ansi_colors::e_reset );
            case LogLevel::e_INFO:
                return m_colors[LogLevel::e_INFO] + "INFO" +
                       ansi_colors::color_to_string( ansi_colors::e_reset );
            case LogLevel::e_WARNING:
                return m_colors[LogLevel::e_WARNING] + "WARNING" +
                       ansi_colors::color_to_string( ansi_colors::e_reset );
            case LogLevel::e_ERROR:
                return m_colors[LogLevel::e_ERROR] + "ERROR" +
                       ansi_colors::color_to_string( ansi_colors::e_reset );
            default:
                break;
        }


}


