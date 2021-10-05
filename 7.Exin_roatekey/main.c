/*-----------------------------------------------------------------------------------------------------
【平    台】CCS
【适 用 单 片 机】msp432P401R
【底 层 库】TIVA WARE /msp432p4xx
【开 发】e芯工作室
/*@@ 库仅供参考 后果自负
 *
 * 版本 v1.0
 * 时间 2020年10月23日22:29:47
-------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------
旋转拨码开关测试例程
    中间按键 3.7;
    A相 4.6;//A相
    B相 3.5//B相
-------------------------------------------------------------------------------------------------------*/
#include "exinlibs\headfile.h"

void main()
{
    system_init(0);
    set_DCO_48MH();
    Rotate_adjust_TEST();
    while(1);
}
