#ifndef PRISM_FILE_SYSTEM_H_
#define PRISM_FILE_SYSTEM_H_

#include <prism/global>
#include <prism/AbstractFileSystem>

PRISM_BEGIN_NAMESPACE

class FileSystem : public AbstractFileSystem {
public:
        static AbstractFileSystem * create();
        void createFile(const char * filename) override;
        const bool exists(const char * filename) const override;
};

PRISM_END_NAMESPACE

#endif
