/*
 * The Blob demo.
 *
 */
#include "app.h"
#include "coreMath.h"
#include "pcontacts.h"
#include "pworld.h"
#include "Quadtree.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <gl/glut.h>
#include <cassert>
#include <iostream>

#define PI 3.14159265
#define BLOB_COUNT 20
#define PLATFORM_COUNT 8
#define UNIQUE_SPAWNS true
const Vector2 Vector2::GRAVITY = Vector2(0, -9.81);

#pragma once

// class that calculates if particles collide using the list of particles and the quadtree
class ParticleCollision : public ParticleContactGenerator {
public:
	Particle *particles;
	Quadtree *quadtree;

	virtual unsigned addContact(ParticleContact *contact, unsigned limit) const;

	void setQuadtree(Quadtree* quad);

	bool checkCollision(Particle *one, Particle *two) const; // checking what type of collision has been run
	bool squareCircleCollision(Particle *square, Particle *circle) const; // if square has collided with circle
	bool circleCircleCollision(Particle *circleOne, Particle *circleTwo) const; // if its purely a circle collision
	bool squareSquareCollision(Particle *squareOne, Particle *squareTwo) const; // if its purely a square collision
	bool edgeCircleCollision(Vector2 start, Vector2 end, Particle *circle) const; // if an edge has collided with a particle

	float QuadrilateralColission(float orgSize, float orgAngle, float ofsParSize, float ofsPerpSize, float ofsAngle) const; // repetative code used for calculations in a square collision
};

// used to set quadtree
void ParticleCollision::setQuadtree(Quadtree* quad) {
	quadtree = quad;
}

// used for checking all relevent particles have collided
unsigned int ParticleCollision::addContact(ParticleContact *contact, unsigned limit) const { // returns the amount of calculations done

	const static float RESTITUTION = 1.0f;
	unsigned used = 0;

	// resetting quadtree for new collision checks
	quadtree->clear();
	for (int i = 0; i < BLOB_COUNT; i++) {
		quadtree->insert(&particles[i]);
	}

	//list to store the particles that need to be checked
	std::vector<Particle*> particlesToCheck; // initialisiation
	std::vector<Particle*> *particlesCheck = &particlesToCheck; // pointer to initialised vector
	std::vector<Particle*> tempVec; // temporary vector for short term storage
	

	for (int x = 0; x < BLOB_COUNT; x++) 
	{
		// resetting the tempVect for use
		tempVec.clear();
		particlesCheck->clear();
		tempVec = quadtree->retrieve(particlesCheck, &particles[x]);

		// for each particle that have a chance of colliding
		for (int i = 0; i < tempVec.size(); i++) {

			if (tempVec[i]->getPosition() == particles[x].getPosition()) continue; // if comparing particle to itself skip
			if (used >= limit) return used; // if limiter has reached its limit then stop checking for collisions

			//std::cout << "tempVec.size() A" << tempVec.size() << std::endl; // debug for particle recognition

			//for each of the particles returned run check collision()
			if (checkCollision(tempVec[i], &particles[x]))
			{
				//std::cout << "Collision detected between: " << i << " and " << x;
				Vector2 toParticle = tempVec[i]->getPosition() - particles[x].getPosition();
				contact->particle[0] = tempVec[i];
				contact->particle[1] = &particles[x];
				contact->penetration = (tempVec[i]->getRadius() - toParticle.magnitude());
				contact->contactNormal = toParticle.unit();
				contact->restitution = RESTITUTION;
				used++;
				contact++;
			}
			//std::cout << "tempVec.size() B" << tempVec.size() << std::endl; // debug for particle recognition
		}
	}
	return used;
}

