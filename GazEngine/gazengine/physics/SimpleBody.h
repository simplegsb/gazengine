#ifndef SIMPLEBODY_H_
#define SIMPLEBODY_H_

#include "Body.h"

class SimpleBody : public Body
{
	public:
		SimpleBody(const Material& material, Model* model, const Matrix44& transformation, bool dynamic);

		SimpleBody(const Material& material, const std::vector<const Model*>& models, const Matrix44& transformation,
			bool dynamic);

		void applyForce(const Vector3& force);

		void applyForce(const Vector3& force, const Vector3& position);

		void applyTorque(const Vector3& torque);

		void clearForces();

		const Vector3& getLinearAcceleration() const;

		const Vector3& getLinearVelocity() const;

		float getMass() const;

		const Material& getMaterial() const;

		const std::vector<const Model*>& getModels() const;

		Matrix44& getTransformation();

		const Matrix44& getTransformation() const;

		bool isDynamic();

		void setDynamic(bool dynamic);

		void setLinearVelocity(const Vector3& linearVelocity);

		void setMass(float mass);

		void setMaterial(const Material& material);

		void setNode(SimpleTree* node);

		void setTransformation(const Matrix44& transformation);

	private:
		bool dynamic;

		Vector3 linearAcceleration;

		Vector3 linearVelocity;

		float mass;

		Material material;

		std::vector<const Model*> models;

		SimpleTree* node;

		Matrix44 transformation;
};

#endif /* SIMPLEBODY_H_ */
