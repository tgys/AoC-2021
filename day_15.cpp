//
// Created by tei on 12/16/21.
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

typedef std::vector<std::vector<int>> Grid;
typedef std::tuple<int ,int> Coord;
typedef std::map<Coord,EdgeType> EdgeTMap;
typedef std::pair<std::vector<Coord>,int> PathTo;
typedef std::map<Coord, PathTo> PathMp;

void compare_and_add(Coord& this_crd, std::vector<Coord>& next, int comp_col, int comp_row, Grid& grid, PathMp& pathmap) {
    int tdist = pathmap[this_crd].second;
    Coord comp_coord{comp_col, comp_row};
    int comp_val = grid[comp_row][comp_col];
    int cur_dist = pathmap[comp_coord].second;
    int new_dist = tdist + comp_val;
    if(new_dist < cur_dist) {
        next.push_back(comp_coord);
        pathmap[comp_coord].second = new_dist;
        std::pair<std::vector<Coord>,int> npair{pathmap[this_crd].first, new_dist};
        npair.first.push_back(comp_coord);
        pathmap[comp_coord] = npair;
    }
}

void find_next_path(Coord& this_crd, PathMp& pathmap, Grid& grid, EdgeTMap& edge_map){

        int col = std::get<0>(this_crd);
        int row = std::get<1>(this_crd);
        std::vector<Coord> next;
        EdgeType edge_type = edge_map[this_crd];
        switch(edge_type) {
            case leftedge : {
                compare_and_add(this_crd, next,col,row+1,grid, pathmap);
                compare_and_add(this_crd, next,col,row-1,grid, pathmap);
                compare_and_add(this_crd, next,col+1,row,grid, pathmap);
                break;
            }
            case rightedge : {
                compare_and_add(this_crd, next,col,row+1,grid, pathmap);
                compare_and_add(this_crd, next,col,row-1,grid, pathmap);
                compare_and_add(this_crd, next,col-1,row,grid, pathmap);
                break;
            }
            case topedge : {
                compare_and_add(this_crd, next,col,row+1,grid, pathmap);
                compare_and_add(this_crd, next,col-1,row,grid, pathmap);
                compare_and_add(this_crd, next,col+1,row,grid, pathmap);
                break;
            }
            case bottomedge : {
                compare_and_add(this_crd, next,col,row-1,grid, pathmap);
                compare_and_add(this_crd, next,col-1,row,grid, pathmap);
                compare_and_add(this_crd, next,col+1,row,grid, pathmap);
                break;
            }
            case corner_tl : {
                compare_and_add(this_crd, next,col,row+1,grid, pathmap);
                compare_and_add(this_crd, next,col+1,row,grid, pathmap);
                break;
            }
            case corner_tr : {
                compare_and_add(this_crd, next,col,row+1,grid, pathmap);
                compare_and_add(this_crd, next,col-1,row,grid, pathmap);
                break;
            }
            case corner_bl : {
                compare_and_add(this_crd, next,col,row-1,grid, pathmap);
                compare_and_add(this_crd, next,col+1,row,grid, pathmap);
                break;
            }
            case corner_br : {
                compare_and_add(this_crd, next,col,row-1,grid, pathmap);
                compare_and_add(this_crd, next,col-1,row,grid, pathmap);
                break;
            }
            case notedge : {
                compare_and_add(this_crd,next,col,row-1,grid, pathmap);
                compare_and_add(this_crd,next,col,row+1,grid, pathmap);
                compare_and_add(this_crd,next,col-1,row,grid, pathmap);
                compare_and_add(this_crd,next,col+1,row,grid, pathmap);
                break;
            }
            default:;
        }
        for(Coord& c : next) {
            find_next_path(c, pathmap, grid, edge_map);
        }

}

int main()
{
    bool lastbuffernull = false;
    EdgeTMap edge_map;
    PathMp path_map;
    Grid grid;

    int curr_row = 0;
    int max_input_len = 200;

    while(!lastbuffernull){
        char buffer[max_input_len];
        std::cin.get(buffer, max_input_len );

        if(strlen(buffer) != 0) {
            std::vector<int> newrw;
            grid.push_back(newrw);
            for(int col = 0; col < strlen(buffer); ++col) {
                int thisint = (int)buffer[col] - 48;
                Coord this_crd{col,curr_row};
                grid[grid.size()-1].push_back(thisint);
                path_map[this_crd].second = INT_MAX;
            }
        }
        curr_row++;
        line_break();
    }
    std::cout << grid.size() <<  ' ' << grid[0].size() << '\n' << curr_row;
    int cols = grid[0].size();
    int rows = grid.size();
    for(int r = 0; r < rows; ++r){
        for(int c = 0; c < cols; ++c){
            Coord this_crd{c,r};
            bool notedge_h = false;
            bool notedge_v = false;

            EdgeType edge_type = unset;
            if(c == 0) {
                if(r == 0){
                    edge_type = corner_tl;
                } else if(r == rows-1) {
                    edge_type = corner_bl;
                } else {
                    edge_type = leftedge;
                }
            } else if(c == cols-1) {
                if(r == 0){
                    edge_type = corner_tr;
                } else if(r == rows-1) {
                    edge_type = corner_br;
                } else {
                    edge_type = rightedge;
                }
            } else {
                notedge_h = true;
            }
            if(r == 0) {
                if(edge_type == unset){
                    edge_type = topedge;
                }
            } else if(r == rows-1) {
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
        }
    }
    Coord first_crd{0,0};
    path_map[first_crd].second = 0;
    path_map[first_crd].first.push_back(first_crd);
    find_next_path(first_crd,path_map,grid, edge_map);
    Coord last_crd{cols-1,rows-1};
    std::cout << "minimum length: " << path_map[last_crd].second << '\n';
    for(Coord c : path_map[last_crd].first){
       // std::cout << std::get<0>(c) << ',' << std::get<1>(c) << '\n';
    }

    return 0;
}
