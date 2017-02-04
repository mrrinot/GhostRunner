#pragma once

class							Layer
{
public:
	enum LayerTypes
	{
		DEFAULT = 0,
		
		PLAYERGHOST,

		PLAYER,
		GHOST,
		
		WALL,
		GHOST_WALL,

		BONUS,

		COUNT
	};

private:
	unsigned int				_layer;
	//bool						_collisionMatrix[COUNT][COUNT];

	void						checkLayerType(LayerTypes lt) const;

public:
	Layer();
	~Layer();

	void						addAllLayer();
	void						rmAllLayer();
	void						addLayer(LayerTypes lt);
	void						removeLayer(LayerTypes lt);
	bool						isInLayer(LayerTypes lt) const;
	bool						shareALayer(Layer l) const;

	static unsigned int			layerToInt(LayerTypes lt); // may be useful. // Nop
};