bool ParticleCollision::checkCollision(Particle *one, Particle *two) const //returns if there is a collision. true == Collision
{
	// used for if statements
	bool oneIsCircle = one->getParticleSides() == 0;
	bool twoIsCircle = two->getParticleSides() == 0;

	// checking if circles were used in collision
	if (oneIsCircle && twoIsCircle) {
		return circleCircleCollision(one, two);
	} 
	else if (oneIsCircle || twoIsCircle) {
		if (oneIsCircle) {
			// particle 1 is the Square/boundry
			return squareCircleCollision(two, one);
		}
		else {
			// particle 2 is the Square/boundry
			return squareCircleCollision(one, two);
		}
	}
	else {
		// if particles are squares
		return squareSquareCollision(one, two) || circleCircleCollision(one, two);
	}
	
	std::cout << "ERROR: somehow escaped if{...}else{...} in ParticleCollision::checkCollision()." << std::endl; // error text, returns a fail value
	return(false);
}

/// look at https://gamedev.stackexchange.com/questions/86755/how-to-calculate-corner-positions-marks-of-a-rotated-tilted-rectangle


bool ParticleCollision::squareCircleCollision(Particle *square, Particle *circle) const {

	//std::cout << "----------------------------------------" << std::endl;

	//std::cout << "center x,y: " << square->getPosition().x << ", " << square->getPosition().y << std::endl;

	Vector2 sRadius; // stores 1/2 the width of the square
	Vector2 corner[4]; // stores all corners of the square
	Vector2 rotated; // temporary storage for calculations
	Vector2 line[] = { Vector2(9999,9999), Vector2(9999,9999) };  // used for square magnitued comparison (represents best distance of circle center from corner)
	Vector2 tempLine; // used for square magnitued comparison (represents test distance of circle center from corner)
	unsigned tempStorage[2]; // stores indexes of best 2 corners

	sRadius.x = sRadius.y = square->getRadius();

	float angle = square->getAngleRad();

	for (unsigned i = 0; i < 4; i++) {
		// calculation for corners
		if (i == 1) sRadius.x = -sRadius.x;
		else if (i == 2) sRadius.y = -sRadius.y;
		else  if (i == 3) sRadius.x = -sRadius.x;
		//std::cout << "sRadius x,y: " << sRadius.x << ", " << sRadius.y << std::endl;

		// calculation for corners after rotation
		rotated.x = sRadius.x*cos(angle) - sRadius.y*sin(angle);
		rotated.y = sRadius.x*sin(angle) + sRadius.y*cos(angle);
		corner[i] = rotated + square->getPosition();
		tempLine = circle->getPosition() - corner[i];

		//std::cout << "corner[i] x,y: " << corner[i].x << ", " << corner[i].y << std::endl;

		// calculation for closest edge
		if (tempLine.squareMagnitude() < line[0].squareMagnitude()) {
			// storing index of closest corner
			tempStorage[1] = tempStorage[0];
			tempStorage[0] = i;
			// updating best and second best found value for future comparison
			line[1] = line[0];
			line[0] = tempLine;

			// debug
			//std::cout << "set new best corner" << std::endl;
			//std::cout << "moved best corner to 2nd best corner" << std::endl;
		}
		else if (tempLine.squareMagnitude() < line[1].squareMagnitude()) {
			// storing index of 2nd closest corner
			tempStorage[1] = i;
			// updating second best found value for future comparison
			line[1] = tempLine;
			//std::cout << "set new 2nd best corner" << std::endl; // debug
		}
	}

	//std::cout << "center of square x,y: " << square->getPosition().x << ", " << square->getPosition().y << std::endl;
	//std::cout << "   start of edge x,y: " << corner[tempStorage[0]].x << ", " << corner[tempStorage[0]].y << std::endl;
	//std::cout << "     end of edge x,y: " << corner[tempStorage[1]].x << ", " << corner[tempStorage[1]].y << std::endl;
	return edgeCircleCollision(corner[tempStorage[0]], corner[tempStorage[1]], circle); // returning if the edge is colliding with the circle

}/// look at https://gamedev.stackexchange.com/questions/86755/how-to-calculate-corner-positions-marks-of-a-rotated-tilted-rectangle

