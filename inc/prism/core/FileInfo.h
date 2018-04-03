#ifndef PRISM_FILE_INFO_H_
#define PRISM_FILE_INFO_H_

#include <prism/global>
#include <prism/Vector>
#include <prism/Stack>
#include <string>

PRISM_BEGIN_NAMESPACE

class FileInfo {
public:
        FileInfo() = default;
        FileInfo(const std::string& filename);

        void setFile(const std::string& filename);
        const bool exists() const;
        const int size() const;
        const std::string filename() const;
        const std::string basename() const;
        const std::string suffix() const;
        const std::string entireSuffix() const;
        const std::string entireBasename() const;
        const std::string absolutePath() const;
        const std::string canonicalFilePath() const;
private:
        Vector<std::string> split(const std::string& filePath, const char delim) const;
        Stack<std::string> removeDotAndDoubleDotComponents(Vector<std::string> * tokens) const;
        const std::string buildCanonicalString(Stack<std::string>& stack) const;
private:
        std::string m_filename{""};
};

PRISM_END_NAMESPACE

#endif
