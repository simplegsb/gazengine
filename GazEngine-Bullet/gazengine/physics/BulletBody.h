#ifndef BULLETBODY_H_
#define BULLETBODY_H_

#include <btBulletDynamicsCommon.h>

#include <gazengine/physics/Body.h>

class BulletBody : public Body
{
	public:
		BulletBody(const Material& material, const Model* model, const Vector3& position);

		~BulletBody();

		void applyForce(const Vector3& force, const Vector3& position);

		void clearForces();

		btRigidBody* getBody();

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
		btRigidBody* body;

		btCollisionShape* bulletModel;

		Vector3 linearAcceleration;

		mutable Vector3 linearVelocity;

		Material material;

		const Model* model;

		btMotionState* motionState;

		mutable Vector3 position;
};

#endif /* BULLETBODY_H_ */
