//
// Created by tei on 12/13/21.
//

#include <bits/stdc++.h>

#define line_break() { \
    std::cin.ignore(10000, '\n'); \
    if(strlen(buffer) == 0){ \
    lastbuffernull = true; \
    }\
}

//typedef std::map<std::tuple<int, int>, int> OverlapMap;
/*
auto val = s.substr(s.find_last_of(' ') + 1, s.npos);
                std::string strnum = val.substr(val.find('=') + 1, val.npos);
                int num = stoi(strnum);
                //std::string cmd = val.substr(0, val.find('='));
                //std::cout << cmd << num << '\n';
                if(val.find('y') != val.npos){
                    for(auto it=map.begin(); it!=map.end(); ++it){
                        //std::cout << std::get<0>(*it) << ',' <<  std::get<1>(*it) << ' ';
                        int pt_x = std::get<0>(*it);
                        int pt_y = std::get<1>(*it);
                        if(pt_y > num){
                            int diff = pt_y - num;
                            int new_y = pt_y - diff;
                            std::tuple<int,int> new_coord{pt_x, new_y};
                            map.erase(it);
                            map.insert(new_coord);
                        }
                    }
                } else {
                    for(auto it=map.begin(); it!=map.end(); ++it){
                        int pt_x = std::get<0>(*it);
                        int pt_y = std::get<1>(*it);
                        if(pt_x > num){
                            int diff = pt_x - num;
                            int new_x = pt_x - diff;
                            std::tuple<int,int> new_coord{new_x, pt_y};
                            map.erase(it);
                            map.insert(new_coord);
                        }
                    }
                    for(auto i : map){
                        int pt_x = std::get<0>(i);
                        int pt_y = std::get<1>(i);
                        std::cout << "new map: \n";
                        std::cout << pt_x <<','<< pt_y << '\n';
                    }
                }
                std::cout << '\n';

 */

inline int svtoi(std::string_view sv) {
    int val;
    std::from_chars(sv.data(), sv.data() + sv.size(), val);
    return val;
}

int main()
{
    bool lastbuffernull = false;
    bool prevbufnull = false;
    int lines = 0;

    std::deque<std::tuple<int,int>> map;
    std::vector<std::tuple<char,int>> cmds;
    int first_dots = 0;

    while(!lastbuffernull){
        std::string s;
        std::getline(std::cin,s);
        if(s.size() != 0){
            if(!prevbufnull){
                auto x = s.substr(0, s.find(','));
                auto y = s.substr(s.find(',') + 1, s.npos);
                int xi = svtoi(x);
                int yi = svtoi(y);
                std::tuple<int,int> coord{xi,yi};
                map.push_back(coord);
            } else {
                auto val = s.substr(s.find_last_of(' ') + 1, s.npos);
                std::string strnum = val.substr(val.find('=') + 1, val.npos);
                int num = stoi(strnum);
                std::string axis = val.substr(0, val.find('='));
                std::tuple<char,int> cmd{axis[0],num};
                cmds.push_back(cmd);
            }
        } else {
            if(prevbufnull){
                int folds = 0;
                for(auto i : cmds) {
                    char cmd = std::get<0>(i);
                    int val = std::get<1>(i);
                    std::cout <<cmd << ' ' << val << '\n';
                    if(cmd == 'y'){
                        int mapsz = map.size();
                        for(int i=0; i < mapsz; ++i){
                            std::tuple<int,int> this_pt = map.back();
                            int pt_x = std::get<0>(this_pt);
                            int pt_y = std::get<1>(this_pt);
                            map.pop_back();
                            if(pt_y < val){
                                int diff = val - pt_y;
                                std::tuple<int,int> new_coord{pt_x, diff};
                                map.push_front(new_coord);
                            } else {
                                int y_shft = pt_y - val;
                                std::tuple<int,int> shift_down{pt_x, y_shft};
                                map.push_front(shift_down);
                            }
                        }
                    } else if (cmd == 'x') {
                        int mapsz = map.size();
                        for(int i=0; i < mapsz; ++i){
                            std::tuple<int,int> this_pt = map.back();
                            int pt_x = std::get<0>(this_pt);
                            int pt_y = std::get<1>(this_pt);
                            map.pop_back();
                            if(pt_x > val){
                                int diff = pt_x - val;
                                int new_x = val - diff;
                                std::tuple<int,int> new_coord{new_x, pt_y};
                                map.push_front(new_coord);
                            } else {
                                std::tuple<int,int> crd{pt_x, pt_y};
                                map.push_front(crd);
                            }
                        }

                    }
                    std::set<std::tuple<int,int>> no_dups(map.begin(),map.end());
                    std::deque<std::tuple<int,int>> newvec(no_dups.begin(),no_dups.end());
                    map = newvec;
                    if(folds==0) {
                        first_dots = map.size();
                    }
                    folds++;

                    int max_x = 0;
                    int max_y = 0;
                    for(auto tup : map){
                        int x = std::get<0>(tup);
                        int y = std::get<1>(tup);
                        if(x > max_x) { max_x = x; }
                        if(y > max_y) { max_y = y; }
                    }

                    std::cout << map.size() << '\n';
                    std::cout << max_x << ' ' << max_y << '\n';
                    for(int y=max_y; y>=0; --y){
                        for(int x=0; x<=max_x; ++x){
                            std::tuple<int,int> thiscrd{x,y};
                            if(no_dups.contains(thiscrd)){
                                std::cout << '#';
                            } else {
                                std::cout << '.';
                            }
                        }
                        std::cout << '\n';
                    }
                }
                break;
            } else {
                prevbufnull = true;
            }
        }
        lines++;
    }
    int max_x = 0;
    int max_y = 0;
    for(auto tup : map){
        int x = std::get<0>(tup);
        int y = std::get<1>(tup);
        if(x > max_x) { max_x = x; }
        if(y > max_y) { max_y = y; }
    }

    std::set<std::tuple<int,int>> setmap(map.begin(),map.end());
    std::cout << map.size() << '\n';
    std::cout << max_x << ' ' << max_y << '\n';
    for(int y=max_y; y>=0; --y){
        for(int x=0; x<=max_x; ++x){
            std::tuple<int,int> thiscrd{x,y};
            if(setmap.contains(thiscrd)){
                std::cout << '#';
            } else {
                std::cout << '.';
            }
        }
        std::cout << '\n';
    }

    std::cout << "no. of points " << first_dots << '\n';
    return 0;
}
