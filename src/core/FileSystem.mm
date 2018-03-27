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

const int
FileSystem::fileSizeInBytes(const std::string& filename) const
{
        if (exists(filename))
        {
                return [[[NSFileManager defaultManager] attributesOfItemAtPath:[NSString stringWithUTF8String:filename.c_str()] error:nil] fileSize];
        }
        return 0;
}

PRISM_END_NAMESPACE
