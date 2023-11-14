//C++ Standard: C++11
#include "log/LogManager.h"
#include <mutex>
#include <iostream>
#include <string>

std::mutex g_LogManagerMtx;
//

CLogManager* CLogManager::m_pInstance = nullptr;

CLogManager* CLogManager::instance()
{
    g_LogManagerMtx.lock();
    if (nullptr == m_pInstance)
    {
        m_pInstance = new CLogManager();
        if (nullptr != m_pInstance)
        {
            g_LogManagerMtx.unlock();
            return m_pInstance;
        }
        else
        {
            g_LogManagerMtx.unlock();
            return nullptr;
        }
    }
    else
    {
        g_LogManagerMtx.unlock();
        return m_pInstance;
    }
}

CLogManager::CLogManager()
{
    // 加载配置文件
    // 需要能够动态调整打印等级
    try
    {
      log4cpp::PropertyConfigurator::configure("../../cfg/log4cfg");
    }
    catch (log4cpp::ConfigureFailure & f)
    {
      std::cerr << "configure problem " << f.what() << std::endl;
    }
}

CLogManager::~CLogManager()
{
     log4cpp::Category & log = log4cpp::Category::getRoot();
     log.shutdown();
}

void CLogManager::logDebug(const std::string & strMsg)
{
    log4cpp::Category & log = log4cpp::Category::getRoot();
    log.debug(strMsg);
}

void CLogManager::logError(const std::string & strMsg)
{
    log4cpp::Category & log = log4cpp::Category::getRoot();
    log.error(strMsg);
}

void CLogManager::logInfo(const std::string & strMsg)
{
    log4cpp::Category & log = log4cpp::Category::getRoot();
    log.info(strMsg);
}

void CLogManager::logWarn(const std::string & strMsg)
{
    log4cpp::Category & log = log4cpp::Category::getRoot();
    log.warn(strMsg);
}

void CLogManager::logFatal(const std::string & strMsg)
{
    log4cpp::Category & log = log4cpp::Category::getRoot();
    log.fatal(strMsg);
}
