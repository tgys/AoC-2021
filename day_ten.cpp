//
// Created by tei on 12/10/21.
//

#include <bits/stdc++.h>

#define line_break() { \
    std::cin.ignore(10000, '\n'); \
    if(strlen(buffer) == 0){ \
    lastbuffernull = true; \
    }\
}

typedef std::array<char,3> Illegals;
typedef std::map<char,Illegals> IllegalsMap;

int main()
{
    int_fast16_t max_input_len = 500;
    bool lastbuffernull = false;
    std::map<char,uint_fast16_t> err_points{{')',3}, {']',57},{'}',1197},{'>',25137}};
    std::array<char,4> openings{'(','[','{','<'};
    std::array<char,4> closings{')',']','}','>'};
    std::map<char,char> matchclosed{{'(',')'},{'[',']'},{'{','}'},{'<','>'}};

    std::vector<uint_fast16_t> first_ilgs;
    unsigned long long error_score = 0;
    std::vector<unsigned long long> all_totals;

    while(!lastbuffernull){
        char buffer[max_input_len];
        std::cin.get(buffer, max_input_len );

        if(strlen(buffer) != 0){
            auto s = std::string_view(buffer);

            bool ignore = false;
            std::vector<char> opened;
            for(int_fast16_t i = 0; i < s.size(); ++i){

                char ch = s[i];
                if(std::any_of(openings.begin(),openings.end(),[ch](char a){ return ch == a; })){
                    opened.push_back(ch);
                } else {
                    char last_opened = opened.back();
                    if (ch == matchclosed[last_opened]){
                        opened.pop_back();
                        continue;
                    } else {
                        int_fast16_t this_point = err_points[ch];
                        first_ilgs.push_back(this_point);
                        error_score += this_point;
                        ignore = true;
                        break;
                    }
                }
            }
            std::map<char,int> points{{')',1},{']',2},{'}',3},{'>',4}};
            if(!ignore && opened.size() > 0){
                unsigned long long total_score = 0;
                for(int_fast16_t i = 0; i < opened.size(); ++i) {
                    opened[i] = matchclosed[opened[i]];
                }

                for(int_fast16_t i = opened.size()-1; i >= 0; --i){
                    unsigned long long new_total = 5*total_score;
                    total_score = new_total + points[opened[i]];
                }
                all_totals.push_back(total_score);

            }
        }
        line_break();
    }


    std::cout << '\n';
    std::cout << "total error score: " << error_score << '\n';
    std::sort(all_totals.begin(),all_totals.end(),[](unsigned long long a, unsigned long long b){ return a < b; });
    int_fast16_t mid = (all_totals.size()-1)/2;
    std::cout << "middle score: " << all_totals[mid] << '\n';
    return 0;
}