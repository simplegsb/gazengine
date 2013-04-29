#ifndef PHYSXBODY_H_
#define PHYSXBODY_H_

#include <PxPhysicsAPI.h>

#include <gazengine/physics/Body.h>

class PhysXBody : public Body
{
	public:
		PhysXBody(physx::PxPhysics& physics, physx::PxCooking& cooking, const Material& material, const Model* model,
			const Matrix44& transformation, bool dynamic);

		PhysXBody(physx::PxPhysics& physics, physx::PxCooking& cooking, const Material& material,
			const vector<const Model*>& models, const Matrix44& transformation, bool dynamic);

		~PhysXBody();

		void applyForce(const Vector3& force);

		void applyForce(const Vector3& force, const Vector3& position);

		void applyTorque(const Vector3& torque);

		void clearForces();

		physx::PxActor* getActor();

		const std::vector<physx::PxGeometry*> getGeometries();

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
		physx::PxRigidActor* actor;

		bool dynamic;

		mutable Vector3 linearVelocity;

		Material material;

		std::vector<const Model*> models;

		physx::PxMaterial* physxMaterial;

		std::vector<physx::PxGeometry*> geometries;

		mutable Matrix44 transformation;

		physx::PxGeometry* createGeometry(physx::PxPhysics& physics, physx::PxCooking& cooking, const Model* model);

		void init(physx::PxPhysics& physics, physx::PxCooking& cooking);
};

#endif /* PHYSXBODY_H_ */
