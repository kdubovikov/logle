/* 
 * File:   ResourceManager.h
 * Author: kdubovikov
 *
 * Created on November 30, 2014, 5:47 PM
 */

#pragma once
#include <functional>
#include <unordered_map>

template <class T>
class ResourceManager {
private:
    std::unordered_map<std::string, T> resourceMap;
public:
    T& getResource(const std::string& key);
    void addResource(const std::string& key, const T& value);
    void forEach(std::function<void (T)> action);
};

