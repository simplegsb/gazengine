#ifndef BULLETBODY_H_
#define BULLETBODY_H_

#include <btBulletDynamicsCommon.h>

#include <gazengine/physics/Body.h>

class BulletBody : public Body
{
	public:
		BulletBody(const Material& material, Model* model, const Matrix44& transformation);

		~BulletBody();

		void applyForce(const Vector3& force, const Vector3& position);

		void applyTorque(const Vector3& torque);

		void clearForces();

		btRigidBody* getBody();

		const Vector3& getLinearAcceleration() const;

		const Vector3& getLinearVelocity() const;

		float getMass() const;

		const Material& getMaterial() const;

		const Model* getModel() const;

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
		btRigidBody* body;

		btCollisionShape* bulletModel;

		Vector3 linearAcceleration;

		mutable Vector3 linearVelocity;

		Material material;

		Model* model;

		btMotionState* motionState;

		mutable Matrix44 transformation;
};

#endif /* BULLETBODY_H_ */
