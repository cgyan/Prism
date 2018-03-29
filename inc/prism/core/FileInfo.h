#ifndef PRISM_FILE_INFO_H_
#define PRISM_FILE_INFO_H_

#include <prism/global>
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
private:
        void init(const std::string& filename);
private:
        std::string m_filename{""};
};

PRISM_END_NAMESPACE

#endif
