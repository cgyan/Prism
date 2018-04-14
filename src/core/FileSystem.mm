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
                        std::string s(buff);
                        size_t pos = s.find_last_of("/");
                        return s.substr(0, pos);
                }
        }
        return std::string{};
}

const std::string
FileSystem::creationDate(const std::string& filename) const
{
        if (filename == "") return std::string{};
        NSDictionary * dict = [[NSFileManager defaultManager] attributesOfItemAtPath: [NSString stringWithUTF8String: filename.c_str()] error: nil];
        NSDate * date = [dict objectForKey: NSFileCreationDate];
        const char * cret = [[date description] UTF8String];
        return std::string{cret, cret + 10};
}

PRISM_END_NAMESPACE
