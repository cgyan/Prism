#include <prism/global>
#include <prism/FileInfo>
#include <prism/FileSystemFactory>
#include <iostream>

PRISM_BEGIN_NAMESPACE

FileInfo::FileInfo(const std::string& filename)
: m_filename{filename}
{}

void
FileInfo::setFile(const std::string& filename)
{
        m_filename = filename;
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
FileInfo::size() const {
        if (m_filename == "")
                return 0;
        return FileSystemFactory::get()->getFileSystem()->fileSizeInBytes(m_filename.c_str());
}

PRISM_END_NAMESPACE
