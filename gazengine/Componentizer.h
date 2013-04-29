#ifndef COMPONENTIZER_H_
#define COMPONENTIZER_H_

#include "Component.h"

template<typename Type>
class Componentizer : public Component
{
	public:
		Componentizer(Type value = Type());

		Type& getValue();

		const Type& getValue() const;

		void setValue(const Type& value);

	private:
		Type value;
};

#include "Componentizer.tpp"

#endif /* COMPONENTIZER_H_ */
