#ifndef CarMovement_hpp
#define CarMovement_hpp

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include <string>

namespace gps {

    class Car
    {
    public:
        //car constructor
        Car(glm::vec3 cameraPosition, glm::vec3 cameraTarget, glm::vec3 cameraUp);
        //return the view matrix, using the glm::lookAt() function
        glm::vec3 getPosition();
        //update the car internal parameters following a car move event
        void move(bool direction, float speed);
        //update the car internal parameters following a car rotate event
        //yaw - car rotation around the y axis
        //pitch - car rotation around the x axis
        void rotate(float pitch, float yaw);

    private:
        glm::vec3 carPosition;
        glm::vec3 carTarget;
        glm::vec3 carFrontDirection;
        glm::vec3 carUpDirection;
    };

}

#endif /* Camera_hpp */
