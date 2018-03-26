#ifndef PRISM_ABSTRACT_FILE_SYSTEM_H_
#define PRISM_ABSTRACT_FILE_SYSTEM_H_

#include <prism/global>
#include <string>

PRISM_BEGIN_NAMESPACE

class AbstractFileSystem {
public:
        virtual ~AbstractFileSystem() {}
        virtual void createFile(const std::string& filename) = 0;
        virtual const bool exists(const std::string& filename) const = 0;
        virtual const unsigned int fileSizeInBytes(const std::string& filename) const = 0;
};

PRISM_END_NAMESPACE

#endif
