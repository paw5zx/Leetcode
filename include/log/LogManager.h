#ifndef CLOGMANAGER_H
#define CLOGMANAGER_H

#include "log4cpp/PropertyConfigurator.hh"
#include "log4cpp/Appender.hh"
#include "log4cpp/Category.hh"
#include "log4cpp/Layout.hh"
#include <stdlib.h>
#include <stdio.h>
#include <string>

#define LC_DEBUG(logEvent) \
{ \
    std::string s = __FILE__;\
    s += " : ";\
    std::stringstream line;\
    line << __LINE__;\
    s += line.str();\
    s += " : ";\
    std::ostringstream  buf ;\
    buf<< logEvent ;\
    s += buf.str();\
    CLogManager::instance()->logDebug(s);\
};

#define LC_ERROR(logEvent) \
{ \
    std::string s = __FILE__;\
    s += " : ";\
    std::stringstream line;\
    line << __LINE__;\
    s += line.str();\
    s += " : ";\
    std::ostringstream  buf ;\
    buf<< logEvent ;\
    s += buf.str();\
    CLogManager::instance()->logError(s);\
};

#define LC_INFO(logEvent) \
{ \
    std::string s = __FILE__;\
    s += " : ";\
    std::stringstream line;\
    line << __LINE__;\
    s += line.str();\
    s += " : ";\
    std::ostringstream  buf ;\
    buf<< logEvent ;\
    s += buf.str();\
    CLogManager::instance()->logInfo(s);\
};

#define LC_WARN(logEvent) \
{ \
    std::string s = __FILE__;\
    s += " : ";\
    std::stringstream line;\
    line << __LINE__;\
    s += line.str();\
    s += " : ";\
    std::ostringstream  buf ;\
    buf<< logEvent ;\
    s += buf.str();\
    CLogManager::instance()->logWarn(s);\
};


#define LC_FATAL(logEvent) \
{ \
    std::string s = __FILE__;\
    s += " : ";\
    std::stringstream line;\
    line << __LINE__;\
    s += line.str();\
    s += " : ";\
    std::ostringstream  buf ;\
    buf<< logEvent ;\
    s += buf.str();\
    CLogManager::instance()->logFatal(s);\
};


class CLogManager
{
public:
    //instances
    //static  ILogManager* instance() ;
    static  CLogManager* instance() ;

    //logDebug
    //param[in] strMsg : 消息
    void logDebug(const std::string & strMsg);

    //logError
    //param[in] strMsg : 消息
     void logError(const std::string & strMsg);

    //logInfo
    //param[in] strMsg : 消息
    void logInfo(const std::string & strMsg);

    //logWarn
    //param[in] strMsg : 消息
    void logWarn(const std::string & strMsg);

    //logFatal
    //param[in] strMsg : 消息
    void logFatal(const std::string & strMsg);

private:
     CLogManager();
     ~CLogManager();

private:
     std::string m_strConfigPath;
     static CLogManager* m_pInstance;
};

#endif // CLOGMANAGER_H
