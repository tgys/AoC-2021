//
// Created by tei on 12/18/21.
//
/* everything works */

#include <bits/stdc++.h>

enum Type{
    leftnode= 0,
    rightnode = 1,
};

struct SFnumber {
    std::shared_ptr<SFnumber> first;
    std::shared_ptr<SFnumber> second;
    std::shared_ptr<SFnumber> parent;
    Type type;
    int nestlevel;
    std::pair<int,int> data;
};

std::string sfn_tostring(std::shared_ptr<SFnumber> sfn){
    std::string start("[");
    if(sfn->data.first != -1){
        start.append(std::to_string(sfn->data.first));
    } else {
        start.append(sfn_tostring(sfn->first));
    }
    start.append(",");
    if(sfn->data.second != -1){
        start.append(std::to_string(sfn->data.second));
    } else {
        start.append(sfn_tostring(sfn->second));
    }
    start.append("]");
    return start;
}

std::shared_ptr<SFnumber> left_search_val(std::shared_ptr<SFnumber> sfn, int& right_val, Type& val_tp){
    if(sfn->data.first != -1){
        right_val = sfn->data.first;
        val_tp = leftnode;
        return sfn;
    } else {
        return left_search_val(sfn->first, right_val, val_tp);
    }
}

std::shared_ptr<SFnumber> right_search_val(std::shared_ptr<SFnumber> sfn, int& left_val, Type& val_tp){
    if(sfn->data.second != -1){
        left_val = sfn->data.second;
        val_tp = rightnode;
        return sfn;
    } else {
        return right_search_val(sfn->second, left_val, val_tp);
    }
}

std::shared_ptr<SFnumber> find_right(std::shared_ptr<SFnumber> sfn, int& right_val, Type& val_tp){
  //  int right = -1;
    std::shared_ptr<SFnumber> right_ptr = nullptr;
    if(sfn->parent != nullptr) {
        if (sfn->type == leftnode) {
            auto parentptr = sfn->parent;
            if (parentptr->data.second != -1) {
                right_val = parentptr->data.second;
                val_tp = rightnode;
                right_ptr = parentptr;
            } else if (parentptr->second != nullptr) {
                right_ptr = left_search_val(parentptr->second, right_val, val_tp);
            }
        } else {
            right_ptr = find_right(sfn->parent, right_val, val_tp);
        }
    }
    return right_ptr;
}

std::shared_ptr<SFnumber> find_left(std::shared_ptr<SFnumber> sfn, int& left_val, Type& val_tp){
    //int left = -1;
    std::shared_ptr<SFnumber> left_ptr = nullptr;
    if(sfn->parent != nullptr) {
        if (sfn->type == rightnode) {
            auto parentptr = sfn->parent;
            if (parentptr->data.first != -1) {
                left_val = parentptr->data.first;
                val_tp = leftnode;
                left_ptr = parentptr;
            } else if (parentptr->first != nullptr) {
                left_ptr = right_search_val(parentptr->first, left_val, val_tp);
            }
        } else {
            left_ptr = find_left(sfn->parent, left_val, val_tp);
        }
    }
    return left_ptr;
}

int find_explode(std::shared_ptr<SFnumber> sfn);
int split(std::shared_ptr<SFnumber> sfn);
void explode_split_loop(std::shared_ptr<SFnumber> sfn);

std::shared_ptr<SFnumber> findroot(std::shared_ptr<SFnumber> sfn){
    if(sfn->parent != nullptr){
        return findroot(sfn->parent);
    } else {
        return sfn;
    }
}

std::shared_ptr<SFnumber> newSFpair(int sfnum){
    SFnumber sfnumber;
    sfnumber.data.first = std::floor(((double)sfnum)/2);
    sfnumber.data.second = std::ceil(((double)sfnum)/2);
    auto thisptr = std::make_shared<SFnumber>(sfnumber);
    return thisptr;
}

