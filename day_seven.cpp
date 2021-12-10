//
// Created by tei on 12/7/21.
//


#include <bits/stdc++.h>

#define line_break() { \
    std::cin.ignore(10000, '\n'); \
    if(strlen(buffer) == 0){ \
    lastbuffernull = true; \
    }\
}

inline uint_fast16_t svtoi(std::string_view sv) {
    uint_fast16_t val;
    std::from_chars(sv.data(), sv.data() + sv.size(), val);
    return val;
}

int main() {

    const uint_fast16_t max_input_len = static_cast<uint_fast16_t>(std::pow(2, 15));

    uint_fast16_t crabs[static_cast<uint_fast16_t>(std::pow(2,16))];
    bool lastbuffernull = false;
    uint_fast64_t inp_length = 0;
    uint_fast16_t max = 0;

    while(!lastbuffernull) {
        char buffer[max_input_len];
        std::cin.get(buffer, max_input_len);
        if(strlen(buffer) != 0){

            uint_fast16_t last_start = 0;
            uint_fast16_t last_len = 0;
            for (size_t i = 0; i <= strlen(buffer); i++){

                if(buffer[i] == ',' || i == strlen(buffer)) {
                    auto s = std::string_view(&buffer[last_start], last_len);
                    uint_fast16_t num = svtoi(s);
                    if (num > max) { max = num; }
                    crabs[inp_length++] = num;
                    last_start = i+1;
                    last_len = 0;
                }
                else {
                    last_len++;
                }
            }
        }

        line_break();
    }

    for(size_t i = 0; i < inp_length; ++i){
        uint_fast16_t col = crabs[i];
        std::cout << col << ' ';
    }
    std::cout << '\n';

    uint_fast16_t fuel[inp_length];
    uint_fast64_t min_sum = static_cast<uint_fast16_t>(std::pow(2,63));;
    for(auto i = 0; i < max; ++i){
        for(size_t j = 0; j < inp_length; ++j){
            int col = crabs[j];
            int diff = std::max(col, i) - std::min(col, i);
            uint_fast32_t dtotal = 0;
            for(auto d = 1; d <= diff; ++d){
                dtotal += d;
            }
            fuel[j] = dtotal;
        }
        uint_fast64_t this_sum = 0;
        for(auto f : fuel) {
            this_sum += f;
        }
        if (this_sum < min_sum) { min_sum = this_sum; }
    }

    std::cout << "alignment with the least fuel used: " << min_sum << '\n';

    return 0;
}
