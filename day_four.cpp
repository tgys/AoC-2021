//
// Created by tei on 12/4/21.
//

#include <bits/stdc++.h>

struct Index
{   //3-bit unsigned fields for the matrix row and column (0-5)
    unsigned int x_pos : 3;
    unsigned int y_pos : 3;
    bool exists;
};

const int max_input_len = 700;
const int matrix_size = 5;
const int matrix_nums = matrix_size*matrix_size;

typedef std::array<int, matrix_nums> Tbl_nums;
typedef std::array<int, matrix_size> Tbl_matches;

struct Matches{
    Tbl_matches x_matches;
    Tbl_matches y_matches;
};

inline int svtoi(std::string_view sv) {
    int val = 0;
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

int main()
{
    int testnumbers[max_input_len];
    bool lastbuffernull = false;
    int unmatched_sum = 0;
    int score = 0;

    char buffer[max_input_len];
    std::cin.get(buffer, max_input_len);
    int inp_length = 0;
    if(strlen(buffer) != 0){

        int last_start = 0;
        int last_len = 0;
        for (int i = 0; i <= strlen(buffer); i++){

            if(buffer[i] == ',' || i == strlen(buffer)) {
                auto s = std::string_view(&buffer[last_start], last_len);
                int num = svtoi(s);
                testnumbers[inp_length++] = num;
                last_start = i+1;
                last_len = 0;
            }
            else {
                last_len++;
            }
        }
    }
    two_line_break();

    typedef std::map<int,Index> Board;
    std::vector<Board> values;
    std::vector<Tbl_nums> unmatched;
    Tbl_nums nums;
    unmatched.push_back(nums);

    std::vector<Matches> matched;
    //int matrix_len = 0;
    int board_num = 0;
    Board tbl;
    values.push_back(tbl);

    unsigned int row_n = 0;
    unsigned int col_n = 0;
    unsigned int this_cnt = 0;

    while(!lastbuffernull){
        char buffer[matrix_size*3];
        std::cin.get( buffer, matrix_size*3);

        if(strlen(buffer) != 0){

            int last_start = 0;
            int last_len = 0;
            for (unsigned int i = 0; i <= strlen(buffer); i++){
                if(buffer[i] == ' ' || i == strlen(buffer)) {
                    if(i != 0 && last_len != 0){
                        auto s = std::string_view(&buffer[last_start], last_len);
                        int input_num = svtoi(s);
                        unmatched[board_num][this_cnt++] = input_num;
                        Index idx = {row_n, col_n, true};
                        values[board_num].insert_or_assign(input_num, idx);
                        col_n++;
                    }
                    last_start = i+1;
                    last_len = 0;
                }
                else {
                    last_len++;
                }
            }

            if(row_n < matrix_size-1) {
                col_n = 0;
                row_n++;
                line_break();
            } else {
                // matrix_len = 0;
                row_n = 0;
                col_n = 0;

                Board tbl;
                values.push_back(tbl);
                this_cnt = 0;
                Tbl_nums newnums;
                unmatched.push_back(newnums);
                Matches tbl_matches;
                tbl_matches.x_matches.fill(0);
                tbl_matches.y_matches.fill(0);
                matched.push_back(tbl_matches);

                board_num++;
                two_line_break();
            }
        } else {
            line_break();
        }
    }

    bool found = false;
    int sum = 0;
    int final_num = -1;
    for (int i = 0; i < inp_length && !found; i++){
        int board_num = 0;
        int thisnum = testnumbers[i];

        for(Board board : values) {
            if(board.size() == 0 || !board[thisnum].exists){
                board_num++;
                continue;
            }
            int j = 0;  //remove the input number from the list of unmatched numbers for this board
            for(int m : unmatched[board_num]){
                if(m == thisnum){
                    unmatched[board_num][j] = 0;
                }
                j++;
            }

            int x = board[thisnum].x_pos;
            int y = board[thisnum].y_pos;
            int num_x_matches = matched[board_num].x_matches[x];
            int num_y_matches = matched[board_num].y_matches[y];
            if(num_x_matches < 4 && num_y_matches < 4){
                matched[board_num].x_matches[x]++;
                matched[board_num].y_matches[y]++;
            } else {  //board <board_num> would win after adding this number

                for(auto u_num : unmatched[board_num]){
                    sum += u_num;
                }
                final_num = thisnum;
                score = sum*thisnum;
                found = true;
                break;
            }
            board_num++;
        }
    }
    std::cout << '\n';
    std::cout << "final score: " << score << " on board no.: " << board_num << " sum: " << sum << " thisnum: " << final_num << '\n';
    return 0;
}