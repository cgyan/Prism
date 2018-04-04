#include <prism/global>
#include <prism/FileInfo>
#include <prism/AbstractFileSystem>
#include <prism/FileSystem>
#include <prism/Vector>
#include <prism/Stack>
#include <prism/algorithm>
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
class FileInfoInternal
{
public:
        enum class Property { Filename, Basename, Suffix, EntireSuffix, EntireBasename, AbsolutePath, CanonicalFilePath };
public:
        FileInfoInternal(const std::string& file, std::shared_ptr<AbstractFileSystem> fileSystem);

        Vector<std::string> split(const std::string& filePath, const char delim) const;
        Stack<std::string> removeDotAndDoubleDotComponents(Vector<std::string> * tokens) const;
        const std::string buildCanonicalString(Stack<std::string>& stack) const;
        std::shared_ptr<AbstractFileSystem> fileSystem() const;
        const std::string file() const;
        const bool fileExists() const;
        const int fileSize() const;
        const std::string fileProperty(Property property) const;
private:
        const std::string absolutePath() const;
        const std::string filename() const;
        const std::string basename() const;
        const std::string suffix() const;
        const std::string entireSuffix() const;
        const std::string entireBasename() const;
        const std::string canonicalFilePath() const;

private:
        std::shared_ptr<AbstractFileSystem> m_fileSystem{nullptr};
        std::string m_file{""};
};

const std::string
FileInfoInternal::fileProperty(FileInfoInternal::Property property) const
{
        switch (property)
        {
                case Property::Filename: return filename(); break;
                case Property::Basename: return basename(); break;
                case Property::Suffix: return suffix(); break;
                case Property::EntireSuffix: return entireSuffix(); break;
                case Property::EntireBasename: return entireBasename(); break;
                case Property::AbsolutePath: return absolutePath(); break;
                case Property::CanonicalFilePath: return canonicalFilePath(); break;
        }
}

FileInfoInternal::FileInfoInternal(const std::string& file, std::shared_ptr<AbstractFileSystem> fileSystem)
: m_file{convertPathToUnixSeparators(file)},
  m_fileSystem{fileSystem}
{}

Vector<std::string>
FileInfoInternal::split(const std::string& filePath, const char delim) const
{
        Vector<std::string> tokens;
        std::stringstream ss(filePath);
        std::string token;
        while(std::getline(ss, token, delim))
                tokens.append(token);
        return tokens;
}

Stack<std::string>
FileInfoInternal::removeDotAndDoubleDotComponents(Vector<std::string> * tokens) const
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
FileInfoInternal::buildCanonicalString(Stack<std::string>& stack) const
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

std::shared_ptr<AbstractFileSystem>
FileInfoInternal::fileSystem() const
{
        return m_fileSystem;
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

const std::string
FileInfoInternal::absolutePath() const
{
        return m_fileSystem->absolutePath(m_file.c_str());
}

const std::string
FileInfoInternal::filename() const
{
        size_t pos = m_file.find_last_of("/");
        return m_file.substr(pos+1);
}

const std::string
FileInfoInternal::basename() const
{
        std::string ret = filename();
        const size_t pos = ret.find_first_of(".");
        return ret.substr(0, pos);
}

const std::string
FileInfoInternal::suffix() const
{
        const size_t pos = m_file.find_last_of(".");
        if (pos == std::string::npos) return "";
        return m_file.substr(pos+1);
}

const std::string
FileInfoInternal::entireSuffix() const
{
        std::string ret = filename();
        const size_t pos = ret.find_first_of(".");
        if (pos == std::string::npos) return "";
        return ret.substr(pos+1);
}

const std::string
FileInfoInternal::entireBasename() const
{
        std::string ret = filename();
        const size_t pos = ret.find_last_of(".");
        return ret.substr(0, pos);
}

const std::string
FileInfoInternal::canonicalFilePath() const
{
        Vector<std::string> tokens = split(m_file, '/');
        Stack<std::string> stack = removeDotAndDoubleDotComponents(&tokens);
        return buildCanonicalString(stack);
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
        *this = FileInfo(file, m_impl->fileSystem());
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
