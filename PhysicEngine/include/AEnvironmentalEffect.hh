#pragma once

#include <string>

namespace EnvironmentalEffect
{
	typedef enum	e_EnvironmentalEffectType
	{
		GRAVITY,
		BLACKHOLE
	}				EET;

	class						AEnvironmentalEffect
	{
	private:
		EET const				_eet;

	protected:
		AEnvironmentalEffect(const AEnvironmentalEffect& eet);
		AEnvironmentalEffect&	operator=(const AEnvironmentalEffect&);

	public:
		AEnvironmentalEffect(const EET& eet);
		virtual	~AEnvironmentalEffect();

		EET const				getEET() const;
		virtual void			applyEffect() = 0;
	};
}