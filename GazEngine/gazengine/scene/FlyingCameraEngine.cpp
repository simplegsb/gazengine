#include "../Events.h"
#include "../GazEngine.h"
#include "../input/KeyboardButtonEvent.h"
#include "../input/MouseMoveEvent.h"
#include "../math/MathFunctions.h"
#include "FlyingCameraEngine.h"

FlyingCameraEngine::FlyingCameraEngine(Camera* camera, float speed, Body* body) :
	body(body),
	camera(camera),
	mouseX(-1.0f),
	mouseY(-1.0f),
	movingBackward(false),
	movingDown(false),
	movingForward(false),
	movingUp(false),
	turningLeft(false),
	turningRight(false),
	speed(speed)
{
}

void FlyingCameraEngine::addEntity(Entity*)
{
}

void FlyingCameraEngine::advance()
{
	if (body == NULL)
	{
		Vector4 right;
		right.X() = camera->getNode()->getTransformation()[0];
		right.Y() = camera->getNode()->getTransformation()[1];
		right.Z() = camera->getNode()->getTransformation()[2];
		right.W() = camera->getNode()->getTransformation()[3];
		right.normalize();
		Vector4 up;
		up.X() = camera->getNode()->getTransformation()[4];
		up.Y() = camera->getNode()->getTransformation()[5];
		up.Z() = camera->getNode()->getTransformation()[6];
		up.W() = camera->getNode()->getTransformation()[7];
		up.normalize();
		Vector4 out;
		out.X() = camera->getNode()->getTransformation()[8];
		out.Y() = camera->getNode()->getTransformation()[9];
		out.Z() = camera->getNode()->getTransformation()[10];
		out.W() = camera->getNode()->getTransformation()[11];
		out.normalize();
		Vector4 position = getTranslation4(camera->getNode()->getTransformation());

		if (movingBackward)
		{
			position -= out * speed * GazEngine::getDeltaTime();
			position.W() = 1.0f;
		}
		if (movingDown)
		{
			position.Y() -= speed * GazEngine::getDeltaTime();
		}
		if (movingForward)
		{
			position += out * speed * GazEngine::getDeltaTime();
			position.W() = 1.0f;
		}
		if (movingUp)
		{
			position.Y() += speed * GazEngine::getDeltaTime();
		}
		if (turningLeft)
		{
			Matrix44 rotation;
			rotate(rotation, -speed * 0.1f * GazEngine::getDeltaTime(), up);

			camera->getNode()->getTransformation() *= rotation;
		}
		if (turningRight)
		{
			Matrix44 rotation;
			rotate(rotation, speed * 0.1f * GazEngine::getDeltaTime(), up);

			camera->getNode()->getTransformation() *= rotation;
		}
	}
	else
	{
		Vector3 right;
		right.X() = body->getTransformation()[0];
		right.Y() = body->getTransformation()[1];
		right.Z() = body->getTransformation()[2];
		right.normalize();
		Vector3 up3;
		up3.X() = body->getTransformation()[4];
		up3.Y() = body->getTransformation()[5];
		up3.Z() = body->getTransformation()[6];
		up3.normalize();
		Vector4 up4;
		up4.X() = body->getTransformation()[4];
		up4.Y() = body->getTransformation()[5];
		up4.Z() = body->getTransformation()[6];
		up4.W() = body->getTransformation()[7];
		up4.normalize();
		Vector3 out;
		out.X() = body->getTransformation()[8];
		out.Y() = body->getTransformation()[9];
		out.Z() = body->getTransformation()[10];
		out.normalize();
		Vector3 position = getTranslation3(body->getTransformation());

		if (movingBackward)
		{
			body->applyForce(out * -10.0f * speed, getTranslation3(body->getTransformation()));
		}
		if (movingDown)
		{
			body->applyForce(up3 * -10.0f * speed, getTranslation3(body->getTransformation()));
		}
		if (movingForward)
		{
			body->applyForce(out * 10.0f * speed, getTranslation3(body->getTransformation()));
		}
		if (movingUp)
		{
			body->applyForce(up3 * 10.0f * speed, getTranslation3(body->getTransformation()));
		}
		if (turningLeft)
		{
			//body->applyTorque(right * -10000.0f * speed);

			Matrix44 rotation;
			rotate(rotation, speed * -0.1f * GazEngine::getDeltaTime(), up4);

			Matrix44 transformation = body->getTransformation();
			transformation *= rotation;
			body->setTransformation(transformation);
		}
		if (turningRight)
		{
			//body->applyTorque(right * 10000.0f * speed);

			Matrix44 rotation;
			rotate(rotation, speed * 0.1f * GazEngine::getDeltaTime(), up4);

			Matrix44 transformation = body->getTransformation();
			transformation *= rotation;
			body->setTransformation(transformation);
		}
	}
}

void FlyingCameraEngine::destroy()
{
	Messages::deregisterRecipient(Events::KEYBOARD_BUTTON, this);
	//Messages::deregisterRecipient(Events::MOUSE_MOVE, this);
}

void FlyingCameraEngine::init()
{
	Messages::registerRecipient(Events::KEYBOARD_BUTTON, this);
	//Messages::registerRecipient(Events::MOUSE_MOVE, this);
}

void FlyingCameraEngine::receive(unsigned short subject, const void* message)
{
	if (subject == Events::KEYBOARD_BUTTON)
	{
		const KeyboardButtonEvent* event = static_cast<const KeyboardButtonEvent*>(message);

		bool buttonDown = false;
		if (event->buttonState == Button::DOWN)
		{
			buttonDown = true;
		}

		if (event->button == Keyboard::ARROW_DOWN)
		{
			movingBackward = buttonDown;
		}
		if (event->button == Keyboard::ARROW_LEFT)
		{
			turningLeft = buttonDown;
		}
		if (event->button == Keyboard::ARROW_RIGHT)
		{
			turningRight = buttonDown;
		}
		if (event->button == Keyboard::ARROW_UP)
		{
			movingForward = buttonDown;
		}
		if (event->button == Keyboard::MINUS)
		{
			movingDown = buttonDown;
		}
		if (event->button == Keyboard::PLUS)
		{
			movingUp = buttonDown;
		}
	}

	if (subject == Events::MOUSE_MOVE)
	{
		const MouseMoveEvent* event = static_cast<const MouseMoveEvent*>(message);
		Vector3 cameraPosition = getTranslation3(camera->getNode()->getTransformation());

		if (mouseX != -1.0f)
		{
			rotate(camera->getNode()->getTransformation(), event->x - mouseX * speed * 0.00001f *
				GazEngine::getDeltaTime(), Vector4(1.0f, 0.0f, 0.0f, 1.0f));
		}

		if (mouseY != -1.0f)
		{
			rotate(camera->getNode()->getTransformation(), event->y - mouseY * speed * 0.00001f *
				GazEngine::getDeltaTime(), Vector4(0.0f, 1.0f, 0.0f, 1.0f));
		}

		mouseX = static_cast<float>(event->x);
		mouseY = static_cast<float>(event->y);
	}
}

void FlyingCameraEngine::removeEntity(const Entity&)
{
}
