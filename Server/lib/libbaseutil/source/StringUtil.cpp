/*!
 * \file StringUtil.cpp
 *
 * \author zjhlogo zjhlogo@gmail.com
 * \date 06/07/2016
 *
 *
 */
#include "StringUtil.h"
#include <algorithm>
#include "utf8/checked.h"

#ifdef WIN32
#    define _tstoi atoi
#    define _tstoi64 _atoi64
#    define _tstof atof
#    define _stscanf sscanf
#    define _sntprintf _snprintf_c
#    define _vsntprintf _vsnprintf
#    define _tcsncpy strncpy
#else
#    define _tstoi atoi
#    define _tstoi64 atoll
#    define _tstof atof
#    define _stscanf sscanf
#    define _sntprintf snprintf
#    define _vsntprintf vsnprintf
#    define _tcsncpy strncpy
#endif

int StringUtil::replaceString(tstring& strInOut, const tstring& strSearch, const tstring& strReplace)
{
    StringList arrSubString;
    splitString(arrSubString, strInOut, strSearch);

    int numSubString = (int)arrSubString.size();
    if (numSubString > 1)
    {
        strInOut = joinString<std::vector<tstring>>(arrSubString, strReplace);
        return numSubString;
    }

    return 0;
}

//template <> int StringUtil::splitString<StringList>(StringList& arrOut, const tstring& strIn, const tstring& strSplit, bool eraseEmpty)
//{
//    int totalSplit = 0;
//    size_t startIndex = 0;
//    size_t endIndex = 0;
//
//    endIndex = strIn.find(strSplit, startIndex);
//    while (endIndex != tstring::npos)
//    {
//        arrOut.push_back(strIn.substr(startIndex, endIndex - startIndex));
//        ++totalSplit;
//
//        startIndex = endIndex;
//        startIndex += strSplit.length();
//        endIndex = strIn.find(strSplit, startIndex);
//    }
//
//    if (totalSplit <= 0)
//    {
//        if (eraseEmpty)
//        {
//            if (!strIn.empty())
//            {
//                arrOut.push_back(strIn);
//                ++totalSplit;
//            }
//        }
//        else
//        {
//            arrOut.push_back(strIn);
//            ++totalSplit;
//        }
//
//        return totalSplit;
//    }
//
//    if (!eraseEmpty)
//    {
//        arrOut.push_back(strIn.substr(startIndex));
//        ++totalSplit;
//    }
//    else
//    {
//        auto res = strIn.substr(startIndex);
//        if (!res.empty())
//        {
//            arrOut.push_back(res);
//            ++totalSplit;
//        }
//    }
//
//    return totalSplit;
//}

template <> bool StringUtil::stringToType<tstring>(tstring& valueOut, const tstring& strIn)
{
    valueOut = strIn;
    return true;
}

template <> bool StringUtil::typeToString<tstring>(tstring& strOut, const tstring& valueIn)
{
    strOut = valueIn;
    return true;
}


void StringUtil::extractNumberFromString(tstring& strOut, const tstring& strIn)
{
    for (tstring::const_iterator it = strIn.begin(); it != strIn.end(); ++it)
    {
        const char& ch = (*it);
        if (isdigit(ch))
        {
            strOut.push_back(ch);
        }
    }
}

bool StringUtil::startsWith(const tstring& str, const tstring& subStr)
{
    return (std::strncmp(str.c_str(), subStr.c_str(), subStr.length()) == 0);
}

bool StringUtil::isEqualCaseInsensitive(const tstring& str1, const tstring& str2)
{
    tstring strA;
    tstring strB;
    StringUtil::tolower(strA, str1);
    StringUtil::tolower(strB, str2);
    return strA == strB;
}

bool StringUtil::trim(std::string& strOut, const std::string& strIn)
{
    if (strIn.empty()) return false;

    strOut = trimLeft(trimRight(strIn));
    return true;
}

std::wstring StringUtil::trimLeft(const std::wstring& wstr)
{
    if (wstr.empty()) return wstr;

    const std::wstring pattern = utf8to16(" \f\n\r\t\v");
    return wstr.substr(wstr.find_first_not_of(pattern));
}

std::string StringUtil::trimLeft(const std::string& str)
{
    if (str.empty()) return str;

    const std::string pattern = " \f\n\r\t\v";
    return str.substr(str.find_first_not_of(pattern));
}

std::wstring StringUtil::trimRight(const std::wstring& wstr)
{
    if (wstr.empty()) return wstr;

    const std::wstring pattern = utf8to16(" \f\n\r\t\v");
    return wstr.substr(0, wstr.find_last_not_of(pattern) + 1);
}

