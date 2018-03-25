#ifndef PRISM_FILE_SYSTEM_FACTORY_H_
#define PRISM_FILE_SYSTEM_FACTORY_H_

#include <prism/global>
#include <prism/FileSystem>

PRISM_BEGIN_NAMESPACE

class FileSystemFactory {
public:
        using AbstractFileSystemFn = AbstractFileSystem*(*)(void);
public:
        static FileSystemFactory * get()
        {
                static FileSystemFactory instance;
                return &instance;
        }

        FileSystemFactory()
        {
                setFileSystem(&FileSystem::create);
        }

        void setFileSystem(AbstractFileSystemFn func)
        {
                m_func = func;
        }

        AbstractFileSystem * getFileSystem()
        {
                return m_func();
        }
private:
        AbstractFileSystemFn m_func;
};

PRISM_END_NAMESPACE

#endif
