#include "pch.h"
#include "MySnake.h"
void MySnake::pMoveTo(MyPoint ptDir)
{
    if (!snake.empty())
    {
        MyPoint newHead;
        double dStep = 0;
        if (IsHuman)
            dStep = 50;
        else
            dStep = 30;
        SetDir(atan2(ptDir.Gety() - snake.back().Gety(), ptDir.Getx() - snake.back().Getx()));
        newHead.Setx(snake.back().Getx() + dStep * cos(GetDir()));
        newHead.Sety(snake.back().Gety() + dStep * sin(GetDir()));
        snake.emplace_back(newHead);
        snake.pop_front();
    }
}

bool MySnake::HitItself()
{
    if (!snake.empty())
    {
    
    
    int cnt = 0;
    MyPoint head = snake.back();//���ͷ������
    for (auto& pt : snake) //������ͷ������ͷ�غ��⣬�����������������ͷ��ײ��cnt�ͻ����1���Ӷ���ײ
    {
        if (pt && head)
            cnt++;
        if (cnt > 1)
            return true;
    }
    return false;
    }
    return false;
}
void MySnake::EatFood(Food& fd)
{
    if (!snake.empty())
    {
        MyPoint newTail;
        MyPoint head = snake.back();//���ͷ������
        auto iter = fd.food.begin();
        while (iter != fd.food.end())
        {
            if ((*iter) && head)
            {
                newTail = snake.front();
                snake.emplace_front(newTail);
                fd.food.erase(iter);
                return;//һ����ײ�Ͼ�Ҫ��ʱreturn����Ϊfood��size�����̸ı䣬����Ҳû�м��������ı�Ҫ
            }
            iter++;
        }
    }
}
bool MySnake::HitStone(Stone& st)
{
    const int SCREEN_CX = 2462;
    const int SCREEN_CY = 1378;
    int heightX = SCREEN_CX;
    int heightY = SCREEN_CY;
    if (!snake.empty())
    {
        MyPoint head = snake.back();
        auto iter = st.stone.begin();
        while (iter != st.stone.end())
        {
            if ((*iter) && head)
            {
                if (!IsHuman)
                {
                    st.stone.erase(iter);
                    
                }

                return true;//һ����ײ�Ͼ�Ҫ��ʱreturn����Ϊfood��size�����̸ı䣬����Ҳû�м��������ı�Ҫ
            }
            iter++;
        }
        return false;
    }
}
Shell MySnake::Fire()
{
    Shell shell;
    double dStep = 400.0;
    shell.Setx(snake.back().Getx() + dStep * cos(GetDir()));
    shell.Sety(snake.back().Gety() + dStep * sin(GetDir()));
    return shell;
}

MyPoint MySnake::AutoFindFood(Food& fd)
{
    if (!snake.empty())
    {
        MyPoint NearFood;
        MyPoint head = snake.back();
        double NearDis = INT_MAX;
        auto iter = fd.food.begin();
        std::list<MyPoint>::iterator dele_iter;
        while (iter != fd.food.end())
        {
            double dis = sqrt(pow(((*iter).Getx() - head.Getx()), 2) + pow(((*iter).Gety() - head.Gety()), 2));
            if (dis < NearDis)
            {
                NearDis = dis;
                NearFood = (*iter);
                dele_iter = iter;
            }
            iter++;
        }
        MyPoint NewTail = snake.front();
        if (fd.food.size() > 1)
        {
            if (head && NearFood)
            {
                fd.food.erase(dele_iter);
                snake.emplace_front(NewTail);
            }
        }

        return NearFood;
    }

}
