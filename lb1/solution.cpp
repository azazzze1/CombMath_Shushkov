#include "solution.hpp"

Solution::Solution(const std::string& fileName){
    std::ifstream diagForm(fileName);

    std::string line;
    std::getline(diagForm, line);

    diagForm.close();

    diagYoungForm = {};

    std::stringstream ss(line);
    int h;
    while (ss >> h) {
        diagYoungForm.push_back(h);
    }

    solutionFile.open("solution.txt");

    if (!solutionFile) {
        std::cerr<<"Ошибка: файл solution.txt не был создан"<<std::endl;
    }

    std::vector<int> filled(diagYoungForm.size(), 0);
    std::vector<int> current;

    totalCells = std::accumulate(diagYoungForm.begin(), diagYoungForm.end(), 0); 

    generateYoungTables(filled, current);
}

void Solution::generateYoungTables(std::vector<int> filled, std::vector<int> current){
    if (current.size() == totalCells){
        for(int i = 0; i < current.size(); ++i){
            if (i>0) solutionFile<<" ";
            solutionFile<<current[i];
        }
        solutionFile<<"\n";
        return;
    }

    for(int i = 0; i < diagYoungForm.size(); ++i){
        if(filled[i] >= diagYoungForm[i]) continue;
        if(i>0 && filled[i-1] <= filled[i]) continue;

        int row = filled[i]++;
        current.push_back(row);

        generateYoungTables(filled, current);

        current.pop_back();
        --filled[i];
    }
}

Solution::~Solution(){
    solutionFile.close(); 
}