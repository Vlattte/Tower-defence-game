#include "mapinfo.h"

map_settings::map_settings()
{
}

void map_settings::set_varieties(number_of_map n)
{
    switch (n)
    {
        case first_map:
            variety.base_point =  {1180.0, 490.0};
            variety.map_name = ":/images/images/lvl_one_background";

            //set tower builder points
            variety.tbp[0] = {660, 400};
            variety.tbp[1] = {340, 75};
            variety.tbp[2] = {600, 190};
            variety.tbp[3] = {900, 200};
            variety.tbp[4] = {900, 410};
            variety.tbp[5] = {55, 240};
            variety.tbp[6] = {360, 250};
            variety.tbp[7] = {210, 425};
            variety.tbp[8] = {1150, 410};
            variety.tbp[9] = {1150, 200};

            //set enemy points
                //bottom way
            variety.bottom_way.a = {500, 205};
            variety.bottom_way.b = {520, 230};
            variety.bottom_way.c = {715, 230};
            variety.bottom_way.d = {785, 270};
            variety.bottom_way.e = {790, 275};
            variety.bottom_way.f = {795, 278};
            variety.bottom_way.g = {795, 490};
            variety.bottom_way.h = {999, 490};
            variety.bottom_way.i = {1000, 490};

                //upper way
            variety.upper_way.a = {500, 160};
            variety.upper_way.b = {510, 130};
            variety.upper_way.c = {530, 110};
            variety.upper_way.d = {550, 90};
            variety.upper_way.e = {600, 65};
            variety.upper_way.f = {990, 65};
            variety.upper_way.g = {1035, 95};
            variety.upper_way.h = {1070, 150};
            variety.upper_way.i = {1070, 500};


            break;
        case second_map:
            break;
    }
}