bool ParticleCollision::edgeCircleCollision(Vector2 start, Vector2 end, Particle *circle) const { // designed to be usable with all shapes if closest edge has been found
	//calculating all relevant values of the edge/circle collision
	Vector2 lineDirection = end - start;
	float platformSqLength = lineDirection.squareMagnitude();
	float squareRadius = circle->getRadius()*circle->getRadius();
	Vector2 toParticle = circle->getPosition() - start;
	float projected = toParticle * lineDirection;
	float distanceToPlatform = toParticle.squareMagnitude() - projected * projected / platformSqLength;

	if (projected <= 0)
	{
		// The circle is nearest to the start point
		return (toParticle.squareMagnitude() < squareRadius);
	}
	else if (projected >= platformSqLength)
	{
		// The circle is nearest to the end point
		toParticle = circle->getPosition() - end;
		return (toParticle.squareMagnitude() < squareRadius);
	}
	else
	{
		// the circle is nearest to the middle.
		float distanceToPlatform = toParticle.squareMagnitude() - projected * projected / platformSqLength;
		return (distanceToPlatform < squareRadius);
	}
	return false;
}

bool ParticleCollision::squareSquareCollision(Particle *squareOne, Particle *squareTwo) const { ///////////////////////////////////////////////////////

	Vector2 squareOneAxis, squareTwoAxis, distance;
	float  halfPi = PI / 2.0;
	float angleDiff = squareOne->getAngleRad() - squareTwo->getAngleRad();

	distance = squareOne->getPosition() - squareTwo->getPosition();

	if (distance.squareMagnitude() < pow(squareOne->getRadius(), 2) + pow(squareTwo->getRadius(), 2)) { // quick check to see if squares are guaranteed to be too far from eachother (a*a + b*b = c*c)
		// getting the squares distance from eachother in their comparative x&y axis (accounting for angles)
		squareOneAxis.x = abs(distance.x * cos(squareOne->getAngleRad())) - (-distance.y * sin(squareOne->getAngleRad()));
		squareOneAxis.y = abs(-distance.y * cos(squareOne->getAngleRad())) - (distance.x * sin(squareOne->getAngleRad()));

		squareTwoAxis.x = abs(distance.x * cos(squareTwo->getAngleRad())) - (-distance.y * sin(squareTwo->getAngleRad()));
		squareTwoAxis.y = abs(-distance.y * cos(squareTwo->getAngleRad())) - (distance.x * sin(squareTwo->getAngleRad()));

		//origin sizeX, origin sizeY, origin angle, offset sizeX, offset sizeY, offset angle, distance

		//std::cout << "axis: " << squareOneAxis.x << ", " << squareOneAxis.y << ", " << squareTwoAxis.x << ", " << squareTwoAxis.y << std::endl; //these values need to be compared

		//setting up test storage
		float test[4];

		// calculating square 2 distance from square 1 perspective 
		float size = squareOne->getRadius();
		float ofsParSize = squareTwo->getRadius();
		test[0] = QuadrilateralColission(size, squareOneAxis.x, ofsParSize, ofsParSize, squareTwoAxis.x);
		test[1] = QuadrilateralColission(size, squareOneAxis.y, ofsParSize, ofsParSize, squareTwoAxis.y);

		// calculating square 1 distance from square 2 perspective
		size = squareTwo->getRadius();
		ofsParSize = squareOne->getRadius();
		test[2] = QuadrilateralColission(size, squareTwoAxis.x, ofsParSize, ofsParSize, squareOneAxis.x);
		test[3] = QuadrilateralColission(size, squareTwoAxis.y, ofsParSize, ofsParSize, squareOneAxis.y);

		// making sure distance is absoloute
		for (unsigned i = 0; i < 4; i++) {
			//std::cout << test[i] << std::endl;
			test[i] = abs(test[i]);
		}

		// comparing tests to sqaures sizes
		bool collision = (squareOne->getRadius() + squareTwo->getRadius() <= test[0] &&
			squareOne->getRadius() + squareTwo->getRadius() <= test[1] &&
			squareOne->getRadius() + squareTwo->getRadius() <= test[2] &&
			squareOne->getRadius() + squareTwo->getRadius() <= test[3]);


		return collision; // returning if there was a collision
	}
	return false; // if the particles are naturally too for from eachother then they won't collide
}

