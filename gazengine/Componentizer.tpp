#include "Componentizer.h"

template<typename Type>
Componentizer<Type>::Componentizer(Type value) :
	value(value)
{
}

template<typename Type>
Type& Componentizer<Type>::getValue()
{
	return value;
}

template<typename Type>
const Type& Componentizer<Type>::getValue() const
{
	return value;
}

template<typename Type>
void Componentizer<Type>::setValue(const Type& value)
{
	this->value = value;
}
