#ifndef SIMPLEBODY_H_
#define SIMPLEBODY_H_

#include "Body.h"

class SimpleBody : public Body
{
	public:
		SimpleBody(Material material, Model* model, Vector2 position);

		void applyForce(const Vector2& force, const Vector2& position);

		void clearForces();

		const Vector2& getLinearAcceleration() const;

		const Vector2& getLinearVelocity() const;

		float getMass() const;

		const Material& getMaterial() const;

		const Model* getModel() const;

		const Vector2& getPosition() const;

		bool isDynamic();

		void setDynamic(bool dynamic);

		void setLinearVelocity(const Vector2& linearVelocity);

		void setMass(float mass);

		void setMaterial(const Material& material);

		void setPosition(const Vector2& position);

	private:
		bool dynamic;

		Vector2 linearAcceleration;

		Vector2 linearVelocity;

		float mass;

		Material material;

		Model* model;

		Vector2 position;
};

#endif /* SIMPLEBODY_H_ */