int split(std::shared_ptr<SFnumber> sfn){

    int exp = 0;
    bool splitright = true;
    if(sfn->first == nullptr && sfn->data.first >= 10){
        //std::cout << "split " << sfn->data.first << '\n';
        std::shared_ptr<SFnumber> f_new = newSFpair(sfn->data.first);
        f_new->type = leftnode;;
        f_new->nestlevel = sfn->nestlevel+1;
        f_new->parent = sfn;
        sfn->data.first = -1;
        sfn->first = f_new;
        std::shared_ptr<SFnumber> rootptr = findroot(sfn);
      //  std::cout << "in split before explode " << sfn_tostring(rootptr) << '\n';
        exp += find_explode(f_new);
        if(f_new->data.first >= 10 || f_new->data.second >= 10){
            splitright = false;
        }
    }
    if(exp == 0 && splitright){
        if(sfn->second == nullptr && sfn->data.second >= 10){
            //std::cout << "split " << sfn->data.second << '\n';
            std::shared_ptr<SFnumber> s_new = newSFpair(sfn->data.second);
            s_new->type = rightnode;
            s_new->nestlevel = sfn->nestlevel+1;
            s_new->parent = sfn;
            sfn->data.second = -1;
            sfn->second = s_new;

            std::shared_ptr<SFnumber> rootptr = findroot(sfn);
     //       std::cout << "in split before explode " << sfn_tostring(rootptr) << '\n';
            exp += find_explode(s_new);

        }
    }
    return exp;
}

std::shared_ptr<SFnumber> find_next_split(std::shared_ptr<SFnumber> sfn){
    int val = -1;
    Type tp;
    int exp = 0;
    std::shared_ptr<SFnumber> leftmost = left_search_val(sfn, val, tp);
    //std::cout << "leftmost: " << sfn_tostring(leftmost) << '\n';
    std::shared_ptr<SFnumber> this_ptr = leftmost;
    while(this_ptr != nullptr){
     //   std::cout << "in find next split  " << sfn_tostring(sfn) << '\n';
        if(this_ptr->data.first >= 10 || this_ptr->data.second >= 10){
             return this_ptr;
        }
        else if(this_ptr != nullptr && this_ptr->second != nullptr){

            if(this_ptr->second->data.first >= 10 || this_ptr->second->data.second >= 10){
                return this_ptr->second;
            }
        }
        int right_val = -1;
        Type r_tp;
        this_ptr = find_right(this_ptr, right_val, r_tp);

        if(this_ptr != nullptr){
    //        std::cout << "right split next: " << sfn_tostring(this_ptr) << '\n';
        }
    }
    return this_ptr;
}

int find_explode(std::shared_ptr<SFnumber> sfn) {

    int exp = 0;
    if(sfn->nestlevel == 4 && sfn->data.first != -1 && sfn->data.second != -1) {
        exp++;
        //std::cout << "\nEXPLODE " << sfn->data.first << ',' << sfn->data.second << '\n';
        std::shared_ptr<SFnumber> rootptr = findroot(sfn);
       // std::cout << "before explode " << sfn_tostring(rootptr) << '\n';
        Type left_val_tp, right_val_tp;
        int left_val = -1;
        int right_val = -1;
        std::shared_ptr<SFnumber> left_ptr = find_left(sfn, left_val, left_val_tp);
        std::shared_ptr<SFnumber> right_ptr = find_right(sfn, right_val, right_val_tp);
       // std::cout << "this left : " << sfn->data.first << '\n';
       // std::cout << "this right : " << sfn->data.second << '\n';
        //std::cout << "left : "<< left_val << '\n';
        //std::cout << "left tp : "<< left_val_tp << '\n';
        //std::cout << "right: " << right_val << '\n';
        //std::cout << "right tp: " << right_val_tp << '\n';
        if(left_ptr != nullptr) {
            int new_val = sfn->data.first + left_val;
            if(left_val_tp == leftnode) {
                left_ptr->data.first = new_val;
            } else {
                left_ptr->data.second = new_val;
            }
            if(new_val >= 10) {
                exp++;
           //     find_next_split(rootptr);
            }
        }
        if(right_ptr != nullptr) {
            int new_val = sfn->data.second + right_val;
            if(right_val_tp == rightnode) {
                right_ptr->data.second = new_val;
            } else {
                right_ptr->data.first = new_val;
            }
            if(new_val >= 10) {
                exp++;
            //    find_next_split(rootptr);
            }
        }
        if(sfn->type == leftnode){
            sfn->parent->first = nullptr;
            sfn->parent->data.first = 0;
        } else {
            sfn->parent->second = nullptr;
            sfn->parent->data.second = 0;
        }

    } else {
        if(sfn->first != nullptr){
            exp += find_explode(sfn->first);
        }
        if(sfn->second != nullptr){
            exp += find_explode(sfn->second);
        }
    }
    return exp;
}


void inc_level(std::shared_ptr<SFnumber> sfn){
    sfn->nestlevel++;
    if(sfn->first != nullptr){
        inc_level(sfn->first);
    }
    if(sfn->second != nullptr){
        inc_level(sfn->second);
    }
}


