#include "object.hpp"
#include <iostream>

void Object::addOwner(Object *owner) {
    if (owner == NULL) {
        return;
    }
    for (auto it : m_owners) {
        if (it == owner) {
            return;
        }
    }

    m_owners.push_back(owner);
}

void Object::signalOwners() {
    for (auto it : m_owners) {
        ObjectManager::getInstance().addObject(it);
    }
}

bool Object::ownersSetToChange() {
    for (auto it : m_owners) {
        if ((ObjectManager::getInstance()).isObjectSetToChange(it)) {
            return true;
        }
    }

    return false;
}


ObjectManager& ObjectManager::getInstance() {
    static ObjectManager instance;
    return instance;
}

void ObjectManager::addObject(Object *object) {
    if (object == NULL) {
        return;
    }

    if (m_isProcessed) {    
        for (auto it : m_nextObjects) {
            if (it == object) {
                return;
            }
        }
        m_nextObjects.push_back(object);
    } else {
        for (auto it : m_objects) {
            if (it == object) {
                return;
            }
        }
        m_objects.push_back(object);
    }
}

bool ObjectManager::signalAllObjects() {
    if (m_objects.empty()) {
        return false;
    }
    m_isProcessed = true;
    std::cout << "&&& cleanup phase" << std::endl;
    for (auto it : m_objects) {
        it->performCleanup();
    }
    for (auto it : m_objects) {
        it->performSetting();
    }
    m_isProcessed = false;
    std::cout << "&&& after signalAllObjects cleanup, objects count: " << std::to_string(m_objects.size()) << ", nextObjects count: " << std::to_string(m_nextObjects.size()) << std::endl;
    m_objects.erase(m_objects.begin(), m_objects.end());
    std::move(m_nextObjects.begin(), m_nextObjects.end(), back_inserter(m_objects));
    m_nextObjects.erase(m_nextObjects.begin(), m_nextObjects.end());
    return true;
}

bool ObjectManager::isObjectSetToChange(Object *obj) {
    for (auto it : m_nextObjects) {
        if (it == obj) {
            return true;
        }
    }

    return false;
}