#include "pch.h"
#include "ModelTempTabel.h"

// shop_model_comming.png
ModelTempTableList g_MaximModelListTable = ModelTempTableList(
    {       // 가격의 1은 공개, 0은 미공개
        { ModelTempTable(0, L"김소희", 1, L"더 보기", "Maxim_01_001.jpg") },
        { ModelTempTable(1, L"김나정", 0, L"곧 만나요!", "Maxim_02_001.jpg") },
        { ModelTempTable(2, L"엄상미", 0, L"곧 만나요!", "Maxim_03_001.jpg") },
    });

ModelTempTable FindMaximModelListTable(int id)
{
    for (ModelTempTableList::iterator it = g_MaximModelListTable.begin(); it != g_MaximModelListTable.end(); ++it)
    {
        if (it->id == id)
            return *it;
    }
    return ModelTempTable();
}


ModelTempTableList g_ModelTempTable = ModelTempTableList(
{ 
    { ModelTempTable(0, L"김소희1", 500000000000, L"0.5조 골드", "Maxim_01_001.jpg") },
    { ModelTempTable(1, L"김소희2", 500000000000, L"0.5조 골드", "Maxim_01_002.jpg") },
    { ModelTempTable(2, L"김소희3", 500000000000, L"0.5조 골드", "Maxim_01_003.jpg") },
    { ModelTempTable(3, L"김소희4", 500000000000, L"0.5조 골드", "Maxim_01_004.jpg") },
    { ModelTempTable(4, L"김소희5", 500000000000, L"0.5조 골드", "Maxim_01_005.jpg") },
    { ModelTempTable(5, L"김소희6", 500000000000, L"0.5조 골드", "Maxim_01_006.jpg") },
    { ModelTempTable(6, L"김소희7", 500000000000, L"0.5조 골드", "Maxim_01_007.jpg") },
    { ModelTempTable(7, L"김소희8", 500000000000, L"0.5조 골드", "Maxim_01_008.jpg") },
    { ModelTempTable(8, L"김소희9", 500000000000, L"0.5조 골드", "Maxim_01_009.jpg") },
    { ModelTempTable(9, L"김소희10", 500000000000, L"0.5조 골드", "Maxim_01_010.jpg") },
    { ModelTempTable(10, L"김소희11", 500000000000, L"0.5조 골드", "Maxim_01_011.jpg") },
    { ModelTempTable(11, L"김소희12", 500000000000, L"0.5조 골드", "Maxim_01_012.jpg") },
    { ModelTempTable(12, L"김소희13", 500000000000, L"0.5조 골드", "Maxim_01_013.jpg") },
    { ModelTempTable(13, L"김소희14", 500000000000, L"0.5조 골드", "Maxim_01_014.jpg") },
    { ModelTempTable(14, L"김소희15", 500000000000, L"0.5조 골드", "Maxim_01_015.jpg") },
    { ModelTempTable(15, L"김소희16", 500000000000, L"0.5조 골드", "Maxim_01_016.jpg") },
    { ModelTempTable(16, L"김소희17", 500000000000, L"0.5조 골드", "Maxim_01_017.jpg") },
    { ModelTempTable(17, L"김소희18", 500000000000, L"0.5조 골드", "Maxim_01_018.jpg") },
    { ModelTempTable(18, L"김소희19", 500000000000, L"0.5조 골드", "Maxim_01_019.jpg") },
    { ModelTempTable(19, L"김소희20", 500000000000, L"0.5조 골드", "Maxim_01_020.jpg") },
    { ModelTempTable(20, L"김소희21", 500000000000, L"0.5조 골드", "Maxim_01_021.jpg") },
    { ModelTempTable(21, L"김소희22", 500000000000, L"0.5조 골드", "Maxim_01_022.jpg") },
    { ModelTempTable(22, L"김소희23", 500000000000, L"0.5조 골드", "Maxim_01_023.jpg") },
    { ModelTempTable(23, L"김소희24", 500000000000, L"0.5조 골드", "Maxim_01_024.jpg") },
    { ModelTempTable(24, L"김소희25", 500000000000, L"0.5조 골드", "Maxim_01_025.jpg") },
    { ModelTempTable(25, L"김소희26", 500000000000, L"0.5조 골드", "Maxim_01_026.jpg") },
    { ModelTempTable(26, L"김소희27", 500000000000, L"0.5조 골드", "Maxim_01_027.jpg") },
    { ModelTempTable(27, L"김소희28", 500000000000, L"0.5조 골드", "Maxim_01_028.jpg") },
    { ModelTempTable(28, L"김소희29", 500000000000, L"0.5조 골드", "Maxim_01_029.jpg") },
    { ModelTempTable(29, L"김소희30", 500000000000, L"0.5조 골드", "Maxim_01_030.jpg") },
    { ModelTempTable(30, L"김소희31", 500000000000, L"0.5조 골드", "Maxim_01_031.jpg") },
    { ModelTempTable(31, L"김소희32", 500000000000, L"0.5조 골드", "Maxim_01_032.jpg") },
    { ModelTempTable(32, L"김소희33", 500000000000, L"0.5조 골드", "Maxim_01_033.jpg") },
    { ModelTempTable(33, L"김소희34", 500000000000, L"0.5조 골드", "Maxim_01_034.jpg") },
    { ModelTempTable(34, L"김소희35", 500000000000, L"0.5조 골드", "Maxim_01_035.jpg") },
    { ModelTempTable(35, L"김소희36", 500000000000, L"0.5조 골드", "Maxim_01_036.jpg") },
    { ModelTempTable(36, L"김소희37", 500000000000, L"0.5조 골드", "Maxim_01_037.jpg") },
    { ModelTempTable(37, L"김소희38", 500000000000, L"0.5조 골드", "Maxim_01_038.jpg") },
    { ModelTempTable(38, L"김소희39", 500000000000, L"0.5조 골드", "Maxim_01_039.jpg") },
    { ModelTempTable(39, L"김소희40", 500000000000, L"0.5조 골드", "Maxim_01_040.jpg") },
    { ModelTempTable(40, L"김소희41", 500000000000, L"0.5조 골드", "Maxim_01_041.jpg") },
    { ModelTempTable(41, L"김소희42", 500000000000, L"0.5조 골드", "Maxim_01_042.jpg") },
    { ModelTempTable(42, L"김소희43", 500000000000, L"0.5조 골드", "Maxim_01_043.jpg") },
    { ModelTempTable(43, L"김소희44", 500000000000, L"0.5조 골드", "Maxim_01_044.jpg") },
    { ModelTempTable(44, L"김소희45", 500000000000, L"0.5조 골드", "Maxim_01_045.jpg") },
    { ModelTempTable(45, L"김소희46", 500000000000, L"0.5조 골드", "Maxim_01_046.jpg") },
    { ModelTempTable(46, L"김소희47", 500000000000, L"0.5조 골드", "Maxim_01_047.jpg") },
    { ModelTempTable(47, L"김소희48", 500000000000, L"0.5조 골드", "Maxim_01_048.jpg") },
    { ModelTempTable(48, L"김소희49", 500000000000, L"0.5조 골드", "Maxim_01_049.jpg") },
    { ModelTempTable(49, L"김소희50", 500000000000, L"0.5조 골드", "Maxim_01_050.jpg") },
    { ModelTempTable(50, L"김소희51", 500000000000, L"0.5조 골드", "Maxim_01_051.jpg") },
    { ModelTempTable(51, L"김소희52", 500000000000, L"0.5조 골드", "Maxim_01_052.jpg") },
    { ModelTempTable(52, L"김소희53", 500000000000, L"0.5조 골드", "Maxim_01_053.jpg") },
    { ModelTempTable(53, L"김소희54", 500000000000, L"0.5조 골드", "Maxim_01_054.jpg") },
    { ModelTempTable(54, L"김소희55", 500000000000, L"0.5조 골드", "Maxim_01_055.jpg") },
    { ModelTempTable(55, L"김소희56", 500000000000, L"0.5조 골드", "Maxim_01_056.jpg") },
    { ModelTempTable(56, L"김소희57", 500000000000, L"0.5조 골드", "Maxim_01_057.jpg") },
    { ModelTempTable(57, L"김소희58", 500000000000, L"0.5조 골드", "Maxim_01_058.jpg") },
    { ModelTempTable(58, L"김소희59", 500000000000, L"0.5조 골드", "Maxim_01_059.jpg") },
    { ModelTempTable(59, L"김소희60", 500000000000, L"0.5조 골드", "Maxim_01_060.jpg") },
});