void explode_split_loop(std::shared_ptr<SFnumber> sfn){
    int exp;
    do {
     //   std::cout << "before  " << sfn_tostring(sfn) << '\n';
        exp = find_explode(sfn);
        while(find_next_split(sfn) != nullptr){
            split(find_next_split(sfn));
        }
    //    std::cout << "after explode  " << sfn_tostring(sfn) << '\n';
    } while(exp != 0);
   // std::cout << "final  " << sfn_tostring(sfn) << '\n';
}

std::shared_ptr<SFnumber> add(std::shared_ptr<SFnumber> left, std::shared_ptr<SFnumber> right){
    SFnumber sfnumber;
    sfnumber.data.first = -1;
    sfnumber.data.second = -1;
    sfnumber.nestlevel=-1;
    sfnumber.first = left;
    sfnumber.second = right;
    sfnumber.first->type = leftnode;
    sfnumber.second->type = rightnode;
    auto thisptr = std::make_shared<SFnumber>(sfnumber);
    sfnumber.first->parent = thisptr;
    sfnumber.second->parent = thisptr;
    inc_level(thisptr);
    explode_split_loop(thisptr);
    return thisptr;
}

int sf_sum(std::shared_ptr<SFnumber> sfn){
    int left_sum, right_sum;
    if(sfn->data.first != -1){
        left_sum = sfn->data.first;
    } else {
        left_sum = sf_sum(sfn->first);
    }
    if(sfn->data.second != -1){
        right_sum = sfn->data.second;
    } else {
        right_sum = sf_sum(sfn->second);
    }
    return (3*left_sum + 2*right_sum);
}

std::shared_ptr<SFnumber> parseSFstr(std::string& s, int nlvl){
    std::string str = s.substr(s.find_first_of("[")+1,s.find_last_of("]")-1);
    std::string left, right;
    int opened = 0;
    for(int i = 0; i < str.size(); ++i){
        char ch = str[i];
        if(ch == '['){
            opened++;
        } else if (ch == ']'){
            opened--;
        } else if (ch == ','){
            if(opened == 0){
                left = str.substr(0,i);
                right = str.substr(i+1, str.npos);
                break;
            }
        }
    }
    std::shared_ptr<SFnumber> sfnumber = std::make_shared<SFnumber>();
    sfnumber->data.first = -1;
    sfnumber->data.second = -1;
    sfnumber->nestlevel=nlvl;
    if(left.find("[") == left.npos){
        sfnumber->data.first = stoi(left);
    } else {
        std::shared_ptr<SFnumber> new_num = parseSFstr(left, nlvl+1);
        new_num->parent = sfnumber;
        new_num->type = leftnode;
        sfnumber->first = new_num;
    }
    if(right.find("[") == right.npos){
        sfnumber->data.second = stoi(right);
    } else {
        std::shared_ptr<SFnumber> new_num = parseSFstr(right, nlvl+1);
        new_num->parent = sfnumber;
        new_num->type = rightnode;
        sfnumber->second = new_num;
    }

    return sfnumber;
}

int main()
{
    int lastbuffernull = 0;
    std::vector<std::shared_ptr<SFnumber>> sfnumbers;
    std::vector<std::string> sfn_strings;

    while(lastbuffernull < 2){
        std::string s;
        std::getline(std::cin,s);
        if(s.size() != 0){
            std::shared_ptr<SFnumber> sfroot = parseSFstr(s,0);
            sfn_strings.push_back(s);
            sfnumbers.push_back(sfroot);
        } else {
            lastbuffernull++;
        }
    }

    //pt1
    std::shared_ptr<SFnumber> added = std::accumulate(sfnumbers.begin()+1, sfnumbers.end(), *sfnumbers.begin(), add);
    int sum = sf_sum(added);

    //pt2
    int max_sum = 0;
    for(int i = 0; i < sfn_strings.size(); ++i){
        for(int j = 0; j < sfn_strings.size(); ++j){
            if(j == i){ continue; }
            std::shared_ptr<SFnumber> fn = parseSFstr(sfn_strings[i],0);
            std::shared_ptr<SFnumber> sn = parseSFstr(sfn_strings[j],0);
           // std::cout << "adding " << sfn_tostring(fn) << "   to   " << sfn_tostring(sn) << '\n';
            std::shared_ptr<SFnumber> result = add(fn,sn);
            int this_sum = sf_sum(result);
           // std::cout << this_sum << '\n';
            if(this_sum > max_sum){
                max_sum = this_sum;
            }
        }
    }
    std::cout << added->nestlevel << '\n';
    std::cout << "magnitude of the final sum : " << sum << '\n';
    std::cout << "largest magnitude: " << max_sum << '\n';

    return 0;
}