#include "Layer.hh"
#include <exception>

Layer::Layer()
{
	_layer = 0;

	//(Layer::WALL);

	//_collisionMatrix =  {{ false, false, false, false, false },
	//					{ false, false, false, false, false }, 
	//					{ false, false, false, false, false }, 
	//					{ false, false, false, false, false }, 
	//					{ false, false, false, false, false }};
}


Layer::~Layer()
{
}

void Layer::checkLayerType(Layer::LayerTypes lt) const
{
	if (COUNT >= sizeof(int)* 4 || lt >= COUNT || lt < 0)
		throw new std::exception("invalid LayerType");
}


void Layer::addAllLayer()
{
	_layer = (unsigned int)-1;
}

void Layer::rmAllLayer()
{
	_layer = 0;
}


void Layer::addLayer(Layer::LayerTypes lt)
{
	checkLayerType(lt);
	_layer |= (1 << lt);
}

void Layer::removeLayer(Layer::LayerTypes lt)
{
	checkLayerType(lt);
	_layer &= ~(1 << lt);
}

bool Layer::isInLayer(Layer::LayerTypes lt) const
{
	checkLayerType(lt);
	return ((_layer & (1 << lt)) != 0);
}

bool Layer::shareALayer(Layer l) const
{
	return ((l._layer & _layer) != 0);
}

unsigned int Layer::layerToInt(Layer::LayerTypes lt)
{
	if (COUNT >= sizeof(int)* 4 || lt >= COUNT || lt < 0)
		throw new std::exception("invalid LayerType");

	return (1 << lt);
}