/**
 * @file   BaseException.h
 * @author xiaofei
 * @date   Tue Jun 05 16:19:20 2007
 *
 * @brief  Define the base exception handle class.
 *
 *
 */

#ifndef __BASE_EXCEPTION_H__
#define __BASE_EXCEPTION_H__
#include <errno.h>
#include <string>
enum ErrorCode
{
    no_error= 0,
    UnKnownActor=10001,
    UnKnownMsg=10002,
    TimeOut=10003
};
/**
 *
 *
 * @brief The Base Exception class
 * @author xiaofei
 * @version 1.0
 */
class BaseException
{
public:
    // Constructor
    BaseException( ErrorCode ec, std::string what_msg )
        : m_error_code( ec ), m_what( what_msg ) {}
    BaseException( ErrorCode ec, const char* what_msg )
        : m_error_code( ec ), m_what( std::string(what_msg)) {}
    // access methods
    ErrorCode      code() const
    {
        return m_error_code;
    }
    std::string    what() const
    {
        return m_what;
    }

private:
    // Data members
    ErrorCode      m_error_code;
    std::string    m_what;
};

#endif
