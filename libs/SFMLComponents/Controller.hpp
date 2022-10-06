/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Controller
*/

#ifndef CONTROLLER_HPP_
#define CONTROLLER_HPP_

#include <SFML/Graphics.hpp>

class Controller {
    public:
        enum controllerInputE
        {
            UNDEFINE,
            BUTTON_1,
            BUTTON_2,
            BUTTON_3,
            BUTTON_4,
            DIRECTION_1,
            DIRECTION_2,
            DIRECTION_3,
            DIRECTION_4,
            JOY_1_1,
            JOY_1_2,
            JOY_1_3,
            JOY_1_4,
            JOY_1_5,
            JOY_2_1,
            JOY_2_2,
            JOY_2_3,
            JOY_2_4,
            JOY_2_5,
            OPTION,
            SHARE,
            HOME,
            BACK_RIGHT_1,
            BACK_RIGHT_2,
            BACK_LEFT_1,
            BACK_LEFT_2
        };
        Controller();
        ~Controller();
    private:
        controllerInputE input;
        float value;
};

#endif /* !CONTROLLER_HPP_ */
