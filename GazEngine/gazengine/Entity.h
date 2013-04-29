#ifndef ENTITY_H_
#define ENTITY_H_

#include <memory>
#include <string>
#include <vector>

class Component;

class Entity
{
	public:
		static const unsigned short UNCATEGORIZED = 0;

		Entity(unsigned short category = UNCATEGORIZED, const std::string& name = std::string());

		virtual ~Entity();

		/**
		 * <p>
		 * Adds a component.
		 * </p>
		 *
		 * @param component The component to add.
		 */
		void addComponent(Component* component);

		unsigned short getCategory() const;

		/**
		 * <p>
		 * Retrieves the components.
		 * </p>
		 *
		 * @return The components.
		 */
		template<typename ComponentType>
		std::vector<ComponentType*> getComponents() const;

		unsigned int getId() const;

		/**
		 * <p>
		 * Retrieves the name of this <code>Entity</code>.
		 * </p>
		 *
		 * @return The name of this <code>Entity</code>.
		 */
		const std::string& getName() const;

		/**
		 * <p>
		 * Retrieves a single component.
		 * </p>
		 *
		 * @return The single component.
		 */
		template<typename ComponentType>
		ComponentType* getSingleComponent() const;

		/**
		 * <p>
		 * Removes a component.
		 * </p>
		 *
		 * @param component The component to remove.
		 */
		void removeComponent(const Component& component);

	private:
		unsigned short category;

		/**
		 * <p>
		 * The components.
		 * </p>
		 */
		std::vector<Component*> components;

		unsigned int id;

		/**
		 * <p>
		 * The name of this <code>Entity</code>.
		 * </p>
		 */
		std::string name;

		static unsigned int nextId;
};

#include "Entity.tpp"

#endif /* ENTITY_H_ */
