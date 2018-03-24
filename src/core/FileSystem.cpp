#include <prism/global>
#include <prism/FileSystem>
#ifdef _WIN32
#       include <windows.h>
#       include <io.h>
#endif

PRISM_BEGIN_NAMESPACE

AbstractFileSystem *
FileSystem::create() {
        static FileSystem instance;
        return &instance;
}

void
FileSystem::createFile(const char * filename) {

}

const bool
FileSystem::exists(const char * filename) const {
        #ifdef _WIN32
        #       define access _access_s
        #endif

        return access(filename, 0) == 0;
}

PRISM_END_NAMESPACE
