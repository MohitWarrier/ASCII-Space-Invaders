/*Space shooter game using c++
  c++ features used - classes,arrays,files
  player scores are saved into files and can be modified by beating previous score
  Highscore List feature to show top 10 scores
  */
#include<iostream>
#include<cstring>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<fstream> 
using namespace std;

char play_again,name[50];
int score,lives,play,bullets,times_played;
bool running;

void gotoxy(int x, int y) 
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); 
    COORD xy = {x, y}; 
    SetConsoleCursorPosition(hOut, xy);
}

class GamePlay 
{
	public:
		char area[20][80],turn;
		int number_of_enemies,upos,initialpos,timer;
		void printarea();
		void UserMovement();
		void EnemyGenerator();
		void ProjectileMovement();
		void checkGameStatus();
		GamePlay()
		{
			upos = 10;
		    running = true;
		    bullets = 70;
		    timer = 0;
		    number_of_enemies = 0;
		    score = 0;
		    times_played = 0;											
		    lives = 10;
		    for(int i = 0;i<20;i++)
		    {
		        for(int j = 0;j<80;j++)
		        {
		            if(i == 0 || i == 19)
		                area[i][j] = (char)205;
		            else if(j == 0 || j == 79)
		                area[i][j] = (char)186;
		            else
		                area[i][j] = ' ';
		
		        }
		    }
		    area[0][79] = (char)187;
		    area[19][79] = (char)188;
		    area[0][0] = (char)201;
		    area[19][0] = (char)200;
		
		    area[upos][1] = '>';
		}
};

class Screen 
{
	public:
		void ShowCursor(bool show);
		void colour(int a);
		void loading();
		void end();
};

class Player: public Screen
{
	public:
		char player_name[15];
		int player_score;
		int no_of_attempts;
		void getName();
		void HighscoreList();
		void EnterToFile();
}p;

void Screen::ShowCursor(bool show) 
{
    HANDLE hConsoleOutput;
    CONSOLE_CURSOR_INFO structCursorInfo;
    hConsoleOutput = GetStdHandle( STD_OUTPUT_HANDLE );
    GetConsoleCursorInfo( hConsoleOutput, &structCursorInfo );
    structCursorInfo.bVisible = show;
    SetConsoleCursorInfo( hConsoleOutput,
    &structCursorInfo );
}

void Screen::colour(int a)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),a);
}

void Player::HighscoreList()
{
	system("cls");
	colour(12);
	cout<<"\t\t\t\t  _   _ _       _"<<endl;                                
	cout<<"\t\t\t\t | | | (_)     | |"<<endl;                                
	cout<<"\t\t\t\t | |_| |_  __ _| |__  ___  ___ ___  _ __ ___  ___"<<endl; 
	cout<<"\t\t\t\t |  _  | |/ _` | '_ \\/ __|/ __/ _ \\| '__/ _ \\/ __|"<<endl;
	cout<<"\t\t\t\t | | | | | (_| | | | \\__ \\ (_| (_) | | |  __/\\__ \\ "<<endl;
	cout<<"\t\t\t\t \\_| |_/_|\\__, |_| |_|___/\\___\\___/|_|  \\___||___/"<<endl;
	cout<<"\t\t\t\t           __/ |                                  "<<endl;
	cout<<"\t\t\t\t          |___/  \n\n\n\n                            ";     
	
	colour(10);
	ifstream fin("HighscoreList.txt",ios::in);	
	if(!fin)
	{
		cout<<"\n\t\t\t\t\t   No one has Played yet!";
	}
	else
	{
		colour(9);
		cout<<"\n\t\t\t\tPlayer Name\t\tScore\t\tTimes Played\n\n";
		colour(10);
		Player P1[100];int n;
		while(!fin.eof())
		{
			fin.read((char*)&p,sizeof(p));
			if (fin.eof())
			break;
			P1[n] = p;
			n++;
		}
		fin.close();
		Player temp;
		for(int i =0;i<n;i++) //bubble sort
		{
			for(int j = 0;j<n-1;j++)
			{
				if(P1[j].player_score < P1[i].player_score)
				{
					temp = P1[j];
					P1[j] = P1[i];
					P1[i] = temp;
				}
			}
		}
		for(int i = 0,j = 0;i<n && j < 10;i++,j++) //Displays Top 10 scores
		{
			if(i == 0)
			colour(12);
			else
			colour(10);
			cout<<"\t\t\t\t";
			cout.width(20);
			cout<<left<<P1[i].player_name<<"\t "<<P1[i].player_score<<"\t\t  "<<P1[i].no_of_attempts<<endl;
		}
		
	}
	colour(15);
	cout<<"\n\n\t\t\t\t\t  Press any key to go back";
	getch();
	system("cls");
}

