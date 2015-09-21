#ifndef CAR_H_
#define CAR_H_

#include "Wheel.h"
#include <vector>
#include <string>
using std::string;
using std::vector;

class Car
{
  private:
     vector<Wheel*> wheels;
     string licencePlate;
     string model;

  public:
    Car(const string& model, const string& material, int diameter, int nrWheels);
    /* pre : diameter > 0 and nrWheels > 2
       post: A Car object is created that contains nrWheels Wheel objects
             with the given material and diameter
    */

   virtual ~Car();
   	/* pre : -
	   post: the Car object is destroyed including all allocated memory
	*/

    string getModel();
    /* pre : -
       post: getModel()= <Car> model
    */

    void setLicencePlate(const string& licence);
    /* pre : -
       post: <Car>'s licence plate is licence
    */

    string getLicencePlate();
    /* pre : -
       post: getLicencePlate()= <Car>'s licence plate
    */

    int getNrWheels();
    /* pre : -
       post: getNrWheels()= <Car>'s nr wheels
    */

    Wheel* getWheel(int index);
    /* pre : 0 <= index < nr wheels in <Car>
       post: getWheel(i) = Wheel nr index of <Car>
    */

    void removeWheel(int index);
    /* pre : -
       post: if 0 <= index < nr wheels in <Car>
             then wheel nr index is removed from <Car>
             else out_of_range exception with text: "illegal index" is thrown
    */

	void addWheel(int diameter, const string& material);
	/* pre : diameter > 0
	   post: a wheel with given diameter and material is added to <Car>
	*/

	Car(const Car& myCar);
    /* pre : -
	   post: a Car object is created with all properties of myCar, a deep copy is performed
    */

	Car& operator=(const Car& mijnCar);
	/* pre : -
	   post: all properties of this object are replaced with myCar's properties,
	         all previously existing properties are properly cleaned up and new
	         properties are deep copied
	*/
};

#endif
