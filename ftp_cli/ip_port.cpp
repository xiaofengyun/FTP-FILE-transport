#include"ip_port.h"
#include <QTextCodec>

bool if_is_ip(QString str)
{
    char*  pszIPAddr;
    QByteArray byte = str.toLatin1();//必须加
    pszIPAddr=byte.data();

    if (!pszIPAddr) return false; //若pszIPAddr为空
    char IP1[100], cIP[4];
    int len = strlen(pszIPAddr);
    int i = 0, j = len - 1;
    int k, m = 0, n = 0, num = 0;
    //去除首尾空格(取出从i-1到j+1之间的字符):
    while (pszIPAddr[i++] == ' ');
    while (pszIPAddr[j--] == ' ');
    for (k = i - 1; k <= j + 1; k++)
    {
        IP1[m++] = *(pszIPAddr + k);
    }
    IP1[m] = '\0';
    char *p = IP1;
    while (*p != '\0')
    {
        if (*p == ' ' || *p<'0' || *p>'9') return false;
        cIP[n++] = *p; //保存每个子段的第一个字符，用于之后判断该子段是否为0开头

        int sum = 0;  //sum为每一子段的数值，应在0到255之间
        while (*p != '.'&&*p != '\0')
        {
            if (*p == ' ' || *p<'0' || *p>'9') return false;
            sum = sum * 10 + *p - 48;  //每一子段字符串转化为整数
            p++;
        }
        if (*p == '.') {
            if ((*(p - 1) >= '0'&&*(p - 1) <= '9') && (*(p + 1) >= '0'&&*(p + 1) <= '9'))//判断"."前后是否有数字，若无，则为无效IP，如“1.1.127.”
            num++;  //记录“.”出现的次数，不能大于3
            else
                return false;
        };

        if ((sum > 255) || (sum > 0 && cIP[0] == '0') || num>3) return false;//若子段的值>255或为0开头的非0子段或“.”的数目>3，则为无效IP
        if (*p != '\0') p++;
        n = 0;
    }
    if (num != 3) return false;
    return true;
}
bool if_is_port(QString port)//判断port是否正确
{
    if(port ==NULL )
        return false;
    int num =port.toInt();
    if(num<=0 ||num >65535)
        return false;
    return true;

}
