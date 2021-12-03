#include <bits/stdc++.h>

int main()
{

    int max_input_len = 40;
    bool lastbuffernull = false;
    int gamma[max_input_len];
    memset(gamma, 0, sizeof(gamma));
    int input_len = 0;
    int gamma_decimal = 0;
    int epsilon_decimal = 0;

    while(!lastbuffernull){
        char buffer[max_input_len];
        std::cin.get(buffer, max_input_len );

        if(strlen(buffer) != 0){
            auto s = string_view(buffer);
            std::cout << s << '\n';
            int i = 0;
            while(buffer[i] != '\0'){
                if(buffer[i] == '0') {
                    gamma[i]--;
                } else {
                    gamma[i]++;
                }
                std::cout << gamma[i];
                i++;
            }

            std::cout << '\n';
            input_len = i;
        }

        std::cin.ignore(10000, '\n');
        if(strlen(buffer) == 0){
            lastbuffernull = true;
        }
    }

    int pow = 0;
    while(input_len > 0){
        if(gamma[input_len-1] > 0){ // only odd lengths (?)
            gamma_decimal += std::pow(2,pow);     //most common was 1
        } else if(gamma[input_len-1] < 0) {
            epsilon_decimal += std::pow(2,pow);     //most common was 0
        }
        pow++;
        input_len--;
    }
    std::cout << "pow_consumption: " << gamma_decimal * epsilon_decimal << '\n';
    return 0;
}
