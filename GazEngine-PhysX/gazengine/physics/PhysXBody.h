#ifndef PHYSXBODY_H_
#define PHYSXBODY_H_

#include <PxPhysicsAPI.h>

#include <gazengine/physics/Body.h>

class PhysXBody : public Body
{
	public:
		PhysXBody(physx::PxPhysics& physics, const Material& material, const Model* model, const Vector3& position,
			bool dynamic);

		~PhysXBody();

		void applyForce(const Vector3& force, const Vector3& position);

		void clearForces();

		physx::PxActor* getActor();

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
		physx::PxActor* actor;

		bool dynamic;

		Vector3 linearAcceleration;

		mutable Vector3 linearVelocity;

		Material material;

		const Model* model;

		physx::PxMaterial* physxMaterial;

		physx::PxGeometry* physxModel;

		mutable Vector3 position;
};

#endif /* PHYSXBODY_H_ */
