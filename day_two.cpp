//
// Created by tei on 12/3/21.
//

#include <bits/stdc++.h>

inline int svtoi(std::string_view sv) {
    int val = 0;
    std::from_chars(sv.data(), sv.data() + sv.size(), val);
    return val;
}

int main()
{
    bool lastbuffernull = false;
    int depth = 0;
    int horizontal_pos = 0;

    while(!lastbuffernull){
        char buffer[sizeof(char)*30];
        std::cin.get( buffer, '\n' );
        if(strlen(buffer) != 0){
            auto s = std::string_view(buffer);
            std::cout << s << '\n';
            auto cmd = s.substr(0,s.find(' '));
            auto value = s.substr(s.find(' ') + 1, s.npos);
            if (cmd == "forward"){
                horizontal_pos += svtoi(value);

            } else if(cmd == "down"){
                depth += svtoi(value);

            } else if(cmd == "up"){
                depth -= svtoi(value);
            }
        }

        std::cin.ignore(10000, '\n');
        if(strlen(buffer) == 0){
            lastbuffernull = true;
        }
    }
    std::cout << "horizontal_pos * depth: " << depth * horizontal_pos << '\n';
    return 0;
}