void Player::getName()
{
	Sleep(500);
	system("cls");
	system("color 0A");	
	char ch[2][50] = {"ENTER YOUR",
					  "NAME:"};
	for(int i=0;i<2;i++)
	{
		cout<<"\n\n ";
	    colour(10);
	  	for(int j=0;ch[i][j]!='\0';j++)
	  	{
	   		cout << ch[i][j];
	   		Sleep(100);
	  	}
	  	Sleep(200);
	}
	while(kbhit())
	getch();
	cout<<"\n\n ";
	colour(9);
	cin.getline(name,50);
	colour(10);
	cout<<"\n Good Luck ";colour(9);
	cout<<name;colour(10);cout<<" !";Sleep(1000); colour(12);
	while(kbhit())
	getch();
	cout<<"\n\n PRESS ANY KEY WHEN YOU ARE READY!!";
	getch();
}

void Flash() //Flashes the screen
{
	system("color 6E");
	Sleep(50);
	system("color E6");
	Sleep(50);
	system("color 7F");
	Sleep(50);
	system("color F7");
	Sleep(50);
    if(lives >= 8 && lives <= 10)
        system("color 0A");
    else if(lives > 3 && lives <8)
        system("color 0E");
    else if(lives <= 3)
        system("color 0C");
}

void Screen::loading()
{
	gotoxy(47,22);
	cout<<"Loading";
	colour(9);
	gotoxy(41,23);
	for(int i = 0;i<20;i++)
	cout<<(char)177;
	colour(153);
	gotoxy(41,23);
	for(int i = 0;i<20;i++)
	{
		cout<<(char)219;
		Sleep(100);
	}
	colour(10);
	while(kbhit())
	getch();
}

void GamePlay::printarea() //Print game map
{
	Screen col;
	col.colour(14);
    cout<<" a - Move Up";
    cout<<"\n d - Move Down";
    col.colour(12);
    cout<<"\n s - Shoot";
    col.colour(13);
    cout<<"\n p - Pause";
    cout<<"\n q - Quit\n\n";
    if(lives >= 7 && lives <= 10)
       col.colour(10);
    else if(lives >= 3 && lives <7)
        col.colour(14);
    else if(lives <= 2)
    col.colour(12);
    for(int i = 0;i<20;i++)
    {
        cout<<endl;
        for(int j = 0;j<80;j++)
        {
            if(j == 0)
				cout<<" ";
            cout<<area[i][j];
        }
    }
    gotoxy(90,8);col.colour(15);cout<<"Score: ";col.colour(14);cout<<score;
    gotoxy(90,9);col.colour(15);cout<<"Bullets: ";col.colour(11);cout<<bullets<<" ";
    gotoxy(90,10);col.colour(15);cout<<"Lives left: ";
    if(lives >= 7 && lives <= 10)
    {
    	 col.colour(10);cout<<lives<<" ";
	}  
    else if(lives >= 3 && lives <7)
    {
    	  col.colour(14);cout<<lives<<" ";
	}      
    else if(lives <= 2)
    {
    	 col.colour(12);
    	 if(lives<=0)cout<<"0";
    	 else
    	 cout<<lives<<" ";
	}
	gotoxy(90,14);col.colour(12);cout<<"kill to receive bullets!!";
}

void GamePlay::UserMovement()//Input user move and update map accordingly
{
    turn = getch();
    switch(turn)
    {
    case 'a':
        if(upos>1)
        {
            area[upos-1][1] = area[upos][1];
            area[upos][1] = ' ';
            upos--;
        }
        break;
    case 'd':
        if(upos < 18)
        {
            area[upos+1][1] = area[upos][1];
            area[upos][1] = ' ';
            upos++;
        }
        break;
    case 's':
        if(bullets > 0)
        {
            area[upos][2] = '-';
            bullets--;
        }
        break;
    case 'q':
        running = false;
        break;
    case 'p':gotoxy(40,17);cout<<"PAUSED";
        getch();
        break;
    }
}

