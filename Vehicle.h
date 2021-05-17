//
// Created by diogo on 16/05/2021.
//

#ifndef UNTITLED21_VEHICLE_H
#define UNTITLED21_VEHICLE_H

#include <iostream>
#include <vector>
#include <string>
#include <iostream>
#include <utility>

#include <limits>
#include <cmath>

class Vehicle{
    private:
         int ID;
         int max_quantity=5000;
    public:
         int get_ID(){
             return ID;
         }
         void set_id(int y){
             ID=y;
         }

         int get_max_quantity(){
             return ID;
         }
};

#endif //UNTITLED21_VEHICLE_H
