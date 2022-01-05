//
// Created by tei on 12/31/21.
//


#include <bits/stdc++.h>

#define line_break() { \
   std::cin.ignore(10000, '\n'); \
   if(strlen(buffer) == 0){ \
   lastbuffernull = true; \
   }\
}

typedef std::vector<std::vector<char>> Grid;
typedef std::pair<int ,int> Crd;
typedef std::map<Crd,EdgeType> EdgeTMap;

void print_grid(Grid& grid) {
    for(int r = 0; r < grid.size(); ++r) {
        for(int c = 0; c < grid[0].size(); ++c) {
            std::cout << grid[r][c];
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

void mv_next(Grid& grid, Crd mvto, char& prev, char nx, std::set<Crd>& mved, char fst){
    char comp = ((mvto.first == 0 && nx == 'v') || (mvto.second == 0 && nx == '>')) ? fst : grid[mvto.first][mvto.second];
    if(comp == '.') {
        grid[mvto.first][mvto.second] = nx;
        mved.insert(mvto);
        prev = '.';
    }
}

void move_east_ccbs(Grid& grid, std::set<Crd>& mved) {
    for(int r = 0; r < grid.size(); ++r) {
        char fst = grid[r][0];
        for(int c = 0; c < grid[0].size(); ++c) {
            if(!mved.contains(Crd{r,c}) && grid[r][c] == '>') {
                mv_next(grid, Crd{r, c == grid[0].size() - 1 ? 0 : c + 1}, grid[r][c], '>', mved, fst);
            }
        }
    }
}

void move_south_ccbs(Grid& grid, std::set<Crd>& mved) {
    for(int c = 0; c < grid[0].size(); ++c) {
        char fst = grid[0][c];
        for(int r = 0; r < grid.size(); ++r) {
            if(!mved.contains(Crd{r,c}) && grid[r][c] == 'v') {
                mv_next(grid, Crd{r == grid.size() - 1 ? 0 : r + 1, c}, grid[r][c], 'v', mved, fst);
            }
        }
    }
}

int move_sea_ccbs(Grid& grid) {
    int step = 1;
    for(;;){
        std::cout << step << '\n';
        std::set<Crd> mved;
        move_east_ccbs(grid, mved);
        move_south_ccbs(grid, mved);
        print_grid(grid);
        if(mved.empty()){
            break;
        }
        step++;
    }
    return step;
}

int main()
{
    bool lastbuffernull = false;
    Grid grid;

    int curr_row = 0;
    int max_input_len = 999;

    while(!lastbuffernull){
        char buffer[max_input_len];
        std::cin.get(buffer, max_input_len );

        if(strlen(buffer) != 0) {
            std::vector<char> new_r;
            grid.push_back(new_r);
            for(int col = 0; col < strlen(buffer); ++col) {
                grid[grid.size()-1].push_back(buffer[col]);
            }
        }
        curr_row++;
        line_break();
    }

    int num_steps = move_sea_ccbs(grid);
    std::cout << "sea cucumbers stop moving after step " << num_steps << '\n';

    return 0;
}
