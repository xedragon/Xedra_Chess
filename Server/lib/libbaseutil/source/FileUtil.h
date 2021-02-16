/*!
 * \file FileUtil.h
 * \date 7-18-2012 12:55:49
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#pragma once

#include <future>

using tstring = std::string;

class FileUtil
{
public:
	static const tstring CURRENT_DIR;
	static const tstring PARENT_DIR;

public:
	static bool readFileIntoString(tstring& stringOut, const tstring& filePath, int storage = 0);


	static tstring getFileExtension(const tstring& strIn);
	static tstring getFileDirectory(const tstring& strIn);
	static tstring getFileName(const tstring& strIn);
	static tstring getFileNameWithoutExtension(const tstring& strIn);
	static tstring getFileNameWithExtension(const tstring& strIn, const tstring& strExt);

	static tstring combinePath(const tstring& path1, const tstring& path2);

	static bool renameFile(const tstring& strOldFile, const tstring& strNewFile);
	static tstring formatFilePath(const tstring& strPath);
	static tstring formatFileDir(const tstring& strDir);

	static tstring getRelativePath(const tstring& src, const tstring& dest);
	static tstring getAbsolutePath(const tstring& baseDir, const tstring& relativeFilePath);
    static tstring getAbsolutePath(const tstring& filePath);

	static const tstring& getMainObbPath() { return m_mainObbPath; }
	static void setMainObbPath(const tstring& path) { m_mainObbPath = path; }

	static const tstring& getPatchObbPath() { return m_patchObbPath; }
	static void setPatchObbPath(const tstring& path) { m_patchObbPath = path; }
	
	static int getObbVersionCode() { return m_obbVersionCode; }
	static void setObbVersionCode(int obbVersionCode) { m_obbVersionCode = obbVersionCode; }


private:
	static tstring m_writableDir;
	static tstring m_writableAssetsDir;
	static tstring m_revisionUpdateDir;

	static tstring m_mainObbPath;
	static tstring m_patchObbPath;
	static int m_obbVersionCode;

};