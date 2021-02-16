/*!
 * \file LogUtil.h
 * \date 10-11-2014 16:13:32
 *
 *
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#pragma once




#ifndef __FUNCTION_NAME__
#    ifdef WIN32 // WINDOWS
#        define __FUNCTION_NAME__ __FUNCTION__
#    else //*NIX
#        define __FUNCTION_NAME__ __func__
#    endif
#endif

#define LOGI(...) (NS::LogUtil::print(__FILE__, __LINE__, __FUNCTION_NAME__, NS::LogUtil::LogPriority::Info, fmt::format(__VA_ARGS__)))
#define LOGD(...) (NS::LogUtil::print(__FILE__, __LINE__, __FUNCTION_NAME__, NS::LogUtil::LogPriority::Debug, fmt::format(__VA_ARGS__)))
#define LOGW(...) (NS::LogUtil::print(__FILE__, __LINE__, __FUNCTION_NAME__, NS::LogUtil::LogPriority::Warning, fmt::format(__VA_ARGS__)))
#define LOGE(...) (NS::LogUtil::print(__FILE__, __LINE__, __FUNCTION_NAME__, NS::LogUtil::LogPriority::Error, fmt::format(__VA_ARGS__)))
#define LOGB(...) (NS::LogUtil::print(__FILE__, __LINE__, __FUNCTION_NAME__, NS::LogUtil::LogPriority::Behavior, fmt::format(__VA_ARGS__)))

#define LOG_EVENT_I(...) (NS::LogUtil::logWithEvent(__FILE__, __LINE__, __FUNCTION_NAME__, NS::LogUtil::LogPriority::Info, fmt::format(__VA_ARGS__)))
#define LOG_EVENT_D(...) (NS::LogUtil::logWithEvent(__FILE__, __LINE__, __FUNCTION_NAME__, NS::LogUtil::LogPriority::Debug, fmt::format(__VA_ARGS__)))
#define LOG_EVENT_W(...) (NS::LogUtil::logWithEvent(__FILE__, __LINE__, __FUNCTION_NAME__, NS::LogUtil::LogPriority::Warning, fmt::format(__VA_ARGS__)))
#define LOG_EVENT_E(...) (NS::LogUtil::logWithEvent(__FILE__, __LINE__, __FUNCTION_NAME__, NS::LogUtil::LogPriority::Error, fmt::format(__VA_ARGS__)))

#define LOG_WORLD_DISPLAY(...) (NS::LogUtil::printWorldDiwplayLog(fmt::format(__VA_ARGS__)))