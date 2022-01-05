//
// Created by tei on 12/21/21.
//
/* mostly garbage */

#include <bits/stdc++.h>

#define line_break() { \
   std::cin.ignore(10000, '\n'); \
   if(strlen(buffer) == 0){ \
   lastbuffernull = true; \
   }\
}

int svtoi(std::string_view sv) {
    int val;
    std::from_chars(sv.data(), sv.data() + sv.size(), val);
    return val;
}

typedef std::vector<int> Moves;
typedef std::set<Moves> MvSet;


bool valid_pairs(Moves n, int start, std::vector<int>& diffs){
   std::vector<int> diff;
   bool ret = true;
   for(int i = 0; i < n.size()-1; ++i) {
       int this_i = n[i];
       int next_i = n[i+1];
       int d;
       if(next_i < this_i){
           d = 10+(next_i-this_i);
       } else {
           d = next_i - this_i;
       }
       diff.push_back(d);
       if(n[0] != start || d < 3){
           ret = false;
       }
   }
   if(ret){
       diffs = diff;
   }
   return ret;
}

bool winning_move(Moves moves){
    int sum = 0;
    for(auto it = moves.begin()+1; it != moves.end(); ++it){
        sum+=*it;
    }
    if(sum >= 21) {
        return true;
    }
    return false;
}

unsigned long long find_rolls(MvSet& diffs, std::map<int,int>& n_sums){
    unsigned long long total_rolls = 0;
    for(const std::vector<int>& diff : diffs){
        unsigned long long rolls = 1;
        for(int d : diff){
            rolls = rolls * n_sums[d];
        }
        total_rolls += rolls;
    }
    return total_rolls;
}

unsigned long long find_dice_rolls_p1(int turns,
                                      std::map<int,std::pair<MvSet,MvSet>>& diffs_p1,
                                      std::map<int,std::pair<MvSet,MvSet>>& diffs_p2,
                                      std::map<int,int>& n_sums){
    MvSet p1wins = diffs_p1[turns].first;
    MvSet p2loses = diffs_p2[turns-1].second;
    unsigned long long rolls_p1_w = find_rolls(p1wins, n_sums);
    unsigned long long rolls_p2_l = find_rolls(p2loses, n_sums);
    return rolls_p1_w * rolls_p2_l;
}

unsigned long long find_dice_rolls_p2(int turns,
                                      std::map<int,std::pair<MvSet,MvSet>>& diffs_p1,
                                      std::map<int,std::pair<MvSet,MvSet>>& diffs_p2,
                                      std::map<int,int>& n_sums){
    MvSet p1loses = diffs_p1[turns].second;
    MvSet p2wins = diffs_p2[turns].first;
    unsigned long long rolls_p2_w = find_rolls(p2wins, n_sums);
    unsigned long long rolls_p1_l = find_rolls(p1loses, n_sums);
    return rolls_p2_w * rolls_p1_l;
}

