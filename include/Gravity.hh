#pragma once

#include "AEnvironmentalEffect.hh"
#include "Scene.hh"

namespace EnvironmentalEffect
{
	class							Gravity : public AEnvironmentalEffect
	{
	private:
		float						_gravityScale;

	public:
		Gravity(float gravityScale = 9.81f);
		virtual ~Gravity();

		float const					getGravityScale() const;
		void						setGravityScale(float gravityScale);

		virtual void applyEffect();
	};
}