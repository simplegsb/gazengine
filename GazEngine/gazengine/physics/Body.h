#ifndef BODY_H_
#define BODY_H_

#include "../Component.h"
#include "../graph/SimpleTree.h"
#include "../model/Model.h"

class Body : public Component
{
	public:
		struct Material
		{
			float density;

			float friction;

			float restitution;
		};

		virtual ~Body()
		{
		}

		//virtual void applyAngularImpulse(float impulse) = 0;

		virtual void applyForce(const Vector3& force) = 0;

		virtual void applyForce(const Vector3& force, const Vector3& position) = 0;

		//virtual void applyLinearImpulse(const Vector3& impulse, const Vector3& position) = 0;

		virtual void applyTorque(const Vector3& torque) = 0;

		virtual void clearForces() = 0;

		virtual const Vector3& getLinearVelocity() const = 0;

		virtual float getMass() const = 0;

		virtual const Material& getMaterial() const = 0;

		virtual const std::vector<const Model*>& getModels() const = 0;

		virtual Matrix44& getTransformation() = 0;

		virtual const Matrix44& getTransformation() const = 0;

		virtual bool isDynamic() = 0;

		virtual void setDynamic(bool dynamic) = 0;

		virtual void setLinearVelocity(const Vector3& linearVelocity) = 0;

		virtual void setMass(float mass) = 0;

		virtual void setMaterial(const Material& material) = 0;

		virtual void setNode(SimpleTree* node) = 0;

		virtual void setTransformation(const Matrix44& transformation) = 0;
};

#endif /* BODY_H_ */
