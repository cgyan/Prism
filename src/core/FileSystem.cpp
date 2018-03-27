#include <prism/global>
#include <prism/FileSystem>
#include <fstream>
#include <shlwapi.h>

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
        return PathFileExists(filename.c_str());
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
