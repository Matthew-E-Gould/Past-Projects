#pragma once

#include <vector>
#include "Particle.h"
#include "pcontacts.h"
#include <list>
#include <string>

class Quadtree {
public:
	Quadtree(float xPos, float yPos, float inpWidth, float inpHeight, int inpLevel, int levelLimit);
	void insert(Particle *object);
	void clear();
	std::vector<Particle*> retrieve(std::vector<Particle*> *pList, Particle* blob);
	void showGrid();
private:
	//Attrbutes of the structure we are passing through, so a rectangle which is the starting grid shape
	float x;
	float y;
	float width;
	float height;
	//the current levle of the tree, max level of depth it can go and max amount of objects in each square
	int level;
	int maxLevel;
	int maxObjects;
	std::string quad_id;
	//Create a list to store an array of pointers to instances of objects
	std::vector<Particle*> particles;
	
	//Create an array of pointers to store quadtree elements
	Quadtree* nodes[4];

	//to split the tree into sub nodes
	void split();
	//get the index of the element to work out where it goes in the tree
	int getIndex(Particle* blob);
};
