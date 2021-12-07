//
// Created by tei on 12/6/21.
//
// Status: tested by comparing the results of method 1 with method 2 on small numbers (up to 80)

#include <bits/stdc++.h>

#define two_line_break() { \
    std::cin.ignore(10000, '\n'); \
    if(strlen(buffer) == 0){ \
    lastbuffernull = true; \
    }\
}

const uint_fast16_t iterations = 256;

inline uint_fast8_t svtoi(std::string_view sv) {
    uint_fast8_t val;
    std::from_chars(sv.data(), sv.data() + sv.size(), val);
    return val;
}

//method 1: calculate the state of the array after every iteration
inline uint_fast8_t* n_day_total(uint_fast16_t n, uint_fast64_t& inp_length, uint_fast8_t* lanternfish) {
    for (size_t t = 0; t < n; ++t) {
        for(size_t i = 0; i < inp_length; ++i){
            if(lanternfish[i]-- == 0){
                lanternfish[i] = 6;
                lanternfish[inp_length++] = 9;
            }
        }
    }
}

//method 2: recursively find the no of new 8s added by adding a new 8 and store new results in a cache
inline long long find_next_sum_nines(uint_fast16_t curr, std::array<long long, iterations+1>& cache) {

    long long res = 1;
    //no of 8s added by the new 8 (at -9 iterations from the total no. of iterations)
    if (curr >= 9) {
       for (uint_fast16_t i = 0; i <= std::floor((curr - 9) / 7); i++){
           uint_fast16_t curr_n = (curr-9) - (i*7);
           long long sum_in_cache = cache[curr_n];
           if(sum_in_cache != -1) {
               res += sum_in_cache;
           } else {
               long long new_sum = find_next_sum_nines(curr_n, cache);
               cache[curr_n] = new_sum;
               res += new_sum;
           }
       }
    }

    return res;
}

inline long long find_next_sum(uint_fast16_t curr, std::array<long long, iterations+1>& cache) {  //no. of new fish after iter iterations
    //new 8s added by the new columns
    long long res = find_next_sum_nines(curr, cache);
    //no. of new 8s added by the currunt column
    uint_fast16_t min_seven = curr - 7;
    for(uint_fast16_t i = 0; i <= std::floor(min_seven / 7); ++i) {
        uint_fast16_t c_next = min_seven - (7*i);
        long long sum_in_cache = cache[c_next];
        if(sum_in_cache != -1) {
            res += sum_in_cache;
        } else {
            long long new_sum = find_next_sum_nines(c_next, cache);
            cache[c_next] = new_sum;
            res += new_sum;
        }
    }
    return res;
}

int main() {

    const uint_fast16_t max_input_len = 999;

    uint_fast8_t lanternfish[static_cast<uint_fast16_t>(std::pow(2,16))];
    bool lastbuffernull = false;
    uint_fast64_t inp_length = 0;

    while(!lastbuffernull) {
        char buffer[max_input_len];
        std::cin.get(buffer, max_input_len);
        if(strlen(buffer) != 0){

            uint_fast16_t last_start = 0;
            uint_fast16_t last_len = 0;
            for (size_t i = 0; i <= strlen(buffer); i++){

                if(buffer[i] == ',' || i == strlen(buffer)) {
                    auto s = std::string_view(&buffer[last_start], last_len);
                    uint_fast8_t num = svtoi(s);
                    lanternfish[inp_length++] = num;
                    last_start = i+1;
                    last_len = 0;
                }
                else {
                    last_len++;
                }
            }
        }

        two_line_break();
    }

    //pt1
    //n_day_total(80, inp_length, lanternfish);
    //std::cout << "total no. of lanternfish after 80 days: " << inp_length << '\n';

    //pt2
    unsigned long long total = 0;
    std::array<long long, iterations+1> cache;
    cache.fill(-1);
    for(size_t i = 0; i < inp_length; ++i){
        int col = lanternfish[i];
        long long result = find_next_sum(((iterations-col) - 1), cache);    // 20 3 <>
        total += result;
    }
    total += inp_length;
    std::cout << "new fish: " << total << '\n';

    return 0;
}
