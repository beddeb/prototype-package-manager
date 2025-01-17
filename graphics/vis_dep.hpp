#pragma once

#include "../include/package_manager.hpp"
#include <SFML/Graphics.hpp>
#include <map>
#include <vector>


class DependencyVisualizer {
public:
    DependencyVisualizer(PackageManager& pm);

    void run();

private:
    PackageManager& packageManager;
    sf::RenderWindow window;
    std::map<std::string, sf::Vector2f> packagePositions;
    float nodeRadius;
    float horizontalSpacing;
    float verticalSpacing;
    sf::Font font;

    void initializePositions();
    void drawDependencies();
    void drawPackages();
    void handleEvents();
    sf::Vector2f calculateNodePosition(int level, int index, int totalNodesInLevel);
    int getMaxDependencyDepth() const;
};