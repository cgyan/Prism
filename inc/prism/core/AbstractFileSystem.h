#ifndef PRISM_ABSTRACT_FILE_SYSTEM_H_
#define PRISM_ABSTRACT_FILE_SYSTEM_H_

#include <prism/global>
#include <string>

PRISM_BEGIN_NAMESPACE

class AbstractFileSystem {
public:
        virtual ~AbstractFileSystem() {}
        
        virtual const bool exists(const std::string&) const = 0;
        virtual const int fileSizeInBytes(const std::string&) const = 0;
        virtual const std::string absolutePath(const std::string&) const = 0;
};

PRISM_END_NAMESPACE

#endif
