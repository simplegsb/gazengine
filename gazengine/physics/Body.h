#ifndef BODY_H_
#define BODY_H_

#include "../Component.h"
#include "../math/Vector2.h"
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

		virtual void applyForce(const Vector2& force, const Vector2& position) = 0;

		//virtual void applyLinearImpulse(const Vector2& impulse, const Vector2& position) = 0;

		//virtual void applyTorque(float torque) = 0;

		virtual void clearForces() = 0;

		virtual const Vector2& getLinearAcceleration() const = 0;

		virtual const Vector2& getLinearVelocity() const = 0;

		virtual float getMass() const = 0;

		virtual const Material& getMaterial() const = 0;

		virtual const Model* getModel() const = 0;

		virtual const Vector2& getPosition() const = 0;

		virtual bool isDynamic() = 0;

		virtual void setDynamic(bool dynamic) = 0;

		virtual void setLinearVelocity(const Vector2& linearVelocity) = 0;

		virtual void setMass(float mass) = 0;

		virtual void setMaterial(const Material& material) = 0;

		virtual void setPosition(const Vector2& position) = 0;
};

#endif /* BODY_H_ */
