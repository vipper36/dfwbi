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
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/dom/DOM.hpp>
#include "XMLConfiger.h"
#include "Logger.h"
#include <string>

enum ErrorCode {
    no_error= 0,
    FileOpenError=20001,
    FileReadError,
    FileWriteError,
    FileLockError,
    FileRemoveError,
    BufNullException,
    DirOpenError,
    DirCloseError,
    DirReadError,
    InParamError,
    CACipherError,
    GetTimeError,
    MQError,
    CodeConvertError,
    DirCreateError,
    DBError,
    DBWriteError,
    DBReadError,
    DBReadNoDataError,
    DBConsViolated,
    DBNullViolated,
    UnKnownPro
};
/** 
 * 
 * 
 * @brief The Base Exception class
 * @author xiaofei
 * @version 1.0
 */
class BaseException {
public:    
        // Constructor
    BaseException( ErrorCode ec, std::string what_msg )
        : m_error_code( ec ), m_what( what_msg ) {}
    BaseException( ErrorCode ec, const char* what_msg )
        : m_error_code( ec ), m_what( std::string(what_msg)) {}
        // access methods
    ErrorCode      code() const { return m_error_code; }
    std::string    what() const { return m_what; }

private:
        // Data members
    ErrorCode      m_error_code;
    std::string    m_what;
};
/** 
 * 
 * @brief When use a DOMWriter, need to write a error handler for it.
 * @author xiaofei
 */
class DOMWriterHandler : public DOMErrorHandler 
{
  public:
    DOMWriterHandler() {};
    ~DOMWriterHandler() {};
    bool handleError(const DOMError &error) 
    {
        char *message = 0;
         MAINLOG.errorStream()<< "Error occurred in DOMBuilder!  Message:  "
                                  <<(message = XMLString::transcode(error.getMessage()))
                                  << " of severity "<< error.getSeverity()
                                  << "." << MAINEND;
        XMLString::release(&message);
        return true;
    }
};
/** 
 * 
 * @brief When use a DOMBuilder, need to write a error handler for it.
 * @author xiaofei
 */
class DOMBuilderHandler : public DOMErrorHandler 
{
  public:
    DOMBuilderHandler() {};
    ~DOMBuilderHandler() {};
    bool handleError(const DOMError &error) 
    {
        char *message = 0;
        MAINLOG.errorStream()<< "Error occurred in DOMBuilder!  Message:  "
                                  <<(message = XMLString::transcode(error.getMessage()))
                                  << " of severity "<< error.getSeverity()
                                  << "." << MAINEND;
        XMLString::release(&message);
        return true;
    }
};
#endif
