#include <prism/global>
#include <prism/FileInfo>
#include <prism/FileSystemFactory>
#include <prism/AbstractFileSystem>
#include <prism/algorithm>
#include <iostream>

PRISM_BEGIN_NAMESPACE

const std::string
convertToUnixSeparators(const std::string& path) {
        std::string ret = path;
        prism::replace(ret.begin(), ret.end(), '\\', '/');
        return ret;
}

FileInfo::FileInfo(const std::string& filename)
{
        init(filename);
}

void
FileInfo::setFile(const std::string& filename)
{
        init(filename);
}

void
FileInfo::init(const std::string& filename)
{
        m_filename = prism::convertToUnixSeparators(std::string(filename));
}

const bool
FileInfo::exists() const
{
        AbstractFileSystem * fileSystem = FileSystemFactory::get()->getFileSystem();
        return fileSystem->exists(m_filename.c_str());
}

const unsigned int
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
        if (pos != std::string::npos)
                return m_filename.substr(pos+1);

        return m_filename;
}

const std::string
FileInfo::basename() const
{
        return "file";
}

PRISM_END_NAMESPACE
