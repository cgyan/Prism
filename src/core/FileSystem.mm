#include <prism/global>
#include <prism/FileSystem>
#include <fstream>
#ifdef _WIN32
#       include <shlwapi.h>
#elif defined __APPLE__
#       include <unistd.h>
#       include <Cocoa/Cocoa.h>
#endif

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
                return PathFileExists(filename.c_str());
        #elif defined __APPLE__
                // return access(filename.c_str(), 0) == 0;
                return [[NSFileManager defaultManager] fileExistsAtPath: [NSString stringWithUTF8String:filename.c_str()]];
        #endif
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
