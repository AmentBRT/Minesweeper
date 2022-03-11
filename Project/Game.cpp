#include "clui.h"
#include <time.h>
#include <fstream>
#include <iostream>
using namespace std;

struct coordinate{
    int rows = get_window_rows();
    int columns = get_window_cols();
    int r_middle = rows/2;
    int c_middle = columns/2;
} windows;

struct slot{
    string name;
    int** game_field;
    char** flag;
    int LENGTH = 0;
    int BOMB = 0;
    int flags;
};

struct score{
    string name;
    int point = -1;
};

void get_name();
void change_name();
void window_background();

void menu_print();
void menu();

void mode_print();
void game_mode();

void new_game(int,int);
void custom_game();
void placing_bomb(int**,int,int);
void empty_cells(int**,int,int,int);

void game_background(int);
void field_background(int);
void solution_print(int**,int,int,int);

void game(int**,char**,int,int,int);
void win_game(int);
void lose_game(int);
void replay(int);
void reset_game(int**,char**,int);

int string_length(string);
void save_game(int**,char**,int,int,int);
bool name_exists(string);

int load_menu();
void load_game();
slot preview_slot(string);
slot load_slot(string);
void loaded_field_background(int**,char**,int);

void scores(int);
score load_score(string);
void leaderboard_print();
void leaderboard();

string Name;
bool Replay=false;

int main(){
    init_clui();

    get_name();

    menu();

    quit();
    return 0;
}

void get_name(){

    cursor_to_pos(windows.r_middle-10, windows.c_middle-5);
    printf("Your Name:");
    cursor_to_pos(windows.r_middle-9, windows.c_middle-4);
    cin >> Name;

    window_background();
}

void change_name(){
    get_name();

    menu();
}

void window_background(){
    clear_screen();

    cursor_to_pos(0,0);
    save_cursor();
    change_color(1);
    change_background_color(3);
    
    for(int r=1; r<windows.rows; r++){
        if(r==1){
            flush();
            printf(" ");
            flush();
            for(int c=2; c<windows.columns; c++) printf("_");
            flush();
            printf(" ");
        }
        if(r==windows.rows-1){
            flush();
            printf("|");
            flush();
            for(int c=2; c<windows.columns; c++) printf("_");
            flush();
            printf("|");
        }
        else{
            flush();
            printf("|");
            flush();
            for(int c=2; c<windows.columns; c++) printf(" ");
            flush();
            printf("|");
        }
    }
    reset_color();
    restore_cursor();
}

void menu_print(){
    save_cursor();
    change_background_color(0);

    cursor_to_pos(windows.r_middle-5, windows.c_middle-8);
    for(int i=11; i; i--){
        if(i==11 || i==1){
            printf(".................");
            cursor_backward(17);
            cursor_down(1);
        }
        else if(i==10){
            printf(".  ^ New Game   .");
            cursor_backward(17);
            cursor_down(1);
        }
        else if(i==8){
            printf(".  ^ Load Game  .");
            cursor_backward(17);
            cursor_down(1);
        }
        else if(i==6){
            printf(". ^ Change Name .");
            cursor_backward(17);
            cursor_down(1);
        }
        else if(i==4){
            printf(". ^ Leaderboard .");
            cursor_backward(17);
            cursor_down(1);
        }
        else if(i==2){
            printf(".    ^ Quit     .");
            cursor_backward(17);
            cursor_down(1);
        }
        else{
            printf(".               .");
            cursor_backward(17);
            cursor_down(1);
        }
    }
    restore_cursor();
    reset_color();
}

void menu(){
    menu_print();

    int i=1;
    while(1){
        char ch=nb_getch();

        if(ch==10 || ch==13 || ch==' '){
            break;
        }

        if(ch=='w' || ch=='W' || ch=='8'){
            if(i-1!=0){
                i--;
            }
        }

        if(ch=='s' || ch=='S' || ch=='2'){
            if(i+1!=6){
                i++;
            }
        }

        if(i==1){
            cursor_to_pos(windows.r_middle-4, windows.c_middle-5);
        }
        if(i==2){
            cursor_to_pos(windows.r_middle-2, windows.c_middle-5);
        }
        if(i==3){
            cursor_to_pos(windows.r_middle, windows.c_middle-6);
        }
        if(i==4){
            cursor_to_pos(windows.r_middle+2, windows.c_middle-6);
        }
        if(i==5){
            cursor_to_pos(windows.r_middle+4, windows.c_middle-3);
        }
    }
    switch(i){
        case 1: game_mode(); break;
        case 2: load_game(); break;
        case 3: change_name(); break;
        case 4: leaderboard(); break;
    }
    return;
}

