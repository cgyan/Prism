#include <prism/global>
#include <prism/algorithm>

PRISM_BEGIN_NAMESPACE

const std::string
FileSystem::convertToUnixSeparators(const std::string& path) const {
        std::string ret = path;
        prism::replace(ret.begin(), ret.end(), '\\', '/');
        return ret;
}

PRISM_END_NAMESPACE
