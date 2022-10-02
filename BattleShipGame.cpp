#include <iostream>
#include <ctime>
#include <vector>
using namespace std;

const int rows = 10, columns = 10;
int PlayerBoard[rows][columns], BotBoard[rows][columns], PlayerViewBoard[rows][columns], BotViewBoard[rows][columns];
int PlayerScore = 0, BotScore = 0; 
vector<vector<int>> BotHits;

void clear(){                                                               // Function which clears all boards
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            PlayerBoard[i][j] = 0;
            BotBoard[i][j] = 0;
            PlayerViewBoard[i][j] = 0;
            BotViewBoard[i][j] = 0;
        }
        cout<<endl;
    }
}

void SetBotShips(){                                                         //  Function which sets up board placing ships at random. 

    for(int i = 0; i < 2; i++){
        int a = rand() % 10;
        int b = rand() % 7;
        for(int i = 0; i < 4; i++){
            BotBoard[a][b + i + 1] = 1;
        }
    }

    for(int i = 0; i < 2; i++){
        int a = rand() % 8;
        int b = rand() % 10;
        for(int i = 0; i < 3; i++){
            BotBoard[a + i + 1][b] = 1;
        }
    }
    
    for(int i = 0; i < 2; i++){
        int a = rand() % 10;
        int b = rand() % 9;
        for(int i = 0; i < 2; i++){
            BotBoard[a][b + i + 1] = 1;
        }
    }

    for(int i = 0; i < 2; i++){
        int a = rand() % 9;
        int b = rand() % 10;
        for(int i = 0; i < 2; i++){
            BotBoard[a + i + 1][b] = 1;
        }
    }

}

void SetPlayerShips(){                                                      //  Function which sets up board placing ships at random. 
    
    for(int i = 0; i < 2; i++){
        int a = rand() % 10;
        int b = rand() % 7;
        for(int i = 0; i < 4; i++){
            PlayerBoard[a][b + i + 1] = 1;
        }
    }

    for(int i = 0; i < 2; i++){
        int a = rand() % 8;
        int b = rand() % 10;
        for(int i = 0; i < 3; i++){
            PlayerBoard[a + i + 1][b] = 1;
        }
    }
    
    for(int i = 0; i < 2; i++){
        int a = rand() % 10;
        int b = rand() % 9;
        for(int i = 0; i < 2; i++){
            PlayerBoard[a][b + i + 1] = 1;
        }
    }

    for(int i = 0; i < 2; i++){
        int a = rand() % 9;
        int b = rand() % 10;
        for(int i = 0; i < 2; i++){
            PlayerBoard[a + i + 1][b] = 1;
        }
    }
}

bool PlayerAttack(int x, int y){                                                    // Function which allows player to attack

    if(BotBoard[x][y] == 1){
        PlayerScore++;
        PlayerViewBoard[x][y] = 1;
        return true;
    }
    return false; 
}

bool BotAttack(int x, int y){                                                       // Function which allows bot to attack

    if(PlayerBoard[x][y] == 1){
        BotScore++;
        BotViewBoard[x][y] = 1;
        BotHits.push_back({x, y});
        return true;
    }
    return false; 
}

void ShowScore(){                                                                   // Function which shows score for player
    cout << "Player Board: " << endl;
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            cout << PlayerViewBoard[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}


bool BotPlays(){                                              //  Function where bot decides where to attack based on previous hits

    if(BotScore == 0){
        int a = rand() % 10;
        int b = rand() % 10;
        return BotAttack(a, b);
    }else{
        int a = rand() % BotHits.size();
        if(BotHits[a][1] + 1 < 10){
            return BotAttack(BotHits[a][0], BotHits[a][1] + 1);
        }
        else if(BotHits[a][1] - 1 < 10){
            return BotAttack(BotHits[a][0], BotHits[a][1] - 1);
        }
        else if(BotHits[a][0] + 1 < 10){
            return BotAttack(BotHits[a][0] + 1, BotHits[a][1]);
        }
        else if(BotHits[a][0] - 1 < 10){
            return BotAttack(BotHits[a][0] - 1, BotHits[a][1]);
        }
        else{
            int r1 = rand() % 10;
            int r2 = rand() % 10;
            return BotAttack(r1, r2);
        }
    }

    return true;
}

int main(){

    srand(time(NULL));
    clear();                                                           

    int x, y;
    string input;


    SetPlayerShips();                                                      
    SetBotShips();

    while(1){

        cout << "Enter Attack Position X: ";
        cin >> input;

        x = input[0] - '0';
        y = input[input.size() - 1] - '0';

        if(PlayerAttack(x, y)){
            cout << "It was a hit." << endl;
        }else{
            cout << "You missed." << endl;
        }
        
        string hitormiss;
        if(BotPlays()){
            hitormiss = "Hit";
        }    
        else{
            hitormiss = "Missed";
        }

        cout << "Bot Attack " << hitormiss << endl;
        cout << endl;
        ShowScore();

        if(PlayerScore == 22){
            cout << "Game Over. Player Won." << endl;
            cout << "Player Score: " << PlayerScore << endl;
            cout << "Bot Score: " << BotScore << endl;
            clear();
            break;
        }

        if(BotScore == 22){
            cout << "Game Over. Bot Won." << endl;
            cout << "Player Score: " << PlayerScore << endl;
            cout << "Bot Score: " << BotScore << endl;
            clear();
            break;
        }
    }
    system("pause");
    return 0; 
}