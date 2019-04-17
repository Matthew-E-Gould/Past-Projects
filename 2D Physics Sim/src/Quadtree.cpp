#include "Quadtree.h"
#include "gl/glut.h"
#include <vector>
#include <iostream>

Quadtree::Quadtree(float xPos, float yPos, float inpWidth, float inpHeight, int inpLevel, int levelLimit) {

	
	maxLevel = levelLimit;

	for (unsigned i = 0; i < 4; i++) nodes[i] = nullptr;
	x = xPos; // center point of grid
	y = yPos; // center point of grid
	width = inpWidth; // width of box
	height = inpHeight; // height of box
	level = inpLevel; // 0 is top layer
	maxObjects = 3; //max amount of objects allowed before node gets split
	//std::cout << "Level: " << level << "\t| Width: " << width << "\t| Height: " << height << "\t| mid.X: " << x << "\t| mid.Y: " << y << std::endl;
}

//clears nodes
void Quadtree::clear() {
	particles.clear();

	//go through each node to clear the contents there are four nodes
	for (int i = 0; i < 4; i++) {
		if (nodes[i] != NULL) {
			nodes[i]->clear();
			nodes[i] = NULL;
		}
	}
}

//creates child nodes
void Quadtree::split() {
	//std::cout << "SPLIT()" << std::endl;
	int childWidth = width / 2;
	int childHeight = height / 2;

	//Create four new instance of quadtree one for each quadrant in the parent node, increment the level of the tree, work out the sizes
	//of the new nodes using the new sub widths

	if (level == 0) {
		nodes[0] = new Quadtree(-childWidth / 2, childHeight / 2, -childWidth, childHeight, level + 1, maxLevel); //NW
		nodes[1] = new Quadtree(childWidth / 2, childHeight / 2, childWidth, childHeight, level + 1, maxLevel);  //NE
		nodes[2] = new Quadtree(-childWidth / 2, -childHeight / 2, -childWidth, -childHeight, level + 1, maxLevel);//SW
		nodes[3] = new Quadtree(childWidth / 2, -childHeight / 2, childWidth, -childHeight, level + 1, maxLevel); //SE
	}
	else {

		//new Quadtree(mid.x, mid.y, subWidth, subHeight, level + 1);
		nodes[0] = new Quadtree(childWidth - childWidth / 2, childHeight + childHeight / 2, childWidth, childHeight, level + 1, maxLevel);//NW
		nodes[1] = new Quadtree(childWidth + childWidth / 2, childHeight + childHeight / 2, childWidth, childHeight, level + 1, maxLevel);//NE
		nodes[2] = new Quadtree(childWidth - childWidth / 2, childHeight - childHeight / 2, childWidth, childHeight, level + 1, maxLevel);//SW
		nodes[3] = new Quadtree(childWidth + childWidth / 2, childHeight - childHeight / 2, childWidth, childHeight, level + 1, maxLevel);//SE
	}
}

//works out where the particle is
int Quadtree::getIndex(Particle* blob) 
{
	int index = -1;
	double verticalMid = 0;
	double horizontalMid = 0;

	//if the y of the particle is above the midpoint then its in one of the top quadrants
	bool topHalf = blob->getPosition().y > horizontalMid 
		&& blob->getPosition().y + blob->getRadius() * 2 > horizontalMid;

	//if the y particle is below the midpoint then its in one of the bottom quadrants
	bool leftHalf = blob->getPosition().x < verticalMid; //horizontalMid);

	if (leftHalf) {
		if (topHalf) {
			//if the particle is above the midpoint then its on the TOP LEFT
			index = 0;
		}
		else
		{
			//else its on the BOTTOM LEFT
			index = 2;
		}	
	}
	else
	{
		//ELSE the particle is on the RIGHT SIDE
		if (topHalf) {
			//if the particle is above the midpoint then its on the TOP RIGHT
			index = 1;
		}
		else
		{
			//else its on the BOTTOM RIGHT
			index = 3;
		}
	}
	
	return index;
}

// shows quadtree
void Quadtree::showGrid()
{
	glLineWidth(1);
	glColor3f(1.0, 1.0, 1.0);

	glBegin(GL_LINES);
	glVertex2f(this->x - (width / 2), this->y);
	glVertex2f(this->x + (width / 2), this->y);
	glVertex2f(this->x, this->y - (height / 2));
	glVertex2f(this->x, this->y + (height / 2));

	if (this->nodes[0]->nodes[0] != nullptr)
		this->nodes[0]->showGrid();

	if (this->nodes[1]->nodes[1] != nullptr)
		this->nodes[1]->showGrid();

	if (this->nodes[2]->nodes[2] != nullptr)
		this->nodes[2]->showGrid();

	if (this->nodes[3]->nodes[3] != nullptr)
		this->nodes[3]->showGrid();
}

// automatically inserts the particle to its node
void Quadtree::insert(Particle *blob) {

	// keep running until particle is a low as it can be in the tree
	if (nodes[0] != NULL) {
		int index = getIndex(blob);
			//std::cout << "index is: " << index << "\n";

		if (index != -1) {
			nodes[index]->insert(blob);
			return;
		}
	}

	//add the particle to the list of particles in this sub quadrant
	particles.push_back(blob);

	//if there are more nodes than a node can hold, split it again
	if (particles.size() > maxObjects && level < maxLevel) 
	{

		if (nodes[0] == NULL) 
		{
			//if the sub tree has not been created then make it
			split();

		}

		int i = 0;
		//move the particles from this nodes into the newly created sub nodes using recursion
		while (i < particles.size()) {
			int index = getIndex(particles[i]);
			//std::cout << blob->getPosition().x << " " << blob->getPosition().y << " " << index << "XY position and index\n\n";
			if (index != -1) {
				nodes[index]->insert(particles.at(i));
				particles.erase(particles.begin() + i);
			}else{
				i++;
			}
		}
	}
}

//gets the particles in the quad
std::vector<Particle*> Quadtree::retrieve(std::vector<Particle*> *objectList, Particle *blob) {
	//get the index of particle
	int index = getIndex(blob);
	//if the value has an index and the nodes has been made
	if (index != -1 && nodes[0] != NULL) {
		// let the recursive insanity begin, or has it already started?
		nodes[index]->retrieve(objectList, blob);
	}

	// add particles in bottom node to list
	objectList->insert(objectList->end(), particles.begin(), particles.end());
	
	//return the list to check
	return *objectList;
}
