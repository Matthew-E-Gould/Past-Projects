
#include "particle.h"
#include <math.h>
#include <assert.h>
#include <float.h>

// initialisation
Particle::Particle() {
	colour[0] = 1.0f;
	colour[1] = 1.0f;
	colour[2] = 1.0f;
	angularVelocity = 0.0f;
	angle = 0.0f;
	sidesCount = 0;
}

// calculations in frame
void Particle::integrate(float duration)
{

	// values can't be 0
	if (inverseMass <= 0.0f) return;
	assert(duration > 0.0f);

	// moves ball for the time period
	position.addScaledVector(velocity, duration);

	// Work out the acceleration from the force
	Vector2 resultingAcc = acceleration;
	resultingAcc.addScaledVector(forceAccum, inverseMass);

	// Update linear velocity from the acceleration.
	velocity.addScaledVector(resultingAcc, duration);

	// update rotation from spin
	setAngle(angle + angularVelocity);

	// Impose drag.
	velocity *= pow(damping, duration);
	angularVelocity *= pow(damping, duration);

	// Clear the forces.
	clearAccumulator();
}

// set and get mass of particle
void Particle::setMass(const float mass)
{
	assert(mass != 0.0f);
	Particle::inverseMass = ((float)1.0f) / mass;
}
float Particle::getMass() const
{
	if (inverseMass == 0.0f) {
		return DBL_MAX;
	}
	else {
		return ((float)1.0) / inverseMass;
	}
}

//sets and gets and returns statement based off inverse mass
void Particle::setInverseMass(const float inverseMass)
{
	Particle::inverseMass = inverseMass;
}
float Particle::getInverseMass() const
{
	return inverseMass;
}
bool Particle::hasFiniteMass() const
{
	return inverseMass >= 0.0f;
}

// set and get damping
void Particle::setDamping(const float damping)
{
	Particle::damping = damping;
}
float Particle::getDamping() const
{
	return damping;
}

// set and get position
void Particle::setPosition(const float x, const float y)
{
	position.x = x;
	position.y = y;
}
void Particle::setPosition(const Vector2 &position)
{
	Particle::position = position;
}

// set and get position of particle
Vector2 Particle::getPosition() const
{
	return position;
}
void Particle::getPosition(Vector2 *position) const
{
	*position = Particle::position;
}

// set and get radius of particle (circle in square geometory)
void Particle::setRadius(const float r)
{
	radius = r;
}
float Particle::getRadius() const
{
	return radius;
}

// set and get velocity of particle in a variety of ways
void Particle::setVelocity(const float x, const float y)
{
	velocity.x = x;
	velocity.y = y;
}
void Particle::setVelocity(const Vector2 &velocity)
{
	this->velocity = velocity;
}
Vector2 Particle::getVelocity() const
{
	return velocity;
}
void Particle::getVelocity(Vector2 *velocity) const
{
	*velocity = Particle::velocity;
}

// set and get acceleration of particle in a variety of ways
void Particle::setAcceleration(const Vector2 &acceleration)
{
	Particle::acceleration = acceleration;
}
void Particle::setAcceleration(const float x, const float y)
{
	acceleration.x = x;
	acceleration.y = y;
}
Vector2 Particle::getAcceleration() const
{
	return acceleration;
}

// eidt values of force on particle as a scalar
void Particle::clearAccumulator()
{
	forceAccum.clear();
}
void Particle::addForce(const Vector2 &force)
{
	forceAccum += force;
}

// set and get RGB vlaues of particle
void Particle::setRGB(float red, float green, float blue) {
	colour[0] = red;
	colour[1] = green;
	colour[2] = blue;
}
void Particle::getRGB(float* red, float* green, float* blue) {
	*red = colour[0];
	*green = colour[1];
	*blue = colour[2];
}

// set and get particle spin (not used)
void Particle::setSpin(float input) {
	angularVelocity = input;
}
float Particle::getSpin() {
	return angularVelocity;
}

// set and get angle of particle
void Particle::setAngle(float input) {
	//input validation (noyl between 0 and 360 degrees)
	while (input >= 360.0) {
		input -= 360.0;
	}
	while (input < 0.0) {
		input += 360.0;
	}
	angle = input;
}
float Particle::getAngle() {
	return angle;
}
// angle in radians
float Particle::getAngleRad() {
#define PI 3.14159265
	return (angle*PI / 180.0);
}

// sets and gets the particles sides, for collision resolution and types of detection
void Particle::setParticleSides(unsigned input) {
	//input validation
	if (input == 0 || 4) {
		sidesCount = input;
	}
	else {
		sidesCount = 0; // if invalid input make circle
	}
}
unsigned Particle::getParticleSides() {
	return sidesCount;
}

// sets and gets if the particle has collided wityh a platform
void Particle::hasCollided() {
	collided = true;
}
bool Particle::getCollided() {
	return collided;
}

// draws the particle
void Particle::draw() {
	glColor3f(colour[0], colour[1], colour[2]); // setting colour of shape
	glPushMatrix();
	glRotatef(angle, 0, 0, 1); // setting angle of shape
	glTranslatef(position.x, position.y, 0); // setting location of shape
	collided = false; // new frame new platform to collide with
	if (sidesCount == 4) glutSolidCube(radius * 2); // if 4 sided make a square
	else glutSolidSphere(radius, 12, 12); // else make a circle
	// https://www.opengl.org/resources/libraries/glut/spec3/node80.html#SECTION000120000000000000000
	glPopMatrix();
}