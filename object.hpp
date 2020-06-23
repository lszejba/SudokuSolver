#ifndef __OBJECT_HPP__
#define __OBJECT_HPP__

#include <vector>
#include <string>

class Object {
    public:
        void addOwner(Object *owner);
        void signalOwners();
        virtual void performCleanup() {}
        virtual void performSetting() {}
//        virtual void performOwnerFunction() {}
        virtual std::string printObject() { return ""; }
        bool ownersSetToChange();
    private:
        std::vector<Object *> m_owners;
};

class ObjectManager {
    public:
        static ObjectManager& getInstance();
        ObjectManager(ObjectManager const&) = delete;
        void operator=(ObjectManager const&) = delete;
        void addObject(Object *object);
        bool signalAllObjects();
        bool isObjectSetToChange(Object *obj);
    private:
        ObjectManager() {}

//        static ObjectManager *m_instance;
        bool m_isProcessed;
        std::vector<Object *> m_objects;
        std::vector<Object *> m_nextObjects;
};

#endif