void mode_print(){
    save_cursor();
    cursor_to_pos(windows.r_middle-4, windows.c_middle-7);

    change_background_color(5);
    for(int i=9; i; i--){
        if(i==9){
            printf("  ^ Easy Mode  ");
            cursor_backward(15);
            cursor_down(1);
            delay(1);
        }
        else if(i==7){
            printf(" ^ Normal Mode ");
            cursor_backward(15);
            cursor_down(1);
            delay(1);
        }
        else if(i==5){
            printf("  ^ Hard Name  ");
            cursor_backward(15);
            cursor_down(1);
            delay(1);
        }
        else if(i==3){
            printf(" ^ Custom Mode ");
            cursor_backward(15);
            cursor_down(1);
            delay(1);
        }
        else if(i==1){
            printf(" ^ Back to Menu");
            cursor_backward(15);
            cursor_down(1);
            delay(1);
        }
        else{
            printf("               ");
            cursor_backward(15);
            cursor_down(1);
            delay(1);
        }
    }
    restore_cursor();
    reset_color();
}

void game_mode(){
    mode_print();

    int i=1;
    while(1){
        char ch=nb_getch();

        if(ch==10 || ch==13 || ch==' '){
            break;
        }

        if(ch=='w' || ch=='W' || ch=='8'){
            if(i-1!=0){
                i--;
            }
        }

        if(ch=='s' || ch=='S' || ch=='2'){
            if(i+1!=6){
                i++;
            }
        }

        if(i==1){
            cursor_to_pos(windows.r_middle-4, windows.c_middle-5);
        }
        if(i==2){
            cursor_to_pos(windows.r_middle-2, windows.c_middle-6);
        }
        if(i==3){
            cursor_to_pos(windows.r_middle, windows.c_middle-5);
        }
        if(i==4){
            cursor_to_pos(windows.r_middle+2, windows.c_middle-6);
        }
        if(i==5){
            cursor_to_pos(windows.r_middle+4, windows.c_middle-6);
        }
    }
    switch(i){
        case 1: new_game(5,4); break;
        case 2: new_game(12,28); break;
        case 3: new_game(20,96); break;
        case 4: custom_game(); break;
        case 5: menu(); break;
    }
}

void new_game(int LENGTH, int BOMB){
    int** game_field = new int*[LENGTH+2];
    char** flag = new char*[LENGTH+2];
    
    for(int i=0; i<LENGTH+2; i++){
        game_field[i] = new int[LENGTH+2]{0};
        flag[i] = new char[LENGTH+2];
        for(int j=0; j<LENGTH+2; j++){
            flag[i][j]=19;
        }
    }

    placing_bomb(game_field, LENGTH, BOMB);

    game_background(LENGTH);
    field_background(LENGTH);

    game(game_field, flag, LENGTH, BOMB, 0);
}

void custom_game(){
    cursor_to_pos(windows.r_middle-10, windows.c_middle-12);
    change_background_color(4);

    int LENGTH;
    printf("Enter LENGTH:");
    cursor_forward(1);
    cin >> LENGTH;

    cursor_to_pos(windows.r_middle-9, windows.c_middle-10);

    int BOMB;
    printf("Enter BOMB:");
    cursor_forward(1);
    cin >> BOMB;

    reset_color();

    new_game(LENGTH, BOMB);
}

void placing_bomb(int** game_field, int LENGTH, int BOMB){
    srand(time(NULL));

    for(int i=0; i<BOMB; i++){
        int a=(rand()%LENGTH)+1, b=(rand()%LENGTH)+1;
        if(game_field[a][b]==9) i--;
        else{
            game_field[a][b]=9;
            empty_cells(game_field, LENGTH, a, b);
        }
    }
}

void empty_cells(int** game_field, int LENGTH, int x, int y){
    for(int i=x-1; i<=x+1; i++)
        for(int j=y-1; j<=y+1; j++){
            if(i==0 || j==0 || i==LENGTH+1 || j==LENGTH+1) continue;
            if(game_field[i][j]!=9) game_field[i][j]++;
        }
}

