//
// Created by tei on 12/9/21.
//

#include <bits/stdc++.h>

#define line_break() { \
    std::cin.ignore(10000, '\n'); \
    if(strlen(buffer) == 0){ \
    lastbuffernull = true; \
    }\
}

enum EdgeType{
    leftedge = 0,
    rightedge = 1,
    topedge = 2,
    bottomedge = 3,
    corner_tl = 6,
    corner_tr = 7,
    corner_bl = 8,
    corner_br = 9,
    notedge = 10,
    unset = 11
};

const uint_fast16_t max_input_len = 2000;
typedef std::array<std::vector<uint_fast8_t>, max_input_len> Grid;
typedef std::tuple<uint_fast16_t ,uint_fast16_t> Coord;
typedef std::map<Coord,EdgeType> EdgeTMap;

inline void coord_compare_insert(std::set<Coord>& visited, std::vector<Coord>& next, uint_fast8_t thisval, uint_fast8_t comp, Coord comp_coord) {
    if(thisval < comp && comp != 9 && !visited.contains(comp_coord)) {
        next.push_back(comp_coord);
    }
}

uint_fast32_t find_basins(Coord current, std::set<Coord>& visited, Grid& grid, EdgeTMap& edge_map, uint_fast32_t sum){
    uint_fast16_t col = std::get<0>(current);
    uint_fast16_t row = std::get<1>(current);
    uint_fast8_t thisv = grid[col][row];
    uint_fast32_t this_sum = sum;
    if(!visited.contains(current)) {
        this_sum++;
        visited.insert(current);
    }
    std::vector<Coord> next;
    EdgeType edge_type = edge_map[current];
    switch(edge_type) {
        case leftedge : {
            uint_fast8_t down = grid[col][row+1];
            std::tuple<uint_fast16_t,uint_fast16_t> down_coord{col,row+1};
            uint_fast8_t up = grid[col][row-1];
            std::tuple<uint_fast16_t,uint_fast16_t> up_coord{col,row-1};
            uint_fast16_t right = grid[col+1][row];
            std::tuple<uint_fast16_t ,uint_fast16_t> right_coord{col+1,row};
            coord_compare_insert(visited, next,thisv,down,down_coord);
            coord_compare_insert(visited, next, thisv,up,up_coord);
            coord_compare_insert(visited, next, thisv,right,right_coord);
            break;
        }
        case rightedge : {
            uint_fast8_t down = grid[col][row+1];
            std::tuple<uint_fast16_t ,uint_fast16_t> down_coord{col,row+1};
            uint_fast8_t up = grid[col][row-1];
            std::tuple<uint_fast16_t ,uint_fast16_t> up_coord{col,row-1};
            uint_fast8_t left = grid[col-1][row];
            std::tuple<uint_fast16_t ,uint_fast16_t> left_coord{col-1,row};
            coord_compare_insert(visited, next,thisv,down,down_coord);
            coord_compare_insert(visited, next, thisv,up,up_coord);
            coord_compare_insert(visited, next, thisv,left,left_coord);
            break;
        }
        case topedge : {
            uint_fast8_t down = grid[col][row+1];
            std::tuple<uint_fast16_t,uint_fast16_t> down_coord{col,row+1};
            uint_fast8_t left = grid[col-1][row];
            std::tuple<uint_fast16_t,uint_fast16_t> left_coord{col-1,row};
            uint_fast8_t right = grid[col+1][row];
            std::tuple<uint_fast16_t,uint_fast16_t> right_coord{col+1,row};
            coord_compare_insert(visited, next,thisv,down,down_coord);
            coord_compare_insert(visited, next, thisv,left,left_coord);
            coord_compare_insert(visited, next, thisv,right,right_coord);
            break;
        }
        case bottomedge : {
            uint_fast8_t up = grid[col][row-1];
            std::tuple<uint_fast16_t,uint_fast16_t> up_coord{col,row-1};
            uint_fast8_t left = grid[col-1][row];
            std::tuple<uint_fast16_t,uint_fast16_t> left_coord{col-1,row};
            uint_fast8_t right = grid[col+1][row];
            std::tuple<uint_fast16_t,uint_fast16_t> right_coord{col+1,row};
            coord_compare_insert(visited, next, thisv,up,up_coord);
            coord_compare_insert(visited, next, thisv,left,left_coord);
            coord_compare_insert(visited, next, thisv,right,right_coord);
            break;
        }
        case corner_tl : {
            uint_fast8_t down = grid[col][row+1];
            std::tuple<uint_fast16_t,uint_fast16_t> down_coord{col,row+1};
            uint_fast8_t right = grid[col+1][row];
            std::tuple<uint_fast16_t,uint_fast16_t> right_coord{col+1,row};
            coord_compare_insert(visited, next,thisv,down,down_coord);
            coord_compare_insert(visited, next, thisv,right,right_coord);
            break;
        }
        case corner_tr : {
            uint_fast8_t down = grid[col][row+1];
            std::tuple<uint_fast16_t,uint_fast16_t> down_coord{col,row+1};
            uint_fast8_t left = grid[col-1][row];
            std::tuple<uint_fast16_t,uint_fast16_t> left_coord{col-1,row};
            coord_compare_insert(visited, next, thisv,down,down_coord);
            coord_compare_insert(visited, next, thisv,left,left_coord);
            break;
        }
        case corner_bl : {
            uint_fast8_t up = grid[col][row-1];
            std::tuple<uint_fast16_t,uint_fast16_t> up_coord{col,row-1};
            uint_fast8_t right = grid[col+1][row];
            std::tuple<uint_fast16_t,uint_fast16_t> right_coord{col+1,row};
            coord_compare_insert(visited, next, thisv,up,up_coord);
            coord_compare_insert(visited, next, thisv,right,right_coord);
            break;
        }
        case corner_br : {
            uint_fast8_t up = grid[col][row-1];
            std::tuple<uint_fast16_t,uint_fast16_t> up_coord{col,row-1};
            uint_fast8_t left = grid[col-1][row];
            std::tuple<uint_fast16_t,uint_fast16_t> left_coord{col-1,row};
            coord_compare_insert(visited, next, thisv,up,up_coord);
            coord_compare_insert(visited, next, thisv,left,left_coord);
            break;
        }
        case notedge : {
            uint_fast8_t up = grid[col][row-1];
            std::tuple<uint_fast16_t,uint_fast16_t> up_coord{col,row-1};
            uint_fast8_t down = grid[col][row+1];
            std::tuple<uint_fast16_t,uint_fast16_t> down_coord{col,row+1};
            uint_fast8_t left = grid[col-1][row];
            std::tuple<uint_fast16_t,uint_fast16_t> left_coord{col-1,row};
            uint_fast8_t right = grid[col+1][row];
            std::tuple<uint_fast16_t,uint_fast16_t> right_coord{col+1,row};
            coord_compare_insert(visited, next, thisv,up,up_coord);
            coord_compare_insert(visited, next, thisv,down,down_coord);
            coord_compare_insert(visited, next, thisv,left,left_coord);
            coord_compare_insert(visited, next, thisv,right,right_coord);
            break;
        }
        default:;
    }
    for(Coord c : next){
        this_sum = find_basins(c, visited, grid, edge_map, this_sum);
    }
    return this_sum;
}

