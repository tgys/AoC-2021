//
// Created by tei on 12/22/21.
//

#include <bits/stdc++.h>

inline int svtoi(std::string_view sv) {
    int val;
    std::from_chars(sv.data(), sv.data() + sv.size(), val);
    return val;
}

#define line_break() { \
   std::cin.ignore(10000, '\n'); \
   if(strlen(buffer) == 0){ \
   lastbuffernull = true; \
   }\
}

typedef std::array<std::array<int,2>,3> Cube;
typedef std::vector<std::pair<int,Cube>> CmdList;
typedef std::tuple<int,int,int> Crd;
typedef std::set<Crd> OnCubes;

int main()
{
    bool lastbuffernull = false;
    int max_input_len = 200;
    int overlap_cnt = 0;
    CmdList cmd_list;
    OnCubes on_cubes;

    while(!lastbuffernull){
        char buffer[max_input_len];
        std::cin.get( buffer, max_input_len );
        if(strlen(buffer) != 0){
            auto s = std::string_view(buffer);
            std::cout << s << '\n';
            int cmd = s.substr(0,s.find_first_of(' ')) == "on" ? 1 : 0;
            Cube cube;
            int last_start = 0;
            int last_len = 0;
            int axis = 0;
            bool valid = true;
            for (int i = 0; i <= strlen(buffer); i++){
                if(buffer[i] == '='){
                    last_start = i+1;
                    last_len = 0;
                }
                if(buffer[i] == ',' || i == strlen(buffer)) {
                    auto str = std::string_view(&buffer[last_start], last_len-1);
                    int start = svtoi(str.substr(0,str.find("..")));
                    int end = svtoi(str.substr(str.find("..")+2, str.npos));
                    //if(start < -50 || end > 50) {  //part 1
                    //    valid = false;
                    //    break;
                    //}
                    cube[axis][0] = start;
                    cube[axis++][1] = end;
                    last_start = i+1;
                    last_len = 0;
                }
                else {
                    last_len++;
                }
            }
            // if(valid){ cmd_list.push_back(std::pair<int,Cube>{cmd,cube}); } //part 1
            cmd_list.push_back(std::pair<int,Cube>{cmd,cube});
        }
        line_break();
    }

    for(std::pair<int,Cube> pair : cmd_list){
        std::vector<Crd> cbs;
        Cube cb = pair.second;
        for(int x = cb[0][0]; x <= cb[0][1]; ++x) {
            for(int y = cb[1][0]; y <= cb[1][1]; ++y) {
                for(int z = cb[2][0]; z <= cb[2][1]; ++z) {
                    cbs.emplace_back(x,y,z);
                }
            }
        }
        if(pair.first == 1) {
            for(Crd crd : cbs){
                on_cubes.insert(crd);
            }
        } else {
            for(Crd crd : cbs){
                on_cubes.erase(crd);
            }
        }
    }

    std::cout << "no. of cubes turned on: " << on_cubes.size() << '\n';
    return 0;
}
