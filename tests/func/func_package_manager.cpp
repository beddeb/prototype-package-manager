#include <iostream>
#include <cassert>
#include "func_package_manager.hpp"


void testInstall() {
    PackageManager pm;
    Package pkg1("pkg1", Version(1, 0, 0));
    pm.install(pkg1);
    assert(("Install_pkg", pm.isInstalled(pkg1)));
    assert(("Install_size", pm.size() == 1));
}


void testInstallWithDependencies() {
    PackageManager pm;
    Package pkg1("pkg1", Version(1, 0, 0));
    Package pkg2("pkg2", Version(1, 0, 0));
    pkg2.dependencies.add("pkg1");

    pm.install(pkg1);
    pm.install(pkg2);

    assert(("InstallWithDependencies_pkg_1", pm.isInstalled(pkg1)));
    assert(("InstallWithDependencies_pkg_2", pm.isInstalled(pkg2)));
    assert(("InstallWithDependencies_size", pm.size() == 2));
}


void testInstallDuplicate() {
    PackageManager pm;
    Package pkg1("pkg1", Version(1, 0, 0));
    pm.install(pkg1);
    try {
        pm.install(pkg1);
        assert(("InstallDuplicate_install", false));
    } catch (const std::runtime_error &e) {
        assert(("InstallDuplicate_OK", e.what()));
    }
}

void testInstallUnsatisfiedDependencies() {
    PackageManager pm;
    Package pkg1("pkg1", Version(1, 0, 0));
    Package pkg2("pkg2", Version(1, 0, 0));
    pkg1.dependencies.add("pkg2");
    try {
        pm.install(pkg1);
        assert(("InstallUnsatisfiedDependencies_install", false));
    } catch (const std::runtime_error &e) {
        assert(("InstallUnsatisfiedDependencies_OK", std::string(e.what()) == "Dependencies not satisfied"));
    }
}


void testRemove() {
    PackageManager pm;
    Package pkg1("pkg1", Version(1, 0, 0));
    pm.install(pkg1);
    pm.remove(pkg1);
    assert(("Remove_is_installed", !pm.isInstalled(pkg1)));
    assert(("Remove_size", pm.size() == 0));
}

void testRemoveDependency() {
    PackageManager pm;
    Package pkg1("pkg1", Version(1, 0, 0));
    Package pkg2("pkg2", Version(1, 0, 0));
    pkg2.dependencies.add("pkg1");

    pm.install(pkg1);
    pm.install(pkg2);

    try {
        pm.remove(pkg1);
        assert(("RemoveDependency_remove", false));
    } catch (const std::runtime_error &e) {
        assert(("RemoveDependency_OK", std::string(e.what()) == "Package is required by other packages"));
    }
}

void testIsInstalled() {
    PackageManager pm;
    Package pkg1("pkg1", Version(1, 0, 0));
    assert(("IsInstalled_is_installed_NOT", !pm.isInstalled(pkg1)));
    pm.install(pkg1);
    assert(("IsInstalled_is_installed_OK", pm.isInstalled(pkg1)));
}

void testGetInstalledPackages() {
    PackageManager pm;
    Package pkg1("pkg1", Version(1, 0, 0));
    pm.install(pkg1);
    const ISet<Package> &packages = pm.getInstalledPackages();
    assert(("GetInstalledPackages_contains", packages.contains(pkg1)));
    assert(("GetInstalledPackages_size", packages.size() == 1));
}

void testFindPackage() {
    PackageManager pm;
    Package pkg1("pkg1", Version(1, 0, 0));
    pm.install(pkg1);
    Package *found = pm.findPackage("pkg1");
    assert(("FindPackage_ptr", found != nullptr));
    assert(("FindPackage_pkg", *found == pkg1));

    found = pm.findPackage("pkg2");
    assert(("FindPackage_NOT_pkg", found == nullptr));
}

void testSize() {
    PackageManager pm;
    assert(("Size_size_0", pm.size() == 0));

    Package pkg1("pkg1", Version(1, 0, 0));
    pm.install(pkg1);
    assert(("Size_size_1", pm.size() == 1));
}

void testPackageManager() {
    testInstall();
    testInstallWithDependencies();
    testInstallDuplicate();
    testInstallUnsatisfiedDependencies();
    testRemove();
    testRemoveDependency();
    testIsInstalled();
    testGetInstalledPackages();
    testFindPackage();
    testSize();

    std::cout << "All tests passed! (PackageManager)" << std::endl;
}