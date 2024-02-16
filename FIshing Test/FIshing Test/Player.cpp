
#include "Player.h"
#include "Fish.h"
#include <iostream>

Player::Player()
{
}

Player::~Player()
{
}



// Object (Fish) Functions
void Player::setupPlayer(sf::Vector2f t_pos)
{
	// Fish
	m_body.setFillColor(sf::Color::Green);
	m_body.setPosition(t_pos);
	m_body.setSize(m_size);
}

void Player::move()
{
	float movement = -5.0f;

	// Constant move
	m_location.y += movement;
	m_body.setPosition(m_location);
}

void Player::gravity()
{
	m_location += m_gravity;
	m_body.setPosition(m_location);
}

void Player::areaBoundries()
{
	const float MAX_HIGHT = 160.0f;
	const float MIN_HIGHT = 445.0f;

	if (m_location.y <= MAX_HIGHT)
	{
		m_location.y = MAX_HIGHT;
		m_body.setPosition(m_location);
	}
	if (m_location.y >= MIN_HIGHT)
	{
		m_location.y = MIN_HIGHT;
		m_body.setPosition(m_location);
	}
}


// Checks if the player is catching the fish
void Player::catchingCheck(bool t_colliding)
{
	if (t_colliding)
	{
		if (m_catchingMeter < WIN_CONDITION)
		{
			m_catchingMeter++;
		}
	}
	else
	{
		if (m_catchingMeter > 0)
		{
			m_catchingMeter -= 3;

			// Makes sure it's not a negative number
			if (m_catchingMeter < 0)
			{
				m_catchingMeter = 0;
			}
		}
	}
}