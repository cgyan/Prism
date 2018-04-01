#include <prism/global>
#include <prism/FileSystem>
#include <fstream>
#include <shlwapi.h>

PRISM_BEGIN_NAMESPACE

void
FileSystem::createFile(const std::string& filename)
{}

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

PRISM_END_NAMESPACE
