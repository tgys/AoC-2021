//
// Created by tei on 12/30/21.
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

typedef std::array<std::array<AType,11>,3> Halls;
typedef std::pair<int,int> Crd;

int get_rm(AType tp) {
    return 2*((int)tp+1);
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
        room = {2,get_rm(type) };
    }
};

std::vector<Crd> next_idx(Crd& room) {
    std::vector<Crd> next;
    if(room.first == 2) {
        next.emplace_back(room.first-1,room.second);
        return next;
    } else if(room.first == 1) {
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
void find_blockers(Crd& crd, Halls& halls, BlockerPrms& BP) {
    if(BP.found.size() < 2 && !BP.visited.contains(crd)) {
        BP.last_dist++;
        BP.visited.insert(crd);
        if(halls[crd.first][crd.second] == BP.type) {
            BP.found.emplace_back(crd,BP.last_dist,BP.path_blkrs);
        } else if(halls[crd.first][crd.second] != Empty) {
            BP.blockers.push_back(crd);
            BP.path_blkrs.push_back(crd);
            if(crd.second == BP.room.second && crd.first == 2 &&
            halls[1][crd.second] == (AType)((BP.room.second/2)-1)) {
                BP.blockers.emplace_back(1,crd.second);
                BP.path_blkrs.emplace_back(1,crd.second);
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
            if(BP.found.size()==2) {
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

std::vector<Crd> find_move_layer(Halls& halls, std::map<int,int>& blkr_cols) {
    std::vector<Crd> move_layer;
    int layer_cnt = 0;
    while(layer_cnt < blkr_cols.size()) {
        for(int i = 0; i <= 2; ++i){
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

void push_erase(BlockerPrms& BP, std::pair<Crd,std::vector<Crd>>& rem_dst, Crd& n_crd,
                std::vector<std::pair<Crd,std::vector<Crd>>>& nearest_dest) {
    rem_dst.second.push_back(n_crd);
    for(std::pair<Crd,std::vector<Crd>>& other_dst : nearest_dest) {
        auto n_crd_pos = std::find(other_dst.second.begin(),other_dst.second.end(), n_crd);
        if(other_dst.first.second != BP.room.second && n_crd_pos != other_dst.second.end()) {
            other_dst.second.erase(n_crd_pos);
        }
    }
}

int sort_blockers(Crd c, AType tp, Halls& halls, std::vector<AType>& unvisited){
    int blocked_by = 0;
    AType tp_at_c = halls[0][c.second];
    if(tp_at_c != Empty){
        blocked_by++;
    }
    halls[0][c.second] = tp;
    for(AType uv_tp : unvisited) {
        BlockerPrms BP(uv_tp);
        BP.type = uv_tp;
        find_blockers(BP.room, halls, BP);
        for(Crd o_blkr : BP.blockers){
            if(o_blkr == c){
                blocked_by++;
            }
        }
    }
    halls[0][c.second] = tp_at_c;
    return blocked_by;
}

bool sort_dist(Crd a, Crd b, AType tp, Crd blkr,
               std::vector<AType>& unvisited, Halls& halls) {
    int dist_a_rm = std::max(a.second, get_rm(tp)) - std::min(a.second, get_rm(tp));
    int dist_a_blkr = std::max(a.second, blkr.second) - std::min(a.second, blkr.second);
    int dist_a = dist_a_rm + dist_a_blkr;
    int dist_b_rm = std::max(b.second, get_rm(tp)) - std::min(b.second, get_rm(tp));
    int dist_b_blkr = std::max(b.second, blkr.second) - std::min(b.second, blkr.second);
    int dist_b = dist_b_rm + dist_b_blkr;
    if(dist_a == dist_b) {
        int blocked_by_a = sort_blockers(a, tp, halls, unvisited);
        int blocked_by_b = sort_blockers(b, tp, halls, unvisited);
        if(blocked_by_a == blocked_by_b) {
            return dist_a_blkr > dist_b_blkr;
        } else
            return blocked_by_a > blocked_by_b;
    }
    else
        return dist_a > dist_b;
}

void move_obstacles(Halls& halls, std::map<AType,int>& moves,
                    std::vector<AType>& unvisited, BlockerPrms& BP) {
    std::set<Crd> dest_v;
    dest_v.insert({0,0});
    dest_v.insert({0,10});
    int c_max = 0;
    int c_min = 10;
    if(BP.room.second < c_min){ c_min = BP.room.second; }
    if(BP.room.second > c_max){ c_max = BP.room.second; }
    for(std::tuple<Crd,int,std::vector<Crd>> tup : BP.found) {
        int t_col = std::get<0>(tup).second;
        if(t_col < c_min){ c_min = t_col; }
        if(t_col > c_max){ c_max = t_col; }
    }

    for(int i = 1; i < halls[0].size()-1; i = i + 2) {
        if(i < c_min || i > c_max) {
            dest_v.insert({0,i});
        }
    }

    std::map<int,int> blkr_cols;
    std::vector<std::pair<Crd,std::vector<Crd>>> nearest_dest;
    std::vector<Crd> other_blkrs;

    for(Crd blkr : BP.blockers) {
        blkr_cols[blkr.second]++;
        AType tp = halls[blkr.first][blkr.second];
        std::vector<Crd> nearest_v(dest_v.begin(),dest_v.end());
        std::sort(nearest_v.begin(), nearest_v.end(),[tp,blkr,&halls,&unvisited](Crd a, Crd b) {
            return sort_dist(a,b,tp,blkr,unvisited,halls);
        });

        AType a = halls[blkr.first][blkr.second];
        AType e = halls[nearest_v.back().first][nearest_v.back().second];
        if(e != Empty) {
            if(int(e) <= int(a)) {
                other_blkrs.emplace_back(nearest_v.back().first,nearest_v.back().second);
            } else {
                nearest_v.pop_back();
            }
        }
        nearest_dest.emplace_back(blkr,nearest_v);
    }
    std::sort(nearest_dest.begin(),nearest_dest.end(),[halls](auto kv1, auto kv2) {
        return (int)halls[kv1.first.first][kv1.first.second] < (int)halls[kv2.first.first][kv2.first.second];
    });

    std::map<Crd,Crd> moveto;

    for(std::pair<Crd,std::vector<Crd>>& rem_dst : nearest_dest) {
        int b_rw = rem_dst.first.first;
        int b_cl = rem_dst.first.second;
        AType blk_type = halls[b_rw][b_cl];
        if(b_cl == BP.room.second) {
            if(blk_type == BP.type) {
                for(int i : std::array<int,2>{BP.room.second-1,BP.room.second+1}) {
                    Crd n_crd{0,i};
                    if(i > c_min && i < c_max) {
                        push_erase(BP, rem_dst, n_crd,nearest_dest);
                    }
                }
            } else if(b_rw == 2 && halls[b_rw-1][b_cl] == BP.type) {
                for(int i : std::array<int,2>{BP.room.second-1,BP.room.second+1}) {
                    Crd n_crd{0,i};
                    if(i < c_min || i > c_max) {
                        push_erase(BP, rem_dst, n_crd,nearest_dest);
                    }
                }
            }
        } else if(b_cl == get_rm(blk_type) && halls[2][b_cl] == BP.type) {
           int drc = (BP.room.second - b_cl) > 0 ? 1 : -1;
           if(halls[0][b_cl - drc] == Empty){
               halls[0][b_cl+drc] = BP.type;
               halls[2][b_cl] = blk_type;
               halls[1][b_cl] = Empty;
               moves[BP.type] += 3;
               moves[blk_type] += 5;
               blkr_cols[b_cl]--;
               remove_empty_kvs(blkr_cols);

               for(auto it = nearest_dest.begin(); it != nearest_dest.end(); ++it){
                   if(it->first == rem_dst.first){
                       nearest_dest.erase(it);
                       break;
                   }
               }
           }
        }
    }

    while(!nearest_dest.empty()) {
        std::pair<Crd,std::vector<Crd>> dst = nearest_dest.back();
        nearest_dest.pop_back();
        Crd nearest = dst.second.back();

        moveto[dst.first] = nearest;
        dest_v.erase(nearest);
        for(std::pair<Crd,std::vector<Crd>>& rem_dst : nearest_dest) {
            Crd other = rem_dst.second.back();
            if(other == nearest) {
                rem_dst.second.pop_back();
            }
        }
    }

    for(Crd oth_b : other_blkrs ) {
        AType tp = halls[oth_b.first][oth_b.second];
        std::vector<Crd> nearest_v(dest_v.begin(),dest_v.end());
        std::sort(nearest_v.begin(), nearest_v.end(),[tp,oth_b,&halls,&unvisited](Crd a, Crd b) {
            return sort_dist(a,b,tp,oth_b,unvisited,halls);
        });
        Crd oth_mt = nearest_v.back();
        int oth_dist = std::max(oth_b.second, oth_mt.second) - std::min(oth_b.second,oth_mt.second);
        moves[tp] += oth_dist;
        halls[oth_mt.first][oth_mt.second] = tp;
        halls[oth_b.first][oth_b.second] = Empty;
    }

    while(!blkr_cols.empty()){
        std::vector<Crd> move_layer = find_move_layer(halls,blkr_cols);
        std::sort(move_layer.begin(),move_layer.end(),[&moveto](Crd a, Crd b) {
            int a_dist = std::max(a.second, moveto[a].second) - std::min(a.second,moveto[a].second);
            int b_dist = std::max(b.second, moveto[b].second) - std::min(b.second,moveto[b].second);

            return a_dist > b_dist;
        });
        for(Crd crd : move_layer) {
            AType tp = halls[crd.first][crd.second];

            int a_dist = std::max(crd.second, moveto[crd].second) - std::min(crd.second,moveto[crd].second);
            moves[tp] += a_dist + crd.first;
            halls[moveto[crd].first][moveto[crd].second] = tp;
            halls[crd.first][crd.second] = Empty;
        }
    }

    for(std::tuple<Crd,int,std::vector<Crd>>& tup : BP.found) {
        Crd fd = std::get<0>(tup);
        int dist = std::get<1>(tup);
        if(halls[fd.first][fd.second] != BP.type) {
            for(int i = 0; i < halls[0].size(); ++i) {
                if(halls[0][i] == BP.type) {
                    fd = Crd{0,i};
                    dist = 2+(std::max(BP.room.second,i) - std::min(BP.room.second,i));
                }
            }
        }
        halls[fd.first][fd.second] = Empty;
        moves[BP.type] += dist;
    }
    halls[BP.room.first][BP.room.second] = BP.type;
    halls[BP.room.first-1][BP.room.second] = BP.type;
    moves[BP.type]--;
    unvisited.pop_back();

}

void find_rooms(
                Halls& halls,
                std::vector<AType>& unvisited,
                std::map<AType,int>& moves) {

        AType tp = unvisited.back();
        BlockerPrms BP(tp);
        BP.type = tp;

        find_blockers(BP.room, halls, BP);
        move_obstacles(halls, moves, unvisited, BP);

        //move unblocked apods to their rooms
        for(auto it = unvisited.begin(); it != unvisited.end() && !unvisited.empty(); ++it) {
            BlockerPrms otherBP(*it);
            find_blockers(otherBP.room, halls, otherBP);
            bool moved = false;
            for(std::tuple<Crd,int,std::vector<Crd>> tup : otherBP.found) {
                Crd fd = std::get<0>(tup);
                if(std::get<2>(tup).empty() && fd.second != otherBP.room.second) {
                    if(halls[otherBP.room.first][otherBP.room.second] != Empty) {
                        halls[otherBP.room.first-1][otherBP.room.second] = otherBP.type;
                        moves[otherBP.type] += std::get<1>(tup) - 1;
                        unvisited.erase(it);
                    } else {
                        halls[otherBP.room.first][otherBP.room.second] = otherBP.type;
                        moves[otherBP.type] += std::get<1>(tup);
                    }
                    halls[fd.first][fd.second] = Empty;
                    moved = true;
                }
            }
            if(moved){ it = unvisited.begin()-1; }
        }

        //sort apod types by the number of blockers (most blocked to least blocked)
        std::map<AType,int> num_b;
        for(auto it = unvisited.begin(); it != unvisited.end() && !unvisited.empty(); ++it) {
            BlockerPrms least_blkd_BP(*it);
            find_blockers(least_blkd_BP.room, halls, least_blkd_BP);
            for(auto& crd : least_blkd_BP.blockers){
                AType tp = halls[crd.first][crd.second];
                num_b[*it] += ((int)tp)+1;
            }
        }
        std::vector<std::pair<AType,int>> num_blked(num_b.begin(),num_b.end());
        std::sort(num_blked.begin(),num_blked.end(),[](auto kv1, auto kv2) {
            return kv1.second > kv2.second;
        });
        for (int i = 0; i < unvisited.size(); ++i) {
            unvisited[i] = num_blked[i].first;
        }

}

int main()
{
    bool lastbuffernull = false;
    int max_input_len = 40;
    int r_idx = 0;
    Halls halls;
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
    std::vector<std::vector<AType>> order;
    for(int i = orig_o.size()-1; i >= 0 ; --i) {
        std::vector<AType> uv(orig_o);
        AType next = uv[i];
        uv.erase(std::find(uv.begin(),uv.end(),next));
        uv.push_back(next);
        order.push_back(uv);
    }

    int min_energy = INT_MAX;
    for(std::vector<AType> unvisited : order) {
        Halls this_hall = halls;
        std::map<AType,int> moves;
        while(!unvisited.empty()) {
            find_rooms(this_hall, unvisited, moves);
        }
        int energy = 0;
        for(auto m : moves) {
            energy += m.second * std::pow(10,(int)m.first);
        }
        if(energy < min_energy) { min_energy = energy; }
        std::cout << "e >> " << energy << '\n';
    }

    std::cout << "least energy required: " << min_energy << '\n';
    return 0;
}