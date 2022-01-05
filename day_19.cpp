//
// Created by tei on 12/19/21.
//

#include <bits/stdc++.h>

typedef std::array<int,3> Coord;

enum CmdOrder{
    rotate_translate = 0,
    translate_rotate = 1
};

typedef std::tuple<Coord,Coord,char> Cmd;


Coord a_to_b(const Coord& a, const Coord& b){
    int move_f = b[0] - a[0];
    int move_s = b[1] - a[1];
    int move_t = b[2] - a[2];
    Coord c{move_f, move_s, move_t};
    return c;
}

Coord find_direction(Coord& bpos, Coord& orig){
    Coord direction;
    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            if(std::abs(bpos[i]) == std::abs(orig[j])){
                int sign = bpos[i] == orig[j] ? 1 : -1;
                direction[i] = sign*(j+1);
            }
        }
    }
    return direction;
}

std::vector<Coord> mp{{1,1,1},{-1,1,1},{-1,-1,1},{1,-1,1},
                      {1,1,-1},{-1,1,-1},{-1,-1,-1},{1,-1,-1}};

void rotate_bpos(Coord bpos, std::map<Coord,std::vector<Coord>>& all_rotated){

        Coord cpy = bpos;
        std::sort(bpos.begin(),bpos.end(),std::less());

        do{
            for(Coord& m : mp){
                int nx = bpos[0]*m[0];
                int ny = bpos[1]*m[1];
                int nz = bpos[2]*m[2];
                Coord new_pos{nx,ny,nz};
                Coord direction = find_direction(new_pos,cpy);
                if(!all_rotated.contains(direction)){
                    std::vector<Coord> rts;
                    all_rotated[direction] = rts;
                }
                all_rotated[direction].push_back(new_pos);
            }
        }while(std::next_permutation(bpos.begin(),bpos.end()));
}

void print_coords(std::vector<Coord>& vecb){
    for(Coord& b : vecb){
        std::cout << b[0] << ',' << b[1] << ',' << b[2] << '\n';
    }
}

std::map<Coord,std::vector<Coord>> rotate_beacons(std::vector<Coord>& beacons){
    std::map<Coord,std::vector<Coord>> all_rotated;
    for(Coord& pos : beacons){
        rotate_bpos(pos, all_rotated);
    }
    return all_rotated;
}

void compare_dist(std::set<Coord>& s1, std::vector<Coord>& this_rt, Coord& match_dist, bool& found){

    for(Coord& p : this_rt){
        for(const Coord& p2 : s1){
            Coord dist = a_to_b(p, p2);
            int matches = 0;
            for(Coord& pp : this_rt){
                Coord p_translated{pp[0]+dist[0],pp[1]+dist[1],pp[2]+dist[2]};
                if(s1.contains(p_translated)){
                    matches++;
                    if(matches >= 12){
                        found = true;
                        //print_coords(matched);
                        match_dist = dist;
                        break;
                    }
                }
            }
        }
        if(found){ break; }
    }
}

Coord find_inverse_drc(Coord& dirc){
    Coord inv;
    for(int i = 0; i < 3; ++i){
        int sign = dirc[i] / std::abs(dirc[i]);
        int ix = std::abs(dirc[i]) - 1;
        inv[ix] = (i+1)*sign;
    }
    return inv;
}

void find_match_dist(std::vector<Coord>& s1, std::vector<Coord>& s2, int sc_1, int sc_2,
                     std::map<std::pair<int,int>,Cmd>& sc_distances,
                     std::map<int,std::set<int>>& adj_m) {

    std::map<Coord,std::vector<Coord>> s2_r = rotate_beacons(s2);
    std::set<Coord>s1set(s1.begin(),s1.end());
    for(auto& rotation : s2_r){
        std::vector<Coord> this_rt = rotation.second;
        Coord dirc = rotation.first;
        bool found = false;
        Coord dist;
        compare_dist(s1set,this_rt,dist,found);
        if(found){
            std::cout << "found overlap: " << sc_1 << ", " << sc_2 << '\n';
            if(!adj_m.contains(sc_1)) { adj_m[sc_1] = std::set<int>{sc_2}; }
            else { adj_m[sc_1].insert(sc_2); }
            if(!adj_m.contains(sc_2)) { adj_m[sc_2] = std::set<int>{sc_1}; }
            else { adj_m[sc_2].insert(sc_1); }

            std::pair<int,int> scp1{sc_2,sc_1}; //beacons in sc_2 from sc_1's perspective
            Cmd cmd{dist, dirc, rotate_translate};
            std::pair<int,int> scp2{sc_1,sc_2};
            Coord inv_d = find_inverse_drc(dirc);
            Cmd inv_cmd{dist, inv_d, translate_rotate};
            sc_distances[scp1] = cmd;
            sc_distances[scp2] = inv_cmd;
            break;
        }
    }
}

int find_path_to_n(int current, int n,
                  std::map<int,std::vector<int>>& found_paths,
                  std::vector<int>& this_path,
                  std::set<int>& visited,
                  std::map<int,std::set<int>>& adj_m) {

    if(!visited.contains(current)){
        this_path.push_back(current);
        visited.insert(current);
        if(adj_m[current].contains(n)){
                this_path.push_back(n);
                visited.insert(n);
                if(!found_paths.contains(this_path[0]) || found_paths[this_path[0]].size() > this_path.size()){
                    found_paths[this_path[0]] = this_path;
                }
            } else {
                //bool found = false;
                for(int next : adj_m[current]){
                    if(!visited.contains(next)){
                        find_path_to_n(next, n, found_paths, this_path, visited, adj_m);
                        if(visited.contains(n)) {
                            break;
                        } else {
                            this_path.erase(std::find(this_path.begin(),this_path.end(),next),this_path.end());
                            visited = std::set<int>(this_path.begin(),this_path.end());
                        }
                    }
                }
            }
    }
}