void GamePlay::EnemyGenerator() 
{
        if(timer%50 == 0)
        {
            for(int i = 0;i<number_of_enemies;i++)
            {
                initialpos = (rand() % 17) + 2;
                area[initialpos][78] = '<';
            }
            number_of_enemies++;
        }
        if(timer%150 == 0 && number_of_enemies!= 1)
        {
            area[initialpos][78] = 'o';
            area[initialpos][77] = 'o';
            area[initialpos][76] = 'o';
        }
        if(timer % 400 == 0 && number_of_enemies != 1)
        {
            initialpos = (rand() % 14) + 4;
            area[initialpos][78] = 'o';
            area[initialpos][77] = 'o';
            area[initialpos + 1][78] = 'o';
            area[initialpos +1][77] = 'o';
        }
}

void GamePlay::ProjectileMovement() //Movement of bullets and enemies
{
    for(int i = 20;i>0;i--) //Bullet movement
    {
        for(int j = 80;j>0;j--)
        {
            if(area[i][j] == '-'  && area[i][j+1] == ' ')
            {
                area[i][j+1] = '-';
				area[i][j] = ' ';
            }
            if(area[i][j] == '-' && j == 78)
                area[i][j] = ' ';
            if(area[i][j] == '-' && (area[i][j+1] == '<'||area[i][j+1] == 'o'))
            {
                area[i][j] = ' ';
                area[i][j+1] = ' ';
                score++;
                if(score%15 == 0)
                    bullets+=20;
            }
        }
    }
    for(int i = 0;i<20;i++) //Enemy movement
    {
        for(int j = 0;j<80;j++)
        {
            if(area[i][j] == '<' && area[i][j-1] == ' ')
            {
                area[i][j-1] = '<';
                area[i][j] = ' ';
            }
            if(area[i][j] == '<' && (j == 1 || area[i][j-1] == '>'))
            {
                area[i][j] = ' ';
                Flash();
                lives--;
                number_of_enemies--;
            }
            if(area[i][j] == 'o' && area[i][j-1] == ' ')
            {
                area[i][j-1] = 'o';
                area[i][j] = ' ';
            }
            if(area[i][j] == 'o' && (j == 1 || area[i][j-1] == '>'))
            {
                area[i][j] = ' ';
                Flash();
                lives--;
                number_of_enemies--;
            }
        }
    }
    timer+=1;
}

void GamePlay::checkGameStatus() //Check if game is over or not
{
    if(lives <= 0 || bullets == 0)
        running = false;
}

void Screen::end()
{
	system("cls");int change;
	while(1)
	{
		if(change%5 == 0)
		colour(15);
		else
		colour(9);
		cout<<"\n\n\t\t\t\t\t _____   "<<endl;                         
		cout<<"\t\t\t\t\t|  __ \\    "<<endl;                       
		cout<<"\t\t\t\t\t| |  \\/ __ _ _ __ ___   ___"<<endl;       
		cout<<"\t\t\t\t\t| | __ / _` | '_ ` _ \\ / _ \\ "<<endl;     
		cout<<"\t\t\t\t\t| |_\\ \\ (_| | | | | | |  __/   "<<endl;   
		cout<<"\t\t\t\t\t \\____/\\__,_|_| |_| |_|\\___|    "<<endl;  
				
		cout<<"\t\t\t\t\t _____                  _ "<<endl;
		cout<<"\t\t\t\t\t|  _  |                | |"<<endl;
		cout<<"\t\t\t\t\t| | | |_   _____ _ __  | |"<<endl;
		cout<<"\t\t\t\t\t| | | \\ \\ / / _ \\ '__| | |"<<endl;
		cout<<"\t\t\t\t\t\\ \\_/ /\\ V /  __/ |    |_|"<<endl;
		cout<<"\t\t\t\t\t \\___/  \\_/ \\___|_|    (_)"<<endl;		 
		colour(15);
		gotoxy(40,16);
        if(lives <= 0)
            cout<<"The enemies have defeated you!!";
        else if(bullets == 0)
            cout<<"You ran out of bullets!!";
        else
            cout<<"Never Give Up!! Try again!!";
        gotoxy(40,17);
        cout<<name<<" has scored: ";colour(12);cout<<score;
        colour(14);
        gotoxy(32,19);
        cout<<"--- Press any key to go back to menu! ---";
       if(kbhit())
       {
       		break;
	   }
	   gotoxy(48,21);
		Sleep(100);  
		gotoxy(0,0);   change++;
	}
}

