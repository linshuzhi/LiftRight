//
//  MapData.h
//  LeftRight
//
//  Created by LinShulong on 15/10/16.
//
//

#ifndef LeftRight_MapData_h
#define LeftRight_MapData_h
#include <string>
#include <vector>

class MapData
{
public:
    MapData(const std::string& filename);
    int getItemData(int x, int y)const;
    int getWidth()const;
    int getHeigth()const;
private:
    void init();
private:
    std::vector<int> _datas;
    std::string _filename;
    int _width;
    int _heigth;
};
#endif
