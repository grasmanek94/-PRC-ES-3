#ifndef WHEEL_H_
#define WHEEL_H_

#include <string>

/*
 *  destructor, copy constructor en assignment operator overloading is not needed as
 *  this class does not contain allocated memory
*/

class Wheel
{
  private:
    int diameter;
	std::string material;

  public:
    Wheel(int diameter, const std::string& material);
    /* pre : d > 0
       post: A Wheel object is created with the given material and diameter
    */

	std::string getMaterial();
    /* pre : -
       post: getMaterial()= <Wheel>'s material
    */

    void setMaterial(const std::string& material);
    /* pre : -
       post: <Wheel>'s material is now material
    */

    int getDiameter();
    /* pre : -
       post getDiameter() = <Wheel>'s diameter
    */

};

#endif
