#include <prism/global>
#include <prism/FileSystem>
#ifdef _WIN32
#       include <windows.h>
#       include <io.h>
#elif defined __APPLE__
#       include <unistd.h>
#endif
#include <iostream>
#include <fstream>

PRISM_BEGIN_NAMESPACE

AbstractFileSystem *
FileSystem::create()
{
        static FileSystem instance;
        return &instance;
}

void
FileSystem::createFile(const std::string& filename)
{}

const bool
FileSystem::exists(const std::string& filename) const
{
        #ifdef _WIN32
        #       define access _access_s
        #endif

        return access(filename.c_str(), 0) == 0;
}

const unsigned int
FileSystem::fileSizeInBytes(const std::string& filename) const
{
        unsigned int i = 0;
        std::ifstream is(filename.c_str(), std::ifstream::binary);
        if (is) {
                is.seekg(0, is.end);
                i = is.tellg();
        }
        return i;
}

PRISM_END_NAMESPACE
