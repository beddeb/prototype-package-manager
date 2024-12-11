#pragma once

#include "../../include/package_manager.hpp"


void testInstall();

void testInstallWithDependencies();

void testInstallDuplicate();

void testInstallUnsatisfiedDependencies();

void testRemove();

void testRemoveDependency();

void testIsInstalled();

void testGetInstalledPackages();

void testFindPackage();

void testSize();

void testPackageManager();