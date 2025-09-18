//
// Created by gnolfix on 9/18/2025.
//
#pragma once
#include <iostream>

#include "LoggerError.h"

enum Tokens : char
{
    e_DATE      = 'D',
    e_LOG       = 'S',
    e_LOG_LEVEL = 'L',

};

class LogFormat
{
    public:
        explicit LogFormat()
        : format( "%L [%D] %S" ){}
        explicit LogFormat(std::string format_)
        : format( std::move( format_ ) )
        {
            validate_format();
        }

        std::string format_to_string( const std::string& log_level,
            const std::string& message );

    private:

        std::string format;

        /**
        Available macros:
           %D/%d - Date Y-m-d H:M:S
            %L/%l - LogLevel
            %S/%s - Log message

        Example:
            format_ = "[%L](%D): %S"
            [INFO](2020-03-12 12:31:20) - Example log

        Default format:
            "%L [%D] %S"
        Throws:
            InvalidMacro if an unsupported macro is found
            FormatError default error

        */
        void validate_format();


};
