#include "mapinfo.h"

map_settings::map_settings()
{ }

void map_settings::set_varieties(number_of_map n)
{
    switch (n)
    {
        case first_map:
            variety.base_point =  {1180, 490};
            variety.map_name = ":/images/images/lvl_one_background.png";    //grass map

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
                //easy way

            variety.special_point[0] = {0, 415};
            variety.special_point[1] = {0, 430};
            variety.special_point[2] = {75, 480};
            variety.special_point[3] = {400, 480};
            variety.special_point[4] = {475, 510};


                //upper way
            variety.upper_way.start = {0, 100};
            variety.upper_way.a0 = {80,100};
            variety.upper_way.a1 = {155, 140};
            variety.upper_way.a2 = {420,140};
            variety.upper_way.a3 = {485, 175};

            variety.upper_way.a = {500, 160};
            variety.upper_way.b = {510, 130};
            variety.upper_way.c = {530, 110};
            variety.upper_way.d = {550, 90};
            variety.upper_way.e = {600, 65};
            variety.upper_way.f = {990, 65};
            variety.upper_way.g = {1035, 95};
            variety.upper_way.h = {1070, 150};
            variety.upper_way.i = {1070, 500};
            variety.upper_way.j = {1080, 510};

                //bottom way
            variety.bottom_way.start = {0, 100};
            variety.bottom_way.a0 = {80,100};
            variety.bottom_way.a1 = {155, 140};
            variety.bottom_way.a2 = {420,140};
            variety.bottom_way.a3 = {485, 175};

            variety.bottom_way.a = {500, 205};
            variety.bottom_way.b = {520, 230};
            variety.bottom_way.c = {715, 230};
            variety.bottom_way.d = {785, 270};
            variety.bottom_way.e = {790, 275};
            variety.bottom_way.f = {795, 278};
            variety.bottom_way.g = {795, 490};
            variety.bottom_way.h = {999, 490};
            variety.bottom_way.i = {1000, 490};
            variety.bottom_way.j = {1080, 510};


            //finish line
            variety.finish = QPoint(1240, 510);


            break;

        case second_map:
            variety.base_point =  {1200, 100};
            variety.map_name = ":/images/images/lvl_two_background.png"; //sand map

            //set tower builder points
            variety.tbp[0] = {790, 220};
            variety.tbp[1] = {110, 310};
            variety.tbp[2] = {590, 220};
            variety.tbp[3] = {400, 310};
            variety.tbp[4] = {725, 490};
            variety.tbp[5] = {955, 360};
            variety.tbp[6] = {320, 580};
            variety.tbp[7] = {210, 400};
            variety.tbp[8] = {110, 580};
            variety.tbp[9] = {1100, 200};

            //set enemy points
                //easy way

            variety.special_point[0] = {0, 460};
            variety.special_point[1] = {600, 460};
            variety.special_point[2] = {665, 395};
            variety.special_point[3] = {850, 385};
            variety.special_point[4] = {850, 315};

                //upper way
            variety.upper_way.start = {0, 175};
            variety.upper_way.a0 = {90,190};
            variety.upper_way.a1 = {445, 190};
            variety.upper_way.a2 = {450,190};
            variety.upper_way.a3 = {490,130};

            variety.upper_way.a = {495, 125};
            variety.upper_way.b = {500, 120};
            variety.upper_way.c = {505, 118};
            variety.upper_way.d = {1001, 117};
            variety.upper_way.e = {1002, 118};
            variety.upper_way.f = {1010, 119};
            variety.upper_way.g = {1020, 118};
            variety.upper_way.h = {1030, 120};
            variety.upper_way.i = {1040, 118};
            variety.upper_way.j = {1041, 120};



                //bottom way
            variety.bottom_way.start = {0, 175};
            variety.bottom_way.a0 = {90, 200};
            variety.bottom_way.a1 = {445, 200};
            variety.bottom_way.a2 = {470, 210};
            variety.bottom_way.a3 = {520, 260};

            variety.bottom_way.a = {530, 275};
            variety.bottom_way.b = {860, 290};
            variety.bottom_way.c = {990, 190};
            variety.bottom_way.d = {1000, 130};
            variety.bottom_way.e = {1005, 129};
            variety.bottom_way.f = {1010, 128};
            variety.bottom_way.g = {1020, 127};
            variety.bottom_way.h = {1030, 126};
            variety.bottom_way.i = {1040, 125};
            variety.bottom_way.j = {1041, 125};


            //finish line
            variety.finish = QPoint(1240, 120);


            break;
    }
}
