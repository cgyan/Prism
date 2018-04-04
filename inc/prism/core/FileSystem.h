#ifndef PRISM_FILE_SYSTEM_H_
#define PRISM_FILE_SYSTEM_H_

#include <prism/global>
#include <prism/AbstractFileSystem>
#include <string>

PRISM_BEGIN_NAMESPACE

class FileSystem : public AbstractFileSystem {
public:
        const bool exists(const std::string&) const override;
        const int fileSizeInBytes(const std::string&) const override;
        const std::string absolutePath(const std::string&) const override;
};

PRISM_END_NAMESPACE

#endif
