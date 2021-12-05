//
// Created by tei on 12/5/21.
//

#include <bits/stdc++.h>

typedef std::map<std::tuple<int, int>, int> OverlapMap;

inline int svtoi(std::string_view sv) {
    int val;
    std::from_chars(sv.data(), sv.data() + sv.size(), val);
    return val;
}

inline void find_overlaps_x(int sy, int ey, int sx,
                            OverlapMap& overlaps,
                            int& overlap_cnt)
{
    for(int j = std::min(sy, ey); j <= std::max(sy, ey); ++j){
        std::tuple<int,int> new_s = {sx, j};
        if(overlaps[new_s] == 1) {
            overlap_cnt++;
        }
        overlaps[new_s] += 1;
    }
}

inline void find_overlaps_y(int sx, int ex, int sy,
                            OverlapMap& overlaps,
                            int& overlap_cnt)
{
    for(int j = std::min(sx, ex); j <= std::max(sx, ex); ++j){
        std::tuple<int,int> new_s = {j, sy};
        if(overlaps[new_s] == 1) {
            overlap_cnt++;
        }
        overlaps[new_s] += 1;
    }
}

int main()
{
    bool lastbuffernull = false;
    int depth = 0;
    int horizontal_pos = 0;
    int max_input_len = 40;
    OverlapMap overlaps;
    int overlap_cnt = 0;

    while(!lastbuffernull){
        char buffer[max_input_len];
        std::cin.get( buffer, max_input_len );
        if(strlen(buffer) != 0){
            auto s = std::string_view(buffer);
            std::cout << s << '\n';
            auto start = s.substr(0,s.find(" -> "));
            auto end = s.substr(s.find(" -> ") + 4, s.npos);

            auto start_x = start.substr(0, start.find(','));
            auto start_y = start.substr(start.find(',') + 1, start.npos);

            auto end_x = end.substr(0, end.find(','));
            auto end_y = end.substr(end.find(',') + 1, end.npos);
            int sx = svtoi(start_x);
            int sy = svtoi(start_y);
            int ey = svtoi(end_y);
            int ex = svtoi(end_x);
            if (start_x == end_x) {
                find_overlaps_x(sy, ey, sx, overlaps,overlap_cnt);
            } else if (start_y == end_y) {
                find_overlaps_y(sx, ex, sy, overlaps,overlap_cnt);
            }

        }

        std::cin.ignore(10000, '\n');
        if(strlen(buffer) == 0){
            lastbuffernull = true;
        }
    }
    std::cout << "no. of points where at least 2 lines overlap: " << overlap_cnt << '\n';
    return 0;
}
