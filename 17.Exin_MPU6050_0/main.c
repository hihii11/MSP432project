/*-----------------------------------------------------------------------------------------------------
��ƽ    ̨��CCS
���� �� �� Ƭ ����msp432P401R
���� �� �⡿TIVA WARE /msp432p4xx
���� ����eо������
/*@@ ������ο� ����Ը�
 *
 * �汾 v1.0
 * ʱ�� 2021��10��5��15:13:36
-------------------------------------------------------------------------------------------------------*/


/************************************************************************************
 *
 * ע�����������ΪMPU6050��������
 *           MPU6050 AD0���Žӵ� ������ַΪ0x68
 *           ��MPU6050ͨ�Ŵ���ʱ������P1.0LED(�����)����˸������IIC������������ַ����û���⣬��ϵ�����
 *           ��������ȫ���μ��ٶȼƣ����ݼ��ٶ�ֱ�ӵó����
 *************************************************************************************/



#include "exinlibs\headfile.h"


short MPU_ID,temp,gx,gy,gz,ax,ay,az;
float roll,yaw,pitch;
uint8 MPU_txt[50]={};//������ʾ
int8 Page=0;//��ǰҳ


void OLED_MPU_SHOW()
{
    if(Page % 3 == 0)
    {
        OLED_Show_String(11,1,"MPU_6050:Gyro  ",8);

        OLED_Show_String(0,2,"Gyrox:",8);
        sprintf(MPU_txt,"%d    ",gx);
        OLED_Show_String(41,2,MPU_txt,8);//��ʾx��Ǽ��ٶ�

        OLED_Show_String(0,3,"Gyroy:",8);
        sprintf(MPU_txt,"%d    ",gy);
        OLED_Show_String(41,3,MPU_txt,8);//��ʾy��Ǽ��ٶ�


        OLED_Show_String(0,4,"Gytoz:",8);
        sprintf(MPU_txt,"%d    ",gz);
        OLED_Show_String(41,4,MPU_txt,8);//��ʾz��Ǽ��ٶ�


        OLED_Show_String(0,5,"temp:",8);
        OLED_Show_float(41,5,((float)temp/100),2,8);//������ǰ�¶�ֵ
    }
    else if(Page % 3 == 1)
    {
        OLED_Show_String(11,1,"MPU_6050:Acc  ",8);

        OLED_Show_String(0,2,"Accx:",8);
        sprintf(MPU_txt,"%d    ",ax);
        OLED_Show_String(41,2,MPU_txt,8);//��ʾx����ٶ�

        OLED_Show_String(0,3,"Accy:",8);
        sprintf(MPU_txt,"%d    ",ay);
        OLED_Show_String(41,3,MPU_txt,8);//��ʾy����ٶ�


        OLED_Show_String(0,4,"Accz:",8);
        sprintf(MPU_txt,"%d    ",az);
        OLED_Show_String(41,4,MPU_txt,8);//��ʾz����ٶ�


        OLED_Show_String(0,5,"temp:",8);
        OLED_Show_float(41,5,((float)temp/100),2,8);//������ǰ�¶�ֵ
    }
    else
    {
        OLED_Show_String(11,1,"MPU_6050:Angle  ",8);

        OLED_Show_String(0,2,"Pitch:",8);
        sprintf(MPU_txt,"%.2f    ",pitch);
        OLED_Show_String(41,2,MPU_txt,8);//��ʾx����ٶ�

        OLED_Show_String(0,3,"Roll:",8);
        sprintf(MPU_txt,"%.2f    ",roll);
        OLED_Show_String(41,3,MPU_txt,8);//��ʾy����ٶ�


        OLED_Show_String(0,4,"Yaw:",8);
        sprintf(MPU_txt,"%.2f    ",yaw);
        OLED_Show_String(41,4,MPU_txt,8);//��ʾz����ٶ�


        OLED_Show_String(0,5,"temp:",8);
        OLED_Show_float(41,5,((float)temp/100),2,8);//������ǰ�¶�ֵ
    }
    if(!key_get(KEY1))
    {
        delay_ms(10);
        Page--;
        OLED_clr();//����
        if(Page == -1)
            Page=3;
        while(!key_get(KEY1));
    }
    if(!key_get(KEY2))
    {
        delay_ms(10);
        Page++;
        OLED_clr();//����
        if(Page == 3)
            Page=0;
        while(!key_get(KEY2));
    }
}

void main()
{
    system_init(1);//��ʼ���δ��ʱ��
    set_DCO_48MH();
    gpio_init(GPIO_PORT_P1,GPIO_PIN0,GPO,0);//��ʼ��LED  IO��
    OLED_init();//OLED��ʼ��
    OLED_clr();//����
    MPU_init();//MPU6050�Ĵ�����ʼ��
    key_init(KEY1|KEY2);//��ʼ������S1��S2���ڷ�ҳ

    while(1)
    {
        temp= MPU_Get_Temp();                     //��ȡ�������¶�
        MPU_Get_Gyro(&gx,&gy,&gz);                //��ȡ������ԭʼ����
        MPU_Get_Acc(&ax,&ay,&az);                 //��ȡԭʼ���ٶ�����
        MPU_Get_Angel(ax,ay,az,&roll,&pitch,&yaw);//ͨ�����ٶȻ���Ƕ�����
        OLED_MPU_SHOW();
    }
}
