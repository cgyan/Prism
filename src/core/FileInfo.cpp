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
        FileInfoInternal(const std::string& filename, std::shared_ptr<AbstractFileSystem> fileSystem);

        Vector<std::string> split(const std::string& filePath, const char delim) const;
        Stack<std::string> removeDotAndDoubleDotComponents(Vector<std::string> * tokens) const;
        const std::string buildCanonicalString(Stack<std::string>& stack) const;
        std::shared_ptr<AbstractFileSystem> fileSystem() const;
        const std::string filename() const;
private:
        std::shared_ptr<AbstractFileSystem> m_fileSystem{nullptr};
        std::string m_filename{""};
};

FileInfoInternal::FileInfoInternal(const std::string& filename, std::shared_ptr<AbstractFileSystem> fileSystem)
: m_filename{convertPathToUnixSeparators(filename)},
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
FileInfoInternal::filename() const
{
        return m_filename;
}
//======================================================================================================================
//
//======================================================================================================================
FileInfo::FileInfo()
{
        *this = FileInfo("");
}

FileInfo::FileInfo(const std::string& filename)
{
        *this = FileInfo(filename, std::make_shared<FileSystem>());
}

FileInfo::FileInfo(const std::string& filename, std::shared_ptr<AbstractFileSystem> fileSystem)
: m_impl{new FileInfoInternal(filename, fileSystem)}
{}

void
FileInfo::setFile(const std::string& filename)
{
        *this = FileInfo(filename, m_impl->fileSystem());
}

const bool
FileInfo::exists() const
{
        return m_impl->fileSystem()->exists(m_impl->filename().c_str());
}

const int
FileInfo::size() const
{
        return m_impl->fileSystem()->fileSizeInBytes(m_impl->filename().c_str());
}

const std::string
FileInfo::filename() const
{
        size_t pos = m_impl->filename().find_last_of("/");
        return m_impl->filename().substr(pos+1);
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
        const size_t pos = m_impl->filename().find_last_of(".");
        if (pos == std::string::npos) return "";
        return m_impl->filename().substr(pos+1);
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

const std::string
FileInfo::absolutePath() const
{
        if (m_impl->filename() == "") return std::string{};
        return m_impl->fileSystem()->absolutePath(m_impl->filename());
}

const std::string
FileInfo::canonicalFilePath() const
{
        Vector<std::string> tokens = m_impl->split(m_impl->filename(), '/');
        Stack<std::string> stack = m_impl->removeDotAndDoubleDotComponents(&tokens);
        return m_impl->buildCanonicalString(stack);
}

PRISM_END_NAMESPACE
