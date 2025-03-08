#pragma once

class Entity
{
public:
	Entity(int id) : m_id(id) {}
	int GetID() const { return m_id; }

private:
	int m_id;
};