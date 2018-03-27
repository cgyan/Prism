#ifndef PRISM_FILE_SYSTEM_H_
#define PRISM_FILE_SYSTEM_H_

#include <prism/global>
#include <prism/AbstractFileSystem>
#include <string>

PRISM_BEGIN_NAMESPACE

class FileSystem : public AbstractFileSystem {
public:
        static AbstractFileSystem * create() {
                static FileSystem instance;
                return &instance;
        }

        void createFile(const std::string& filename) override;
        const bool exists(const std::string& filename) const override;
        const int fileSizeInBytes(const std::string& filename) const override;
private:
        FileSystem() = default;
        FileSystem(const FileSystem& other) = default;
        FileSystem& operator=(const FileSystem& rhs) = default;
};

PRISM_END_NAMESPACE

#endif
