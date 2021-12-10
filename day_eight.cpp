//
// Created by tei on 12/8/21.
//

#include <bits/stdc++.h>

const uint_fast16_t max_input_len = 200;

inline uint_fast16_t svtoi(std::string_view sv) {
    uint_fast16_t val = 0;
    std::from_chars(sv.data(), sv.data() + sv.size(), val);
    return val;
}

#define line_break() { \
    std::cin.ignore(10000, '\n'); \
    if(strlen(buffer) == 0){ \
    lastbuffernull = true; \
    }\
}

#define two_line_break() { \
    std::cin.ignore(10000, '\n'); \
    std::cin.ignore(10000, '\n'); \
    if(strlen(buffer) == 0){ \
    lastbuffernull = true; \
    }\
}

struct Key
{
    std::string_view chars;
    uint_fast16_t value;
};

typedef std::array<std::vector<Key>, 8> Lengths;

int main()
{
    bool lastbuffernull = false;
    uint_fast64_t sum_easy = 0;
    uint_fast64_t sum_all = 0;

    while(!lastbuffernull) {
        char buffer[max_input_len];
        std::cin.get(buffer, max_input_len);
        Lengths lengths;
        std::map<std::string_view, uint_fast16_t> keys5;
        std::map<std::string_view, uint_fast16_t> keys6;
        if(strlen(buffer) != 0){

            uint_fast32_t sum_this = 0;
            auto s = std::string_view(buffer);
            auto display = s.substr(0,s.find(" | "));
            auto this_output = s.substr(s.find(" | ") + 3, s.npos);
            uint_fast16_t last_start = 0;
            uint_fast16_t last_len = 0;
            for(size_t i = 0; i <= display.size(); ++i) {
                if(display[i] == ' ' || i == display.size()) {
                    auto s = std::string_view(&display[last_start], last_len);
                    uint_fast16_t len = s.size();
                    Key key;
                    key.chars = s;
                    switch(len) {
                        case 7 : { key.value = 8; break; }
                        case 4 : { key.value = 4; break; }
                        case 3 : { key.value = 7; break; }
                        case 2 : { key.value = 1; break; }
                        default:;
                    }
                    lengths[len].push_back(key);
                    last_start = i+1;
                    last_len = 0;
                }
                else {
                    last_len++;
                }
            }
            last_start = 0;
            last_len = 0;

            for(auto i = 0; i < 3; ++i) {
                std::string_view sv = lengths[6][i].chars;
                uint_fast16_t matches1 = 0;
                for(char ch : sv) {  //compare with 4 (length 4)
                    if(lengths[2][0].chars.find(ch) != lengths[2][0].chars.npos) {
                        matches1++;
                    }
                }
                if(matches1 == 1) {
                    lengths[6][i].value = 6;
                    std::string_view sv2, sv3;
                    switch(i) {
                        case 0 : { sv2 = lengths[6][1].chars; break; }
                        case 1 : { sv2 = lengths[6][0].chars; break; }
                        case 2 : { sv2 = lengths[6][0].chars; break; }
                        default:;
                    }
                    uint_fast16_t matches4 = 0;
                    for(char ch : sv2) {  //compare with 4 (length 4)
                        if(lengths[4][0].chars.find(ch) != lengths[4][0].chars.npos) {
                            matches4++;
                        }
                    }
                    if(matches4 == 4) {
                        switch(i) {
                            case 0 : { lengths[6][1].value = 9; lengths[6][2].value = 0;  break; }
                            case 1 : { lengths[6][0].value = 9; lengths[6][2].value = 0;  break; }
                            case 2 : { lengths[6][0].value = 9; lengths[6][1].value = 0;  break; }
                            default:;
                        }
                    } else {
                        switch(i) {
                            case 0 : { lengths[6][1].value = 0; lengths[6][2].value = 9;  break; }
                            case 1 : { lengths[6][0].value = 0; lengths[6][2].value = 9;  break; }
                            case 2 : { lengths[6][0].value = 0; lengths[6][1].value = 9;  break; }
                            default:;
                        }
                    }
                }

            }

            uint_fast16_t matches_f = 0;

            for(auto i : lengths[5]) {    //using the vector as a stack...
                Key thiskey = lengths[5].back();
                std::string_view sv = thiskey.chars;
                lengths[5].pop_back();
                for(auto j : lengths[5]) {
                    matches_f = 0;
                    for(char ch : sv) {
                        if(j.chars.find(ch) != j.chars.npos) {
                            matches_f++;
                        }
                    }
                }

                if(matches_f != 3) {
                    lengths[5].insert(lengths[5].begin(), thiskey);
                    continue;
                } else {
                    uint_fast16_t matchesf4 = 0;
                    for(char ch : sv) {  //compare with 4 (length 4)
                        if(lengths[4][0].chars.find(ch) != lengths[4][0].chars.npos) {
                            matchesf4++;
                        }
                    }
                    if(matchesf4 == 2) {
                        //3 and 5 left
                        Key secondkey = lengths[5].back();
                        lengths[5].pop_back();
                        std::string_view sv2 = secondkey.chars;
                        uint_fast16_t matchesf7 = 0;
                        for(char ch : sv2) {  //compare with 7 (length 3)
                            if(lengths[3][0].chars.find(ch) != lengths[3][0].chars.npos) {
                                matchesf7++;
                            }
                        }
                        if(matchesf7 == 2) {  //only 3 left
                            Key thirdkey = lengths[5].back();
                            lengths[5].pop_back();
                            std::string_view sv3 = thirdkey.chars;
                            Key k5{sv2,5};
                            lengths[5].push_back(k5);
                            Key k3{sv3,3};
                            lengths[5].push_back(k3);
                        }
                        Key k2{sv,2};
                        lengths[5].push_back(k2);
                    } else { // == 3
                        Key secondkey = lengths[5].back();
                        lengths[5].pop_back();
                        std::string_view sv2 = secondkey.chars;
                        uint_fast16_t matchesf7 = 0;
                        for(char ch : sv2) {  //compare with 7 (length 3)
                            if(lengths[3][0].chars.find(ch) != lengths[3][0].chars.npos) {
                                matchesf7++;
                            }
                        }
                        if(matchesf7 == 2) {  //only 3 left
                            Key thirdkey = lengths[5].back();
                            lengths[5].pop_back();
                            std::string_view sv3 = thirdkey.chars;
                            Key k5{sv2,2};
                            lengths[5].push_back(k5);
                            Key k3{sv3,3};
                            lengths[5].push_back(k3);
                        }

                        Key k5{sv,5};   // 3 and 2 left
                        lengths[5].push_back(k5);
                    }
                    break;
                }

            }

            uint_fast16_t ix = 0;
            const uint_fast16_t num_digits_output = 4;
            std::string string;
            for (size_t i = 0; i <= this_output.size(); ++i) {
                if(this_output[i] == ' ' || i == this_output.size()) {
                    auto s = std::string_view(&this_output[last_start], last_len);
                    uint_fast16_t len = s.size();
                    uint_fast16_t p_of_10 = std::pow(10, (num_digits_output-1)-ix);
                    if(len != 5 && len != 6) {
                        sum_easy++;
                        uint_fast16_t m = lengths[len][0].value;
                        sum_this += m*p_of_10;
                        string.append(std::to_string(m));
                    }
                    else {
                        for(auto m : lengths[len]) {
                            uint_fast16_t matches = 0;
                            for(char ch : s) {
                                if(m.chars.find(ch) != m.chars.npos) {
                                    matches++;
                                }
                            }

                            if(matches == len) {
                                 sum_this += m.value*p_of_10;
                                 string.append(std::to_string(m.value));
                            }
                        }
                    }

                    last_start = i+1;
                    last_len = 0;
                    ix++;
                }
                else {
                    last_len++;
                }

            }
            sum_all += sum_this;
        }

        line_break();
    }

    std::cout << "total no. of digits that are either 1, 4, 7, or 8: " << sum_easy << '\n';
    std::cout << "sum of all output values: " << sum_all << '\n';
    return 0;
}
