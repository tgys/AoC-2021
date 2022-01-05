//
// Created by tei on 12/20/21.
//

#include <bits/stdc++.h>

typedef std::vector<std::vector<int>> Grid;

int bin_to_dec(std::array<int,9> bin){
    int num = 0;
    for (int n = bin.size()-1; n >=0; --n){
        int pow = (bin.size()-1) - n;
        num += bin[n]*std::pow(2,pow);
    }
    return num;
}

void print_grid(Grid& grid){
    for(auto r : grid){
        for(auto c : r){
            if(c){
                std::cout << '#';
            } else {
                std::cout << '.';
            }
        }
        std::cout << '\n';
    }
}

Grid pad_image(Grid& img){
    int pad_h = img.size() + 6;
    int pad_w = img[0].size() + 6;
    Grid padded;
    for(int r = 0; r < pad_h; ++r){
        std::vector<int> prow;
        padded.push_back(prow);
        for(int c = 0; c < pad_w; ++c){
            if(r == 0 || r == 1 || r == 2 || r == pad_h-1 || r == pad_h-2 || r == pad_h-3
            || c == 0 || c == 1 || c == 2 || c == pad_w-1 || c == pad_w-2 || c == pad_w-3){
                padded[padded.size()-1].push_back(0);
            } else {
                padded[padded.size()-1].push_back(img[r-3][c-3]);
            }
        }
    }
    return padded;
}

Grid enhance(Grid& pd_img, std::vector<int>& algo, int& nlit){
    int num_lit = 0;
    int window_h = pd_img.size() - 4;
    int window_w = pd_img[0].size() - 4;
    Grid result;
    for(int i = 0; i < window_h; ++i){
        std::vector<int> row(window_w, 0);
        result.push_back(row);
    }
    int dec;

    int iter = 0;
    for(int r = 0; r < window_h; ++r){
        for(int c = 0; c < window_w; ++c){
            int center_R = r+2;
            int center_C = c+2;
            std::array<int,9> bin;
            int i = 0;
            for(int R = 0; R < 3; ++R){
                for(int C = 0; C < 3; ++C){
                    int this_r = (center_R-1) + R;
                    int this_c = (center_C-1) + C;
                    bin[i++] = pd_img[this_r][this_c];
                    std::cout << "pd img " << this_r << ',' << this_c << '\n';
                }
            }

            //std::cout << result.size() << 'x' << result[0].size() << '\n';
            //std::cout << result.size()*result[0].size() << '\n';
            //std::cout << pd_img.size() << 'x'<< pd_img[0].size() << '\n';
            //std::cout << num_lit << '\n' << "dec : " << dec << '\n';
            //std::cout << "center of padded " << center_R << ',' << center_C << '\n';
            //std::cout << iter <<'\n';
            dec = bin_to_dec(bin);
            bool is_lit = algo[dec];
            if(is_lit){
                result[r][c] = 1;
                num_lit++;
            }

            iter++;

        }
    }
    nlit = num_lit;
    print_grid(result);
    return result;
}

Grid enhance_n(int n, Grid pd_img, std::vector<int>& algo, int& num_lit){
    for(int i = 0; i < n; ++i){
        pd_img = pad_image(pd_img);
        pd_img = enhance(pd_img, algo, num_lit);
    }
    return pd_img;
}


int main()
{
    int lastbuffernull = 0;
    Grid image;
    int curr_row = 0;
    std::vector<int> algo;

    while(lastbuffernull < 2){
        std::string s;
        std::getline(std::cin,s);
        if(s.size() != 0){
            if(lastbuffernull == 0){
                for(int i = 0; i < s.size(); ++i){
                    int elem = 0;
                    if(s[i] == '#') { elem = 1; }
                    algo.push_back(elem);
                }
            } else {
                std::vector<int> row;
                image.push_back(row);
                for(int i = 0; i < s.size(); ++i){
                    int elem = 0;
                    if(s[i] == '#') { elem = 1; }
                    image[image.size()-1].push_back(elem);
                }
            }
            curr_row++;
        } else {
            curr_row = 0;
            lastbuffernull++;
        }
    }

    int num_lit = 0;
    Grid enhanced = enhance_n(2, image, algo, num_lit);
    print_grid(enhanced);
    //num_lit = 0;
    //for(int r = 1; r < enhanced.size()-1; ++r){
    //   num_lit += std::count(enhanced[r].begin()+1, enhanced[r].end()-1, 1);
    //}

    std::cout << "number of pixels lit: " << num_lit << '\n';
}