void game_background(int LENGTH){
    window_background();

    change_background_color(1);

    cursor_to_pos(windows.r_middle-(LENGTH+1)/2, windows.c_middle-(LENGTH+1));
    for(int i=(LENGTH+1)*2; i; i--){
        printf(".");
        flush();
        delay(1);
    }
    for(int i=LENGTH+1; i; i--){
        cursor_backward(1);
        cursor_down(1);
        printf(".");
        flush();
        delay(1);
    }
    for(int i=(LENGTH+1)*2; i; i--){
        cursor_backward(2);
        printf(".");
        flush();
        delay(1);
    }
    for(int i=LENGTH+1; i; i--){
        cursor_backward(1);
        cursor_up(1);
        printf(".");
        flush();
        delay(1);
    }
    reset_color();
}

void field_background(int LENGTH){
    change_background_color(0);
    for(int a=1; a<=LENGTH; a++){
        cursor_to_pos(windows.r_middle-((LENGTH-1)/2)+a-1, windows.c_middle-(LENGTH+1));
        flush();
        for(int i=LENGTH; i; i--) printf(" X");
        flush();
        printf(" ");
    }
    reset_color();
}

void solution_print(int** game_field, int LENGTH, int r, int c){
    for(int i=1; i<=LENGTH; i++, r++){
        cursor_to_pos(r, c);

        for(int j=1; j<=LENGTH; j++){
            if(game_field[i][j]==9){
                flush();
                change_color(3);
                printf("B ");
                delay(1);
                reset_color();
            }
            else if(game_field[i][j]==0){
                flush();
                printf("  ");
                delay(1);
            }
            else if(game_field[i][j]!=0){
                flush();
                change_color(11);
                printf("%d ", game_field[i][j]);
                delay(1);
                reset_color();
            }
        }
    }
}

void game(int** game_field, char** flag, int LENGTH, int BOMB, int flags){
    if(LENGTH%2==0) cursor_to_pos(windows.r_middle, windows.c_middle-2);
    if(LENGTH%2!=0) cursor_to_pos(windows.r_middle, windows.c_middle-1);

    //int start=time(NULL);

    bool b_to_menu=false;

    for(int i=(LENGTH+1)/2, j=(LENGTH+1)/2;;){
        //int now=time(NULL);
        /*if(now-start>=TIME_LIMIT){
            play_beep();
            cursor_to_pos(r_middle-(LENGTH/2)-4, c_middle-6);
            flush();
            printf("Time's Up!");

            cursor_to_pos(r_middle-(LENGTH/2)-3, c_middle-5);
            flush();
            printf("You Lost!");

            cursor_to_pos(r_middle-(LENGTH/2)-2, c_middle-11);
            flush();
            printf("press \"R\" for \"Replay\"");

            solution_print(r_middle-((LENGTH-1)/2), c_middle-LENGTH);

            int time1=time(NULL);
            flush();
            for(;;){
                int time2=time(NULL);
                if(time2-time1>=7) break;
                if(nb_getch()=='r' || nb_getch()=='R'){
                    clear_screen();
                    window_background(rows, columns);
                    game_background(r_middle, c_middle);
                    for(int a=1; a<=LENGTH; a++)
                        for(int b=1; b<=LENGTH; b++){
                            game_field[a][b]=0;
                            flag[a][b]=0;
                        }
                    bomb();
                    game(r_middle, c_middle, rows, columns);
                }
            }
            break;
        }*/

        int win=0;
        for(int a=1; a<=LENGTH; a++){
            for(int b=1; b<=LENGTH; b++){
                if(flag[a][b]==game_field[a][b]*11) win++;
            }
        }

        if(win==25){
            win_game(LENGTH);
            scores(BOMB*LENGTH*2);

            solution_print(game_field, LENGTH, windows.r_middle-((LENGTH-1)/2), windows.c_middle-LENGTH);

            replay(LENGTH);
            if(Replay){
                reset_game(game_field, flag, LENGTH);
                placing_bomb(game_field, LENGTH, BOMB);
                game(game_field, flag, LENGTH, BOMB, 0);
            }
            break;
        }

        flush();
        char ch=nb_getch();

        if(ch=='f' || ch=='F'){
            if(flag[i][j]!=game_field[i][j]*11){
                if(flag[i][j]==18){
                    flush();
                    printf("X");
                    cursor_backward(1);
                    flag[i][j]=19;
                    flags--;
                }
                else if(flags!=BOMB){
                    flush();
                    change_color(1);
                    printf("F");
                    reset_color();
                    cursor_backward(1);
                    flag[i][j]=18;
                    flags++;
                }
            }
        }

        if(ch==10 || ch==13 || ch==' '){
            if(flag[i][j]!=18){
                if(game_field[i][j]==9){
                    lose_game(LENGTH);
                    scores(0);

                    solution_print(game_field, LENGTH, windows.r_middle-((LENGTH-1)/2), windows.c_middle-LENGTH);

                    replay(LENGTH);
                    if(Replay){
                        reset_game(game_field, flag, LENGTH);
                        placing_bomb(game_field, LENGTH, BOMB);
                        game(game_field, flag, LENGTH, BOMB, 0);
                    }
                    break;
                }
                else if(game_field[i][j]!=0){
                    flush();
                    change_color(11);
                    printf("%d", game_field[i][j]);
                    cursor_backward(1);
                    reset_color();

                    flag[i][j]=game_field[i][j]*11;
                }
                else if(game_field[i][j]==0){
                    flush();
                    printf(" ");
                    cursor_backward(1);

                    flag[i][j]=game_field[i][j]*11;
                }
            }
        }

        if(ch=='w' || ch=='W' || ch=='8'){
            if(i-1!=0){
                cursor_up(1);
                i--;
            }
        }
        if(ch=='s' || ch=='S' || ch=='2'){
            if(i+1!=LENGTH+1){
                cursor_down(1);
                i++;
            }
        }
        if(ch=='a' || ch=='A' || ch=='4'){
            if(j-1!=0){
                cursor_backward(2);
                j--;
            }
        }
        if(ch=='d' || ch=='D' || ch=='6'){
            if(j+1!=LENGTH+1){
                cursor_forward(2);
                j++;
            }
        }

        if(ch=='o' || ch=='O'){
            save_game(game_field, flag, LENGTH, BOMB, flags);
            b_to_menu=true;
            break;
        }

        if(ch=='q' || ch=='Q'){
            b_to_menu=true;
            break;
        }
    }
    
    if(b_to_menu){
        window_background();
        menu();
    }
}

