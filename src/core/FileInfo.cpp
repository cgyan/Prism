#include <prism/global>
#include <prism/FileInfo>
#include <prism/AbstractFileSystem>
#include <prism/FileSystem>
#include <prism/Vector>
#include <prism/Stack>
#include <prism/algorithm>
#include <string>
#include <sstream>
#include <iostream>

PRISM_BEGIN_NAMESPACE

const std::string
FileInfo::toNormalizedSeparators(const std::string& path) {
        std::string ret = path;
        prism::replace(ret.begin(), ret.end(), '\\', '/');
        return ret;
}
//======================================================================================================================
//
//======================================================================================================================
class FileProperty
{
public:
        enum class Property { Filename, Basename, Suffix, EntireSuffix, EntireBasename, AbsolutePath, CanonicalFilePath };
public:
        static const std::string absolutePath(const std::string& file, std::shared_ptr<AbstractFileSystem> fileSystem);
        static const std::string canonicalFilePath(const std::string& file);
        static const std::string entireBasename(const std::string& file);
        static const std::string suffix(const std::string& file);
        static const std::string entireSuffix(const std::string& file);
        static const std::string basename(const std::string& file);
        static const std::string filename(const std::string& file);
private:
        static Vector<std::string> split(const std::string& file, const char delim);
        static Stack<std::string> removeDotAndDoubleDotComponents(Vector<std::string> * tokens);
        static const std::string buildCanonicalString(Stack<std::string>& stack);
};

const std::string
FileProperty::absolutePath(const std::string& file, std::shared_ptr<AbstractFileSystem> fileSystem)
{
        if (file == "") return std::string{};
        return fileSystem->absolutePath(file.c_str());
}

const std::string
FileProperty::canonicalFilePath(const std::string& file)
{
        Vector<std::string> tokens = FileProperty::split(file, '/');
        Stack<std::string> stack = FileProperty::removeDotAndDoubleDotComponents(&tokens);
        return FileProperty::buildCanonicalString(stack);
}

Vector<std::string>
FileProperty::split(const std::string& file, const char delim)
{
        Vector<std::string> tokens;
        std::stringstream ss(file);
        std::string token;
        while(std::getline(ss, token, delim))
                tokens.append(token);
        return tokens;
}

Stack<std::string>
FileProperty::removeDotAndDoubleDotComponents(Vector<std::string> * tokens)
{
        Stack<std::string> stack;
        for (auto i = 0; i < tokens->size(); ++i)
        {
                std::string token = tokens->at(i);
                if (token != "." && token != "..") stack.push(token);
                if (token == "..") stack.pop();
        }
        return stack;
}

const std::string
FileProperty::buildCanonicalString(Stack<std::string>& stack)
{
        std::string ret;
        std::string separator = "";
        while (!stack.empty())
        {
                std::string token = stack.top();
                stack.pop();
                token.append(separator);
                ret.insert(0, token);
                separator = "/";
        }
        return ret;
}

const std::string
FileProperty::entireBasename(const std::string& file)
{
        std::string ret = FileProperty::filename(file);
        const size_t pos = ret.find_last_of(".");
        return ret.substr(0, pos);
}

const std::string
FileProperty::suffix(const std::string& file)
{
        const size_t pos = file.find_last_of(".");
        if (pos == std::string::npos) return "";
        return file.substr(pos+1);
}

const std::string
FileProperty::entireSuffix(const std::string& file)
{
        std::string ret = FileProperty::filename(file);
        const size_t pos = ret.find_first_of(".");
        if (pos == std::string::npos) return "";
        return ret.substr(pos+1);
}

const std::string
FileProperty::basename(const std::string& file)
{
        std::string ret = FileProperty::filename(file);
        const size_t pos = ret.find_first_of(".");
        return ret.substr(0, pos);
}

const std::string
FileProperty::filename(const std::string& file)
{
        size_t pos = file.find_last_of("/");
        return file.substr(pos+1);
}
//======================================================================================================================
//
//======================================================================================================================
class FileInfoInternal
{
public:
        FileInfoInternal(const std::string& file, std::shared_ptr<AbstractFileSystem> fileSystem);
        FileInfoInternal(const FileInfoInternal& copy);

