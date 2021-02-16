/*!
 * \file FileUtil.cpp
 * \date 7-18-2012
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "FileUtil.h"
#include "StringUtil.h"
#include "LogUtil.h"

#if defined(_WIN32)
#include <direct.h>
#elif defined(__unix__) || defined(__linux__) || defined(__APPLE__)
#include <dirent.h>
#endif


const tstring FileUtil::CURRENT_DIR = ".";
const tstring FileUtil::PARENT_DIR = "..";

tstring FileUtil::m_writableDir{};
tstring FileUtil::m_writableAssetsDir{};
tstring FileUtil::m_revisionUpdateDir{};
tstring FileUtil::m_mainObbPath{"Resource/main.obb"};
tstring FileUtil::m_patchObbPath{};
int FileUtil::m_obbVersionCode{ 0 };


void getFileDir(tstring& strOut, const tstring& strIn)
{
	size_t nPosEnd = strIn.find_last_of("/\\");

	if (nPosEnd == tstring::npos)
	{
		strOut.clear();
		return;
	}

	strOut = strIn.substr(0, nPosEnd);
}