Coord align(Coord& dirc, Coord& bpos){
    Coord aligned;
    for(int i = 0; i < 3; ++i){
        int sign = dirc[i] / std::abs(dirc[i]);
        int ix = std::abs(dirc[i]) - 1;
        aligned[i] = bpos[ix]*sign;
    }
    return aligned;
}

typedef std::map<int,std::vector<int>> Paths;

std::map<int,Paths> find_path_groups(int& num_scanners, std::map<int,std::set<int>>& adj_m){
    std::map<int,Paths> found_paths;
    std::vector<int> unvisited;
    for(int i = num_scanners-1; i >= 0; --i){
        unvisited.push_back(i);
    }
    while(!unvisited.empty()){
        int n = unvisited.back();
        Paths paths_to_n;
      //  found_paths[n] = paths_to_n;
        unvisited.pop_back();
        for(int i = 0; i < num_scanners; ++i){
            //if(i == n || (std::find(unvisited.begin(),unvisited.end(),i) == unvisited.end())){
            if(i == n){
                continue;
            }
            std::vector<int> this_path;
            std::set<int> visited;
            find_path_to_n(i,n,paths_to_n,this_path,visited,adj_m);
            if(visited.contains(n)){
                unvisited.erase(std::find(unvisited.begin(),unvisited.end(),i));
            }
        }
        found_paths[n] = paths_to_n;
    }
    return found_paths;
}


std::set<Coord> add_beacons(std::map<int,Paths>& path_groups, std::vector<std::vector<Coord>>& scanners, std::map<std::pair<int,int>,Cmd>& sc_distances){

    std::set<Coord> total_beacons;
    for(auto& kv : path_groups){
        int origin = kv.first;
        std::set<Coord> found_beacons(scanners[origin].begin(), scanners[origin].end());
        for(auto& path : path_groups[origin]){

            std::vector<Coord> beacons = scanners[path.first];
            for(int i = 0; i < path.second.size()-1; ++i){
                std::pair<int,int> transform{path.second[i],path.second[i+1]};
                Cmd cmd = sc_distances[transform];
                Coord dist = std::get<0>(cmd);
                Coord direction = std::get<1>(cmd);
                if(std::get<2>(cmd) == rotate_translate){
                    for(Coord& crd : beacons){
                        crd = align(direction, crd);
                        for(int j = 0; j < 3; ++j){
                            crd[j] += dist[j];
                        }
                    }
                } else {
                    for(Coord& crd : beacons){
                        for(int j = 0; j < 3; ++j){
                            crd[j] -= dist[j];
                        }
                        crd = align(direction, crd);
                    }
                }
            }
            for(Coord& beacon : beacons){
                found_beacons.insert(beacon);
            }
            //print_coords(beacons);
        }
        for(Coord beacon : found_beacons) {
            total_beacons.insert(beacon);
        }
        std::cout << total_beacons.size() << '\n';
        std::cout << "TOTAL BC\n";
    }
    return total_beacons;
}

int find_sum_beacons(std::vector<std::vector<Coord>>& scanners){

    std::map<std::pair<int,int>,Cmd> sc_distances;
    std::map<int,std::set<int>> adj_m;
    int num_scanners = scanners.size();
    for(int i = 0; adj_m.size() < num_scanners && i < scanners.size()-1; ++i){
        for(int j = i+1; adj_m.size() < num_scanners && j < scanners.size(); ++j){
            find_match_dist(scanners[i], scanners[j], i, j, sc_distances, adj_m);
        }
    }

   // std::cout << sc_distances.size() <<'\n';

    std::map<int,Paths> path_groups = find_path_groups(num_scanners, adj_m);
    std::set<Coord> total_beacons = add_beacons(path_groups, scanners, sc_distances);

    return total_beacons.size();
}

int main()
{
    int lastbuffernull = 0;
    std::vector<std::vector<Coord>> scanners;
    int curr_row = 0;


    while(lastbuffernull < 2){
        std::string s;
        std::getline(std::cin,s);
        if(s.size() != 0){
            lastbuffernull = 0;
            if(curr_row == 0){
                auto scnr = s.substr(s.find("scanner")+8,1);
                std::vector<Coord> beacons;
                scanners.push_back(beacons);
            }
            else {
                int last_start = 0;
                int last_len = 0;
                Coord bpos;
                int xyz = 0;
                for (int i = 0; i <= s.size(); i++){
                    if(s[i] == ',' || i == s.size()) {
                        std::string str = s.substr(last_start, last_len);
                        int num = stoi(str);
                       // std::cout << num << ' ';
                        bpos[xyz++] = num;
                        last_start = i+1;
                        last_len = 0;
                    }
                    else {
                        last_len++;
                    }
                }
                scanners[scanners.size()-1].push_back(bpos);
            }
            curr_row++;
        } else {
            curr_row = 0;
            lastbuffernull++;
        }
    }

    int num_beacons = find_sum_beacons(scanners);

    std::cout << "No. of beacons: " << num_beacons << '\n';
}