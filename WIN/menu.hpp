
void menu_init()
{
    system("cls");
/*    COORD menu_0={21,12};
    setColor(2,0);
    SetConsoleCursorPosition(hOutput,menu_0);
    cout<<"��ʼ��Ϸ";
    setColor(7,0);
    COORD menu_1={21,14};
    SetConsoleCursorPosition(hOutput,menu_1);
    cout<<"��Ϸ˵��";

    COORD menu_1={21,16};
    SetConsoleCursorPosition(hOutput,menu_1);
    cout<<"�����޸�";
*/
    setColor(11,0);
    cout<<"��Ϸ˵����"<<endl<<endl;
    cout<<"    ��ɫ��ΪP1����ɫ��ΪP2�����ǵ����ִ��������ǵ�HP��";
    cout<<"�������ߵ����ֱַ���P1��P2��Ӧ���ӵ�������������ֵ����(P2���ұ�)������������ӵ�����Ĳ�ͬģʽ����ͬģʽ�»�����ҵ�Ч����ͬ"<<endl;
    cout<<"    ��'+'ģʽ�£���ҵ�HP��ΪԭHP�����ӵ���Ӧ������Ȼ��ȡ��λ��"<<endl;
    cout<<"    ��'-'ģʽ�£���ҵ�HP��ΪԭHP��ȥ�ӵ���Ӧ������Ȼ���10��ȡ��λ��"<<endl;
    cout<<"    ��'*'ģʽ�£���ҵ�HP��ΪԭHP�����ӵ���Ӧ������Ȼ��ȡ��λ��"<<endl;
    cout<<"    ��'^'ģʽ�£���ҵ�HP��ΪԭHP���ӵ���Ӧ�����ֵĴη�"<<endl;
    cout<<"    �ڴ����ӵ������ֵ��·�����ĸ(m��a)������Ƕ�Ӧ�����ģʽ��a(atack)������ǹ���ģʽ���ڴ�ģʽ����Ӧ����������ӵ���m(move)��������ƶ�ģʽ"<<endl<<endl;
    cout<<"P1������"<<endl;
    cout<<"    +��u��   -��i��   *��o��   ^��l��   a��j��"<<endl;
    cout<<"    �ϣ�w��   �£�s��   ��a��   �ң�d��   m��k��"<<endl;
    cout<<"P2������"<<endl;
    cout<<"    +��4��   -��5��   *��6��   ^��3��   a��1��"<<endl;
    cout<<"    ��:����  ��:����  ��:����  ��:����  m��2��"<<endl;
    cout<<"\t\t";

    COORD test={15,25};
    SetConsoleCursorPosition(hOutput,test);
    system("pause");
}
