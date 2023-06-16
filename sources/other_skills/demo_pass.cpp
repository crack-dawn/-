#include "my.h"

#pragma comment(lib, "worldmodel_lib.lib")

//�û�ע�⣻�ӿ���Ҫ��������
extern "C" _declspec(dllexport) PlayerTask player_plan(const WorldModel *model, int robot_id); //��ɫ����Ϊ�������� player_plan

// ���� 
PlayerTask player_plan(const WorldModel *model, int robot_id)
{
	PlayerTask task;

	
	const point2f &ball = model->get_ball_pos(); //��������
	point2f goal; 		//Ŀ�������  ������ ���� Ҳ������ ĳ����Ա�� ���Ǵ���������Ҫ ������
	int my_kick_power; //��������
	int receiver_id = GetReceverID(model, robot_id);
	const point2f receiverPos = model->get_our_player_pos(receiver_id); //�����Ա ����

	goal = receiverPos;
	const float toGoalDir = DIR((goal - ball).angle()); //����Ŀ��ķ���
	const float toGoalDist = (goal - ball).length();	//����Ŀ���ľ���
	my_kick_power = SetPassPower(toGoalDist); // ����Ҳ����дһ�� ��Ծ�����ֶ� ʲô�ģ� ���Ӿ�ϸ

 

	static int i = 0; //��̬��־ ȷ�� ����Ƕȼ�״̬
	static int nearBall = false; //�ӽ�placePos��
	static const float circleR = 35; //���е����뾶
	const point2f &playerPos = model->get_our_player_pos(robot_id); //��Ա����
	const float &robot_dir = model->get_our_player_dir(robot_id); //��Ա����
	float g2b = DIR((ball - goal).angle());//Ŀ�굽��ķ�
	float b2g = DIR(Reverse_Dir(g2b));//��Ŀ��ķ���
	float r2b = DIR((ball - playerPos).angle());//��Ա��������ķ���
	float b2r = DIR((playerPos - ball).angle()); //�������Ա�ķ���
	float toBallDist = DIR((playerPos - ball).length());//��Ա������ľ���



	const point2f &firstPos = ball + Maths::vector2polar(circleR - 2, b2r);//Զ���� Ӧ�ôﵽԲ���ϵ�λ��
	const point2f &placePos = ball - Maths::vector2polar(circleR - 2, toGoalDir);//Բ���� �ʺ����� kickPos��λ��
	float toPlaceposDist = (playerPos - placePos).length();//���������� 
	const point2f &kickPos = ball - Maths::vector2polar(MAX_ROBOT_SIZE - 2, toGoalDir);//���� Ӧ�ôﵽ�� kickPos
	float toKickPosDist = (playerPos - kickPos).length();//�����ŵ� ����


	


		if (toBallDist > circleR) //����δ�����㹻��, �����򿿽� ȥ�� ֱ�߾���Բ���������һ��
		{
			if (ball.X() < 300 && ball.X() > -300 && ball.Y() < 200 && ball.Y() > -200) //����ͼ����ʱ���������λ��
			{
				//��������

				/*������ ϸ��*/
				task.orientate = b2r + PI;
				task.target_pos = ball + Maths::vector2polar(circleR - 1, RunToCircleDir(b2r, b2g));

				/*����*/
				/*task.orientate = r2b;
				task.target_pos = firstPos;*/
			}
		}

		/* ��Բ�� ���ϱƽ� placePos */
		else if (toBallDist < circleR + 5 && toBallDist > circleR - 12)
		{
			task.target_pos = ball + Maths::vector2polar(circleR - 1, RunOnCircleDir(b2r, b2g, PI / 5)); // +˳ʱ�� || -��ʱ�� 
			task.orientate = r2b;

			if (toPlaceposDist < 12 || toKickPosDist < 12) // �ӽ������
			{
				nearBall = 1;
				task.target_pos = kickPos;
				task.orientate = toGoalDir;
				task.needCb = true;
			}
		}

		/*�ƽ������*/
		if (nearBall)
		{
			task.target_pos = kickPos;
			task.orientate = toGoalDir;
			task.needCb = true;
		}

		/* �������� */
		if (toKickPosDist < MAX_ROBOT_SIZE+4)  //�� placePos���� �ƽ�kickPos ��׼������
		{
			task.target_pos = kickPos;
			task.orientate = toGoalDir;
			task.needCb = true;
			if (fabs(r2b - toGoalDir) < PI /6 && toBallDist < MAX_ROBOT_SIZE+3)
			{
				task.needCb = false;
				task.needKick = true;
				task.kickPower = my_kick_power;
			}
		}


		//bool start_action = (BallSpeed(0, 1) < 2) ? true : false;
		//if (start_action == false)
		//{
		//	task.target_pos =   ball + Maths::vector2polar(35, b2r);
		//}
	

	return task;
}










