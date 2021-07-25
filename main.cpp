#include <iostream>
//#include <vector>
//#include <string>
using namespace std;

void initPole(char field[][10]){
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            field[i][j] = '.';
        }
    }

}

void outPole(char field[][10]){
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            cout << field[i][j] << " ";
        }
        cout << endl;
    }
}

void outTwoPole(char field01[][10], char field02[][10]){
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            cout << field01[i][j] << " ";
        }
        cout << " | ";
        for(int j = 0; j < 10; j++){
            cout << field02[i][j] << " ";
        }
        cout << endl;
    }
}

bool inputShip(char field[][10], int shipLength){
    int x1; int y1; int x2; int y2;
    cout << "Input please " << shipLength << "-piece ship" << endl;
    cin >> x1 >> y1 >> x2 >> y2;

    if((x1!=x2)&&(y1!=y2)){
        cout << "Invalid input. Diagonal ship!" << endl;
        return false;
    } else if((x1 < 0)||(x2 >= 10)||(y1 < 0)||(y2 >= 10)) {
        cout << "Invalid input. Ship out of border!" << endl;
        return false;
    } else if((abs(y2 - y1) + abs(x2 - x1) + 1) != shipLength){
        cout << "Invalid input. Length is not match!" << endl;
        return false;
    } else {
        bool intersect = false;
        for (int i = y1; i <= y2; i++) {
            for (int j = x1; j <= x2; j++) {
                if(field[i][j] == 'H') intersect = true;
            }
        }
        if(intersect) {
            cout << "Invalid input. Ships intersects!" << endl;
            return false;
        } else {
            for (int i = y1; i <= y2; i++) {
                for (int j = x1; j <= x2; j++) {
                    field[i][j] = 'H';
                }
            }
        }
    }
    return true;
}

void inputShips(char field[][10]){
    for(int sl = 1; sl <=4; sl++){
        for(int ns = 4; ns >= sl; ns--) {
            bool inputed = false;
            while(!inputed){
                inputed = inputShip(field, sl);
            }
            outPole(field);

        }
    }

}
bool shot(char field[][10]){
    int x,y;
    cout << "Input coordinates of shot" << endl;

    bool suitShot = false;
    while(!suitShot){
        cin >> x >> y;
        suitShot = (x >= 0)&&(x <10)&&(y >= 0)&&(y < 10);
        if(!suitShot) cout << "Shout out of range. Try again!" << endl;
    }
    if (field[y][x] == 'H'){
        field[y][x] = 'X';
        return true;
    } else {
        field[y][x] = '0';
        return false;
    }

}

bool checkField(char field[][10]){
    for(int i = 0; i <10; i++){
        for(int j = 0; j < 10; j++){
            if(field[i][j] =='H') return false;
        }
    }
    return true;
}

void battle(char field01[][10], char field02[][10]){
    bool player1Win = false;
    bool player2Win = false;
    while((!player1Win)&&(!player2Win)){
        cout << "Player1!" << endl;
        if (shot(field02)){
            cout <<"Hit!" <<endl;
        } else cout << "Miss" << endl;
        outTwoPole(field01,field02);
        player1Win = checkField(field02);
        if(player1Win){
            cout << "Player1 won!" << endl;
        } else {
            cout << "Player2!" << endl;
            if (shot(field01)){
                cout <<"Hit!" <<endl;
            } else cout << "Miss" << endl;
            outTwoPole(field01,field02);
            player2Win = checkField(field01);
            if(player2Win) cout << "Player2 won!";
        }

    }
    cout << "Battle is finished!" << endl;
}

int main() {
    char field1[10][10];
    char field2[10][10];

    initPole(field1);
    initPole(field2);

    outTwoPole(field1, field2);
    cout << endl;

    cout << "Player 1!. Input your ships!" << endl;
    inputShips(field1);
    cout << "Player 2!. Input your ships!" << endl;
    inputShips(field2);
    cout << "The battle has begun!" << endl;
    battle(field1,field2);
    cout << "Good bye!" << endl;

    return 0;
}
