#include <prism/global>
#include <prism/FileSystem>
#include <fstream>
#include <shlwapi.h>

PRISM_BEGIN_NAMESPACE

const bool
FileSystem::exists(const std::string& filename) const
{
        return PathFileExists(filename.c_str());
}

const int
FileSystem::fileSizeInBytes(const std::string& filename) const
{
        const int errorSize = -1;

        if (exists(filename)) {
                WIN32_FILE_ATTRIBUTE_DATA fad;
                if (!GetFileAttributesEx(filename.c_str(), GetFileExInfoStandard, &fad))
                        return errorSize; // error condition, could call GetLastError to find out more
                LARGE_INTEGER size;
                size.HighPart = fad.nFileSizeHigh;
                size.LowPart = fad.nFileSizeLow;
                return size.QuadPart;
        }
        return errorSize;
}

const std::string
FileSystem::absolutePath(const std::string& filename) const
{
        if (exists(filename)) {
                char absPathAndFilename[4096];
                if (GetFullPathName(filename.c_str(), 4096, absPathAndFilename, NULL)) {
                        std::string s = std::string(absPathAndFilename);
                        return s.substr(0, s.find_last_of("\\"));
                }
        }
        return std::string{};
}

const std::string
FileSystem::creationDate(const std::string& filename) const
{
        if (filename == "") return std::string{};

        HANDLE hFile;
        hFile = CreateFile(filename.c_str(), 0, 0, NULL, OPEN_EXISTING, 0, NULL);
        TCHAR buff[MAX_PATH];
        FILETIME ft;
        GetFileTime(hFile, &ft, NULL, NULL);
        SYSTEMTIME st;
        FileTimeToSystemTime(&ft, &st);
        CloseHandle(hFile);

        std::string ret;
        std::string year = std::to_string(st.wYear);
        ret.append(year);
        ret.append("-");
        std::string month = std::to_string(st.wMonth);
        if (month.length() == 1)
                ret.append("0");
        ret.append(month);
        ret.append("-");
        std::string day = std::to_string(st.wDay);
        ret.append(day);

        return ret;
}

PRISM_END_NAMESPACE