void win_game(int LENGTH){
    play_beep();
    cursor_to_pos(windows.r_middle-(LENGTH/2)-3, windows.c_middle-5);
    flush();
    printf("You Won!");
    delay(2000);
}

void lose_game(int LENGTH){
    flush();
    play_beep();
    change_color(1);
    printf(":)");
    reset_color();
    delay(800);
    
    cursor_to_pos(windows.r_middle-(LENGTH/2)-3, windows.c_middle-5);
    flush();
    printf("You Lost!");
}

void replay(int LENGTH){
    cursor_to_pos(windows.r_middle-(LENGTH/2)-2, windows.c_middle-11);
    flush();
    printf("press \"R\" for \"Replay\"");
    
    int time1=time(NULL);
    flush();
    while(1){
        int time2=time(NULL);
        if(time2-time1>=7) break;
        if(nb_getch()=='r' || nb_getch()=='R'){
            Replay=true;
            game_background(LENGTH);
            field_background(LENGTH);
        }
    }
}

void reset_game(int** game_field, char** flag, int LENGTH){
    for(int i=1; i<=LENGTH; i++){
        for(int j=1; j<=LENGTH; j++){
            game_field[i][j]=0;
            flag[i][j]=19;
        }
    }
}

int string_length(string text){
    int length=0;
    for(; text[length]!='\0'; length++);

    return length;
}

void save_game(int** game_field, char** flag, int LENGTH, int BOMB, int flags){
    string location;

    for(int i=1;;i++){
        string loc{"Saves/"};
        loc += i+'0';
        loc += ".txt";

        ifstream MyReadFile(loc);

        string text;
        getline(MyReadFile, text);
        MyReadFile.close();

        location=loc;

        if(name_exists(text)) break;
        if(string_length(text)==0) break;
    }

    ofstream MyFile(location);

    MyFile << '!' << Name;
    MyFile << '@' << LENGTH;
    MyFile << '#' << BOMB;

    MyFile << '$';
    for(int i=1; i<=LENGTH; i++){
        for(int j=1; j<=LENGTH; j++){
            MyFile << game_field[i][j];
        }
    }

    MyFile << '%';
    for(int i=1; i<=LENGTH; i++){
        for(int j=1; j<=LENGTH; j++){
            MyFile << flag[i][j];
        }
    }
    
    MyFile << '^' << flags;
    MyFile << '&';

    MyFile.close();
}

