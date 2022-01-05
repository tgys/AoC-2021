//
// Created by tei on 12/16/21.
//


#include <bits/stdc++.h>

#define line_break() { \
    std::cin.ignore(10000, '\n'); \
    if(strlen(buffer) == 0){ \
    lastbuffernull = true; \
    }\
}

std::array<int,4> fb_binary(char ch){
    int char_int = (int)ch;
    if(!std::isdigit(ch)){
        char_int = int(ch) - 55;
    }
    std::array<int,4> arr;
    int i=0,r;
    while(char_int!=0)
    {
        r = char_int%2;
        arr[i++] = r;
        char_int /= 2;
    }
    while(i<4){
        arr[i++] = 0;
    }
    return arr;
}

std::string parsehex(std::string_view& s){
    std::ostringstream ss;
    for(char c : s){
        std::array<int,4> hexarr = fb_binary(c);
        for(int n = 3; n >= 0; n--){
            ss << hexarr[n];
        }
    }
    return ss.str();
}

unsigned long bin_to_dec(std::string& bin){
    unsigned long num = 0;
    for (int n = bin.size()-1; n >=0; --n){
        int pow = (bin.size()-1) - n;
        num += ((int)bin[n] - 48)*std::pow(2,pow);
    }
    return num;
}

struct Packet{
    int version;
    int type_id;
    char length_type;
    int l_num;
    int l_len;
};

void parse_header(Packet& pk, std::string& binstr){
    std::string vvv = binstr.substr(0,3);
    pk.version = bin_to_dec(vvv);
    std::string ttt = binstr.substr(3,3);
    pk.type_id = bin_to_dec(ttt);
}

int parsebin(std::string& binstr, std::vector<int>& v_nums, int& pkt_num, unsigned long& pkt_val){
    Packet pk;
    parse_header(pk, binstr);
    int this_len = 6;
    int sub_len = 0;
    int sub_num = 0;
    v_nums.push_back(pk.version);
    std::vector<int> sub_pk_vals;
    if(pk.type_id != 4){ //operator
        //std::cout <<binstr.substr(6,1) << '\n';
        pk.length_type = binstr.substr(6,1)[0];
        this_len++;
        if(pk.length_type == '0'){
            std::string l_bin = binstr.substr(7, 15);
            this_len+=15;
            pk.l_len = bin_to_dec(l_bin);
            pk.l_num = 0;
            while(sub_len < pk.l_len){
                std::string nextstr = binstr.substr(22+sub_len, binstr.npos);
                unsigned long pkt_val;
                sub_len += parsebin(nextstr,v_nums, sub_num, pkt_val);
                sub_pk_vals.push_back(pkt_val);
            }
        } else { // '1'
            std::string l_bin = binstr.substr(7, 11);
            this_len+=11;
            pk.l_num = bin_to_dec(l_bin);
            pk.l_len = 0;
            int this_pk_num = 0;
            while(this_pk_num < pk.l_num){
                std::string nextstr = binstr.substr(18+sub_len, binstr.npos);
                unsigned long pkt_val;
                sub_len += parsebin(nextstr, v_nums, sub_num, pkt_val);
                sub_pk_vals.push_back(pkt_val);
                this_pk_num++;
            }
        }
        this_len+=sub_len;
        sub_num++;
        pkt_num+=sub_num;
        switch(pk.type_id) {
            case 0 : {
                pkt_val = std::accumulate(sub_pk_vals.begin()+1, sub_pk_vals.end(), *sub_pk_vals.begin(), [](unsigned long a, unsigned long b){ return a+b; });
                break;
            }
            case 1 : {
                pkt_val = std::accumulate(sub_pk_vals.begin()+1, sub_pk_vals.end(), *sub_pk_vals.begin(), [](unsigned long a, unsigned long b){ return a*b; });
                break;
            }
            case 2 : {
                unsigned long min = ULONG_MAX;
                for(auto i : sub_pk_vals){
                    if(i < min){ min = i; }
                }
                pkt_val = min;
                break;
            }
            case 3 : {
                unsigned long max = 0;
                for(auto i : sub_pk_vals){
                    if(i > max){ max = i; }
                }
                pkt_val = max;
                break;
            }
            case 5 : {
                if(sub_pk_vals[0] > sub_pk_vals[1]){
                    pkt_val = 1;
                } else
                    pkt_val = 0;
                break;
            }
            case 6 : {
                if(sub_pk_vals[0] < sub_pk_vals[1]){
                    pkt_val = 1;
                } else
                    pkt_val = 0;
                break;
            }
            case 7 : {
                if(sub_pk_vals[0] == sub_pk_vals[1]){
                    pkt_val = 1;
                } else
                    pkt_val = 0;
                break;
            }
            default:;
        }
    } else { //literal
        std::string prefix = binstr.substr(this_len,1);
        std::string val;
        while(prefix != "0"){
            val.append(binstr.substr(this_len+1,4));
            sub_len+=5;
            this_len+=5;
            prefix = binstr.substr(this_len,1);
        }
        val.append(binstr.substr(this_len+1,4));
        this_len+=5;
        pkt_num++;
        pkt_val = bin_to_dec(val);
    }
    return this_len;
}

int main()
{
    bool lastbuffernull = false;
    int max_input_length = 99999;
    int pkt_num = 0;
    unsigned long pkt_val;
    int total_len = 0;
    std::vector<int> v_nums;

    while(!lastbuffernull){
        char buffer[max_input_length];
        std::cin.get( buffer, max_input_length);
        if(strlen(buffer) != 0){
            auto s = std::string_view(buffer);
            std::string bin_str = parsehex(s);
            //std::cout << bin_str <<'\n';
            total_len = parsebin(bin_str,v_nums,pkt_num, pkt_val);
            std::cout << "bin sz: " << total_len << '\n';
        }

        line_break();
    }
    int version_sum = 0;
    for(int n : v_nums){
        version_sum+=n;
    }
    std::cout << "final packet value: " << pkt_val << '\n';
    std::cout << "sum of version numbers: " << version_sum << '\n';
    return 0;
}
