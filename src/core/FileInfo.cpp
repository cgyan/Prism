#include <prism/global>
#include <prism/FileInfo>
#include <prism/FileSystemFactory>
#include <cstring>

PRISM_BEGIN_NAMESPACE

FileInfo::FileInfo(const char * filename)
: m_filename{filename}
{

}

void
FileInfo::setFile(const char * filename)
{
        m_filename = filename;
}

const bool
FileInfo::exists() const
{
        if (strcmp(m_filename, "") == 0)
                return false;
        AbstractFileSystem * fileSystem = FileSystemFactory::get()->getFileSystem();
        return fileSystem->exists(m_filename);
}

const unsigned int
FileInfo::size() const {
        if (strcmp(m_filename, "") == 0)
                return 0;
        return FileSystemFactory::get()->getFileSystem()->fileSizeInBytes(m_filename);
}

PRISM_END_NAMESPACE
