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
convertPathToUnixSeparators(const std::string& path) {
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
        enum class Property { Filename, Basename, Suffix, EntireSuffix, EntireBasename, AbsolutePath, CanonicalFilePath };
public:
        FileInfoInternal(const std::string& file, std::shared_ptr<AbstractFileSystem> fileSystem);

        void setFile(const std::string& file);
        const std::string file() const;
        const bool fileExists() const;
        const int fileSize() const;
        const std::string fileProperty(Property property) const;
private:
        std::shared_ptr<AbstractFileSystem> m_fileSystem{nullptr};
        std::string m_file{""};
};

const std::string
FileInfoInternal::fileProperty(FileInfoInternal::Property property) const
{
        switch (property)
        {
                case Property::Filename: return FileProperty::filename(m_file); break;
                case Property::Basename: return FileProperty::basename(m_file); break;
                case Property::EntireSuffix: return FileProperty::entireSuffix(m_file); break;
                case Property::Suffix: return FileProperty::suffix(m_file); break;
                case Property::EntireBasename: return FileProperty::entireBasename(m_file); break;
                case Property::AbsolutePath: return FileProperty::absolutePath(m_file, m_fileSystem); break;
                case Property::CanonicalFilePath: return FileProperty::canonicalFilePath(m_file); break;
        }
}

FileInfoInternal::FileInfoInternal(const std::string& file, std::shared_ptr<AbstractFileSystem> fileSystem)
: m_file{convertPathToUnixSeparators(file)},
  m_fileSystem{fileSystem}
{}

void
FileInfoInternal::setFile(const std::string& file)
{
        m_file = convertPathToUnixSeparators(file);
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

FileInfo::FileInfo(const std::string& file, std::shared_ptr<AbstractFileSystem> fileSystem)
: m_impl{new FileInfoInternal(file, fileSystem)}
{}

void
FileInfo::setFile(const std::string& file)
{
        // *this = FileInfo(file, m_impl->fileSystem());
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
FileInfo::filename() const
{
        return m_impl->fileProperty(FileInfoInternal::Property::Filename);
}

const std::string
FileInfo::basename() const
{
        return m_impl->fileProperty(FileInfoInternal::Property::Basename);
}

const std::string
FileInfo::suffix() const
{
        return m_impl->fileProperty(FileInfoInternal::Property::Suffix);
}

const std::string
FileInfo::entireSuffix() const
{
        return m_impl->fileProperty(FileInfoInternal::Property::EntireSuffix);
}

const std::string
FileInfo::entireBasename() const
{
        return m_impl->fileProperty(FileInfoInternal::Property::EntireBasename);
}

const std::string
FileInfo::absolutePath() const
{
        if (m_impl->file() == "") return std::string{};
        return m_impl->fileProperty(FileInfoInternal::Property::AbsolutePath);
}

const std::string
FileInfo::canonicalFilePath() const
{
        return m_impl->fileProperty(FileInfoInternal::Property::CanonicalFilePath);
}

PRISM_END_NAMESPACE