        void setFile(const std::string& file);
        const std::string file() const;
        const bool fileExists() const;
        const int fileSize() const;
        const std::string fileProperty(FileProperty::Property property) const;
private:
        std::shared_ptr<AbstractFileSystem> m_fileSystem{nullptr};
        std::string m_file{""};
};

const std::string
FileInfoInternal::fileProperty(FileProperty::Property property) const
{
        switch (property)
        {
                case FileProperty::Property::Filename: return FileProperty::filename(m_file); break;
                case FileProperty::Property::Basename: return FileProperty::basename(m_file); break;
                case FileProperty::Property::EntireSuffix: return FileProperty::entireSuffix(m_file); break;
                case FileProperty::Property::Suffix: return FileProperty::suffix(m_file); break;
                case FileProperty::Property::EntireBasename: return FileProperty::entireBasename(m_file); break;
                case FileProperty::Property::AbsolutePath: return FileProperty::absolutePath(m_file, m_fileSystem); break;
                case FileProperty::Property::CanonicalFilePath: return FileProperty::canonicalFilePath(m_file); break;
        }
}

FileInfoInternal::FileInfoInternal(const std::string& file, std::shared_ptr<AbstractFileSystem> fileSystem)
: m_fileSystem{fileSystem}
{
        setFile(file);
}

FileInfoInternal::FileInfoInternal(const FileInfoInternal& copy)
{
        m_file = copy.m_file;
        m_fileSystem = copy.m_fileSystem;
}

void
FileInfoInternal::setFile(const std::string& file)
{
        m_file = FileInfo::toNormalizedSeparators(file);
}

const std::string
FileInfoInternal::file() const
{
        return m_file;
}

const bool
FileInfoInternal::fileExists() const
{
        return m_fileSystem->exists(m_file.c_str());
}

const int
FileInfoInternal::fileSize() const
{
        return m_fileSystem->fileSizeInBytes(m_file.c_str());
}
//======================================================================================================================
//
//======================================================================================================================
FileInfo::FileInfo()
{
        *this = FileInfo("");
}

FileInfo::FileInfo(const std::string& file)
{
        *this = FileInfo(file, std::make_shared<FileSystem>());
}

FileInfo::FileInfo(const FileInfo& copy)
{
        std::shared_ptr<FileInfoInternal> copyImpl(new FileInfoInternal(*copy.m_impl));
        prism::swap(this->m_impl, copyImpl);
}

FileInfo::FileInfo(const std::string& file, std::shared_ptr<AbstractFileSystem> fileSystem)
: m_impl{new FileInfoInternal(file, fileSystem)}
{}

FileInfo&
FileInfo::operator=(const FileInfo& rhs)
{
        std::shared_ptr<FileInfoInternal> copyImpl(new FileInfoInternal(*rhs.m_impl));
        prism::swap(this->m_impl, copyImpl);
        return *this;
}

void
FileInfo::setFile(const std::string& file)
{
        m_impl->setFile(file);
}

const bool
FileInfo::exists() const
{
        return m_impl->fileExists();
}

const int
FileInfo::size() const
{
        return m_impl->fileSize();
}

const std::string
FileInfo::file() const
{
        return m_impl->file();
}

const std::string
FileInfo::filename() const
{
        return m_impl->fileProperty(FileProperty::Property::Filename);
}

const std::string
FileInfo::basename() const
{
        return m_impl->fileProperty(FileProperty::Property::Basename);
}

const std::string
FileInfo::suffix() const
{
        return m_impl->fileProperty(FileProperty::Property::Suffix);
}

const std::string
FileInfo::entireSuffix() const
{
        return m_impl->fileProperty(FileProperty::Property::EntireSuffix);
}

const std::string
FileInfo::entireBasename() const
{
        return m_impl->fileProperty(FileProperty::Property::EntireBasename);
}

const std::string
FileInfo::absolutePath() const
{
        return m_impl->fileProperty(FileProperty::Property::AbsolutePath);
}

const std::string
FileInfo::absolutePathWithFilename() const
{
        std::string ret{};
        if (exists())
        {
                ret = absolutePath() + std::string("/") + filename();
        }
        return toNormalizedSeparators(ret);
}

const std::string
FileInfo::canonicalFilePath() const
{
        return m_impl->fileProperty(FileProperty::Property::CanonicalFilePath);
}

PRISM_END_NAMESPACE
