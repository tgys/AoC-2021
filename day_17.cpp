//
// Created by tei on 12/18/21.
//


#include <bits/stdc++.h>

#define line_break() { \
    std::cin.ignore(10000, '\n'); \
    if(strlen(buffer) == 0){ \
    lastbuffernull = true; \
    }\
}

int svtoi(std::string_view sv) {
    int val;
    std::from_chars(sv.data(), sv.data() + sv.size(), val);
    return val;
}

struct Target{
    int min_x,max_x,min_y,max_y;
};

bool step(int& x, int& y, int& vel_x, int& vel_y, Target target){
    x += vel_x;
    y += vel_y;
    if(vel_x < 0){ vel_x+=1; } else if(vel_x > 0){ vel_x -=1; }
    vel_y = vel_y - 1;
    if(x >= target.min_x && x <= target.max_x && y >= target.min_y && y <= target.max_y){
        return false;
    }
    else return true;
}

int main()
{
    bool lastbuffernull = false;
    int max_input_len = 40;
    int high_x,high_y,high_y_pos = 0;
    std::vector<std::pair<int,int>> initial_vels;

    while(!lastbuffernull){
        char buffer[max_input_len];
        std::cin.get( buffer, max_input_len );
        if(strlen(buffer) != 0){
            auto s = std::string_view(buffer);
            //std::cout << s << '\n';
            auto tx = s.substr(0,s.find(", "));
            auto ty = s.substr(s.find(", ") + 2, s.npos);
            Target target;
            int x1 = svtoi(tx.substr(tx.find("=") + 1, tx.find("..")-2));
            int x2 = svtoi(tx.substr(tx.find("..") + 2, tx.npos));
            int y1 = svtoi(ty.substr(ty.find("=") + 1, ty.find("..")-2));
            int y2 = svtoi(ty.substr(ty.find("..") + 2, ty.npos));
            target.min_x = std::min(x1,x2);
            target.max_x = std::max(x1,x2);
            target.min_y = std::min(y1,y2);
            target.max_y = std::max(y1,y2);

            int mx = std::min(std::abs(x1), std::abs(x2));
            int min_vel_x = 0;
            while(min_vel_x*(min_vel_x+1) < 2*mx){
                min_vel_x++;
            }

            int min_vel_y_pt1 = 0;
            if(target.min_y > 0){
                int my = std::min(std::abs(y1), std::abs(y2));
                while(min_vel_y_pt1*(min_vel_y_pt1+1) < 2*my){
                    min_vel_y_pt1++;
                }
            }
            int max_vel_x = std::max(std::abs(x1), std::abs(x2));
            if(target.min_x < 0){
                 min_vel_x = 0-min_vel_x;
                 max_vel_x = 0-max_vel_x;
            }
            int m_cnt = 0;
            //part1
            for(int start_vel_y = min_vel_y_pt1; m_cnt < target.max_y-target.min_y; ++start_vel_y) {
                int x = 0;
                int y = 0;
                int vel_y = start_vel_y;
                int vel_x = min_vel_x;
                int steps = 0;
                bool miss = true;
                while(std::abs(vel_x) > 0 && miss){
                    miss = step(x, y, vel_x, vel_y, target);
                    steps++;
                }
                if(vel_x == 0 && miss){
                    while(y > target.min_y && miss){
                        miss = step(x, y, vel_x, vel_y, target);
                        steps++;
                    }
                }
                if(!miss){
                    if(start_vel_y > high_y){
                        high_y = start_vel_y;
                        high_x = min_vel_x;
                    }
                    m_cnt = 0;
                } else {
                    m_cnt++;
                }
            }
            high_y_pos = (high_y*(high_y+1))/2;
            for(int start_vel_x = max_vel_x; start_vel_x >= min_vel_x; --start_vel_x){
                m_cnt = 0;
                for(int start_vel_y = high_y; m_cnt < 9999; --start_vel_y) {
                    int x = 0;
                    int y = 0;
                    int vel_y = start_vel_y;
                    int vel_x = start_vel_x;
                    int steps = 0;
                    bool miss = true;
                    while(std::abs(vel_x) > 0 && miss){
                        miss = step(x, y, vel_x, vel_y, target);
                        steps++;
                    }
                    if(vel_x == 0 && miss){
                        while(y > target.min_y && miss){
                            miss = step(x, y, vel_x, vel_y, target);
                            steps++;
                        }
                    }
                    if(!miss){
                        std::pair<int,int> this_ini{start_vel_x,start_vel_y};
                        initial_vels.push_back(this_ini);
                        m_cnt = 0;
                    } else {
                        m_cnt++;
                    }
                }
            }


        }
        line_break();
    }

    std::cout<< "number of different initial velocity values: "<< initial_vels.size() << '\n';
    std::cout << "highest y position: " << high_y_pos << " highest initial velocity: " << high_x << ',' << high_y << '\n';
    return 0;
}