int add_moves_p1(std::set<std::tuple<Moves, std::vector<int>,int>>& pos_sc_p1, std::set<std::tuple<Moves, std::vector<int>, int>>& pos_sc_p2,
                  std::map<int,int>& n_sums, unsigned long long& rolls_W, unsigned long long& rolls_L){
    int turns = 0;
    std::set<std::tuple<Moves,std::vector<int>,int>> new_scs_p1;
    std::set<std::tuple<Moves,std::vector<int>,int>> new_scs_p2;
    std::pair<MvSet,MvSet> dp1;
    std::pair<MvSet,MvSet> dp2;
    std::set<int> new_sc_p1;
    std::set<int> new_sc_p2;
    unsigned long long np1_w = 0; unsigned long long np1_l = 0;
    unsigned long long np2_w = 0; unsigned long long np2_l = 0;
    for(const auto& pos_sc : pos_sc_p1){
        int p_sc = std::get<2>(pos_sc);
        Moves p_mvs = std::get<0>(pos_sc);
        for(const auto& sum : n_sums){
            int new_pos = (p_mvs[p_mvs.size()-1]+sum.first) % 10;
            int new_rolls = sum.second;
            new_pos = (new_pos != 0) ? new_pos : 10;
            int n_sc = p_sc + new_pos;
            new_sc_p1.insert(n_sc);
            Moves new_mvs{p_mvs};
            new_mvs.push_back(new_pos);
            std::vector<int> n_df = std::get<1>(pos_sc);
            n_df.push_back(sum.first);
            if(n_sc >= 21){
                np1_w += new_rolls;
            } else {
                np1_l += new_rolls;
            }
            std::tuple<Moves,std::vector<int>,int> new_psc{new_mvs,n_df,n_sc};
            new_scs_p1.insert(new_psc);
        }
    }
    rolls_W += np1_w;
    rolls_L += np1_l;

    pos_sc_p1 = new_scs_p1;

    for(const auto& pos_sc : pos_sc_p2){
        Moves p_mvs = std::get<0>(pos_sc);
        int p_sc = std::get<2>(pos_sc);
        for(const auto& sum : n_sums){
            int new_pos = (p_mvs[p_mvs.size()-1]+sum.first) % 10;
            int new_rolls = sum.second;
            new_pos = (new_pos != 0) ? new_pos : 10;
            int n_sc = p_sc + new_pos;
            new_sc_p2.insert(n_sc);
            Moves new_mvs{p_mvs};
            new_mvs.push_back(new_pos);
            std::vector<int> n_df = std::get<1>(pos_sc);
            n_df.push_back(sum.first);
            if(n_sc >= 21){
                np2_w += new_rolls;
            } else {
                np2_l += new_rolls;
            }
            std::tuple<Moves,std::vector<int>,int> new_psc{new_mvs,n_df,n_sc};
            new_scs_p2.insert(new_psc);

        }
    }
    pos_sc_p2 = new_scs_p2;

//    prev_sc = std::pair<std::set<int>,std::set<int>>(new_sc_p1,new_sc_p2);

    std::cout << rolls_W << '\n';
    std::cout << rolls_L << '\n';
    unsigned long long p1_nth_l = std::count_if(new_sc_p1.begin(),new_sc_p1.end(),[](int a){ return a < 21; });
    unsigned long long p1_nth_w = new_sc_p1.size() - p1_nth_l;
    unsigned long long p1_nth_w2 = std::count_if(new_sc_p1.begin(),new_sc_p1.end(),[](int a){ return a >= 21; });
    if(p1_nth_l == 0){
        return rolls_W;
    }
    return add_moves_p1(pos_sc_p1, pos_sc_p2, n_sums, rolls_W, rolls_L);
    // turns++;

}

void nCk_moves(const int k, int start, std::vector<int>& board,
                std::map<int,MvSet>& cache,
                std::map<int, std::pair<MvSet,MvSet>>& diffs,
                std::map<int,int>& n_sums){

    if(!cache.contains(k)) {
        //MvSet prev_combs;
        if(!cache.contains(k-1) && k > 2){
            nCk_moves(k-1, start, board, cache, diffs, n_sums);
        }

        MvSet cmbs;
        int n = board.size();
        n--;
        std::vector<int> v(k+1, 0);
        for(;;){
            for (int i = 0; i < k; ++i){
                if (v[i] > n){
                    v[i + 1] += 1;
                    for (int k = i; k >= 0; --k){
                        v[k] = v[i + 1];
                    }
                }
            }

            if (v[k] > 0){ break; }
            std::vector<int> new_cmb;
            for (int i = 0; i < k; ++i){
                new_cmb.push_back(board[v[i]]);
            }
            std::sort(new_cmb.begin(),new_cmb.end(),std::less());
            do{
                std::vector<int> diff;
                if(valid_pairs(new_cmb, start, diff)){
                    if(winning_move(new_cmb)){
                        //win_ls[k].first.insert(new_cmb);
                        diffs[k].first.insert(diff);
                    } else {
                       // win_ls[k].second.insert(new_cmb);
                        diffs[k].second.insert(diff);
                    }
                    cmbs.insert(new_cmb);
                }
            } while(std::next_permutation(new_cmb.begin(),new_cmb.end()));
            //cmbs.insert(new_cmb);
            v[0] += 1;
        }

        cache[k] = cmbs;
    //    return combs;
    }
}


