#include <prism/global>
#include <prism/FileInfo>
#include <prism/FileSystemFactory>
#include <iostream>

PRISM_BEGIN_NAMESPACE

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
        m_filename = FileSystemFactory::get()->getFileSystem()->convertToUnixSeparators(filename);
}

const bool
FileInfo::exists() const
{
        if (m_filename == "")
                return false;
        AbstractFileSystem * fileSystem = FileSystemFactory::get()->getFileSystem();
        return fileSystem->exists(m_filename.c_str());
}

const unsigned int
FileInfo::size() const
{
        if (m_filename == "")
                return 0;
        return FileSystemFactory::get()->getFileSystem()->fileSizeInBytes(m_filename.c_str());
}

const std::string
FileInfo::filename() const
{
        size_t pos = m_filename.find_last_of("/");
        if (pos != std::string::npos)
                return m_filename.substr(pos+1);

        return m_filename;
}

PRISM_END_NAMESPACE
