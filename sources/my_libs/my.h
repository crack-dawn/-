#ifndef my_H
#define MY_H


#include "maths.h"
#include "worldmodel.h"
#include "PlayerTask.h"


/*
1. ��������˳��� �Ƕ�����ϵ �� atanf2 , ��-PI, PI],
2. X��������Ϊ �е�->�Է����ŵ�λ�ã� ˳ʱ��ת�� 90�㣬Ϊy��������
*/


/* �Զ��庯�� */

float my_limite(float x, float max, float min);//�޶���С��ֵ

float atan2fCorrect(float dir);//atan2f ��ԽPI �� -PI  ʱ���¸���




float DIR(float d);/*atan2f  �Ƕ� ת��Ϊ ��0 �� 2 PI�� �Ƕ�*/

//DIR֮ǰ�Ƕ�
//---�Է�����-----
//       |
//       |
//       0
//       |
//       |
//(-90)--|---(90)-
//       |
//       |
//      180
//       |
//    �ҷ�����

/*---�Է�����-----
//       |
//       |
//       0
//       |
//       |
/(270)---|-----90
//       |
//       |
//       180
//       |
//    �ҷ�����     */





int GetReceverID(const WorldModel *model, int robot_id);/*��ȡ�ҷ������Ա ID*/

float RunOnCircleDir(float b2r, float b2g, float DetAngle);/*��Բ�� ת��ʱ ÿ��ת��ʱ������ ����/�Ƕ� || ������  ��->��Ա�� ��->Ŀ���  ��ת����*/

float RunToCircleDir(float b2r, float b2g);/* ����Բ��ʱ Ӧ�õ���� λ�ýǶ�ֵ ||������  ��->��Ա�� ��->Ŀ���  */

float Reverse_Dir(float dir);			   // atanf2 �Ƕȷ�ת
// float SetKickPower(float dist�� param..... param... ); // ���ݾ��� �� �ۺϳ� ���ʵ� ��������

int GetOppGoalieID(const WorldModel *model, int robot_id);

const point2f GetOppGoaliePos(const WorldModel *model, int robot_id);

//��ǰʱ�� ��0 �� ��ȥ֡����5����ʾ������֡���߹��ľ���  //��������ͷ  60Hz ��ͼ
const float KickDir(point2f goalpos, point2f ballpos, point2f oppGoaliePos);


const float BallSpeed(int current, int  pastcnt);//���ܳ�֮Ϊ�ٶȣ�ֻ��˵�ǵ�λ֡�����ƶ��ľ���

const float BallMoveDir(int current, int  pastcnt); //��λ�Ƶķ���


float SetPassPower(float dist);


#endif