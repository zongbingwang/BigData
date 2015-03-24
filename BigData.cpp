#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>
#include <map>
#define dataMax 361

using namespace std;


struct data
{
    string date;
    string minute;
    int day_of_week;
    int flowcount;
    int occupancy;
    int det_int_id;
    int link_int_id;
    int junc_int_id;
    int region_int_id;
    int hour;
    data(char* d_date,int d_day_of_week,int d_flowcount,int d_occupancy,char* d_minute,int d_det_int_id,int d_link_int_id,int d_junc_int_id,int d_region_int_id,int d_hour)
    {
        for (int i=0;i<(int)strlen(d_date);i++) date=date+d_date[i];
        for (int i=0;i<(int)strlen(d_minute);i++) minute=minute+d_minute[i];
        day_of_week=d_day_of_week;
        flowcount=d_flowcount;
        occupancy=d_occupancy;
        det_int_id=d_det_int_id;
        link_int_id=d_link_int_id;
        junc_int_id=d_junc_int_id;
        region_int_id=d_region_int_id;
        hour=d_hour;
    }
};

class BigData
{
private:
    int date_num;
    int minute_num;
    int junc_num;
    int standCap_day;
    int standCap_hour;

    map<string,int>DATE;
    map<string,int>MINUTE;
    map<int,int> DET;
    map<int,int> LINK;
    map<int,int> JUNC;
    map<int,int> REGION;

    vector<data> DATA;
    vector<int> V_DATE[dataMax];
    vector<int> V_MINUTE[dataMax];
    vector<int> V_DET[dataMax];
    vector<int> V_LINK[dataMax];
    vector<int> V_JUNC[dataMax];
    vector<int> V_REGION[dataMax];

public:
    BigData()
    {
        date_num=0;
        minute_num=0;
        junc_num=0;
    }

    void get_Data()
    {
        char date[15];
        char minute[10];
        int day_of_week;
        int flowcount;
        int occupancy;
        int det_int_id;
        int link_int_id;
        int junc_int_id;
        int region_int_id;
        int hour;

        while(scanf("%s%d%d%d%s%d%d%d%d%d",date,&day_of_week,&flowcount,&occupancy,minute,&det_int_id,&link_int_id,&junc_int_id,&region_int_id,&hour)!=EOF)
        {
            DATA.push_back(data(date,day_of_week,flowcount,occupancy,minute,det_int_id,link_int_id,junc_int_id,region_int_id,hour));
        }
    }

    void assort_Data()
    {
        for (int i=0;i<(int)DATA.size();i++)
        {
            data Value=DATA[i];
            if (DATE.find(Value.date)==DATE.end()) {DATE[Value.date]=date_num++;} V_DATE[DATE[Value.date]].push_back(i);
            if (MINUTE.find(Value.minute)==MINUTE.end()) {MINUTE[Value.minute]=minute_num++;} V_MINUTE[MINUTE[Value.minute]].push_back(i);
            if (JUNC.find(Value.junc_int_id)==JUNC.end()) {JUNC[Value.junc_int_id]=junc_num++;} V_JUNC[JUNC[Value.junc_int_id]].push_back(i);
        }
    }

    void get_Parameters()
    {
        scanf("%d%d",&standCap_day,&standCap_hour);
    }

    void count_Days()
    {
        string MAX_day_date;
        int Max_day_num=0;

        for (int i=0;i<date_num;i++)
        {
            int sum=0;
            for (int p=0;p<V_DATE[i].size();p++)
            {
                int v=V_DATE[i][p];
                if( DATA[v].occupancy>=standCap_day) sum++;
            }
            if (sum>Max_day_num)
            {
                Max_day_num=sum;
                MAX_day_date=DATA[V_DATE[i][0]].date;
            }
            if (sum>V_DATE[i].size()/3) cout<<DATA[V_DATE[i][0]].date<<endl;   //定义比例
        }
        cout<<"MAX: "<<MAX_day_date<<endl;
    }

    void count_Minutes()
    {
        string MAX_minute_date;
        int Max_minute_num=0;

        for (int i=0;i<minute_num;i++)
        {
            int sum=0;
            for (int p=0;p<V_MINUTE[i].size();p++)
            {
                int v=V_MINUTE[i][p];
                if(DATA[v].occupancy>=standCap_hour) sum++;
            }
            if (sum>Max_minute_num)
            {
                Max_minute_num=sum;
                MAX_minute_date=DATA[V_MINUTE[i][0]].minute;
            }
            if (sum>=V_MINUTE[i].size()/3) cout<<DATA[V_MINUTE[i][0]].minute<<endl;       //需要定义比例
        }
        cout<<"MAX: "<<MAX_minute_date<<endl;
    }

    void count_Junc()
    {

    }
};





int main()
{
    freopen("data1.txt","r",stdin);
    BigData Example;
    Example.get_Data();
    freopen("CON","r",stdin);

    Example.assort_Data();
    Example.get_Parameters();
    Example.count_Days();
    printf("~~~~~~~~~~~~~~~~~~~~~~\n");
    Example.count_Minutes();
    return 0;
}
