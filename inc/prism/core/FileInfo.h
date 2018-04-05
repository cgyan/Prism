#ifndef PRISM_FILE_INFO_H_
#define PRISM_FILE_INFO_H_

#include <prism/global>
#include <memory>

PRISM_BEGIN_NAMESPACE

class FileInfoInternal;
class AbstractFileSystem;
class string;

class FileInfo {
public:
        FileInfo();
        FileInfo(const std::string& file);
        FileInfo(const FileInfo& copy);
        FileInfo& operator=(const FileInfo& rhs);

        // internal
        FileInfo(const std::string& file, std::shared_ptr<AbstractFileSystem> fileSystem);

        void setFile(const std::string& file);
        const bool exists() const;
        const int size() const;

        const std::string filePath() const;
        const std::string filename() const;
        const std::string basename() const;
        const std::string suffix() const;
        const std::string entireSuffix() const;
        const std::string entireBasename() const;
        const std::string absolutePath() const;
        const std::string canonicalFilePath() const;
private:
        std::shared_ptr<FileInfoInternal> m_impl{nullptr};
};

PRISM_END_NAMESPACE

#endif
