
void menu_init()
{
    system("cls");
/*    COORD menu_0={21,12};
    setColor(2,0);
    SetConsoleCursorPosition(hOutput,menu_0);
    cout<<"开始游戏";
    setColor(7,0);
    COORD menu_1={21,14};
    SetConsoleCursorPosition(hOutput,menu_1);
    cout<<"游戏说明";

    COORD menu_1={21,16};
    SetConsoleCursorPosition(hOutput,menu_1);
    cout<<"按键修改";
*/
    setColor(11,0);
    cout<<"游戏说明："<<endl<<endl;
    cout<<"    红色的为P1，蓝色的为P2。他们的数字代表着他们的HP，";
    cout<<"左右两边的数字分别是P1、P2对应的子弹，最下面的数字的左边(P2是右边)的运算符代表子弹发射的不同模式，不同模式下击中玩家的效果不同"<<endl;
    cout<<"    在'+'模式下，玩家的HP变为原HP加上子弹对应的数字然后取个位数"<<endl;
    cout<<"    在'-'模式下，玩家的HP变为原HP减去子弹对应的数字然后加10再取个位数"<<endl;
    cout<<"    在'*'模式下，玩家的HP变为原HP乘上子弹对应的数字然后取个位数"<<endl;
    cout<<"    在'^'模式下，玩家的HP变为原HP的子弹对应的数字的次方"<<endl;
    cout<<"    在代表子弹的数字的下方的字母(m或a)代表的是对应的玩家模式：a(atack)代表的是攻击模式，在此模式按对应方向键发射子弹；m(move)代表的是移动模式"<<endl<<endl;
    cout<<"P1操作："<<endl;
    cout<<"    +：u键   -：i键   *：o键   ^：l键   a：j键"<<endl;
    cout<<"    上：w键   下：s键   左：a键   右：d键   m：k键"<<endl;
    cout<<"P2操作："<<endl;
    cout<<"    +：4键   -：5键   *：6键   ^：3键   a：1键"<<endl;
    cout<<"    上:↑键  下:↓键  左:←键  右:→键  m：2键"<<endl;
    cout<<"\t\t";

    COORD test={15,25};
    SetConsoleCursorPosition(hOutput,test);
    system("pause");
}
