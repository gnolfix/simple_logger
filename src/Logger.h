//
// Created by gnolfix on 9/16/2025.
//
#pragma once
#include <string>
#include <fstream>

#include "LoggerError.h"

struct
logger_config
{
    bool in_file = false;
    std::string file_name;


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
                m_log_file.open( m_log_conf.file_name , std::ios::app);
                if ( !m_log_file.is_open() )
                {
                    throw FileOpenError( "Cannot open file: " + m_file_name );
                }

            }

        };
        enum log_level
        {
            e_DEBUG = 0,
            e_INFO = 1,
            e_WARNING = 2,
            e_ERROR = 3
        };

        void INFO(const std::string& text);
        void ERROR(const std::string& text);
        void WARNING(const std::string& text);
        void DEBUG(const std::string& text);

        void set_current_log_level(log_level l_log_level);
    private:
        logger_config m_log_conf;
        const std::string m_file_name = m_log_conf.file_name;
        std::ofstream m_log_file;
        int current_log_level = e_DEBUG;
        std::string level_to_string(log_level l_log_level);
        void logger(log_level l_log_level, const std::string& text);


};