#ifndef PRISM_ABSTRACT_FILE_SYSTEM_H_
#define PRISM_ABSTRACT_FILE_SYSTEM_H_

#include <prism/global>

PRISM_BEGIN_NAMESPACE

class AbstractFileSystem {
public:
        virtual ~AbstractFileSystem() {}
        virtual void createFile(const char * filename) = 0;
        virtual const bool exists(const char * filename) const = 0;
        virtual const unsigned int fileSizeInBytes(const char * filename) const = 0;
};

PRISM_END_NAMESPACE

#endif
