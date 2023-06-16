
#include "my.h"
/*
1. ��������˳��� �Ƕ�����ϵ �� atanf2 , ��-PI, PI],
2. X��������Ϊ �е�->�Է����ŵ�λ�ã� ˳ʱ��ת�� 90�㣬Ϊy��������
*/
/*-----------------------------------------------------------------------------------*/


const float BallSpeed(int current, int  pastcnt)//���ܳ�֮Ϊ�ٶȣ�ֻ��˵�ǵ�λ֡�����ƶ��ľ���
{
	//int cnt = pastcnt - current;
	Ball ball_;
	float speed = 0;
	const point2f &ballPos = ball_.get_pos(current); // param ��ʾ ǰparam ֡������λ�ã�0 ��ʾ��ǰʱ������λ�� �� �����ô˼���������ٶ� ������ͷ���� 30֡/�� ���� ����  
	const point2f &ballPosPast = ball_.get_pos(pastcnt);
	speed = (ballPos - ballPosPast).length();
	return speed;
}
const float BallMoveDir(int current, int  pastcnt) //��λ�Ƶķ���
{
	//int cnt = pastcnt - current;
	Ball ball_;
	float dir;
	const point2f &ballPos = ball_.get_pos(current); // param ��ʾ ǰparam ֡������λ�ã�0 ��ʾ��ǰʱ������λ�� �� �����ô˼���������ٶ� ������ͷ���� 30֡/�� ���� ����  
	const point2f &ballPosPast = ball_.get_pos(pastcnt);
	dir = (ballPos - ballPosPast).angle();
	return dir;
}


//���ݾ����  ��ò�Ҫ����35
// 100֮�� ��= 20
// 150֮�� ��= 25
// 200     ��= 30
float SetPassPower(float dist)
{
	float power = 14;
	if (dist > 100) power++;
	if (dist > 150) power++;
	if (dist > 190) power++;
	if (dist > 240) power++;

	return power;
}


// ��ȡ����������Ա ID���
int GetOppGoalieID(const WorldModel *model, int robot_id)
{
	int oppGoalieID = -100;

	oppGoalieID = model->get_opp_goalie();

	if (oppGoalieID >= 1 && oppGoalieID <= 12)
	{
		return oppGoalieID;
	}
	else
	{
		return -100; // wrong  û������Ա
	}
}
// ��ȡ����������Աλ��
const point2f GetOppGoaliePos(const WorldModel *model, int robot_id)
{
	point2f oppGoaliePos = { 300, 0 };
	int oppGoalieID = GetOppGoalieID(model, robot_id);
	if (oppGoalieID != -100)
	{
		oppGoaliePos = model->get_opp_player_pos(oppGoalieID);
	}
	return oppGoaliePos;
}


// ��ȡ���ŷ���
const float KickDir(point2f goalpos, point2f ballpos, point2f oppGoaliePos)
{
	// �������λ���ж�ƫ��
	goalpos.y = ballpos.y > 0 ? abs(goalpos.y) : -abs(goalpos.y);

	// ��������Ա�ж�ƫ��
	if (oppGoaliePos.x != 300 && oppGoaliePos.y != 0)
	{
		if (oppGoaliePos.y >= 0)
		{
			goalpos.y = -abs(goalpos.y);
		}
	}
	return DIR((goalpos - ballpos).angle()); // ���ŷ���
}

/*��ȡ�ҷ������Ա ID*/
int GetReceverID(const WorldModel *model, int robot_id){
	int  receiver_id = -100;

	for (int i = 0; i < 6; i++)
	{
		if (i == robot_id || i == model->get_our_goalie())
			continue;
		if (model->get_our_exist_id()[i])
			receiver_id = i;
	}
	return receiver_id;
}



//�޶���С��ֵ
float my_limite(float x, float max, float min)
{
	if (x - max> 0)
	{
		x = max;
	}
	else if (min - x > 0)
	{
		x = min;
	}
	return x;
}


//atan2f ��ԽPI �� -PI  ʱ���¸��£���Ϊ��-PI, PI�Ƕȡ� 
float atan2fCorrect(float dir)
{
	float result = dir;
	if (result > PI)
	{
		return (result - PI - PI);
	}
	else if (result < -PI)
	{
		return (result + PI + PI);
	}
	else
	{
		return result;
	}
}


/*atan2f  �Ƕ� ת��Ϊ ��0 �� 2 PI�� �Ƕ�*/
float DIR(float d)
{
	d = (d >= 0 ? d : (d + PI + PI));
	return d;
}

/*��Բ�� ת��ʱ ÿ��ת��ʱ������ ����/�Ƕ� */
/* ת����Ҫ�� �Ƕ� �� ��->��Ա�� ��->Ŀ���, ת���ǡ� 18��  �� 60�㡿�� 36��Ϻ�*/
float RunOnCircleDir(float b2r, float b2g, float DetAngle)
{
	//   ��Ϊ�����ӽ�
	if (DetAngle > 0.33*PI || DetAngle < 0.1*PI)
	{
		DetAngle = PI / 5;
	}
	//DetAngle= my_limite( DetAngle, 0.33*PI, 0.1*PI );

	float dir;
	if (b2r >= b2g && fabs(b2r - b2g) <= PI)
	{
		dir = b2r + DetAngle; //˳ʱ��
	}
	else if (b2r < b2g && fabs(b2r - b2g) <= PI)
	{
		dir = b2r - DetAngle; //��ʱ��
	}
	else if (b2r >= b2g && fabs(b2r - b2g) >= PI)
	{
		dir = b2r - DetAngle;
	}
	else if (b2r < b2g && fabs(b2r - b2g) > PI)
	{
		dir = b2r + DetAngle;
	}
	return dir;
}


//atanf2 �Ƕȷ�ת
float Reverse_Dir(float dir)
{
	if (dir >= 0)
	{
		dir -= PI;
	}
	else
	{
		dir += PI;
	}
	return dir;
}


/* ����Բ��ʱ Ӧ�õ���� λ�ýǶ�ֵ */
/* ת����Ҫ�� �Ƕ� �� ��->��Ա�� ��->Ŀ���*/
float RunToCircleDir(float b2r, float b2g)
{
	//   ��Ϊ�����ӽ�
	//����Ҫ���� ֱ���ܹ�ȥ
	if (fabs(b2r - b2g) >= 0.60*PI && fabs(b2r - b2g) <= 1.40 * PI)
	{
		return b2r;
	}

	//��Ҫ��                                      
	if (b2r > b2g && fabs(b2r - b2g) < 0.60 * PI)//
	{
		return b2g + PI - 0.4*PI;
	}
	else if (b2r < b2g && fabs(b2r - b2g) < 0.60 * PI)
	{
		return b2g + PI + 0.4*PI;
	}

	else if (b2r > b2g && fabs(b2r - b2g) > 1.40 * PI)//
	{
		return b2g + PI + 0.4*PI;
	}
	else if (b2r < b2g && fabs(b2r - b2g) > 1.40 * PI)
	{
		return b2g + PI - 0.4*PI;
	}

	else {
		return b2r;
	}

}
 