int main()
{
    int lastbuffernull = 0;
    int max_input_len = 50;
    std::array<int,2> pos{};
    std::array<int,2> scores{0,0};

    while(!lastbuffernull){
        char buffer[max_input_len];
        std::cin.get( buffer, max_input_len );
        if(strlen(buffer) != 0){
            auto s = std::string_view(buffer);
            std::string_view p_num = s.substr(s.find("Player ") + 7,1);
            std::string_view p_start = s.substr(s.find("position: ") + 10,1);
            if(p_num == "1"){
                pos[0] = svtoi(p_start);
            } else {
                pos[1] = svtoi(p_start);
            }
        }
        line_break();
    }

    std::array<int,2> poscpy = pos;

    int losing_sc;
    int n = 0;
    for(;;){
        pos[0] = (pos[0] + 9*n + 6) % 10;
        scores[0] += (pos[0] != 0) ? pos[0] : 10;
        if(scores[0] >= 1000){
            losing_sc = scores[1];
            n++;
            break;
        }
        n++;
        pos[1] = (pos[1] + 9*n + 6) % 10;
        scores[1] += (pos[1] != 0) ? pos[1] : 10;
        if(scores[1] >= 1000){
            losing_sc = scores[0];
            n++;
            break;
        }
        n++;
    }

    std::map<int,int> n_sums;
    std::map<std::array<int,3>,int> dice_sums;
    std::set<int> sum_vals;
    for(int i = 1; i <=3; ++i){
        for(int j = 1; j <=3; ++j){
            for(int k = 1; k <= 3; ++k){
                dice_sums[std::array<int,3>{i,j,k}] = i+j+k;
                n_sums[i+j+k] += 1;
                sum_vals.insert(i+j+k);
            }
        }
    }
    std::vector<int> board;
    for(int n = 1; n <=10; ++n){
        board.push_back(n);
    }

    std::map<int,MvSet> mvset_p1;
    std::map<int,MvSet> mvset_p2;
    std::map<int, std::pair<MvSet,MvSet>> win_ls_p1;
    std::map<int, std::pair<MvSet,MvSet>> win_ls_p2;

    std::map<int, std::pair<MvSet,MvSet>> diffs_p1;
    std::map<int, std::pair<MvSet,MvSet>> diffs_p2;

    //unsigned long long rolls_p1_w = 0;
    //int turns = 3;

    //unsigned long long p1_diffs_w;
    //unsigned long long p1_diffs_l;
    //unsigned long long p2_diffs_w;
    //unsigned long long p2_diffs_l;
    //do{
    //    nCk_moves(turns+1, poscpy[0], board, mvset_p1, diffs_p1, n_sums);
    //    nCk_moves(turns+1, poscpy[1], board, mvset_p2, diffs_p2, n_sums);

    //    p1_diffs_l = diffs_p1[turns+1].second.size();
    //    p2_diffs_l = diffs_p2[turns+1].second.size();
    //    rolls_p1_w += find_dice_rolls_p1(turns+1, diffs_p1, diffs_p2,n_sums);
    //    turns++;
    //}while(p1_diffs_l != 0 || p2_diffs_l == 0);

    std::set<std::tuple<Moves,std::vector<int>,int>> pos_sc_p1;
    std::set<std::tuple<Moves,std::vector<int>,int>> pos_sc_p2;
    pos_sc_p1.insert(std::tuple<Moves,std::vector<int>,int>{std::vector<int>{poscpy[0]},std::vector<int>(),0});
    pos_sc_p2.insert(std::tuple<Moves,std::vector<int>,int>{std::vector<int>{poscpy[1]},std::vector<int>(),0});

    unsigned long long r_w = 0;
    unsigned long long r_l = 0;
    add_moves_p1(pos_sc_p1, pos_sc_p2, n_sums, r_w, r_l);


    std::vector<int> sums;

    int num_rolls = n*3;
    std::cout << num_rolls << ' ' << losing_sc <<'\n';
    std::cout << "total number of rolls * score of the losing player: " << num_rolls*losing_sc <<'\n';
}