int main()
{
    bool lastbuffernull = false;
    uint_fast32_t low_sum = 0;
    Grid grid;

    uint_fast16_t curr_row = 0;
    uint_fast16_t collength = 0;

    while(!lastbuffernull){
        char buffer[max_input_len];
        std::cin.get(buffer, max_input_len );

        if(strlen(buffer) != 0) {
            if(curr_row == 0) {
                collength = strlen(buffer);
            }
            for(uint_fast16_t i = 0; i < collength; ++i) {
                uint_fast8_t thisint = (uint_fast8_t)buffer[i] - 48;
                grid[i].push_back(thisint);
            }
        }
        curr_row++;
        line_break();
    }
    const uint_fast16_t rowlength = grid[0].size();
    int num_matches = 0;
    EdgeTMap edge_types;
    std::vector<Coord> low_pt_coords;

    for (uint_fast16_t r = 0; r < rowlength; r++) {
        for(uint_fast16_t c = 0; c < collength; c++) {
            uint_fast8_t thisint = grid[c][r];
            bool leftright_low = false;
            bool updown_low = false;
            bool notedge_h = false;
            bool notedge_v = false;
            Coord this_coord{c,r};

            EdgeType edge_type = unset;
            if(c == 0) {
                if(r == 0){
                    edge_type = corner_tl;
                } else if(r == rowlength-1) {
                    edge_type = corner_bl;
                } else {
                    edge_type = leftedge;
                }
                uint_fast8_t right = grid[c+1][r];
                if(thisint < right) {
                    leftright_low = true;
                }
            } else if(c == collength-1) {
                if(r == 0){
                    edge_type = corner_tr;
                } else if(r == rowlength-1) {
                    edge_type = corner_br;
                } else {
                    edge_type = rightedge;
                }
                uint_fast8_t left = grid[c-1][r];
                if(thisint < left) {
                    leftright_low = true;
                }
            } else {
                notedge_h = true;
                uint_fast8_t left = grid[c-1][r];
                uint_fast8_t right = grid[c+1][r];
                if(thisint < right && thisint < left) {
                    leftright_low = true;
                }
            }
            if(r == 0) {
                if(edge_type == unset){
                    edge_type = topedge;
                }
                uint_fast8_t down = grid[c][r+1];
                if(thisint < down) {
                    updown_low = true;
                }
            } else if(r == rowlength-1) {
                if(edge_type == unset){
                    edge_type = bottomedge;
                }
                uint_fast8_t up = grid[c][r-1];
                if(thisint < up) {
                    updown_low = true;
                }
            } else {
                notedge_v = true;
                uint_fast8_t up = grid[c][r-1];
                uint_fast8_t down = grid[c][r+1];
                if(thisint < up && thisint < down) {
                    updown_low = true;
                }
            }
            if(notedge_h && notedge_v) {
                edge_type = notedge;
            }
            edge_types[this_coord] = edge_type;

            if(updown_low && leftright_low) {
                low_sum += thisint + 1;
                low_pt_coords.push_back(this_coord);
                num_matches++;
            }
        }
    }

    std::vector<uint_fast32_t> basin_sums;
    for(auto crd : low_pt_coords) {
        std::set<Coord> visited;
        uint_fast32_t this_basin_sum = find_basins(crd, visited, grid, edge_types, 0);
        basin_sums.push_back(this_basin_sum);
    }
    std::sort(basin_sums.begin(),basin_sums.end(),[](uint_fast32_t a, uint_fast32_t b){ return a > b; });

    std::cout << "num matches: " << num_matches << '\n';
    std::cout << "sum of risk levels: " << low_sum << '\n';
    std::cout << "product of the 3 largest basin sizes: " << basin_sums[0]*basin_sums[1]*basin_sums[2] << '\n';
    return 0;
}
