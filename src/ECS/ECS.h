#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;
class Manager;

using ComponentID = std::size_t;	// standard(namespace)::(scope)size_t(unsigned int storing the maximum size of the object)
using Group = std::size_t;

// inline requests compiler to avoid execution time from function calls
// by moving function code to the main function where it is called
inline ComponentID getNewComponentTypeID()		// returns a typeID for component
{
	static ComponentID lastID = 0u;
	return lastID++;
}

// function does not 'exist' until it is called by compiler
// useful for creating similar functions/classes using different types as parameters/variables
// getComponentTypeID<typename T>();
template <typename T> inline ComponentID getComponentTypeID() noexcept
{
	static ComponentID typeID = getNewComponentTypeID();
	return typeID;
}

// constant expression; evaluated at compile time and cannot be modified
constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;

// declares a namespace that is a standard global scope of C++ standard template library
// ComponentBitSet is the namespace that contains a bitset with template of size_t (unsigned int)
using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitSet = std::bitset<maxGroups>;
using ComponentArray = std::array<Component*, maxComponents>;	// ComponentArray is the namespace that contains an array of components with size of maxComponents

class Component
{
public:
	Entity* entity;		// create a pointer for object of class Entity
	virtual void init() {}		// virtual functions allow inherited objects to call functions correlating to the class object instead of the parents
	virtual void update() {}
	virtual void draw() {}

	virtual ~Component() {}
private:
};

class Entity
{
private:
	Manager &manager;
	bool active = true;		// tracks if Entity object is active/in use
	
	// std::vector is a sequence of storage that represents arrays that can change size
	// unique_ptr is a smart pointer that owns and manages another object and deletes the object when unique_ptr goes out of scope
	// 
	std::vector<std::unique_ptr<Component>> components;		

	ComponentArray componentArray;		// initializes an array of components called componentArray
	ComponentBitSet componentBitSet = false;	// initializes a bitset called componentBitSet
	GroupBitSet groupBitSet;

public:
	Entity(Manager& mManager) : manager(mManager) {}
	
	void update()
	{
		// auto directs the compiler to use the variable or expression to deduce its type
		for (auto& c : components) c->update();		// iterates through each object in the components vector and calls update() for each one
	}

	void draw() 
	{
		for (auto& c : components) c->draw();		// iterates through each object in the components vector and calls draw() for each one
	}

	// const makes it a compiler error for writing inside of the function; thus, this function is read-only
	bool isActive() const { return active; }		// returns if the Entity is active
	void destroy() { active = false; }		// calling the function will set the Entity to not active/inactive

	bool hasGroup(Group mGroup)
	{
		return groupBitSet[mGroup];
	}

	void addGroup(Group mGroup);
	void delGroup(Group mGroup)
	{
		groupBitSet[mGroup] = false;
	}

	template <typename T> bool hasComponent() const
	{
		return componentBitSet[getComponentTypeID<T>()];		// returns whether the Entity has at least one component(s)
	}

	// takes a number of arguments
	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs)		// returns a T pointer value		
	{
		// std::forward preserves value of pointer type; "universal" pointer
		T* c(new T(std::forward<TArgs>(mArgs)...));		// initializes a var called c of type T pointer
		c->entity = this;		// sets the entity variable in Component to be equal to this (the current Entity object)
		std::unique_ptr<Component> uPtr{ c };		// 
		// emplace_back inserts a new element at the end of the vector
		components.emplace_back(std::move(uPtr));	// inserts uPtr at the end of the components object vector

		componentArray[getComponentTypeID<T>()] = c;

		componentBitSet[getComponentTypeID<T>()] = true;

		c->init();
		return *c;
	}

	template <typename T> T& getComponent() const
	{
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}

	//gameobject.getComponent<PositionComponent>().setXPos(25); example of use of entity
};

class Manager
{
private:
	std::vector<std::unique_ptr<Entity>> entities;
	std::array<std::vector<Entity*>, maxGroups> groupedEntities;	// initializes an array of type vector with size maxGroups called groupedEntities

public:
	void update()
	{
		for (auto& e : entities) e->update();	// iterates through each object in the components vector and calls update() for each one
	}

	void draw()
	{
		for (auto& e : entities) e->draw();		// iterates through each object in the components vector and calls draw() for each one
	}

	void refresh()
	{
		for (auto i(0u); i < maxGroups; i++)
		{
			auto& vector(groupedEntities[i]);
			vector.erase(std::remove_if(std::begin(vector), std::end(vector), [i](Entity* mEntity)
				{
					return !mEntity->isActive() || !mEntity->hasGroup(i);
				}), std::end(vector));
		}
		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
			[](const std::unique_ptr<Entity>& mEntity)
		{
				return !mEntity->isActive();
		}),
		std::end(entities));
	}

	void addToGroup(Entity* mEntity, Group mGroup)
	{
		groupedEntities[mGroup].emplace_back(mEntity);
	}

	std::vector<Entity*>& getGroup(Group mGroup)
	{
		return groupedEntities[mGroup];
	}

	Entity& addEntity()
	{
		Entity* e = new Entity(*this);
		std::unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(std::move(uPtr));
		return *e;
	}
};