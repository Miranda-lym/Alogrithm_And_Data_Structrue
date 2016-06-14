#include <iostream>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
using namespace std;

typedef string keyType; //����
typedef int valueType; //��Ƶ
typedef map<keyType, valueType> MapType; //�@����Խ�unordered_map��Ϊmap����
//���������ʹ�õıȽϺ���,����֤����Ƶ����
template<typename T1, typename T2>
int cmp(const pair<T1, T2>& x, const pair<T1, T2>& y)
{
    return x.second > y.second;
}
//��map��ֵ����
template<typename T1, typename T2>
void sortMapByValue(const MapType& tMap, vector<pair<T1, T2> >& tVector)
{
    tVector.reserve(tMap.size()); //��ap�е����ݸ��Ƶ�vector�в�����
    for (auto &elem : tMap)
        tVector.push_back(make_pair(elem.first, elem.second));
    sort(tVector.begin(), tVector.end(), cmp<T1, T2>);
}

int main(int argc, char* argv[])
{
    MapType wordCount;
    keyType tmpKey;
    ifstream fileIn;
    if (argc > 1) //����Ǵ������д�,�������˲���,����������еĲ���
        fileIn.open(argv[1]);
    else  //����ֱ�Ӵ��ļ���ȡ����
        fileIn.open("../res/wordsList");
    int t_start = clock();
    while (fileIn >> tmpKey) //���϶�ȡһ��key,����wordCount
        ++wordCount[tmpKey];
    fileIn.close();
    cout << wordCount.size() << "�����ʱ�����map�к�ʱ: " << clock() - t_start
         << "ms" << endl;
    vector<pair<keyType, valueType> > sortVec;
    sortMapByValue(wordCount, sortVec);
    cout << "�����ʱ" << clock() - t_start << "ms\n" << endl << "top 20��\n";
    for (int i = 0; i < 20; ++i)
        cout << sortVec[i].first << " \t" << sortVec[i].second << endl;
    cin.get();
    return 0;
}
