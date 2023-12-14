#define ROTATE_SPEED 10

/*
* Przykładowy zestaw poleceń
*/

Begin_Parallel_Actions
    Set Base 0 0 0 0 0 0
    Set Base.Hood 0 0 0 0 0 0
    Set Base.Boot 0 0 0 0 0 0
    Set Base.Boot.WheelLeft 0 0 0 0 0 0
    Set Base.Boot.WheelRight 0 0 0 0 0 0
    Set Base.Hood.WheelLeft 0 0 0 0 0 0
    Set Base.Hood.WheelRight 0 0 0 0 0 0
End_Parallel_Actions
Begin_Parallel_Actions
    Rotate Base OZ ROTATE_SPEED 90 
    Rotate Base OX ROTATE_SPEED 180 
    Rotate Base OY ROTATE_SPEED 360 
    Rotate Base.Boot.WheelLeft OZ ROTATE_SPEED 180 
    Rotate Base.Boot.WheelRight OZ ROTATE_SPEED 180 
    Rotate Base.Hood.WheelLeft OZ ROTATE_SPEED 180 
    Rotate Base.Hood.WheelRight OZ ROTATE_SPEED 180 
End_Parallel_Actions
Begin_Parallel_Actions
    Rotate Base.Boot.WheelLeft OZ 20 10080 
    Rotate Base.Boot.WheelRight OZ 40 10080 
    Rotate Base.Hood.WheelLeft OZ 2 10080 
    Rotate Base.Hood.WheelRight OZ 20 10080 
End_Parallel_Actions
