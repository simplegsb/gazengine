#ifndef SIMPLEBODY_H_
#define SIMPLEBODY_H_

#include "Body.h"

class SimpleBody : public Body
{
	public:
		SimpleBody(Material material, Model* model, Vector3 position, bool dynamic);

		void applyForce(const Vector3& force, const Vector3& position);

		void clearForces();

		const Vector3& getLinearAcceleration() const;

		const Vector3& getLinearVelocity() const;

		float getMass() const;

		const Material& getMaterial() const;

		const Model* getModel() const;

		const Vector3& getPosition() const;

		bool isDynamic();

		void setDynamic(bool dynamic);

		void setLinearVelocity(const Vector3& linearVelocity);

		void setMass(float mass);

		void setMaterial(const Material& material);

		void setNode(SimpleTree* node);

		void setPosition(const Vector3& position);

	private:
		bool dynamic;

		Vector3 linearAcceleration;

		Vector3 linearVelocity;

		float mass;

		Material material;

		Model* model;

		SimpleTree* node;

		Vector3 position;
};

#endif /* SIMPLEBODY_H_ */
