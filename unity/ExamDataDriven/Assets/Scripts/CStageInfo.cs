using System;
using System.Collections.Generic;

[Serializable]
public class CStageInfo
{
    public int id;
    public int total_enemy_count;
    public List<CUnitInfo> unit_info;
}
