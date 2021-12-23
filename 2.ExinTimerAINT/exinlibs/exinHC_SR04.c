/*-----------------------------------------------------------------------------------------------------
��ƽ    ̨��CCS
���� �� �� Ƭ ����msp432P401R
���� �� �⡿TIVA WARE /msp432p4xx
���� ����eо������
/*@@ ������ο� ����Ը�
 *
 * �汾 v1.0
 * ʱ�� 2021��2��24��13:12:44
-------------------------------------------------------------------------------------------------------*/
#include"headfile.h"
#include"exinHC_SR04.h"
//�������ò鿴exinHC_SR04.h
void HC_SR04_init()
{
    gpio_init(TRIG_PORT,TRIG_PIN,GPO,1);
    gpio_init(ECHO_PORT,ECHO_PIN,GPI,0);//��ʼ�����ͺͽ�������
}

float HC_SR04_dis()
{
   static float distance;
   gpio_set(TRIG_PORT,TRIG_PIN,0); //���ͷ������Ų��ȴ���ʹ��ǰ�η��͵ĳ���������Ӱ�챾�β��
   delay_us(5);       // ����5us�͵�ƽ
   gpio_set(TRIG_PORT,TRIG_PIN,1);  //���߷������ŷ��ͳ�����
   delay_us(12);  // ��������12us
   gpio_set(TRIG_PORT,TRIG_PIN,0); //���ͷ�������
   while(gpio_get(ECHO_PORT,ECHO_PIN)==0);
   systic_start();//�����δ��ʱ��
   while(gpio_get(ECHO_PORT,ECHO_PIN)==1);//���ʱ150ms
   systic_end();//�رյδ��ʱ��
   distance=(float)(systic_read(us)* 17/1000.0);
   distance=(int)(distance*100)/100.0;
   return distance;
}
