#pragma once

#include "package.hpp"
#include <string>
#include <stdexcept>


class PackageManager {
private:
    ISet<Package> installed_packages;

    [[nodiscard]] bool checkDependencies(const Package& package) const {
        for (const auto& dep : package.dependencies) {
            bool found = false;
            for (const auto& installed_pair : installed_packages) {
                if (installed_pair.first.name == dep) {
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
            throw std::runtime_error("Package already installed");
        }

        if (!checkDependencies(package)) {
            throw std::runtime_error("Dependencies not satisfied");
        }

        for (const auto& installed_pair : installed_packages) {
            if (installed_pair.first.name == package.name &&
                installed_pair.first.version < package.version) {
                installed_packages.remove(installed_pair.first);
                break;
            }
        }

        installed_packages.add(package);
    }

    void remove(const Package& package) {
        for (const auto& installed_pair : installed_packages) {
            for (const auto& dep : installed_pair.first.dependencies) {
                if (dep == package.name) {
                    throw std::runtime_error("Package is required by other packages");
                }
            }
        }

        installed_packages.remove(package);
    }

    [[nodiscard]] bool isInstalled(const Package& package) const {
        return installed_packages.contains(package);
    }

    [[nodiscard]] const ISet<Package>& getInstalledPackages() const {
        return installed_packages;
    }

    Package* findPackage(const std::string& name) {
        for (const auto& package_pair : installed_packages) {
            if (package_pair.first.name == name) {
                return const_cast<Package*>(&package_pair.first);
            }
        }
        return nullptr;
    }

    size_t size() {
        return installed_packages.size();
    }

    static void printPackageInfo(const Package& pkg);

    static void printInstalledPackages(const PackageManager& pm);
};