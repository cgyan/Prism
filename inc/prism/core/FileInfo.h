#ifndef PRISM_FILE_INFO_H_
#define PRISM_FILE_INFO_H_

#include <prism/global>

PRISM_BEGIN_NAMESPACE

class FileInfo {
public:
        FileInfo() = default;
        FileInfo(const char * filename);

        void setFile(const char * filename);
        const bool exists() const;
private:
        const char * m_filename{""};
};

PRISM_END_NAMESPACE

#endif
