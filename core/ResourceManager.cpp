/* 
 * File:   ResourceManager.cpp
 * Author: kdubovikov
 * 
 * Created on November 30, 2014, 5:47 PM
 */

#include "ResourceManager.h"

template<class T>
void ResourceManager<T>::addResource(const std::string& key, const T& value) {
    resourceMap[key] = value;
}

template<class T>
T& ResourceManager<T>::getResource(const std::string& key) {
    return resourceMap[key];
}

template<class T>
void ResourceManager<T>::forEach(std::function<void (T)> action) {
    for (auto const& kv : resourceMap) {
        action(kv.second);
    }
}


// should directly all needed template types tell to compiler so it would build them
// see http://stackoverflow.com/questions/8752837/undefined-reference-to-template-class-constructor
template class ResourceManager<unsigned int>;


