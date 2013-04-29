#ifndef FLYINGCAMERAENGINE_H_
#define FLYINGCAMERAENGINE_H_

#include "../engine/Engine.h"
#include "../Messages.h"
#include "../physics/Body.h"
#include "Camera.h"

class FlyingCameraEngine : public Engine, public Messages::Recipient
{
	public:
		FlyingCameraEngine(Camera* camera, float speed, Body* body = NULL);

		void addEntity(Entity* entity);

		void advance();

		void destroy();

		void init();

		void receive(unsigned short subject, const void* message);

		void removeEntity(const Entity& entity);

	private:
		Body* body;

		Camera* camera;

		float mouseX;

		float mouseY;

		bool movingBackward;

		bool movingDown;

		bool movingForward;

		bool movingUp;

		bool turningLeft;

		bool turningRight;

		float speed;
};

#endif /* FLYINGCAMERAENGINE_H_ */
