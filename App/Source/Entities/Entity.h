#pragma once

class Entity
{
public:
	Entity();
	Entity(Vector3 position);
	virtual ~Entity() = default;
	Entity(const Entity& other) = default; // copy constructor
	Entity(Entity&& other) noexcept = default; // move constructor
	Entity& operator=(const Entity& other) = default; //copy assignment
	Entity& operator = (Entity&& other) noexcept = default; //Move assignment

	//Getters
	[[nodiscard]] Vector3 GetPosition() const;
	[[nodiscard]] Model GetModel() const;
	[[nodiscard]] BoundingBox GetBoundingBox() const;
	//Setters
	void SetPosition(Vector3 position);
	void SetModel(Model model);
	virtual void SetBoundingBox(BoundingBox boundingBox);
	//Functions
	virtual void Move(Vector3 velocity, float delta, float baseSpeed = 1);
private:
	Vector3 m_position;
protected:
	Model m_model;
	BoundingBox m_boundingBox;
};