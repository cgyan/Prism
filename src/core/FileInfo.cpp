#include <prism/global>
#include <prism/FileInfo>
#include <prism/FileSystemFactory>
#include <prism/AbstractFileSystem>
#include <prism/algorithm>
#include <iostream>

PRISM_BEGIN_NAMESPACE

const std::string
convertPathToUnixSeparators(const std::string& path) {
        std::string ret = path;
        prism::replace(ret.begin(), ret.end(), '\\', '/');
        return ret;
}

FileInfo::FileInfo(const std::string& filename)
{
        m_filename = prism::convertPathToUnixSeparators(std::string(filename));
}

void
FileInfo::setFile(const std::string& filename)
{
        m_filename = prism::convertPathToUnixSeparators(std::string(filename));
}

const bool
FileInfo::exists() const
{
        AbstractFileSystem * fileSystem = FileSystemFactory::get()->getFileSystem();
        return fileSystem->exists(m_filename.c_str());
}

const int
FileInfo::size() const
{
        if (exists())
                return FileSystemFactory::get()->getFileSystem()->fileSizeInBytes(m_filename.c_str());

        const int errorSize = -1;
        return errorSize;

}

const std::string
FileInfo::filename() const
{
        size_t pos = m_filename.find_last_of("/");
        return m_filename.substr(pos+1);
}

const std::string
FileInfo::basename() const
{
        std::string ret = filename();
        const size_t pos = ret.find_first_of(".");
        return ret.substr(0, pos);
}

const std::string
FileInfo::suffix() const
{
        const size_t pos = m_filename.find_last_of(".");
        if (pos == std::string::npos) return "";
        return m_filename.substr(pos+1);
}

const std::string
FileInfo::entireSuffix() const
{
        std::string ret = filename();
        const size_t pos = ret.find_first_of(".");
        if (pos == std::string::npos) return "";
        return ret.substr(pos+1);
}

const std::string
FileInfo::entireBasename() const
{
        std::string ret = filename();
        const size_t pos = ret.find_last_of(".");
        return ret.substr(0, pos);
}

PRISM_END_NAMESPACE
