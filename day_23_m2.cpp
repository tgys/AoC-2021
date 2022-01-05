//
// Created by tei on 12/01/21.
//

#include <bits/stdc++.h>

int svtoi(std::string_view sv) {
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

enum AType{
    A = 0,
    B = 1,
    C = 2,
    D = 3,
    Empty = 4
};

typedef std::array<std::array<AType,11>,5> Halls_5;
typedef std::pair<int,int> Crd;
typedef std::map<AType,int> Moves;

int get_rm(AType tp) {
    return 2*((int)tp+1);
}

void find_rooms(Halls_5& halls, std::vector<AType>& unvisited, Moves& moves,
                std::pair<int, std::map<AType,int>>& min_moves, bool st);

char tp_to_ch(AType tp) {
    return tp == Empty ? '.' : tp == A ? 'A' : tp == B ? 'B' : tp == C ? 'C' : 'D';
}

void print_hall(Halls_5& halls){
    for(int i = 0; i < halls[0].size()+2; i++) {
        std::cout << '=';
    }
    std::cout << '\n';
    for(int i = 0; i < halls.size(); i++) {
        std::cout << '|';
        for(int j = 0; j < halls[i].size(); ++j) {
            AType tp = halls[i][j];
            char ch;
            if(i == 0){
                ch = tp_to_ch(tp);
            } else {
                if(j > 1 && j < 9 && j % 2 == 0){
                    ch = tp_to_ch(tp);
                } else {
                    ch = '!';
                }
            }
            std::cout << ch;
        }
        std::cout << "|\n";
    }
    for(int i = 0; i < halls[0].size()+2; i++) {
        if(i == 0 || i == 1 || i == halls[0].size() || i == halls[0].size()+1){
            std::cout << ' ';
        } else {
            std::cout << '=';
        }
    }
    std::cout << '\n';
}

class BlockerPrms{
public:
    AType type;
    Crd room;
    std::vector<Crd> blockers;
    std::vector<Crd> path_blkrs;
    std::vector<std::tuple<Crd,int,std::vector<Crd>>> found;
    std::set<Crd> visited;
    int last_dist = -1;
    explicit BlockerPrms(AType tp) {
        type = tp;
        room = {4,get_rm(type) };
    }
};

std::vector<Crd> next_idx(Crd& room) {
    std::vector<Crd> next;
    if(room.first == 4) {
        next.emplace_back(room.first-1,room.second);
        return next;
    } else if(room.first == 1 || room.first == 2 || room.first == 3) {
        next.emplace_back(room.first-1,room.second);
        next.emplace_back(room.first+1,room.second);
    } else {
        if(std::set<int>({2,4,6,8}).contains(room.second)) {
            next.emplace_back(room.first+1,room.second);
        }
        if(room.second == 0) {
            next.emplace_back(room.first,room.second+1);
        } else if(room.second == 10) {
            next.emplace_back(room.first,room.second-1);
        } else {
            next.emplace_back(room.first,room.second+1);
            next.emplace_back(room.first,room.second-1);
        }
    }
    return next;
}

/* DFS to find the crds of blockers (all blockers for a given room type stored in BP.blockers,
 * blockers in the path of a matching apod stored in a tuple in BP.found which also stores
 * the positions/distances of matching apods (from the bottom room)
 */
void find_blockers(Crd& crd, Halls_5& halls, BlockerPrms& BP) {
    if(BP.found.size() < 4 && !BP.visited.contains(crd)) {
        BP.last_dist++;
        BP.visited.insert(crd);
        if(halls[crd.first][crd.second] == BP.type) {
            if(BP.last_dist != 0) {
                if(!(BP.path_blkrs.empty() && crd.second == BP.room.second)) {
                    BP.found.emplace_back(crd,BP.last_dist,BP.path_blkrs);
                }
            }
        } else if(halls[crd.first][crd.second] != Empty) {
            BP.blockers.push_back(crd);
            BP.path_blkrs.push_back(crd);
            if(crd.second == BP.room.second &&
            halls[crd.first-1][crd.second] == (AType)((BP.room.second/2)-1)) {
                BP.blockers.emplace_back(crd.first-1,crd.second);
                BP.path_blkrs.emplace_back(crd.first-1,crd.second);
            }
        }
        std::vector<Crd> next = next_idx(crd);
        std::vector<Crd> cur_blockers(BP.blockers);
        std::vector<Crd> cur_path_blockers(BP.path_blkrs);
        int cur_dist = BP.last_dist;
        int num_found = BP.found.size();
        for(Crd n_crd : next) {
            if(!BP.visited.contains(n_crd)) {
                find_blockers(n_crd, halls, BP);
            }
            if(BP.found.size()==4) {
                break;
            }
            BP.last_dist = cur_dist;
            BP.path_blkrs = cur_path_blockers;
            if(BP.found.size() == num_found) {
                BP.blockers = cur_blockers;
            }
        }
    }
}

void remove_empty_kvs(std::map<int,int>& kvm){
    for(auto iter = kvm.begin(); iter != kvm.end() && kvm.size() != 0; ++iter) {
        if(iter->second == 0) {
            kvm.erase(iter--->first);   //not a typo
        }
    }
}

int col_from_p_idx(int ix){
    switch(ix) {
        case 0 : return 0;
        case 6 : return 10;
        default: return (2*ix)-1;
    }
}

int get_energy(Moves& moves) {
    int energy = 0;
    for(auto m : moves) {
        if(m.first != Empty){
            energy += m.second * std::pow(10,(int)m.first);
        }
    }
    return energy;
}

int check_size(Halls_5& halls) {
    int sz = 0;
    for(auto rw : halls) {
        for(AType tp : rw){
            if(tp != Empty) {
               sz++;
            }
        }
    }
    return sz;
}

bool valid_order_exst(std::array<Crd,7>& mov_locations, std::map<Crd,int>& exst_order) {
    int ix = 0;
    for(Crd& mov_location : mov_locations) {
        if(exst_order.contains(mov_location)) {
            if(ix == exst_order[mov_location]){
                ix++;
            } else {
                return false;
            }
        }
    }
    return true;
}

bool not_blocking(std::array<Crd,7>& mov_locations, std::pair<int,int>& block_range) {
    for(int i = 0; i < mov_locations.size(); ++i) {
        int col = col_from_p_idx(i);
        if(col >= block_range.first && col <= block_range.second
        && mov_locations[i].second != -1) {
            return false;
        }
    }
    return true;
}

bool check_fixed(std::array<Crd,7>& mov_loc_old, std::array<Crd,7>& mov_loc_new) {
    for(int i = 0; i < mov_loc_old.size(); ++i) {
        if(mov_loc_old[i].second != -1 && (mov_loc_old[i] != mov_loc_new[i])) {
            return false;
        }
    }
    return true;
}

bool check_range(std::array<Crd,7>& mov_locs, std::map<Crd,std::pair<int,int>>& ranges) {
    for(int i = 0; i < mov_locs.size(); ++i) {
        if(ranges.contains(mov_locs[i])) {
            if(i <= ranges[mov_locs[i]].first || i >= ranges[mov_locs[i]].second) {
                return false;
            }
        }
    }
    return true;
}

std::vector<Crd> find_move_layer(Halls_5& halls, std::map<int,int>& blkr_cols) {
    std::vector<Crd> move_layer;
    int layer_cnt = 0;
    while(layer_cnt < blkr_cols.size()) {
        for(int i = 1; i <= 4; ++i){
            for(auto bk : blkr_cols) {
                int j = bk.first;
                if(halls[i][j] != Empty) {
                    move_layer.emplace_back(i,j);
                    layer_cnt++;
                    blkr_cols[j]--;
                }
            }
            if(layer_cnt == blkr_cols.size()) {
                break;
            }
        }
    }
    remove_empty_kvs(blkr_cols);
    return move_layer;
}

std::array<Crd,7> new_layer_ord(std::map<Crd,int>& exst_order, Halls_5& halls) {
    int ix = 0;
    int ixe = 0;
    std::array<Crd,7> mv_loc_layers;
    for(int i = 0; i < halls[0].size(); i++) {
        if(halls[0][i] != Empty) {
            exst_order[Crd{0,i}] = ixe++;
            mv_loc_layers[ix++] = {0,i};
        } else if(!std::set({2,4,6,8}).contains(i)){
            mv_loc_layers[ix++] = {-1,-1};
        }
    }
    return mv_loc_layers;
}

void add_to_mv_locs(std::vector<Crd>& move_layer, std::array<Crd,7>& mv_loc_layer) {
    std::vector<Crd> move_layer_cpy(move_layer);   ///
    for(int i = 0; !move_layer_cpy.empty() && i < mv_loc_layer.size(); ++i) {
        if(mv_loc_layer[i].second == -1) {
            mv_loc_layer[i] = move_layer_cpy.back();
            move_layer_cpy.pop_back();
        }
    }
}

std::map<AType,int> find_unblocked(Halls_5& halls,
                                   std::vector<AType>& unvisited){
    std::map<AType,int> num_unblocked;
    for(auto it = unvisited.begin(); it != unvisited.end() && !unvisited.empty(); ++it) {
        BlockerPrms otherBP(*it);
        num_unblocked[*it] = 0;
        find_blockers(otherBP.room, halls, otherBP);
        for(std::tuple<Crd,int,std::vector<Crd>> tup : otherBP.found) {
            Crd fd = std::get<0>(tup);
            if(std::get<2>(tup).empty() && fd.second != otherBP.room.second) {
                num_unblocked[*it]++;
            }
        }
    }
    return num_unblocked;
}

std::pair<int,int> try_move(std::array<Crd,7>& loc, Halls_5& halls, std::vector<AType>& unvisited,
                            Moves& moves, bool ignore_ext = false) {
    int sz = check_size(halls);
    int total_e = 0;
    Halls_5 n_hall(halls);
    std::set<int> moved;
    for(int i = 0; i < loc.size(); ++i) {
        int n_col = col_from_p_idx(i);
        if(loc[i].first == -1 || n_col == loc[i].second) { continue; }
        AType tp = halls[loc[i].first][loc[i].second];
        if(tp != Empty){
            int this_dist = loc[i].first + (std::max(n_col, loc[i].second) - std::min(n_col,loc[i].second));
            moves[tp] += this_dist;
            total_e += this_dist * std::pow(10,(int)tp);
            n_hall[0][n_col] = tp;
            moved.insert(n_col);
            if(!moved.contains(loc[i].second)) {
                n_hall[loc[i].first][loc[i].second] = Empty;
            }
        }
    }
    halls = n_hall;
    std::map<AType,int> unblocked = find_unblocked(halls, unvisited);
    int total_ub = 0;
    for (auto ub : unblocked) { total_ub += ub.second; }
    sz = check_size(halls);
    return std::pair<int,int>{total_ub,total_e};
}

std::array<AType,7> get_tp_arr(std::array<Crd,7>& mv_locs, Halls_5& halls) {
    std::array<AType,7> tp_arr{};
    int ix = 0;
    for(Crd crd : mv_locs) {
        if(crd.second == -1){
            tp_arr[ix++] = Empty;
        } else {
            tp_arr[ix++] = halls[0][col_from_p_idx(ix)];
        }
    }
    return tp_arr;
}

typedef std::tuple<std::array<AType,7>,std::array<Crd,7>,Halls_5,Moves> ObsTup;

void layer_permutations(Halls_5& halls, std::vector<AType>& unvisited, std::pair<int,int>& block_range,
                                      Moves& moves, std::map<std::array<AType,7>,std::pair<int,Moves>>& tp_set,
                                      std::map<std::array<AType,7>,std::pair<Halls_5,Moves>>& final_states,
                                      std::map<int,int>& blkr_cols) {
    if(!blkr_cols.empty()){
        std::deque<ObsTup> obst_locations;
        std::map<Crd,int> exst_order;
        std::array<Crd,7> mv_loc_layers = new_layer_ord(exst_order,halls);
        std::sort(mv_loc_layers.begin(),mv_loc_layers.end(),std::less());
        do{
            if(valid_order_exst(mv_loc_layers, exst_order) && not_blocking(mv_loc_layers, block_range)) {
                Halls_5 halls_cpy(halls);
                std::vector<AType> unvisited_cpy(unvisited);
                Moves moves_t(moves);

                try_move(mv_loc_layers, halls_cpy, unvisited_cpy, moves_t);
                std::array<AType,7> tp_arr = get_tp_arr(mv_loc_layers, halls_cpy);

                int this_e = get_energy(moves_t);
                if(!tp_set.contains(tp_arr)){
                    tp_set[tp_arr] = std::pair<int,Moves>{this_e,moves_t};
                    obst_locations.emplace_back(tp_arr,mv_loc_layers,halls_cpy,moves_t);
                } else {
                    auto set_tup = tp_set[tp_arr];
                    if(this_e < set_tup.first || set_tup.first == 0) {
                        tp_set[tp_arr].first = this_e;
                        tp_set[tp_arr].second = moves_t;
                        obst_locations.emplace_back(tp_arr,mv_loc_layers,halls_cpy,moves_t);
                    } else {
                        obst_locations.emplace_back(tp_arr,mv_loc_layers,halls_cpy,tp_set[tp_arr].second);
                    }
                }
            }
        } while(std::next_permutation(mv_loc_layers.begin(),mv_loc_layers.end()));

        int obst_layer_sz = obst_locations.size();
        std::map<int,int> blkr_cols_t(blkr_cols);
        std::vector<Crd> move_layer = find_move_layer(halls,blkr_cols_t);
        for(int i = 0; i < obst_layer_sz; ++i) {
            ObsTup obstup = obst_locations.back();
            Halls_5 halls_t = std::get<2>(obstup);
            std::array<Crd,7> mv_loc_curr = std::get<1>(obstup);
            obst_locations.pop_back();
            std::map<Crd,std::pair<int,int>> ranges;
            bool skip = false;
            for(Crd& c : move_layer) {
                ranges[c] = std::pair<int,int>{-1,7};
                for(int p = c.second/2; p >= 0; --p) {
                    if(mv_loc_curr[p].second != -1) {
                        ranges[c].first = p;
                        break;
                    }
                }
                for(int p = c.second/2+1; p <= 6; ++p) {
                    if(mv_loc_curr[p].second != -1) {
                        ranges[c].second = p;
                        break;
                    }
                }
            }
            std::array<Crd,7> mv_locs_old(mv_loc_curr);
            add_to_mv_locs(move_layer, mv_loc_curr);
            std::sort(mv_loc_curr.begin(),mv_loc_curr.end(),std::less());
            do{
                if(check_fixed(mv_locs_old, mv_loc_curr) && check_range(mv_loc_curr, ranges) &&
                not_blocking(mv_loc_curr, block_range)) {

                    Moves obs_moves = std::get<3>(obstup);
                    Halls_5 obs_halls(halls);
                    std::vector<AType> unvisited_cpy(unvisited);

                    try_move(mv_loc_curr, obs_halls, unvisited_cpy, obs_moves, true);

                    std::array<AType,7> tp_arr = get_tp_arr(mv_loc_curr,obs_halls);
                    int this_e = get_energy(obs_moves);

                    if(!tp_set.contains(tp_arr)){
                        tp_set[tp_arr] = std::pair<int,Moves>{this_e,obs_moves};
                        obst_locations.push_front(ObsTup{tp_arr,mv_loc_curr,obs_halls,obs_moves});
                    } else {
                        auto set_tup = tp_set[tp_arr];
                        if(this_e < tp_set[tp_arr].first || tp_set[tp_arr].first == 0) {
                            tp_set[tp_arr].first = this_e;
                            tp_set[tp_arr].second = obs_moves;
                            obst_locations.push_front(ObsTup{tp_arr,mv_loc_curr,obs_halls,obs_moves});
                        } else {
                            obst_locations.push_front(ObsTup{tp_arr,mv_loc_curr,obs_halls,tp_set[tp_arr].second});
                        }
                    }
                }
            } while(std::next_permutation(mv_loc_curr.begin(),mv_loc_curr.end()));
        }
        if(!blkr_cols_t.empty()){
            for(ObsTup& tup : obst_locations) {
                Moves moves_t = std::get<3>(tup);
                std::vector<AType> unvisited_cpy(unvisited);
                std::array<Crd,7> mv_loc_curr = std::get<1>(tup);
                Halls_5 halls_t = std::get<2>(tup);
                layer_permutations(halls_t,unvisited_cpy, block_range,
                                   moves_t,tp_set,final_states,blkr_cols_t);
            }
        } else {
            for(ObsTup& tup : obst_locations) {
                Moves mv = std::get<3>(tup);
                std::array<AType,7> tp_arr = std::get<0>(tup);
                if(!final_states.contains(tp_arr)){
                    final_states[std::get<0>(tup)] = std::pair<Halls_5,Moves>{std::get<2>(tup), mv};
                } else {
                    int prev_e = get_energy(final_states[std::get<0>(tup)].second);
                    if(get_energy(std::get<3>(tup)) < prev_e) {
                        final_states[std::get<0>(tup)] = std::pair<Halls_5,Moves>{std::get<2>(tup), mv};
                    }
                }
            }
        }
    }
}

bool obstacle_permutations(Halls_5& halls, std::tuple<Crd,int,std::vector<Crd>>& found_blkrs, BlockerPrms& BP,
                           std::vector<AType>& unvisited, std::map<std::array<AType,7>,std::pair<Halls_5,Moves>>& final_states) {

    std::map<std::array<Crd,7>,std::pair<Moves,Halls_5>> loc_moves;
    std::array<Crd,7> mv_loc_layers;
    std::map<Crd,int> exst_order;
    new_layer_ord(exst_order,halls);

    int not_in_hallw = 0;
    std::map<int,int> blkr_cols;
    for(Crd& c : std::get<2>(found_blkrs)) {
        if(c.first != 0) {
            not_in_hallw++;
            blkr_cols[c.second]++;
        }
    }
    Crd fd_crd = std::get<0>(found_blkrs);
    int max_slots = 7-(std::abs(BP.room.second-fd_crd.second)/2);
    if((not_in_hallw+exst_order.size()) >= max_slots){
        return false;
    }

    std::pair<int,int> block_range{std::min(fd_crd.second, BP.room.second),std::max(fd_crd.second,BP.room.second)};
    std::set<std::array<Crd,7>> loc_set;
    std::map<std::array<AType,7>,std::pair<int,Moves>> tp_set;
    Moves moves{{A,0},{B,0},{C,0},{D,0}};
    layer_permutations(halls,unvisited, block_range,
                                                  moves,tp_set,final_states,blkr_cols);
    int sz = check_size(halls);
    return true;
}


std::map<AType,int> blocker_score(Halls_5& halls,
                                   std::vector<AType>& unvisited,
                                   std::map<AType,std::tuple<Crd,int,std::vector<Crd>>>& min_match){
    std::map<AType,int> min_scores{};
    for(auto it = unvisited.begin(); it != unvisited.end() && !unvisited.empty(); ++it) {
        BlockerPrms otherBP(*it);
        min_scores[*it] = 4000;
        find_blockers(otherBP.room, halls, otherBP);
        //BPs[*it] = otherBP;
        for(std::tuple<Crd,int,std::vector<Crd>> tup : otherBP.found) {
            int score = 0;
            for(Crd blkr : std::get<2>(tup)){
                score += std::pow(10,(int)halls[blkr.first][blkr.second]);
            }
            if(score < min_scores[*it]) {
                min_scores[*it] = score;
                min_match[*it] = tup;
            }
        }
    }
    return min_scores;
}

std::map<AType,int> least_blockers_in_fd(Halls_5& halls,
                                  std::vector<AType>& unvisited,
                                  std::map<AType,std::tuple<Crd,int,std::vector<Crd>>>& min_match){
    std::map<AType,int> min_scores{};
    for(auto it = unvisited.begin(); it != unvisited.end() && !unvisited.empty(); ++it) {
        BlockerPrms otherBP(*it);
        min_scores[*it] = 4000;
        find_blockers(otherBP.room, halls, otherBP);
        for(std::tuple<Crd,int,std::vector<Crd>> tup : otherBP.found) {
            int score = 0;
            for(Crd blkr : std::get<2>(tup)){
                score++;
            }
            if(score < min_scores[*it]) {
                min_scores[*it] = score;
                min_match[*it] = tup;
            }
        }
    }
    return min_scores;
}

void sort_least_blocked(Halls_5& halls,
                        std::vector<AType>& unvisited,
                        std::map<AType,std::tuple<Crd,int,std::vector<Crd>>>& min_match){

    auto num_b_map = blocker_score(halls,unvisited, min_match);
    std::vector<std::pair<AType,int>> num_b{num_b_map.begin(),num_b_map.end()};
    std::sort(num_b.begin(),num_b.end(),[](auto kv1, auto kv2) {
        return kv1.second > kv2.second;
    });
    for (int i = 0; i < unvisited.size(); ++i) {
        unvisited[i] = num_b[i].first;
    }
}

bool move_unblocked(Halls_5& halls,
                          std::vector<AType>& unvisited,
                          Moves& moves,
                          std::pair<int, std::map<AType,int>>& min_moves) {
    bool complete_mv = false;
    for(auto it = unvisited.begin(); it != unvisited.end() && !unvisited.empty(); ++it) {
        BlockerPrms otherBP(*it);
        find_blockers(otherBP.room, halls, otherBP);
        bool moved = false;
        for(std::tuple<Crd,int,std::vector<Crd>> tup : otherBP.found) {
            Crd fd = std::get<0>(tup);
            if(std::get<2>(tup).empty() && fd.second != otherBP.room.second) {
                print_hall(halls);
                int num_existing = 0;
                for(int i = 4; i > 0; --i){
                    if(halls[i][otherBP.room.second] != Empty) {
                        num_existing++;
                    } else {
                        break;
                    }
                }
                halls[otherBP.room.first-num_existing][otherBP.room.second] = otherBP.type;
                moves[otherBP.type] += std::get<1>(tup) - num_existing;
                if(num_existing == 3) {
                    unvisited.erase(it);
                    complete_mv = true;
                }
                halls[fd.first][fd.second] = Empty;
                moved = true;
            }
        }
        if(moved){ it = unvisited.begin()-1; }
    }
    if(unvisited.empty()) {
        int this_e = get_energy(moves);
        if(this_e < min_moves.first) {
            min_moves = std::pair<int, std::map<AType,int>>({this_e, moves});
        }
        std::cout << "TOTAL ENERGY: " << this_e << '\n';
        std::cout << "A :" << moves[A] << '\n';
        std::cout << "B :" << moves[B] << '\n';
        std::cout << "C :" << moves[C] << '\n';
        std::cout << "D :" << moves[D] << '\n';
        print_hall(halls);
    }
    return complete_mv;
}


void push_lt_max(std::vector<std::tuple<int,Halls_5,Moves>>& locs,
                 std::pair<Halls_5,Moves>& loc,
                 std::pair<int,int>& ub_e) {
    int max_e = 0;
    for(auto tup : locs) {
        if(std::get<0>(tup) > max_e) { max_e = std::get<0>(tup); }
    }
    if(ub_e.second < max_e) {
        for(auto it = locs.begin(); it != locs.end(); ++it) {
            if(std::get<0>(*it) == max_e){
                locs.erase(it);
                break;
            }
        }
        locs.push_back({ub_e.second,loc.first, loc.second});
    }
}

void add_moves(Moves& new_moves, Moves& moves){
    for(auto& tp_cnt : moves) {
        tp_cnt.second += new_moves[tp_cnt.first];
    }
}
//std::map<std::array<AType,7>,std::pair<Halls_5,Moves>>& final_states,
std::pair<int,int> count_unblocked(std::pair<Halls_5,Moves>& changes,
                                   std::vector<AType>& unvisited,
                                        Moves& moves) {
    Moves mvs(moves);   ////??
    Halls_5 this_hall = changes.first;
    add_moves(changes.second,mvs);
    int total_e = get_energy(moves);
    std::map<AType,int> unblocked = find_unblocked(this_hall, unvisited);
    int total_ub = 0;
    for (auto ub : unblocked) { total_ub += ub.second; }
    return std::pair<int,int>{total_ub,total_e};
    int sz = check_size(this_hall);
}


bool move_obstacles(Halls_5& halls, Moves& moves,
                    std::vector<AType>& unvisited,
                    std::tuple<Crd,int,std::vector<Crd>>& tup,
                    std::pair<int, std::map<AType,int>>& min_moves,
                    BlockerPrms& BP) {

    std::map<std::array<AType,7>,std::pair<Halls_5,Moves>> final_states;
    if(obstacle_permutations(halls, tup, BP, unvisited, final_states) && !final_states.empty()){
        int max_ub = 0;
        int max_ub_next = 0;
        std::vector<std::tuple<int,Halls_5,Moves>> locs;
        for(auto& position : final_states) {
            std::vector<AType> unvisited_cpy(unvisited);
            std::pair<Halls_5,Moves> changes = position.second;
            std::pair<int,int> ub_e = count_unblocked(changes, unvisited, moves);
            if(ub_e.first >= max_ub && ub_e.first != 0) {
                max_ub = ub_e.first;
                if(locs.size() < 5) {
                    locs.push_back({ub_e.second,changes.first,changes.second});
                } else {
                    push_lt_max(locs, changes, ub_e);
                }
            }else if(ub_e.first == max_ub && ub_e.first != 0) {
              move_unblocked(changes.first, unvisited_cpy, changes.second, min_moves);
              std::map<AType,int> next_unblocked = find_unblocked(changes.first, unvisited_cpy);
              int total_ub = 0;
              for (auto ub : next_unblocked) { total_ub += ub.second; }
              if(total_ub >= max_ub_next) {
                  max_ub_next = total_ub;
                  push_lt_max(locs, changes, ub_e);
              }
            }
        }
        for(std::tuple<int,Halls_5,Moves> next : locs) {
            Halls_5 halls_cpy(std::get<1>(next));
            std::vector<AType> unvisited_cpy(unvisited);
            Moves moves_t(std::get<2>(next));
            int sz = check_size(halls_cpy);
            //bool complete_mv = move_unblocked(halls_cpy, unvisited_cpy, moves_t, min_moves);
            move_unblocked(halls_cpy, unvisited_cpy, moves_t, min_moves);
            sz = check_size(halls_cpy);
            find_rooms(halls_cpy, unvisited_cpy, moves_t, min_moves, false);
            sz = check_size(halls_cpy);
        }
        return true;
    } else {
        return false;
    }
}

std::tuple<Crd,int,std::vector<Crd>> next_found(Halls_5& halls_cpy, BlockerPrms& BP,
                                                std::vector<AType>& unvisited_cpy, AType& tp) {
    find_blockers(BP.room, halls_cpy, BP);
    std::map<AType,std::tuple<Crd,int,std::vector<Crd>>> min_match;
    least_blockers_in_fd(halls_cpy, unvisited_cpy, min_match);
    std::tuple<Crd,int,std::vector<Crd>> tup = min_match[tp];
    int sz = check_size(halls_cpy);
    return tup;
}

void find_rooms(
                Halls_5& halls,
                std::vector<AType>& unvisited,
                Moves& moves,
                std::pair<int, std::map<AType,int>>& min_moves, bool sort) {

     if(!unvisited.empty()) {
        // int iter = 0;
         for(AType tp : unvisited) {
             Moves moves_cpy(moves);
             std::vector<AType> unvisited_cpy(unvisited);
             Halls_5 halls_cpy(halls);
             int sz = check_size(halls_cpy);
             BlockerPrms BP(tp);
             std::tuple<Crd,int,std::vector<Crd>> tup;
             if(sort){
                 std::map<AType,std::tuple<Crd,int,std::vector<Crd>>> min_match;
                 sort_least_blocked(halls_cpy, unvisited_cpy, min_match);
                 BP = BlockerPrms(unvisited_cpy.back());
                 find_blockers(BP.room, halls_cpy, BP);
                 tp = unvisited_cpy.back();
                 tup = min_match[tp];
             } else {
                 tup = next_found(halls, BP, unvisited, tp);
             }
             if(!move_obstacles(halls_cpy, moves_cpy, unvisited_cpy, tup, min_moves, BP)){
                 if(sort) { sort = false; }
             }
             sz = check_size(halls_cpy);
             print_hall(halls_cpy);
         }
     }
}

int main()
{
    bool lastbuffernull = false;
    int max_input_len = 40;
    int r_idx = 0;
    Halls_5 halls;
    std::array<AType,11> rows{};
    rows.fill(Empty);
    halls.fill(rows);

    while(!lastbuffernull) {
        char buffer[max_input_len];
        std::cin.get( buffer, max_input_len );
        if(strlen(buffer) != 0) {
            auto s = std::string_view(buffer);
            if(std::any_of(s.begin(), s.end(), [](char c){ return isalpha(c); })) {
                for(int i = 0; i < s.size(); ++i) {
                    if(s[i] != '#' && s[i] != ' ') {
                        int rm = i-1;
                        auto tp = static_cast<AType>((int) s[i] - 65);
                        halls[r_idx+1][rm] = tp;
                    }
                }
                r_idx++;
            }
        }
        line_break();
    }

    std::vector<AType> orig_o{A,B,C,D};
    std::vector<std::vector<AType>> order{orig_o};

    int min_energy = INT_MAX;
    std::pair<int, std::map<AType,int>> min_moves;
    min_moves.first = 9999999;
    for(std::vector<AType> unvisited : order) {

        Halls_5 this_hall = halls;
        Moves moves;

        while(!unvisited.empty()) {
            find_rooms(this_hall, unvisited, moves, min_moves, true);
        }
        int energy = get_energy(moves);
        if(energy < min_energy) { min_energy = energy; }
        std::cout << "e >> " << energy << '\n';
    }

    std::cout << "least energy required: " << min_energy << '\n';
    return 0;
}