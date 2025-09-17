//
// Created by gnolfix on 9/17/2025.
//
#pragma once
#include <stdexcept>


class LoggerError : public std::runtime_error
{
    public:
        using std::runtime_error::runtime_error;
};

class FileOpenError : LoggerError
{

    public:
        using LoggerError::LoggerError;
};

class FileNameError : LoggerError
{

    public:
        using LoggerError::LoggerError;
};
