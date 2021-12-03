//
// Created by tei on 12/3/21.
//

#include <bits/stdc++.h>

int main()
{
    bool lastbuffernull = false;
    int lastdepth = 0;
    int incs = 0;

    while(!lastbuffernull){
        char buffer[sizeof(char)*30];
        std::cin.get( buffer, '\n' );
        if(strlen(buffer) != 0) {
            int depth = atoi(buffer);
            if(lastdepth != 0 && depth > lastdepth) {
                incs++;
            }
            lastdepth = depth;
        }

        std::cin.ignore(10000, '\n');
        if(strlen(buffer) == 0){
            lastbuffernull = true;
        }
    }
    std::cout << "no. of times measurement increased from the prv: " << incs << '\n';
    return 0;
}