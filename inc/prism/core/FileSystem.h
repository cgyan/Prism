#ifndef PRISM_FILE_SYSTEM_H_
#define PRISM_FILE_SYSTEM_H_

#include <prism/global>
#include <prism/AbstractFileSystem>
#include <string>

PRISM_BEGIN_NAMESPACE

class FileSystem : public AbstractFileSystem {
public:
        static AbstractFileSystem * create();
        void createFile(const std::string& filename) override;
        const bool exists(const std::string& filename) const override;
        const unsigned int fileSizeInBytes(const std::string& filename) const override;
};

PRISM_END_NAMESPACE

#endif
