//
// Created by tei on 12/31/21.
//

#include <bits/stdc++.h>

//method 1: parse instructions into an AST, turn it into an eqn involving w,x,y,z where z=0
//and simplify...

//method 2:

#define apply_op(OP) { \
   if(std::isdigit(cmd[2][0])) { \
      vars[cmd[1][0]] OP std::stoi(cmd[2]); \
   } else { \
      vars[cmd[1][0]] OP vars[cmd[2][0]]; \
   } \
}

typedef std::array<std::string,3> Cmd;

struct Input{
    unsigned long long start = 100000000000000;
    unsigned long long stop = 9999999999999;
    std::string s;
    std::vector<int> next_input(){
        start -= 1;
        s = std::to_string(start);
        std::vector<int> inp;
        int i = 0;
        for(const char ch : s) {
            i++;
            if(ch == '0') {
                int pw = 14-i;
                start -= std::pow(10,pw);
                start += 1;
                next_input();
            }
            inp.push_back(std::atoi(&ch));
        }
        return inp;
    }
};


std::map<char,int> run_program(std::vector<int>& input, std::vector<Cmd>& cmds) {
    std::map<char, int> vars;
    vars['w'] = 0; vars['x'] = 0; vars['y'] = 0; vars['z'] = 0;
    auto inp_it = input.begin();
    int inp_count = 0;
    for(Cmd cmd : cmds){
        std::string op = cmd[0];
        if(op == "inp") {
            int inp = *(inp_it+inp_count);
            vars[cmd[1][0]] = inp;
            inp_count++;
        } else if(op == "add") {
            apply_op(+=)
        } else if(op == "mul") {
            apply_op(*=)
        } else if(op == "mod") {
            apply_op(%=)
        } else if(op == "div") {
            if(std::isdigit(cmd[2][0])) {
                vars[cmd[1][0]] = std::floor((double)vars[cmd[1][0]]/(double)std::stoi(cmd[2]));
            } else {
                vars[cmd[1][0]] = std::floor((double)vars[cmd[1][0]]/(double)vars[cmd[2][0]]);
            }
        } else if(op == "eql") {
            vars[cmd[1][0]] = (vars[cmd[1][0]] == vars[cmd[2][0]]) ? 1 : 0;
        }
    }
    return vars;
}

int main()
{
    bool prevbufnull = false;
    int lines = 0;
    std::vector<Cmd> cmds;

    for(;;){
        std::string s;
        std::getline(std::cin,s);
        if(s.size() != 0) {
            if(!prevbufnull) {
                int last_start = 0;
                int last_len = 0;
                int ix = 0;
                Cmd cmd;
                for (int i = 0; i <= s.size(); i++){
                    if(s[i] == ' ' || i == s.size()) {
                        auto str = s.substr(last_start, last_len);
                        cmd[ix++] = str;
                        last_start = i+1;
                        last_len = 0;
                    }
                    else {
                        last_len++;
                    }
                }
                cmds.push_back(cmd);
            }
        } else {
            if(prevbufnull){
                break;
            } else {
                Input input;
                std::map<char,int> res;
                do{
                    std::vector<int> new_inp = input.next_input();
                    std::cout << input.start << '\n';
                    res = run_program(new_inp,cmds);
                } while(res['z'] != 0 && input.start > input.stop);
                prevbufnull = true;
            }
        }
        lines++;
    }

    return 0;
}