void menu()
{	
	int flicker = 0;
	play = ' ';
	Screen ob;
	while(play!='p' && play!='h')
	{	
		ob.colour(9);	         		
		cout<<"\n\n\n\t\t\t\t\t _____        "<<endl;            
		cout<<"\t\t\t\t\t/  ___|         "<<endl;      
		cout<<"\t\t\t\t\t\\ `--. _ __   __ _  ___ ___ "<<endl;
		cout<<"\t\t\t\t\t `--. \\ '_ \\ / _` |/ __/ _ \\ "<<endl;
		cout<<"\t\t\t\t\t/\\__/ / |_) | (_| | (_|  __/"<<endl;
		cout<<"\t\t\t\t\t\\____/| .__/ \\__,_|\\___\\___|"<<endl;
		cout<<"\t\t\t\t\t      | |"<<endl;
		cout<<"\t\t\t\t\t      |_|"<<endl;
					
		cout<<"\t\t\t\t _____                    _               "<<endl;
		cout<<"\t\t\t\t|_   _|                  | |              "<<endl;
		cout<<"\t\t\t\t  | | _ ____   ____ _  __| | ___ _ __ ___ "<<endl;
		cout<<"\t\t\t\t  | || '_ \\ \\ / / _` |/ _` |/ _ \\ '__/ __|"<<endl;
		cout<<"\t\t\t\t _| || | | \\ V / (_| | (_| |  __/ |  \\__ \\ "<<endl;
		cout<<"\t\t\t\t \\___/_| |_|\\_/ \\__,_|\\__,_|\\___|_|  |___/"<<endl;
		if(flicker%2 == 0)
		ob.colour(14);
		else 
		ob.colour(11);
		cout<<"\n\t\t\t\t Press p to play, h to view Highscore List";
		ob.colour(10);
		gotoxy(90,10);cout<<"<";
		gotoxy(10,11);cout<<">";gotoxy(17,11);cout<<"-";
		gotoxy(90,20);cout<<"ooo";
		gotoxy(100,15);cout<<"oo";		
		gotoxy(100,16);cout<<"oo";
	
		ob.colour(12);
		gotoxy(40,29);
		cout << "--- Made by Mohit ---";   
		ob.colour(13);
		gotoxy(0,0);cout<<"Esc to quit";
		if(kbhit())
		play = getch();  
		if(play == (char)27)break;                         		
	    gotoxy(0,0);
	    Sleep(200);
	    flicker++;
	}
}

void Player::EnterToFile()
{
	times_played++;
	int pos;
	ifstream check("HighscoreList.txt");
	ofstream fout("HighscoreList.txt",ios::app);
	while(!check.eof())
	{
		pos = check.tellg();
		if(pos == -1)
		break;
	 	check.read((char*)&p,sizeof(p));
	 	if(strcmp(p.player_name,name) == 0 )
	 	{
	 		if(p.player_score < score)
	 		{
	 			player_score = score;
				strcpy(player_name,name);
				no_of_attempts++;
				fstream fwrite("HighscoreList.txt",ios::out|ios::in);
				fwrite.seekp(pos,ios::beg);
				fwrite.write((char*)&p,sizeof(p));
				fwrite.close();
			}
			else
			{
				no_of_attempts++;
				fstream fwrite("HighscoreList.txt",ios::out|ios::in);
				fwrite.seekp(pos,ios::beg);
				fwrite.write((char*)&p,sizeof(p));
				fwrite.close();
				
			}
			return;
		}
	}
	player_score = score;
	strcpy(player_name,name);
	no_of_attempts = times_played;
	fout.write((char*)&p,sizeof(p));
	fout.close();
	check.close();
}

int main()
{
	Screen main;
	main.ShowCursor(false);
	menu:menu();
	if(play == 'h')
	{
		main.loading();
		p.HighscoreList();
		goto menu;
	}
	else if(play == (char)27)
		goto quitgame;
	else
	{
		main.loading();
		p.getName();
		GamePlay game_play;
        srand(time(0));
        system("cls");
        do
        {
            game_play.printarea();
            if(kbhit())
               game_play.UserMovement();
            game_play.EnemyGenerator();
            game_play.ProjectileMovement();
            gotoxy(0,0);
            game_play.checkGameStatus();
        }while(running);
        Sleep(800);
        while(kbhit())
		getch();
		p.EnterToFile();
     	main.end();
        system("cls");
   		goto menu;	
	}
	
    quitgame:system("cls");
    return 0;
}

