#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
using namespace std;

class Component;
class Entity;
class Manager;


// these two inline function is for compile-time ID generation
// assign a unique ID to every type T
using ComponentID = size_t;
using Group = size_t;
inline ComponentID getUniqueComponentTypeID() noexcept {
    static ComponentID lastID = 0u;
    return lastID++;
}
template <typename T> inline ComponentID getComponentTypeID() noexcept {
    static_assert (is_base_of<Component, T>::value, "");
    static ComponentID typeID = getUniqueComponentTypeID();
    return typeID;
}

constexpr size_t maxComponents = 32;
constexpr size_t maxGroups = 32;

using ComponentBitSet = bitset<maxComponents>;
using GroupBitSet = bitset<maxGroups>;

using ComponentArray = array<Component*, maxComponents>;

class Component {

public :
    Entity* entity;
    virtual void init() {}
    virtual void update() {}
    virtual void draw() {}
    virtual ~Component() {}

};

class Entity {

private :
    Manager& manager;
    bool active = true;
    vector<unique_ptr<Component>> components;
    ComponentArray componentArray;
    ComponentBitSet componentBitSet;
    GroupBitSet groupBitSet;

public :
    Entity(Manager& mManager) : manager(mManager) {}
    void update() { for (auto& c : components) c->update(); }
    void draw() { for (auto& c : components) c->draw();}
    bool isActive() { return active; }
    void destroy() { active = false; }
    bool hasGroup(Group mGroup) { return groupBitSet[mGroup]; }
    void addGroup(Group mGroup);
    void delGroup(Group mGroup) { groupBitSet[mGroup] = false; }

    template <typename T> bool hasComponent() {
        return componentBitSet[getComponentTypeID<T>()];
    }

    // typename... TArgs --> variadic template parameter pack
    // meanning it accept any # of arg and any type
    // TArgs&&... mArgs --> universal reference to catch arg
    template <typename T, typename... TArgs>
    T& addComponent(TArgs&&... mArgs) {
        // perfect forwarding, unpack & pass the arg to new constructor
        T* c(new T(std::forward<TArgs>(mArgs)...));
        c->entity = this;

        components.emplace_back(c);
        componentArray[getComponentTypeID<T>()] = c;
        componentBitSet[getComponentTypeID<T>()] = true;

        c->init();
        return *c;
    }

    template<typename T> T& getComponent() const {
        auto ptr(componentArray[getComponentTypeID<T>()]);
        return *static_cast<T*>(ptr);
    }

};

class Manager {

private :
    vector<unique_ptr<Entity>> entities;
    array<vector<Entity*>, maxGroups> groupedEntities;

public :
    void update() {
        for (auto& e : entities) e->update();
    }

    void draw() {
        for (auto& e : entities) e->draw();
    }

    // move all the active one to the front
    // the iterator eventually point to the first inactive one
    // then it destroy all th inactive one from there to the end
    void refresh() {
        for (auto i(0u); i < maxGroups; i++) {
            auto& v(groupedEntities[i]);
            v.erase(remove_if(begin(v), end(v), [i](Entity* mEntity) {
                return !mEntity->isActive() || !mEntity->hasGroup(i);
            }), end(v));
        }
        entities.erase(remove_if(begin(entities), end(entities), [](const unique_ptr<Entity> &mEntity) {
            return !mEntity->isActive();
        }), end(entities));
    }

    void addToGroup(Entity* mEntity, Group mGroup) {
        groupedEntities[mGroup].emplace_back(mEntity);
    }

    vector<Entity*>& getGroup(Group mGroup) {
        return groupedEntities[mGroup];
    }

    Entity& addEntity() {
        Entity* e = new Entity(*this);
        entities.emplace_back(e);
        return *e;
    }
};