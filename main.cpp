#include <iostream>
#include <cstdio>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <fstream>
#include <vector>
#include <map>
#include <unordered_map>
#include <sys/time.h>
#include <chrono>

using namespace std;

//获得时间当前时间戳（毫秒级）
time_t getTimeStamp()
{
    std::chrono::time_point<std::chrono::system_clock,std::chrono::milliseconds> tp = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());//获取当前时间点
    std::time_t timestamp =  tp.time_since_epoch().count(); //计算距离1970-1-1,00:00的时间长度
    return timestamp;
}

class Solution
{
public:

    void parseInput()
    {
        //c风格FILE读文件，fscanf固定格式
        //FILE * inFile = fopen("/data/test_data.txt", "r");
        FILE * inFile = fopen("./3738/test_data.txt", "r");
        //FILE * inFile = fopen("./38252/test_data.txt", "r");
        //FILE * inFile = fopen("./58284/test_data.txt", "r");
        //FILE * inFile = fopen("./77409/test_data.txt", "r");
        //FILE * inFile = fopen("./1004812/test_data.txt", "r");
        unsigned int u, v, w;   //本端账号u，对端账号v，转账金额w
        TransferNum = 0;
        while(fscanf(inFile,"%u,%u,%u", &u, &v, &w) != EOF)
        {
            inputs.push_back(u);
            inputs.push_back(v);
            ++TransferNum;
        }
    }

    void buildAdjacencyGraph()
    {
        for (int i = 0; i < inputs.size(); i+=2)
        {
            if(AdjacencyGraph.find(inputs[i]) == AdjacencyGraph.end())
            {
                AdjacencyGraph.insert(pair<unsigned int, vector<unsigned int>>(inputs[i], vector<unsigned int>{inputs[i+1]}));
                if(AllNode.find(inputs[i]) == AllNode.end())
                {
                    AllNode.insert(pair<unsigned int, bool>(inputs[i], false));
                }
                if(AllNode.find(inputs[i+1]) == AllNode.end())
                {
                    AllNode.insert(pair<unsigned int, bool>(inputs[i+1], false));
                }
            }
            else
            {
                AdjacencyGraph.at(inputs[i]).push_back(inputs[i+1]);
                if(AllNode.find(inputs[i+1]) == AllNode.end())
                {
                    AllNode.insert(pair<unsigned int, bool>(inputs[i+1], false));
                }
            }
        }
    }

    void slove()
    {
        vector<unsigned int> path;
        for(auto iter = AdjacencyGraph.begin(); iter != AdjacencyGraph.end(); ++iter)
        {
            dfs(iter->first, iter->first, 1, path);
        }
    }

    void dfs(unsigned int head, unsigned int current, int depth, vector<unsigned int> &path)
    {
        AllNode[current] = true;
        path.push_back(current);
        if(AdjacencyGraph.find(current) != AdjacencyGraph.end())
        {
            for(unsigned int &v : AdjacencyGraph[current])
            {
                if(v == head && depth >= 3 && depth <= 7)
                {
                    result[depth].push_back(path);
                }
                if(depth < 7 && !AllNode[v] && v > head)
                {
                    dfs(head, v, depth + 1, path);
                }
            }
        }
        AllNode[current] = false;
        path.pop_back();
    }

    void save()
    {
        ofstream outFile("./projects/student/result.txt");
        //ofstream outFile("/projects/student/result.txt");
        outFile << result[3].size() + result[4].size() + result[5].size() + result[6].size() + result[7].size() << endl;
        for (int i = 3; i <= 7; ++i)
        {
            for(int j = 0; j < result[i].size(); ++j)
            {
                outFile << result[i][j][0];
                for(int k = 1; k < result[i][j].size(); ++k)
                {
                    outFile << "," << result[i][j][k];
                }
                outFile << endl;
            }
        }
    }

public:
    map<unsigned int, vector<unsigned int>> AdjacencyGraph;
    int TransferNum;
    vector<unsigned int> inputs;
    vector<vector<unsigned int>> result[8];
    unordered_map<unsigned int, bool> AllNode;
};

int main()
{
    ////时间戳
    //std::time_t timestampstart;
    //std::time_t timestampstop;

    //timestampstart = getTimeStamp();
    Solution solution;
    solution.parseInput();
    solution.buildAdjacencyGraph();
    solution.slove();
    solution.save();
    //timestampstop = getTimeStamp();
    //cout << "程序运行时间：" << timestampstop - timestampstart << endl;

    return 0;
}