//
// Created by tei on 12/3/21.
//

#include <bits/stdc++.h>


#define line_break() { \
   std::cin.ignore(10000, '\n'); \
   if(strlen(buffer) == 0){ \
   lastbuffernull = true; \
   }\
}

inline void find_paths(std::set<std::string>& tails, std::vector<std::tuple<std::string,bool>>& paths, std::map<std::string,std::unordered_set<std::string>>& cave_map){
    std::string this_tail;

    for(const std::string& tail : tails){
        std::vector<std::tuple<std::string,bool>> path_matches;
        if(tail == "end"){
            continue;
        } else {
            if(tail == "start"){
               path_matches.emplace_back("start",false);
            } else {
                for(int i = 0; i < paths.size(); ++i){
                    std::string path = std::get<0>(paths[i]);
                    bool two_caves = std::get<1>(paths[i]);
                    std::string path_tail = path.substr(path.find_last_of(' ', path.npos)+1,path.npos);
                    if(path_tail == tail){
                        path_matches.emplace_back(path,two_caves);
                        paths.erase(paths.begin() + i);
                        i--;
                    }
                }
            }
        }
        std::set<std::string> newtails;
        for(std::tuple<std::string,bool>& match : path_matches) {
            for(const auto adj : cave_map[tail]) {
                int lw = 0;
                for(char ch : adj) {
                    if(std::islower(ch)){ lw++; }
                }
                std::string startstr(std::get<0>(match));
                bool two_caves = std::get<1>(match);
                if(lw == adj.size()) {
                    if(startstr.find(adj) == startstr.npos){
                        newtails.insert(adj);
                        paths.emplace_back(startstr.append(" ").append(adj),two_caves);
                    } else {
                        if(!two_caves && adj != "start" && adj != "end"){
                            newtails.insert(adj);
                            paths.emplace_back(startstr.append(" ").append(adj),true);
                        }
                    }
                } else {
                    newtails.insert(adj);
                    paths.emplace_back(startstr.append(" ").append(adj),two_caves);
                }
            }
        }
        find_paths(newtails, paths, cave_map);
    }

}

int main()
{
    int max_input_len = 40;
    bool lastbuffernull = false;
    std::map<std::string,std::unordered_set<std::string>> cave_map;

    while(!lastbuffernull){
        char buffer[max_input_len];
        std::cin.get(buffer, max_input_len );

        if(strlen(buffer) != 0){
            auto s = std::string_view(buffer);
            std::string start = std::string(s.substr(0,s.find("-")));
            std::string end = std::string(s.substr(s.find("-") + 1, s.npos));
            cave_map[start].insert(end);
            cave_map[end].insert(start);
        }
        line_break();
    }

    std::vector<std::tuple<std::string,bool>> paths;
    std::set<std::string> tails{"start"};
    find_paths(tails, paths, cave_map);
    for(int i=0; i < paths.size(); ++i){
        int pos = std::get<0>(paths[i]).find("end");
        if(pos == std::get<0>(paths[i]).npos){
            paths.erase(paths.begin()+i);
            i--;
        }
    }

    std::cout << "no. of paths that visit a single small cave at most twice: " << paths.size() << '\n';
    return 0;
} //144603
