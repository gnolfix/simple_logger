//
// Created by gnolfix on 9/18/2025.
//
#include <chrono>
#include <string>
#include <cctype>

#include "LogFormat.h"



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
LogFormat::validate_format ()
{
    size_t pos = 0;
    if ( format.empty() )
    {
        format = "%L [%D] %S";
    }
    while ( ( pos = format.find( '%', pos ) ) != std::string::npos )
    {
        if ( pos + 1 < format.size() )
        {
            char macro = static_cast<char>( std::toupper(  format[ pos + 1 ] ) );
            switch ( macro )
            {
                case Tokens::e_DATE:
                case Tokens::e_LOG:
                case Tokens::e_LOG_LEVEL:
                    break;
                default:
                    throw InvalidMacro( "Invalid format macro" );
            }
        }
        pos++;
    }
}

std::string
LogFormat::format_to_string (  const std::string& log_level,
    const std::string& message)
{
 // "%L [%D] %S"
    std::string s;

    auto it = format.begin();

    while (it != format.end()) {
        // ищем следующий '%'
        auto macro_it = std::find_if(it, format.end(),
            [](char c){ return c == '%'; });

        // копируем всё до макроса
        s.append(it, macro_it);

        if (macro_it != format.end() && (macro_it + 1) != format.end()) {
            char macro = std::toupper( *(macro_it + 1) );
            switch (macro) {
                case 'D': s += current_date_time(); break;
                case 'L': s += log_level; break;
                case 'S': s += message; break;
                default: throw std::runtime_error("Invalid macro");
            }
            it = macro_it + 2; // пропускаем макрос
        } else {
            break; // больше макросов нет
        }
    }
    return s;
}

