//
// Created by gnolfix on 9/16/2025.
//
#pragma once
#include <map>
#include <string>
#include <fstream>

#include "LogFormat.h"
#include "LoggerError.h"

enum class LogLevel
{
    e_DEBUG = 0,
    e_INFO = 1,
    e_WARNING = 2,
    e_ERROR = 3
};

class ansi_colors
{
    public:
        enum colors_codes
        {
            e_reset   = 0,
            e_black   = 30,
            e_red     = 31,
            e_green   = 32,
            e_yellow  = 33,
            e_blue    = 34,
            e_magenta = 35,
            e_cyan    = 36,
            e_white   = 37,
        };

        static std::string
        color_to_string ( colors_codes code );

};

struct
logger_config
{
        bool in_file = false;
        bool no_ansi = false;
        std::string file_name = {0};
        std::map<LogLevel, std::string> colors =
        {
            {LogLevel::e_DEBUG, ansi_colors::color_to_string( ansi_colors::e_cyan )},
            {LogLevel::e_INFO, ansi_colors::color_to_string( ansi_colors::e_white )},
            {LogLevel::e_WARNING, ansi_colors::color_to_string( ansi_colors::e_yellow )},
            {LogLevel::e_ERROR, ansi_colors::color_to_string( ansi_colors::e_red )}
        };
};


class Logger
{
    public:
        explicit
        Logger ( logger_config log_conf )
        : m_log_conf( std::move(log_conf) )
        {
            if ( m_log_conf.in_file )
            {
                if ( m_log_conf.file_name.empty() )
                {
                    throw FileNameError("Log file name cannot be empty");
                }
                m_log_file.open( m_log_conf.file_name , std::ios::out | std::ios::trunc);
                if ( !m_log_file.is_open() )
                {
                    throw FileOpenError( "Cannot open file: " + m_file_name );
                }

            }

        };


        void INFO(const std::string& text);
        void ERROR(const std::string& text);
        void WARNING(const std::string& text);
        void DEBUG(const std::string& text);

        void set_current_log_level(LogLevel l_log_level);
        void set_log_format(std::string format);
    private:

        logger_config m_log_conf;
        const std::string m_file_name = m_log_conf.file_name;
        std::map<LogLevel, std::string> m_colors = m_log_conf.colors;
        std::ofstream m_log_file;
        LogLevel m_current_log_level = LogLevel::e_DEBUG;
        LogFormat m_format{};

        std::string level_to_string( LogLevel l_log_level );
        void logger( LogLevel l_log_level, const std::string& text );

};