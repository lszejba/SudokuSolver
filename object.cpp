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
//        std::cout << "&&& Object " << printObject() << " added owner " << it->printObject() << std::endl;
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
//    if (ObjectManager::m_instance == NULL) {
//        ObjectManager::m_instance = new ObjectManager();
//    }

//    return ObjectManager::m_instance;
}

void ObjectManager::addObject(Object *object) {
//    std::cout << "... addObject" << std::endl;
    if (object == NULL) {
        return;
    }

    if (m_isProcessed) {    
        for (auto it : m_nextObjects) {
            if (it == object) {
                return;
            }
        }
//        std::cout << "... ... nextObjects" << std::endl;
        m_nextObjects.push_back(object);
    } else {
        for (auto it : m_objects) {
            if (it == object) {
                return;
            }
        }
//        std::cout << "... ... objects" << std::endl;
        m_objects.push_back(object);
    }
}

bool ObjectManager::signalAllObjects() {
//    std::cout << "... signalAllObjects()" << std::endl;
    if (m_objects.empty()) {
        return false;
    }
//    std::cout << "... ... size(" << std::to_string(m_objects.size()) << ")" << std::endl;
    m_isProcessed = true;
    std::cout << "&&& cleanup phase" << std::endl;
    for (auto it : m_objects) {
//        std::cout << "... performOwnerFunction" << std::endl;
//        std::cout << "... ..." << &it << std::endl;
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