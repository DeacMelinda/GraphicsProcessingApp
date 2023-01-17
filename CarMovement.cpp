#include "CarMovement.hpp"

namespace gps {

    //Car constructor
    Car::Car(glm::vec3 carPosition, glm::vec3 carTarget, glm::vec3 carUp) {

        this->carPosition = carPosition;
        this->carTarget = carTarget;
        this->carUpDirection = carUp;
        this->carFrontDirection = glm::normalize(carPosition - carTarget);
    }

    //return the view matrix, using the glm::lookAt() function
    glm::vec3 Car::getPosition() {

        return this->carPosition;
    }

    //update the car internal parameters following a car move event
    void Car::move(bool front, float speed) {

        if (front) {
            this->carPosition.x -= this->carFrontDirection.x * speed;
            this->carPosition.z -= this->carFrontDirection.z * speed;
        } else {

            this->carPosition.x += this->carFrontDirection.x * speed;
            this->carPosition.z += this->carFrontDirection.z * speed;
        }

        //carFrontDirection = glm::normalize(carPosition - carTarget);
        this->carTarget = this->carFrontDirection + this->carPosition;
    }

    //update the car internal parameters following a car rotate event
    //yaw - car rotation around the y axis
    //pitch - car rotation around the x axis
    void Car::rotate(float pitch, float yaw) {

        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

        this->carFrontDirection = glm::normalize(direction);
        this->carTarget = this->carFrontDirection + this->carPosition;
    }
}