// function to reduce repetative code
float ParticleCollision::QuadrilateralColission(float orgSize, float orgAngle, float ofsParSize, float ofsPerpSize, float ofsAngle) const {
	float angleDiff = ofsAngle - orgAngle;
	float output = abs(orgSize + (ofsParSize*cos(angleDiff)) + (ofsPerpSize*sin(angleDiff)));

	// debug

	//std::cout << "Angle as Deg: " << (angleDiff*float(180 / PI)) << std::endl;
	//std::cout << "angleDiff: " << angleDiff << std::endl;

	//std::cout << "orgSize " << orgSize << std::endl;
	//std::cout << "orgAngle " << orgAngle << std::endl;

	//std::cout << "ofsParSize " << ofsParSize << std::endl;
	//std::cout << "ofsPerpSize " << ofsPerpSize << std::endl;
	//std::cout << "ofsAngle " << ofsAngle << std::endl;

	//std::cout << "output " << output << std::endl;
	//std::cout << "--------------------------------" << std::endl;
	return(output);
}

// returns if there is a circle/circle collision
bool ParticleCollision::circleCircleCollision(Particle *circleOne, Particle *circleTwo) const {
	// pythagoras theorum to detect collision
	float distance = sqrt(pow(circleOne->getPosition().x - circleTwo->getPosition().x, 2)
		+ pow(circleOne->getPosition().y - circleTwo->getPosition().y, 2));

	distance -= circleOne->getRadius() + circleTwo->getRadius();

	return(distance < 0.0f);
}


class Platform : public ParticleContactGenerator
{
public:
	// storage for lines values
	Vector2 start;
	Vector2 end;
	float restitution;
	Particle *particles; // pointer for particle collision
	float colour[3];

	void setRestitution(float input);
	virtual unsigned addContact(ParticleContact *contact, unsigned limit) const;
	Platform();
	void getRGB(float* red, float* green, float* blue);
	void draw();
	void platformPointContact(ParticleContact* contact, int index, Vector2 toParticle, unsigned* used) const;
};

// initialisation
Platform::Platform() {
	restitution = 1.0f;
	colour[0] = 0.0f; // red
	colour[1] = 1.0f; // green
	colour[2] = 1.0f; // blue
}

// draw function for the platform, following the Liskov substitution principle 
void Platform::draw() {
	glColor3f(colour[0], colour[1], colour[2]);
	glVertex2f(start.x, start.y);
	glVertex2f(end.x, end.y);
}

// uses 3 pointers to get the Red, Green and blue values of the platform
void Platform::getRGB(float* red, float* green, float* blue) {
	*red = colour[0];
	*green = colour[1];
	*blue = colour[2];
}

void Platform::setRestitution(float input) {
	restitution = input;
	if (restitution < 0.0f) {
		// platform has a negative restitution
		colour[0] = 1.0f;
		colour[1] = 1.0f;
		colour[2] = 1.0f;
	}
	else if (restitution <= 1.0f) {
		// platform is a boundry
		colour[0] = 0.0f;
		colour[1] = 1.0f;
		colour[2] = 1.0f;
	}
	else {
		// platform is a bounce pad
		colour[0] = 1.0f;
		colour[1] = 0.0f;
		colour[2] = 0.0f;

	}
}

