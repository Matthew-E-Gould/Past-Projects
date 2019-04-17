#include <float.h>
#include <pcontacts.h>
#include <iostream>

// Contact implementation
void ParticleContact::resolve(float duration)
{
	resolveInterpenetration(duration);
    resolveVelocity(duration);
}

// calculates how much the particles bounce away for its collision
float ParticleContact::calculateSeparatingVelocity() const
{
    Vector2 relativeVelocity = particle[0]->getVelocity();
    if (particle[1]) relativeVelocity -= particle[1]->getVelocity();
    return relativeVelocity * contactNormal;
}

void ParticleContact::resolveVelocity(float duration)
{
    // Find the velocity in the direction of the contact
    float separatingVelocity = calculateSeparatingVelocity();

    // Check if it needs to be resolved
    if (separatingVelocity > 0)
    {
        // The contact is either separating, or stationary - there's
        // no impulse required.
        return;
    }
    // Calculate the new separating velocity
    float newSepVelocity = -separatingVelocity * restitution;

    float deltaVelocity = newSepVelocity - separatingVelocity;

    // We apply the change in velocity to each object in proportion to
    // their inverse mass (i.e. those with lower inverse mass [higher
    // actual mass] get less change in velocity)..
    float totalInverseMass = particle[0]->getInverseMass();
    if (particle[1]) totalInverseMass += particle[1]->getInverseMass();

    // If all particles have infinite mass, then impulses have no effect
    if (totalInverseMass <= 0) return;

    // Calculate the impulse to apply
    float impulse = deltaVelocity / totalInverseMass;

    // Find the amount of impulse per unit of inverse mass
    Vector2 impulsePerIMass = contactNormal * impulse;

	//maths debug
	//std::cout << "=====================================================================================" << std::endl;
	//std::cout << "restitution: " << restitution << std::endl;
	//std::cout << "separatingVelocity: " << separatingVelocity << std::endl;
	//std::cout << "newSepVelocity: " << newSepVelocity << std::endl;
	//std::cout << "separatingVelocity: " << separatingVelocity << std::endl;
	//std::cout << "deltaVelocity: " << deltaVelocity << std::endl;
	//std::cout << "totalInverseMass: " << totalInverseMass << std::endl;
	//std::cout << "impulsePerIMass: x-> " << impulsePerIMass.x << " y-> " << impulsePerIMass.y << std::endl;
	//std::cout << "contactNormal:   x-> " << contactNormal.x << " y-> " << contactNormal.y << std::endl;
	//std::cout << "impulse: " << impulse << std::endl;
	//std::cout << "=====================================================================================" << std::endl;

    // Apply impulse
    particle[0]->setVelocity(particle[0]->getVelocity() +
        impulsePerIMass * particle[0]->getInverseMass()
        );
    if (particle[1])
    {
        // Particle 1 bounces away
        particle[1]->setVelocity(particle[1]->getVelocity() +
            impulsePerIMass * -particle[1]->getInverseMass()
            );
    }
}

void ParticleContact::resolveInterpenetration(float duration)
{
	// If we don't have any penetration, skip this step.
	if (penetration <= 0) return;
	// The movement of each object is based on their inverse mass, so
	// total that.
	float totalInverseMass = particle[0]->getInverseMass();
	if (particle[1]) totalInverseMass += particle[1]->getInverseMass();
	// If all particles have infinite mass, then we do nothing
	if (totalInverseMass <= 0) return;
	// Find the amount of penetration resolution per unit of inverse mass
	Vector2 movePerIMass = contactNormal * (penetration / totalInverseMass);
	// Calculate the the movement amounts
	particleMovement[0] = movePerIMass * particle[0]->getInverseMass();
	if (particle[1]) {
		particleMovement[1] = movePerIMass * -particle[1]->getInverseMass();
	}
	else {
		particleMovement[1].clear();
	}
	// Apply the penetration resolution
	particle[0]->setPosition(particle[0]->getPosition() + particleMovement[0]);
	if (particle[1]) {
		particle[1]->setPosition(particle[1]->getPosition() + particleMovement[1]);
	}
}

void ParticleContactResolver::updateInterpenetrations(ParticleContact *contactArray, unsigned numContacts,
	unsigned maxIndex) {
}
ParticleContactResolver::ParticleContactResolver(unsigned iterations)
:
iterations(iterations)
{
}

void ParticleContactResolver::setIterations(unsigned iterations)
{
    ParticleContactResolver::iterations = iterations;
}

void ParticleContactResolver::resolveContacts(ParticleContact *contactArray, unsigned numContacts, float duration)
{
    unsigned i;

    for (iterationsUsed = 0; iterationsUsed < iterations; iterationsUsed++)
    {
        // Find the contact with the largest closing velocity;
        float max = DBL_MAX;
        unsigned maxIndex = numContacts;
        for (i = 0; i < numContacts; i++)
        {
            float sepVel = contactArray[i].calculateSeparatingVelocity();
            if (sepVel < max &&
                (sepVel < 0 || contactArray[i].penetration > 0))
            {
                max = sepVel;
                maxIndex = i;
            }
        }
         // if there are no resolutions left, break
        if (maxIndex == numContacts) break;

        // Resolve contact
        contactArray[maxIndex].resolve(duration);
		Vector2 *move = contactArray[maxIndex].particleMovement;
		for (int i = 0; i < numContacts; i++)
		{
			//std::cout << "interpenetration" << std::endl;
			if (contactArray[i].particle[0] == contactArray[maxIndex].particle[0])
			{
				contactArray[i].penetration -= move[0] * contactArray[i].contactNormal;
			}
			else if (contactArray[i].particle[0] == contactArray[maxIndex].particle[1])
			{
				contactArray[i].penetration -= move[1] * contactArray[i].contactNormal;
			}
			if (contactArray[i].particle[1])
			{
				if (contactArray[i].particle[1] == contactArray[maxIndex].particle[0])
				{
					contactArray[i].penetration += move[0] * contactArray[i].contactNormal;
				}
				else if (contactArray[i].particle[1] == contactArray[maxIndex].particle[1])
				{
					contactArray[i].penetration += move[1] * contactArray[i].contactNormal;
				}
			}
		}
    }
}