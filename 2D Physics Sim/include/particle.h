/**
 * A particle is the simplest object that can be simulated in the
 * physics system.

 */

#ifndef PARTICLE_H
#define PARTICLE_H

#include "coreMath.h"
#include <vector>
#include <gl/glut.h>

class Particle
{
public:

	Particle();

	void integrate(float duration);
	void setMass(const float mass);
	float getMass() const;
	void setInverseMass(const float inverseMass);
	float getInverseMass() const;
	bool hasFiniteMass() const;

	void setDamping(const float damping);
	float getDamping() const;

	void setPosition(const float x, const float y);
	void setPosition(const Vector2 &position);
	Vector2 getPosition() const;
	void getPosition(Vector2 *position) const;

	void setRadius(const float r);
	float getRadius() const;

	void setVelocity(const Vector2 &velocity);
	void setVelocity(const float x, const float y);
	Vector2 getVelocity() const;
	void getVelocity(Vector2 *velocity) const;

	void setAcceleration(const Vector2 &acceleration);
	void setAcceleration(const float x, const float y);
	Vector2 getAcceleration() const;

	void clearAccumulator();
	void addForce(const Vector2 &force);

	void setRGB(float red, float green, float blue);
	void getRGB(float* red, float* green, float* blue);

	void setSpin(float input);
	float getSpin();

	void setAngle(float input);
	float getAngle();
	float getAngleRad();

	void setParticleSides(unsigned input);
	unsigned getParticleSides(); // stores how many sides the shape has (0=Circle, 4=Square)

	void hasCollided();
	bool getCollided();

	void draw();

protected:

	Vector2 position;
	Vector2 velocity;
	Vector2 forceAccum;
	Vector2 acceleration;

	float angularVelocity; // +ve is CW, -ve is CCW
	float angle; // 1 = 2Pi

	float inverseMass;
	float damping;
	float radius;
	float colour[3];

	unsigned sidesCount;

	bool collided;
};

#endif // 