unsigned Platform::addContact(ParticleContact *contact, unsigned limit) const
{
	unsigned used = 0;
	for (unsigned i = 0; i < BLOB_COUNT; i++)
	{
		if (used >= limit) return used;

		// Check for penetration
		Vector2 toParticle = particles[i].getPosition() - start;
		Vector2 lineDirection = end - start;

		float projected = toParticle * lineDirection;
		float platformSqLength = lineDirection.squareMagnitude();
		float squareRadius = particles[i].getRadius()*particles[i].getRadius();

		if (projected <= 0 && !particles[i].getCollided())
		{

			// The blob is nearest to the start point
			if (toParticle.squareMagnitude() < squareRadius)
			{
				// collision
				///std::cout << "Collision. platform #" << ID << " start point with Ball #" << i << std::endl;
				platformPointContact(contact, i, toParticle, &used);
			}

		}
		else if (projected >= platformSqLength && !particles[i].getCollided())
		{
			// The blob is nearest to the end point
			toParticle = particles[i].getPosition() - end;

			if (toParticle.squareMagnitude() < squareRadius)
			{
				// collision
				///std::cout << "Collision. platform #" << ID << " end point with Ball #" << i << std::endl;
				platformPointContact(contact, i, toParticle, &used);
			}
		}
		else
		{
			// the blob is nearest to the middle.
			float distanceToPlatform = toParticle.squareMagnitude() - projected * projected / platformSqLength;
			if (distanceToPlatform < squareRadius)
			{
				//std::cout << "Collision. platform #" << ID << " middle with Ball #" << i << std::endl;
				// collision
				Vector2 closestPoint = start + lineDirection * (projected / platformSqLength);
				contact->contactNormal = (particles[i].getPosition() - closestPoint).unit();
				contact->restitution = restitution;
				contact->particle[0] = particles + i;
				contact->particle[1] = 0;
				contact->penetration = particles[i].getRadius() - sqrt(distanceToPlatform);
				used++;
				contact++;

			}
		}
	}
	return used;
}

void Platform::platformPointContact(ParticleContact *contact, int index, Vector2 toParticle, unsigned* used) const { // this may be causing the balls to go through platforms if they hit 2 endpoints at once
	contact->contactNormal = toParticle.unit();
	contact->restitution = restitution;
	contact->particle[0] = particles + index;
	contact->particle[1] = 0;
	contact->penetration = particles[index].getRadius() - toParticle.magnitude();
	used++;
	contact++;
	particles[index].hasCollided();
}

class BlobDemo : public Application
{
	// class pointer storage
	Particle *blob;
	Platform *platforms;
	ParticleWorld world;
	ParticleCollision *collision;
	Quadtree *quadtree;

	// storage for consistantly used values
	float colour[3];
	unsigned fps;

	std::time_t timer;

public:
	// constructors and destructors
	BlobDemo();
	virtual ~BlobDemo();

	// gets window title
	virtual const char* getTitle();

	// draws the display
	virtual void display();

	// updates physics for each particle
	virtual void update();

	// makes the location of balls unique, used to fix the spawns
	virtual void uniqueSpawns();
};

