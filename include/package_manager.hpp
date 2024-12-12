#pragma once

#include "package.hpp"
#include "iset.hpp"
#include <string>
#include <stdexcept>
#include <fstream>


class PackageManager {
private:
    ISet<Package> installed_packages;

    [[nodiscard]] bool checkDependencies(const Package& package) const {
        for (const auto& dep : package.dependencies) {
            bool found = false;
            for (const auto& installed_pair : installed_packages) {
                if (installed_pair.name == dep) {
                    found = true;
                    break;
                }
            }
            if (!found) return false;
        }
        return true;
    }

public:
    void install(const Package& package) {
        if (installed_packages.contains(package)) {
            throw std::runtime_error("Package '" + package.name + "' with version " + std::to_string(package.version.major) + "." + std::to_string(package.version.minor) + "." + std::to_string(package.version.patch) + " is already installed.");
        }
        if (!checkDependencies(package)) {
            throw std::runtime_error("Dependencies not satisfied");
        }
        for (const auto& installed_pac : installed_packages) {
            if (installed_pac.name == package.name) {
                if (installed_pac.version < package.version) {
                    installed_packages.remove(installed_pac);
                    break;
                } else if (installed_pac.version > package.version) {
                    throw std::runtime_error("Is already a package with a newer version");
                }
            }
        }
        installed_packages.add(package);
    }

    void remove(const Package& package) {
        for (const auto& installed_pac : installed_packages) {
            for (const auto& dep : installed_pac.dependencies) {
                if (dep == package.name) {
                    throw std::runtime_error("Package is required by other packages");
                }
            }
        }
        if (installed_packages.contains(package)){
            installed_packages.remove(package);
        } else {
            throw std::runtime_error("Package '" + package.name + "' with version " + std::to_string(package.version.major) + "." + std::to_string(package.version.minor) + "." + std::to_string(package.version.patch) + " is not installed.");
        }

    }

    [[nodiscard]] bool isInstalled(const Package& package) const {
        return installed_packages.contains(package);
    }

    [[nodiscard]] const ISet<Package>& getInstalledPackages() const {
        return installed_packages;
    }

    Package* findPackage(const std::string& name) {
        for (const auto& package_pair : installed_packages) {
            if (package_pair.name == name) {
                return const_cast<Package*>(&package_pair);
            }
        }
        return nullptr;
    }

    size_t size() {
        return installed_packages.size();
    }

    static void printPackageInfo(const Package& pkg);

    static void printInstalledPackages(const PackageManager& pm);

    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);

    static bool is_valid_name(const std::string& name);

};