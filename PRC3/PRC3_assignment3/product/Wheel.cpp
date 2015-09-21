#include <string>
#include "Wheel.h"

Wheel::Wheel(int diameter, const std::string& material)
	: diameter(diameter), material(material)
{

}
/* pre : d > 0
post: A Wheel object is created with the given material and diameter
*/

std::string Wheel::getMaterial()
{
	return material;
}
/* pre : -
post: getMaterial()= <Wheel>'s material
*/

void Wheel::setMaterial(const std::string& material)
{
	this->material = material;
}
/* pre : -
post: <Wheel>'s material is now material
*/

int Wheel::getDiameter()
{
	return diameter;
}
/* pre : -
post getDiameter() = <Wheel>'s diameter
*/