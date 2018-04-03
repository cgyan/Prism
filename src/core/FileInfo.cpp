#include <prism/global>
#include <prism/FileInfo>
#include <prism/FileSystemFactory>
#include <prism/AbstractFileSystem>
#include <prism/algorithm>
#include <prism/Vector>
#include <sstream>
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
        m_filename = prism::convertPathToUnixSeparators(filename);
}

void
FileInfo::setFile(const std::string& filename)
{
        m_filename = prism::convertPathToUnixSeparators(filename);
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
        return FileSystemFactory::get()->getFileSystem()->fileSizeInBytes(m_filename.c_str());

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

const std::string
FileInfo::absolutePath() const
{
        if (m_filename == "") return std::string{};
        return FileSystemFactory::get()->getFileSystem()->absolutePath(m_filename);
}

Vector<std::string>
FileInfo::split(const std::string& filePath, const char delim) const
{
        Vector<std::string> tokens;
        std::stringstream ss(filePath);
        std::string token;
        while(std::getline(ss, token, delim))
                tokens.append(token);
        return tokens;
}

Stack<std::string>
FileInfo::removeDotAndDoubleDotComponents(Vector<std::string> * tokens) const
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
FileInfo::buildCanonicalString(Stack<std::string>& stack) const
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
FileInfo::canonicalFilePath() const
{
        Vector<std::string> tokens = split(m_filename, '/');
        Stack<std::string> stack = removeDotAndDoubleDotComponents(&tokens);
        return buildCanonicalString(stack);
}

PRISM_END_NAMESPACE
