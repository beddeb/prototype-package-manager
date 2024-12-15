#pragma once

#include "iset.hpp"


struct Version {
    int major, minor, patch;

    explicit Version(int maj = 0, int min = 0, int p = 0)
            : major(maj), minor(min), patch(p) {}

    bool operator==(const Version &other) const {
        return major == other.major &&
               minor == other.minor &&
               patch == other.patch;
    }

    bool operator<(const Version &other) const {
        if (major != other.major) return major < other.major;
        if (minor != other.minor) return minor < other.minor;
        return patch < other.patch;
    }

    bool operator>(const Version &other) const {
        if (major != other.major) return major > other.major;
        if (minor != other.minor) return minor > other.minor;
        return patch > other.patch;
    }
};

struct Package {
    std::string name;
    Version version;
    Sequence<std::string> dependencies;

    explicit Package(const std::string &n = "", const Version &v = Version())
            : name(n), version(v) {}

    bool operator==(const Package &other) const {
        return name == other.name && version == other.version;
    }
};

namespace std {
    template<>
    struct hash<Package> {
        size_t operator()(const Package &p) const {
            return hash<string>()(p.name) ^
                   (hash<int>()(p.version.major) << 1) ^
                   (hash<int>()(p.version.minor) << 2) ^
                   (hash<int>()(p.version.patch) << 3);
        }
    };
}