bool name_exists(string text){
    if(string_length(text)!=0){
        string s_name;
        int i=1;
        int a=0;

        for(; text[i]!='@'; a++, i++){
            s_name[a]=text[i];
        } s_name[a]=0;

        int len = string_length(s_name);
        if(string_length(Name)==len){
            for(int j=0; j<len; j++){
                if(s_name[j]!=Name[j]) return false;
            }

            return true;
        }
    }

    return false;
}

int load_menu(){
    window_background();

    cursor_to_pos(4, 4);
    change_background_color(3);
    for(int j=18; j; j--){
        printf(".");
    }
    cursor_to_pos(5,4);
    for(int j=20; j; j--){
        printf(".");
        cursor_backward(1);
        cursor_down(1);
    }
    reset_color();

    change_color(10);
    change_background_color(0);
    int i=1;
    while(1){
        string loc{"Saves/"};
        loc += i+'0';
        loc += ".txt";

        ifstream MyReadFile(loc);

        string text;
        getline(MyReadFile, text);
        MyReadFile.close();

        if(string_length(text)==0){
            break;
        }

        slot preview=preview_slot(text);

        cursor_to_pos(6+i*2,6);
        
        printf("^ ");
        for(int j=0; preview.name[j]!=0; j++){
            cout << preview.name[j];
        }

        printf("  LENGTH: ");
        printf("%d", preview.LENGTH);

        i++;
    }
    reset_color();

    cursor_to_pos(6,6);
    change_color(10);
    change_background_color(0);
    printf("^ Back to Menu");
    reset_color();

    return i;
}

void load_game(){
    int slots=load_menu();
    
    cursor_to_pos(6, 6);
    int i=0;
    while(1){
        char ch=nb_getch();

        if(ch==10 || ch==13 || ch==' '){
            break;
        }

        if(ch=='w' || ch=='W' || ch=='8'){
            if(i-1>=0){
                cursor_up(2);
                i--;
            }
        }

        if(ch=='s' || ch=='S' || ch=='2'){
            if(i+1!=slots){
                cursor_down(2);
                i++;
            }
        }
    }
    if(i!=0){
        string loc{"Saves/"};
        loc += i+'0';
        loc += ".txt";

        ifstream MyReadFile(loc);

        string text;
        getline(MyReadFile, text);
        MyReadFile.close();

        slot loaded=load_slot(text);

        Name=loaded.name;

        game_background(loaded.LENGTH);
        loaded_field_background(loaded.game_field, loaded.flag, loaded.LENGTH);
        game(loaded.game_field, loaded.flag, loaded.LENGTH, loaded.BOMB, loaded.flags);
    }
    else{
        window_background();
        menu();
    }
}

slot preview_slot(string text){
    slot load;

    int i=1;
    int a=0;
    
    for(; text[i]!='@'; a++, i++){
        load.name[a]=text[i];
    } load.name[a]=0;

    for(i++; text[i]!='#'; i++){
        load.LENGTH += text[i]-'0';
        load.LENGTH *= 10;
    } load.LENGTH /= 10;
    
    return load;
}

slot load_slot(string text){
    slot load;

    int i=1;
    int a=0;
    
    for(; text[i]!='@'; a++, i++){
        load.name[a]=text[i];
    } load.name[a]=0;

    for(i++; text[i]!='#'; i++){
        load.LENGTH += text[i]-'0';
        load.LENGTH *= 10;
    } load.LENGTH /= 10;

    for(i++; text[i]!='$'; i++){
        load.BOMB += text[i]-'0';
        load.BOMB *= 10;
    } load.BOMB /= 10, i++;

    load.game_field = new int*[load.LENGTH+2];
    for(int a=1; text[i]!='%'; a++){
        load.game_field[a] = new int[load.LENGTH+2];
        for(int b=1; b<=load.LENGTH; b++, i++){
            load.game_field[a][b]=text[i]-'0';
        }
    } i++;

    load.flag = new char*[load.LENGTH+2];
    for(int a=1; text[i]!='^'; a++){
        load.flag[a] = new char[load.LENGTH+2];
        for(int b=1; b<=load.LENGTH; b++, i++){
            load.flag[a][b]=text[i];
        }
    }

    for(i++; text[i]!='&'; i++){
        load.flags += text[i]-'0';
        load.flags *= 10;
    } load.flags /= 10;

    return load;
}

