#include <prism/global>
#include <prism/FileSystem>
#include <fstream>
#include <unistd.h>
#include <Cocoa/Cocoa.h>

PRISM_BEGIN_NAMESPACE

void
FileSystem::createFile(const std::string& filename)
{}

const bool
FileSystem::exists(const std::string& filename) const
{

        return [[NSFileManager defaultManager] fileExistsAtPath: [NSString stringWithUTF8String:filename.c_str()]];
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