std::string StringUtil::trimRight(const std::string& str)
{
    if (str.empty()) return str;

    const std::string pattern = " \f\n\r\t\v";
    return str.substr(0, str.find_last_not_of(pattern) + 1);
}

bool StringUtil::trim(std::wstring& wstrOut, const std::wstring& wstrIn)
{
    if (wstrIn.empty()) return false;

    wstrOut = trimLeft(trimRight(wstrIn));
    return true;
}

void StringUtil::toupper(tstring& strOut, const tstring& strIn)
{
    strOut = strIn;
    std::transform(strOut.begin(), strOut.end(), strOut.begin(), ::toupper);
}

void StringUtil::tolower(tstring& strOut, const tstring& strIn)
{
    strOut = strIn;
    std::transform(strOut.begin(), strOut.end(), strOut.begin(), ::tolower);
}

void StringUtil::towupper(std::wstring& strOut, const std::wstring& strIn)
{
    strOut = strIn;
    std::transform(strOut.begin(), strOut.end(), strOut.begin(), ::towupper);
}

void StringUtil::towlower(std::wstring& strOut, const std::wstring& strIn)
{
    strOut = strIn;
    std::transform(strOut.begin(), strOut.end(), strOut.begin(), ::towlower);
}

bool StringUtil::isSpace(const tstring& strIn)
{
    int len = (int)strIn.size();
    if (len == 0 || (len == 1 && hasSpace(strIn))) return true;
    return false;
}

bool StringUtil::isLinebreak(char ch)
{
    static const char LineFeed = '\x000A';
    static const char VerticalTab = '\x000B';
    static const char FormFeed = '\x000C';
    static const char CarriageReturn = '\x000D';
    static const char NextLine = '\x0085';

    return ch == LineFeed || ch == VerticalTab || ch == FormFeed || ch == CarriageReturn || ch == NextLine;
}

bool StringUtil::isLinebreak(wchar_t ch)
{
    static const wchar_t LineFeed = '\x000A';
    static const wchar_t VerticalTab = '\x000B';
    static const wchar_t FormFeed = '\x000C';
    static const wchar_t CarriageReturn = '\x000D';
    static const wchar_t NextLine = '\x0085';

    return ch == LineFeed || ch == VerticalTab || ch == FormFeed || ch == CarriageReturn || ch == NextLine;
}

void StringUtil::bool2str(tstring& strOut, bool bValue)
{
    if (bValue)
    {
        strOut = ("true");
    }
    else
    {
        strOut = ("false");
    }
}

void StringUtil::int2str(tstring& strOut, int nValue)
{
    typeToString(strOut, nValue);
}

tstring StringUtil::int2str(int value)
{
    tstring strValue;
    int2str(strValue, value);
    return strValue;
}

void StringUtil::str2int64(int64& value, tstring strIn)
{
    typeToString(strIn, value);
}

void StringUtil::uint2str(tstring& strOut, uint nValue)
{
    typeToString(strOut, nValue);
}

void StringUtil::float2str(tstring& strOut, float fValue)
{
    typeToString(strOut, fValue);
}

void StringUtil::formatChat(tstring& strOut, const tstring& strIn)
{
    for (auto ch : strIn)
    {
        if (ch != '\n' && ch != '\t' && ch != '\r')
        {
            strOut.append(1, ch);
        }
    }

    replaceString(strOut, "&#x0A;", EMPTY_STRING); // 过滤换行
}

void StringUtil::clearStrTag(tstring& strInOut, const tstring& clearTag, char replaceChar)
{
    for (auto&& it = strInOut.begin(); it != strInOut.end(); ++it)
    {
        for (auto&& cit = clearTag.begin(); cit != clearTag.end(); ++cit)
        {
            if (*it == *cit)
            {
                *it = replaceChar;
            }
        }
    }
}

std::string StringUtil::utf16to8(const std::wstring& strUtf16)
{
    // Convert it to utf-8
    std::string tUtf8;
    utf8::utf16to8(strUtf16.begin(), strUtf16.end(), back_inserter(tUtf8));
    return tUtf8;
}

std::wstring StringUtil::utf8to32(const std::string& strUtf8)
{
    // Convert it to utf-32
    std::wstring wUtf32;
    utf8::utf8to32(strUtf8.begin(), strUtf8.end(), back_inserter(wUtf32));
    return wUtf32;
}

std::string StringUtil::utf32to8(const std::wstring& strUtf32)
{
    // Convert it to utf-8
    std::string tUtf8;
    utf8::utf32to8(strUtf32.begin(), strUtf32.end(), back_inserter(tUtf8));
    return tUtf8;
}
