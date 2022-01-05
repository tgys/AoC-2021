//
// Created by tei on 12/11/21.
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

const int grid_size = 10;
typedef std::array<std::array<int,grid_size>, grid_size> Grid;
typedef std::tuple<int ,int> Coord;
typedef std::map<Coord,EdgeType> EdgeTMap;

inline void add_next(std::vector<Coord>& next, int comp_col, int comp_row, Grid& grid) {
    Coord comp_coord{comp_col, comp_row};
    grid[comp_col][comp_row]++;
    int comp = grid[comp_col][comp_row];
    if(comp > 9) {
        next.push_back(comp_coord);
    }
}

int flash(Coord current, std::set<Coord>& visited, Grid& grid, EdgeTMap& edge_map, int sum){

    int col = std::get<0>(current);
    int row = std::get<1>(current);
    int this_sum = sum;
    std::vector<Coord> next;
    if(!visited.contains(current)) {
        this_sum++;
        EdgeType edge_type = edge_map[current];
        switch(edge_type) {
            case leftedge : {
                add_next(next,col,row+1,grid);
                add_next(next,col,row-1,grid);
                add_next(next,col+1,row,grid);
                add_next(next,col+1,row-1,grid);
                add_next(next,col+1,row+1,grid);
                break;
            }
            case rightedge : {
                add_next(next,col,row+1,grid);
                add_next(next,col,row-1,grid);
                add_next(next,col-1,row,grid);
                add_next(next,col-1,row+1,grid);
                add_next(next,col-1,row-1,grid);
                break;
            }
            case topedge : {
                add_next(next,col,row+1,grid);
                add_next(next,col-1,row,grid);
                add_next(next,col+1,row,grid);
                add_next(next,col-1,row+1,grid);
                add_next(next,col+1,row+1,grid);
                break;
            }
            case bottomedge : {
                add_next(next,col,row-1,grid);
                add_next(next,col-1,row,grid);
                add_next(next,col+1,row,grid);
                add_next(next,col-1,row-1,grid);
                add_next(next,col+1,row-1,grid);
                break;
            }
            case corner_tl : {
                add_next(next,col,row+1,grid);
                add_next(next,col+1,row,grid);
                add_next(next,col+1,row+1,grid);
                break;
            }
            case corner_tr : {
                add_next(next,col,row+1,grid);
                add_next(next,col-1,row,grid);
                add_next(next,col-1,row+1,grid);
                break;
            }
            case corner_bl : {
                add_next(next,col,row-1,grid);
                add_next(next,col+1,row,grid);
                add_next(next,col+1,row-1,grid);
                break;
            }
            case corner_br : {
                add_next(next,col,row-1,grid);
                add_next(next,col-1,row,grid);
                add_next(next,col-1,row-1,grid);
                break;
            }
            case notedge : {
                add_next(next,col,row-1,grid);
                add_next(next,col,row+1,grid);
                add_next(next,col-1,row,grid);
                add_next(next,col+1,row,grid);
                add_next(next,col-1,row-1,grid); //up, left
                add_next(next,col+1,row-1,grid); //up, right
                add_next(next,col+1,row+1,grid); //down,right
                add_next(next,col-1,row+1,grid); //down, left
                break;
            }
            default:;
        }
        visited.insert(current);
    }

    for(Coord c : next){
        this_sum = flash(c, visited, grid, edge_map, this_sum);
    }
    return this_sum;
}

inline int start_flash(Grid& grid, EdgeTMap& edge_map){
    std::set<Coord> to_flash;
    for (int r = 0; r < grid_size; r++) {
        for(int c = 0; c < grid_size; c++) {
            int thisint = grid[c][r];
            Coord this_crd{c,r};
            thisint++;
            if(thisint > 9){
                to_flash.insert(this_crd);
            }
            grid[c][r] = thisint;
        }
        //std::cout<<'\n';
    }
    int step_flashes = 0;
    std::set<Coord> visited;

    for(auto crd : to_flash){
        int new_flashes = flash(crd, visited, grid, edge_map, 0);
        step_flashes += new_flashes;
    }
    for(Coord v : visited) {
        grid[std::get<0>(v)][std::get<1>(v)] = 0;
    }
    //std::cout << "step flashes " << step_flashes << '\n';
    return step_flashes;
}

inline int flash_n_steps(int steps, Grid& grid, EdgeTMap& edge_map){
    int total_flashes = 0;
    for(int i = 0; i < steps; ++i) {
        total_flashes += start_flash(grid, edge_map);
    }
    return total_flashes;
}

inline int flash_until_all_flash(Grid& grid, EdgeTMap& edge_map){
    int step_flashes = 0;
    int count = 0;
    while(step_flashes != 100) {
        step_flashes = start_flash(grid, edge_map);
        count++;
    }
    return count;
}

int main()
{
    bool lastbuffernull = false;
    EdgeTMap edge_map;
    Grid grid;

    int curr_row = 0;
    int max_input_len = 200;

    while(!lastbuffernull){
        char buffer[max_input_len];
        std::cin.get(buffer, max_input_len );

        if(strlen(buffer) != 0) {
            for(int col = 0; col < strlen(buffer); ++col) {
                int thisint = (int)buffer[col] - 48;
                Coord this_crd{col,curr_row};
                grid[col][curr_row] = thisint;
                bool notedge_h = false;
                bool notedge_v = false;

                EdgeType edge_type = unset;
                if(col == 0) {
                    if(curr_row == 0){
                        edge_type = corner_tl;
                    } else if(curr_row == 9) {
                        edge_type = corner_bl;
                    } else {
                        edge_type = leftedge;
                    }
                } else if(col == 9) {
                    if(curr_row == 0){
                        edge_type = corner_tr;
                    } else if(curr_row == 9) {
                        edge_type = corner_br;
                    } else {
                        edge_type = rightedge;
                    }
                } else {
                    notedge_h = true;
                }
                if(curr_row == 0) {
                    if(edge_type == unset){
                        edge_type = topedge;
                    }
                } else if(curr_row == 9) {
                    if(edge_type == unset){
                        edge_type = bottomedge;
                    }
                } else {
                    notedge_v = true;
                }
                if(notedge_h && notedge_v) {
                    edge_type = notedge;
                }
                edge_map[this_crd] = edge_type;
           ; }
        }
        curr_row++;
        line_break();
    }

    Grid gridcpy = grid;
    //part 1
    int total_flashes_100_steps = flash_n_steps(100, grid, edge_map);

    std::cout << "total flashes " << total_flashes_100_steps << '\n';

    int step = flash_until_all_flash(gridcpy,edge_map);
    std::cout << "first step when all octopuses flash: " << step << '\n';

    return 0;
}