void loaded_field_background(int** game_field, char** flag, int LENGTH){
    
    change_background_color(0);

    for(int a=1; a<=LENGTH; a++){
        cursor_to_pos(windows.r_middle-((LENGTH-1)/2)+a-1, windows.c_middle-(LENGTH+1));
        flush();
        for(int b=1; b<=LENGTH; b++){
            if(flag[a][b]==18){
                change_color(1);
                printf(" F");
                reset_color();
            }
            else if(flag[a][b]==0){
                printf("  ");
            }
            else if(flag[a][b]==game_field[a][b]*11){
                change_color(11);
                printf(" %d", game_field[a][b]);
                reset_color();
            }
            else printf(" X");
        }
        flush();
        printf(" ");
    }
    reset_color();
}

void remove_save(string);

void scores(int point){
    string location;

    for(int i=1;;i++){
        string loc{"Scores/"};
        loc += i+'0';
        loc += ".txt";

        ifstream MyReadFile(loc);

        string text;
        getline(MyReadFile, text);
        MyReadFile.close();

        location=loc;

        if(name_exists(text)){
            break;
        }
        if(string_length(text)==0){
            break;
        }
    }

    ifstream MyReadFile(location);

    string text;
    getline(MyReadFile, text);
    MyReadFile.close();
    point += load_score(text).point;

    ofstream MyFile(location);

    MyFile << '!' << Name;
    MyFile << '@' << point;
    MyFile << '#';

    MyFile.close();
    }

score load_score(string text){
    score load;
    int i=1;
    int a=0;
    
    for(; text[i]!='@'; a++, i++){
        load.name[a]=text[i];
    } load.name[a]=0;

    for(i++; text[i]!='#'; i++){
        load.point += text[i]-'0';
        load.point *= 10;
    } load.point /= 10;

    return load;
}

void leaderboard_print(){
    cursor_to_pos(windows.r_middle-5, windows.c_middle-14);
    change_background_color(0);

    for(int i=13; i; i--){
        if(i==13 || i==1){
            printf(".............................");
            cursor_backward(29);
            cursor_down(1);
        }
        else{
            printf(".                           .");
            cursor_backward(29);
            cursor_down(1);
        }
    }

    score* max_score = new score;
    for(int i=1;; i++){
        string loc{"Scores/"};
        loc += i+'0';
        loc += ".txt";

        ifstream MyReadFile(loc);

        string text;
        getline(MyReadFile, text);
        MyReadFile.close();

        if(string_length(text)==0) break;

        score view = load_score(text);

        if(view.point>max_score[0].point){
            max_score[0].name=view.name;
            max_score[0].point=view.point;
        }
        else if(view.point>max_score[1].point){
            max_score[1].name=view.name;
            max_score[1].point=view.point;
        }
        else if(view.point>max_score[2].point){
            max_score[2].name=view.name;
            max_score[2].point=view.point;
        }
        else if(view.point>max_score[3].point){
            max_score[3].name=view.name;
            max_score[3].point=view.point;
        }
        else if(view.point>max_score[4].point){
            max_score[4].name=view.name;
            max_score[4].point=view.point;
        }
    }

    int r=-2;
    for(int j=0; j<5; j++, r++){
        cursor_to_pos(windows.r_middle+r*2, windows.c_middle-13);
        
        printf("^ ");
        if(string_length(max_score[j].name)!=0) cout<<max_score[j].name;

        printf("  POINT: ");
        printf("%d", max_score[j].point);
    }

    cursor_to_pos(windows.r_middle+r*2, windows.c_middle-13);
    printf(" ^ Back to Menu");
    reset_color();
}

void leaderboard(){
    leaderboard_print();

    cursor_to_pos(windows.r_middle-6, windows.c_middle-13);
    while(1){
        char ch=nb_getch();

        if(ch==10 || ch==13 || ch==' ') break;
    }

    menu();
}
