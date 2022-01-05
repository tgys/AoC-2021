//
// Created by tei on 12/13/21.
//

#include <bits/stdc++.h>

#define line_break() { \
    std::cin.ignore(10000, '\n'); \
    if(strlen(buffer) == 0){ \
    lastbuffernull = true; \
    }\
}

inline int svtoi(std::string_view sv) {
    int val;
    std::from_chars(sv.data(), sv.data() + sv.size(), val);
    return val;
}

inline void insert_pairs_step(int& steps, std::vector<std::pair<char,char>>& pairs, std::map<std::pair<char,char>,char>& rewrites, std::string& tstr){

    while(steps > 0){

        int tpos = 0;
        for(int i = 0; i < pairs.size(); ++i){
            auto fp = pairs[i];
            if(rewrites.contains(fp)){
                tstr.insert(tstr.begin()+tpos+1,rewrites[fp]);
                tpos++;
            }
            tpos++;
        }
        std::vector<std::pair<char,char>> newpairs;
        for(int i = 0; i < tstr.size()-1; ++i){
            std::pair<char,char> p{tstr[i],tstr[i+1]};
            newpairs.push_back(p);
        }
        steps--;
        insert_pairs_step(steps, newpairs, rewrites,tstr);
    }
}

int main()
{
    bool lastbuffernull = false;
    bool prevbufnull = false;
    int lines = 0;

    std::vector<std::pair<char,char>> firstpairs;
    std::map<std::pair<char,char>,char> rewrites;
    std::string firststr;
    while(!lastbuffernull){
        std::string s;
        std::getline(std::cin,s);
        if(s.size() != 0){
            if(!prevbufnull){
                firststr = s;
                for(int i = 0; i < s.size()-1; ++i){
                    std::pair<char,char> p{s[i],s[i+1]};
                    firstpairs.push_back(p);
                }
            } else {
                auto start = s.substr(0,s.find(" -> "));
                auto end = s.substr(s.find(" -> ") + 4, s.npos);
                std::pair<char,char> key{start[0],start[1]};
                rewrites[key] = end[0];
            }
        } else {
            if(prevbufnull){
                int steps = 19;
                insert_pairs_step(steps, firstpairs, rewrites, firststr);
                std::map<char,unsigned long long> cnts;
                unsigned long long max = 0;
                unsigned long long min = ULLONG_MAX;
                std::cout << "sz "<< firststr.size() << '\n';
                for(char ch : firststr){
                    cnts[ch]++;
                }
                for(auto kv : cnts){
                    if(kv.second < min){
                        min = kv.second;
                    }
                    if(kv.second > max){
                        max = kv.second;
                    }
                }
                std::cout << "quantity of the most common element - least common: " << max-min << '\n';
                break;
            } else {
                prevbufnull = true;
            }
        }
        lines++;
    }

    return 0;
}
