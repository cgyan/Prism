#include <prism/global>
#include <prism/FileSystem>
#include <fstream>
#include <unistd.h>
#include <Cocoa/Cocoa.h>
#include <stdlib.h> // for realpath()

PRISM_BEGIN_NAMESPACE

const bool
FileSystem::exists(const std::string& filename) const
{

        return [[NSFileManager defaultManager] fileExistsAtPath: [NSString stringWithUTF8String:filename.c_str()]];
}

const int
FileSystem::fileSizeInBytes(const std::string& filename) const
{
        if (exists(filename))
                return [[[NSFileManager defaultManager] attributesOfItemAtPath:[NSString stringWithUTF8String:filename.c_str()] error:nil] fileSize];

        const int errorSize = -1;
        return errorSize;
}

const std::string
FileSystem::absolutePath(const std::string& filename) const
{
        if (exists(filename))
        {
                char buff[PATH_MAX];
                if (realpath(filename.c_str(), buff) != NULL)
                {
                        size_t pos = std::string(buff).find_last_of("/");
                        return std::string(buff).substr(0, pos);
                }
        }
        return std::string{};
}

PRISM_END_NAMESPACE
