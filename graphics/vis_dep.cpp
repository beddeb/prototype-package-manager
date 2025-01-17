#include "vis_dep.hpp"
#include <queue>
#include <algorithm>
#include <functional>


DependencyVisualizer::DependencyVisualizer(PackageManager& pm)
        : packageManager(pm),
          window(sf::VideoMode(1200, 800), "Package Dependencies"),
          nodeRadius(30.0f),
          horizontalSpacing(150.0f),
          verticalSpacing(100.0f)
{
    if (!font.loadFromFile("../externallibs/font.ttf")) {
        throw std::runtime_error("Could not load font");
    }
    initializePositions();
}

void DependencyVisualizer::run() {
    while (window.isOpen()) {
        handleEvents();
        window.clear(sf::Color::White);
        drawDependencies();
        drawPackages();
        window.display();
    }
}

void DependencyVisualizer::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}

int DependencyVisualizer::getMaxDependencyDepth() const {
    int maxDepth = 0;

    std::function<int(const std::string&, int)> getDepth =
            [&](const std::string& packageName, int currentDepth) {
                Package* package = packageManager.findPackage(packageName);
                if (!package) {
                    return currentDepth;
                }

                int maxSubDepth = currentDepth;
                for (const std::string& depName : package->dependencies) {
                    maxSubDepth = std::max(maxSubDepth, getDepth(depName, currentDepth + 1));
                }
                return maxSubDepth;
            };

    for (const auto& package : packageManager.getInstalledPackages()) {
        bool isRoot = true;
        for(const auto& other : packageManager.getInstalledPackages()) {
            if (other.dependencies.contains(package.name)) {
                isRoot = false;
                break;
            }
        }
        if (isRoot) {
            maxDepth = std::max(maxDepth, getDepth(package.name, 0));
        }

    }
    return maxDepth;
}


sf::Vector2f DependencyVisualizer::calculateNodePosition(int level, int index, int totalNodesInLevel)
{
    float x = (window.getSize().x / (float)(totalNodesInLevel + 1)) * (index + 1);
    float y = (level + 1) * verticalSpacing;
    return sf::Vector2f(x, y);
}


void DependencyVisualizer::initializePositions() {
    packagePositions.clear();

    std::vector<std::string> rootPackages;
    for (const auto& package : packageManager.getInstalledPackages()) {
        bool isRoot = true;
        for (const auto& otherPackage : packageManager.getInstalledPackages()) {
            if (otherPackage.dependencies.contains(package.name)) {
                isRoot = false;
                break;
            }
        }
        if (isRoot) {
            rootPackages.push_back(package.name);
        }
    }

    std::queue<std::pair<std::string, int>> q;
    std::map<int, std::vector<std::string>> levelMap;

    for (const auto& rootName : rootPackages) {
        q.push({rootName, 0});
        levelMap[0].push_back(rootName);
    }


    while (!q.empty()) {
        std::string currentPackageName = q.front().first;
        int currentLevel = q.front().second;
        q.pop();

        Package* currentPackage = packageManager.findPackage(currentPackageName);
        if (!currentPackage) continue; // Should not happen

        for (const std::string& depName : currentPackage->dependencies)
        {
            if(packagePositions.find(depName) == packagePositions.end())
            {
                q.push({depName, currentLevel + 1});
                levelMap[currentLevel + 1].push_back(depName);
            }
        }
    }

    for (const auto& [level, packages] : levelMap) {
        int numPackages = packages.size();
        for (size_t i = 0; i < numPackages; ++i)
        {
            packagePositions[packages[i]] = calculateNodePosition(level, i, numPackages);
        }

    }

}


void DependencyVisualizer::drawDependencies() {
    for (const auto& package : packageManager.getInstalledPackages()) {
        if (packagePositions.find(package.name) == packagePositions.end()) continue;

        sf::Vector2f startPos = packagePositions[package.name];

        for (const std::string& depName : package.dependencies) {
            if (packagePositions.find(depName) != packagePositions.end()) {
                sf::Vector2f endPos = packagePositions[depName];
                sf::Vertex line[] = {
                        sf::Vertex(startPos + sf::Vector2f(nodeRadius, nodeRadius), sf::Color::Blue),
                        sf::Vertex(endPos + sf::Vector2f(nodeRadius, nodeRadius), sf::Color::Blue)
                };
                window.draw(line, 2, sf::Lines);
            }
        }
    }
}

void DependencyVisualizer::drawPackages() {
    for (const auto& [packageName, pos] : packagePositions) {
        Package* package = packageManager.findPackage(packageName);
        if (!package) continue;

        sf::CircleShape node(nodeRadius);
        node.setPosition(pos);
        node.setFillColor(sf::Color::Green);
        node.setOutlineThickness(2);
        node.setOutlineColor(sf::Color::Black);
        window.draw(node);

        sf::Text text(package->name + " (" + std::to_string(package->version.major) + "." +
                      std::to_string(package->version.minor) + "." +
                      std::to_string(package->version.patch) + ")", font, 16);

        text.setPosition(pos.x + nodeRadius - text.getLocalBounds().width / 2, pos.y + nodeRadius - text.getLocalBounds().height / 2);
        text.setFillColor(sf::Color::Black);
        window.draw(text);
    }
}