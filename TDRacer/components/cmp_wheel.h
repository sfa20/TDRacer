#include "Box2D\Box2D.h"
#include "ecm.h"


enum {
	TDC_LEFT = 0x1,
	TDC_RIGHT = 0x2,
	TDC_UP = 0x4,
	TDC_DOWN = 0x8
};


#pragma region needs Seperated into own classes

enum fixtureUserDataType {
	FUD_CAR_TIRE,
	FUD_GROUND_AREA
};

//a class to allow subclassing of different fixture user data
class FixtureUserData {
	fixtureUserDataType m_type;
protected:
	FixtureUserData(fixtureUserDataType type) : m_type(type) {}
public:
	virtual fixtureUserDataType getType() { return m_type; }
	virtual ~FixtureUserData() {}
};

//class to allow marking a fixture as a car tire
class CarTireFUD : public FixtureUserData {
public:
	CarTireFUD() : FixtureUserData(FUD_CAR_TIRE) {}
};

//class to allow marking a fixture as a ground area
class GroundAreaFUD : public FixtureUserData {
public:
	float frictionModifier;
	bool outOfCourse;

	GroundAreaFUD(float fm, bool ooc) : FixtureUserData(FUD_GROUND_AREA) {
		frictionModifier = fm;
		outOfCourse = ooc;
	}
};


#pragma endregion


class WheelComponent : public Component {
public:
	b2Body* body;
	
	float maxForwardSpeed;
	float maxBackwardSpeed;
	float maxDriveForce;
	float maxLateralImpulse;
	float maxLateralForce;
	
	std::set<GroundAreaFUD*> groundAreas;
	float currentTraction;

	WheelComponent(Entity* p);

	~WheelComponent();

	void setCharacteristics(float maxForwardSpeed, float maxBackwardSpeed, float maxDriveForce, float maxLateralImpulse);

	void addGroundArea(GroundAreaFUD* ga);
	void removeGroundArea(GroundAreaFUD* ga);

	void updateTraction();

	b2Vec2 getLateralVelocity();

	b2Vec2 getForwardVelocity();

	void updateFriction();

	void updateDrive(int controlState);

	void updateTurn(int controlState);
};