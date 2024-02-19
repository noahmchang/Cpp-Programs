#include <iostream>
#include <stdio.h>
#include <vector>

std::vector<int> mat_mult(std::vector<int> matrixa, std::vector<int> matrixb, int dimensions){
    std::vector<int> matrixc(dimensions*(dimensions+1)/2, 0);
    //int indexa;
    //int indexb;
    int indexc=0;
    for(int i=0; i<dimensions; i++){ //row
        for(int j=i; j<dimensions; j++){ //col
        int sum=0;
            for(int k=i; k<=j; k++){ //col of matrix b
                // indexa = i * dimensions - (i*(i+1)) / 2 + j;
                // indexb = j * dimensions - (j*(k+1)) / 2 + k;
                // indexc = i * dimensions - (i*(i+1)) / 2 + k;
                sum += matrixa[i*(2*dimensions-i-1)/2 + k] * matrixb[k*(2*dimensions-k-1)/2 + j];
            }
            matrixc[indexc] = sum;
            indexc++;
        }
    }
    return matrixc;
}

int main(int argc, char** argv){
    FILE* fpa = fopen(argv[1], "r");
    FILE* fpb = fopen(argv[2], "r");
    std::vector<int> matrixa;
    std::vector<int> matrixb;
    std::vector<int> matrixc;
    int dimensions;
    fscanf(fpa, "%d", &dimensions);
    fscanf(fpb, "%d", &dimensions);
    int temp;
    while(!feof(fpa)){
        fscanf(fpa, "%d", &temp);
        matrixa.push_back(temp);
        fscanf(fpb, "%d", &temp);
        matrixb.push_back(temp);
    }
    if(dimensions == 1){ // 1x1 base case
        std::cout << (matrixa[0] * matrixb[0]) << std::endl;
        return 0;
    }
    matrixc = mat_mult(matrixa, matrixb, dimensions);

    for(unsigned int i=0; i<matrixc.size(); i++){
        std::cout << matrixc[i] << " ";
    }

    fclose(fpa);
    fclose(fpb);
    return 0;
}