const uint64 SlotExNeedGold = 300000000000;

ModelTempTable FindModelTable(int id)
{
    for (ModelTempTableList::iterator it = g_ModelTempTable.begin(); it != g_ModelTempTable.end(); ++it)
    {
        if (it->id == id)
            return *it;
    }
    return ModelTempTable();
}

//vector<vector<int> > arr({
//
//    vector<int>({ 0, 1, 2 }),
//
//    vector<int>({ 3, 7, 9, 11 }),
//
//    vector<int>({ 4, 10, 14, 15 }),
//
//    vector<int>({ 0, 4, 5, 6, 7 }),
//
//    vector<int>({ 6, 7, 8, 10, 12 }),
//
//    vector<int>({ 0, 2, 14, 15 }),
//
//    vector<int>({ 3, 14, 15 }),
//
//    vector<int>({ 4, 5, 7, 14, 15 }),
//
//    vector<int>({ 1, 2, 3, 4, 5 }),
//
//    vector<int>({ 3, 4, 5, 9, 13 })
//
//    });

ModelSubTempTableArr g_ModelSubTempTableArr = ModelSubTempTableArr(
{
    { ModelTempTable(0, L"김소희1", 500000000000, L"0.5조 골드", "Maxim_01_001.jpg") ,
      ModelTempTable(1, L"김소희2", 500000000000, L"0.5조 골드", "Maxim_01_002.jpg") ,
      ModelTempTable(2, L"김소희3", 500000000000, L"0.5조 골드", "Maxim_01_003.jpg") ,
      ModelTempTable(3, L"김소희4", 500000000000, L"0.5조 골드", "Maxim_01_004.jpg") ,
      ModelTempTable(4, L"김소희5", 500000000000, L"0.5조 골드", "Maxim_01_005.jpg") ,
      ModelTempTable(5, L"김소희6", 500000000000, L"0.5조 골드", "Maxim_01_006.jpg") ,
      ModelTempTable(6, L"김소희7", 500000000000, L"0.5조 골드", "Maxim_01_007.jpg") ,
      ModelTempTable(7, L"김소희8", 500000000000, L"0.5조 골드", "Maxim_01_008.jpg") ,
      ModelTempTable(8, L"김소희9", 500000000000, L"0.5조 골드", "Maxim_01_009.jpg") ,
      ModelTempTable(9, L"김소희10", 500000000000, L"0.5조 골드", "Maxim_01_010.jpg") ,
      ModelTempTable(10, L"김소희11", 500000000000, L"0.5조 골드", "Maxim_01_011.jpg") ,
      ModelTempTable(11, L"김소희12", 500000000000, L"0.5조 골드", "Maxim_01_012.jpg") ,
      ModelTempTable(12, L"김소희13", 500000000000, L"0.5조 골드", "Maxim_01_013.jpg") ,
      ModelTempTable(13, L"김소희14", 500000000000, L"0.5조 골드", "Maxim_01_014.jpg") ,
      ModelTempTable(14, L"김소희15", 500000000000, L"0.5조 골드", "Maxim_01_015.jpg") ,
      ModelTempTable(15, L"김소희16", 500000000000, L"0.5조 골드", "Maxim_01_016.jpg") ,
      ModelTempTable(16, L"김소희17", 500000000000, L"0.5조 골드", "Maxim_01_017.jpg") ,
      ModelTempTable(17, L"김소희18", 500000000000, L"0.5조 골드", "Maxim_01_018.jpg") ,
      ModelTempTable(18, L"김소희19", 500000000000, L"0.5조 골드", "Maxim_01_019.jpg") ,
      ModelTempTable(19, L"김소희20", 500000000000, L"0.5조 골드", "Maxim_01_020.jpg") ,
      ModelTempTable(20, L"김소희21", 500000000000, L"0.5조 골드", "Maxim_01_021.jpg") ,
      ModelTempTable(21, L"김소희22", 500000000000, L"0.5조 골드", "Maxim_01_022.jpg") ,
      ModelTempTable(22, L"김소희23", 500000000000, L"0.5조 골드", "Maxim_01_023.jpg") ,
      ModelTempTable(23, L"김소희24", 500000000000, L"0.5조 골드", "Maxim_01_024.jpg") ,
      ModelTempTable(24, L"김소희25", 500000000000, L"0.5조 골드", "Maxim_01_025.jpg") ,
      ModelTempTable(25, L"김소희26", 500000000000, L"0.5조 골드", "Maxim_01_026.jpg") ,
      ModelTempTable(26, L"김소희27", 500000000000, L"0.5조 골드", "Maxim_01_027.jpg") ,
      ModelTempTable(27, L"김소희28", 500000000000, L"0.5조 골드", "Maxim_01_028.jpg") ,
      ModelTempTable(28, L"김소희29", 500000000000, L"0.5조 골드", "Maxim_01_029.jpg") ,
      ModelTempTable(29, L"김소희30", 500000000000, L"0.5조 골드", "Maxim_01_030.jpg") ,
      ModelTempTable(30, L"김소희31", 500000000000, L"0.5조 골드", "Maxim_01_031.jpg") ,
      ModelTempTable(31, L"김소희32", 500000000000, L"0.5조 골드", "Maxim_01_032.jpg") ,
      ModelTempTable(32, L"김소희33", 500000000000, L"0.5조 골드", "Maxim_01_033.jpg") ,
      ModelTempTable(33, L"김소희34", 500000000000, L"0.5조 골드", "Maxim_01_034.jpg") ,
      ModelTempTable(34, L"김소희35", 500000000000, L"0.5조 골드", "Maxim_01_035.jpg") ,
      ModelTempTable(35, L"김소희36", 500000000000, L"0.5조 골드", "Maxim_01_036.jpg") ,
      ModelTempTable(36, L"김소희37", 500000000000, L"0.5조 골드", "Maxim_01_037.jpg") ,
      ModelTempTable(37, L"김소희38", 500000000000, L"0.5조 골드", "Maxim_01_038.jpg") ,
      ModelTempTable(38, L"김소희39", 500000000000, L"0.5조 골드", "Maxim_01_039.jpg") ,
      ModelTempTable(39, L"김소희40", 500000000000, L"0.5조 골드", "Maxim_01_040.jpg") ,
      ModelTempTable(40, L"김소희41", 500000000000, L"0.5조 골드", "Maxim_01_041.jpg") ,
      ModelTempTable(41, L"김소희42", 500000000000, L"0.5조 골드", "Maxim_01_042.jpg") ,
      ModelTempTable(42, L"김소희43", 500000000000, L"0.5조 골드", "Maxim_01_043.jpg") ,
      ModelTempTable(43, L"김소희44", 500000000000, L"0.5조 골드", "Maxim_01_044.jpg") ,
      ModelTempTable(44, L"김소희45", 500000000000, L"0.5조 골드", "Maxim_01_045.jpg") ,
      ModelTempTable(45, L"김소희46", 500000000000, L"0.5조 골드", "Maxim_01_046.jpg") ,
      ModelTempTable(46, L"김소희47", 500000000000, L"0.5조 골드", "Maxim_01_047.jpg") ,
      ModelTempTable(47, L"김소희48", 500000000000, L"0.5조 골드", "Maxim_01_048.jpg") ,
      ModelTempTable(48, L"김소희49", 500000000000, L"0.5조 골드", "Maxim_01_049.jpg") ,
      ModelTempTable(49, L"김소희50", 500000000000, L"0.5조 골드", "Maxim_01_050.jpg") ,
      ModelTempTable(50, L"김소희51", 500000000000, L"0.5조 골드", "Maxim_01_051.jpg") ,
      ModelTempTable(51, L"김소희52", 500000000000, L"0.5조 골드", "Maxim_01_052.jpg") ,
      ModelTempTable(52, L"김소희53", 500000000000, L"0.5조 골드", "Maxim_01_053.jpg") ,
      ModelTempTable(53, L"김소희54", 500000000000, L"0.5조 골드", "Maxim_01_054.jpg") ,
      ModelTempTable(54, L"김소희55", 500000000000, L"0.5조 골드", "Maxim_01_055.jpg") ,
      ModelTempTable(55, L"김소희56", 500000000000, L"0.5조 골드", "Maxim_01_056.jpg") ,
      ModelTempTable(56, L"김소희57", 500000000000, L"0.5조 골드", "Maxim_01_057.jpg") ,
      ModelTempTable(57, L"김소희58", 500000000000, L"0.5조 골드", "Maxim_01_058.jpg") ,
      ModelTempTable(58, L"김소희59", 500000000000, L"0.5조 골드", "Maxim_01_059.jpg") ,
      ModelTempTable(59, L"김소희60", 500000000000, L"0.5조 골드", "Maxim_01_060.jpg") },
    { ModelTempTable(0, L"김나정1", 500000000000, L"0.5조 골드", "Maxim_02_001.jpg") },
    { ModelTempTable(0, L"엄상미1", 500000000000, L"0.5조 골드", "Maxim_03_001.jpg") }
});

ModelTempTable FindModelSubTable(int idx, int subIdx)
{

    if (idx < g_ModelSubTempTableArr.size())
    {
        if (subIdx < g_ModelSubTempTableArr[idx].size())
        {
            return g_ModelSubTempTableArr[idx][subIdx];
        }
    }
    
    //for (int i = 0; i < g_ModelSubTempTableArr.size(); i++)
    //{
    //    for (int j = 0; j < g_ModelSubTempTableArr[i].size(); j++)
    //    {
    //        if(g_ModelSubTempTableArr[i][j].id = 
    //        return g_ModelSubTempTableArr[i][j];
    //        //cout << g_ModelSubTempTableArr[i][j] << " ";
    //    }
    //    //cout << endl;
    //}
    
    return ModelTempTable();
}