// Method definitions
BlobDemo::BlobDemo() :world(PLATFORM_COUNT + BLOB_COUNT, BLOB_COUNT)
{
	fps = 0;
	int seed = time(NULL);
	//int seed = 3465835;
	std::cout << "Sim Seed: " << seed << std::endl;
	srand(seed);

	//setup for bounds of sim
	width = 400; height = 400; nRange = 100.0;
	float margin = 0.95;
	float standard_restitution = 1.0f;

	// Creating storage
	blob = new Particle[BLOB_COUNT];
	platforms = new Platform[PLATFORM_COUNT];
	quadtree = new Quadtree(0, 0, 200, 200, 0, 2);

	// setting up bounding platforms
	platforms[0].start = Vector2(-nRange * margin, -nRange * margin);
	platforms[0].end = Vector2(nRange * margin, -nRange * margin);
	platforms[0].restitution = standard_restitution;

	platforms[1].start = Vector2(-nRange * margin, nRange * margin);
	platforms[1].end = Vector2(nRange * margin, nRange * margin);
	platforms[1].restitution = standard_restitution;

	platforms[2].start = Vector2(-nRange * margin, -nRange * margin);
	platforms[2].end = Vector2(-nRange * margin, nRange * margin);
	platforms[2].restitution = standard_restitution;

	platforms[3].start = Vector2(nRange * margin, -nRange * margin);
	platforms[3].end = Vector2(nRange * margin, nRange * margin);
	platforms[3].restitution = standard_restitution;

	// setting up custom platforms
	platforms[4].start = Vector2(0.0, -50);
	platforms[4].end = Vector2(-25.0, -95.0);
	platforms[4].setRestitution(0.8f);

	platforms[5].start = platforms[4].start;
	platforms[5].end = Vector2(25.0, -95.0);
	platforms[5].setRestitution(0.8f);

	platforms[6].start = Vector2(-95, -70.0);
	platforms[6].end = Vector2(0.0, -95.0);
	platforms[6].setRestitution(1.1f);

	platforms[7].start = Vector2(95, -70.0);
	platforms[7].end = Vector2(0.0, -95.0);
	platforms[7].setRestitution(1.1f);

	Vector2 location;
	 //Create the blobs
	float minColour = 0.2f;
	for (unsigned i = 0; i < BLOB_COUNT; i++) {

		// generating values for blob colour
		for (unsigned j = 0; j < 3; j++) {
			colour[j] = float(rand() % 256) / 256;
			if (colour[j] < minColour) colour[j] += minColour; // making sure the ball doesn't blend in with the background
		}
		// generating values for blob location
		location = Vector2(float(rand() % 170 - 85), float(rand() % 150 - 65));
		

		//setting up blob inital values
		blob[i].setRGB(colour[0], colour[1], colour[2]);
		blob[i].setPosition(location.x, location.y);
		blob[i].setParticleSides(0); // making blob a circle
		blob[i].setRadius(4);
		blob[i].setVelocity(rand() % 20 - 10, 0);
		blob[i].setDamping(0.9);
		blob[i].setMass(30.0f);
		blob[i].setAcceleration(Vector2::GRAVITY * blob[i].getMass());
		blob[i].clearAccumulator();
		world.getParticles().push_back(blob + i);// adding blob to world
		
	}
	for (unsigned i = 0; i < BLOB_COUNT/2; i++) blob[i].setParticleSides(4); // making half the circles a square

	// Make sure the platform knows which particle it should collide with.
	for (unsigned i = 0; i < PLATFORM_COUNT; i++) {
		platforms[i].particles = blob;
		world.getContactGenerators().push_back(platforms + i);
	}

	// code to generate a 
	collision = new ParticleCollision();
	collision->setQuadtree(quadtree);
	collision->particles = blob;

	uniqueSpawns();

	world.getContactGenerators().push_back(collision);
	timer = std::time(nullptr);

}

void BlobDemo::uniqueSpawns() { // makes it so any colliding particles are placed in non-collision locations
	if (UNIQUE_SPAWNS) {
		std::cout << "============================================================================" << std::endl;
		std::cout << "Running the unique spawns code..." << std::endl;
		std::cout << "If it takes too long you may have too many particles for the simulated area." << std::endl;
		std::cout << "============================================================================" << std::endl;
		// will stay in while loop if it has had to change the location of a particle in the run of the for loop
		// uses optimised brute force
		// can get caught in a loop if there are too many particles
		// high density but plausable simulations may also not complete since it's entirely random
		bool torf = true;
		while (torf) {
			torf = false;
			for (unsigned i = 0; i < BLOB_COUNT - 1; i++) {
				for (unsigned j = i + 1; j < BLOB_COUNT; j++) {
					if (collision->checkCollision(&blob[i], &blob[j])) {
						blob[i].setPosition(float(rand() % 180 - 90), float(rand() % 180 - 90));
						torf = true;
					}
				}
			}
		}
	}
}

BlobDemo::~BlobDemo()
{
	delete blob;
}

void BlobDemo::display()
{
	Application::display();
	// drawing all lines
	glBegin(GL_LINES);
	for (unsigned i = 0; i < PLATFORM_COUNT; i++) platforms[i].draw();
	glEnd();

	// drawing all particles
	for (unsigned i = 0; i < BLOB_COUNT; i++) blob[i].draw();

	glutSwapBuffers();
}

void BlobDemo::update()
{
	// Recenter the axes
	float duration = timeinterval / 1000;
	// Run the simulation
	world.runPhysics(duration);

	Application::update();

	// frames per second output
	fps++;
	if (timer != std::time(nullptr)) {
		timer = std::time(nullptr);
		std::cout << "FPS: " << fps << std::endl;
		fps = 0;
	}
}

// returns title for application
const char* BlobDemo::getTitle()
{
	return "Blob Demo";
}

// returns a blob demo for external use
Application* getApplication()
{
	return new BlobDemo();
}