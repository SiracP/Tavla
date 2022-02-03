//Siraç Petmezçiler
//1306190011
//Visual Studio 2019

#include <iostream>
#include <vector>
#include <ctime>
#include <string>
#include <fstream>
using namespace std;

vector<string> board(26);
vector <string> broken(2);
vector<int>dices;
bool turn, xDobla = false, yDobla = false, Exit = false;

void appendLogFile(string s) {
    ofstream logFile("Log.txt", ofstream::app);
    logFile << s << endl;
    logFile.close();
}
vector<int> toDice() {
    vector<int> dices1(2);
    vector<int> dices2(4);
    srand(time(NULL));
    int a = rand() % 6 + 1;
    int b = rand() % 6 + 1;

    ofstream logFile("Log.txt", ofstream::app);
    logFile << "Zar Atıldı : ";

    if (a == b) {
        dices2[0] = a;
        dices2[1] = a;
        dices2[2] = a;
        dices2[3] = a;

        for (int i = 0;i < 4;i++) {
            logFile << a ;
            if (i != 3) {
                logFile << " , ";
            }
        }
        logFile << endl;
        logFile.close();
        return dices2;
    }
    else
    {
        dices1[0] = a;
        dices1[1] = b;

        logFile << a << " , " << b << endl;
        logFile.close();
        return dices1;
    }
}
bool startingDice() {
    vector<int>startDices = toDice();

    if (startDices[0] > startDices[1]) {
        cout << " Baslangic Zarlari :  X : " << startDices[0] << "  Y : " << startDices[1] << endl;
        cout << " X ilk basliyor" << endl;
        turn = false;
        appendLogFile("X ilk basliyor");
        cout << "Devam etmek icin 1 i tuslayiniz ";
        string s;
        cin >> s;
        return false;
    }
    else if (startDices[0] < startDices[1]) {
        cout << " Baslangic Zarlari :  X : " << startDices[0] << "  Y : " << startDices[1] << endl;
        cout << " Y ilk basliyor" << endl;
        turn = true;
        appendLogFile("Y ilk basliyor");
        cout << "Devam etmek icin  1 i tuslayiniz ";
        string s;
        cin >> s;
        return false;
    }
    else {
        return true;
    }
}

string adderX(string loc) {
    if (loc == "--") {
        loc = "1X";
    }
    else {
        int x = (int)loc[0];
        x += 1;
        loc[0] = (char)x;
    }
    return loc;
}

string adderY(string loc) {
    if (loc == "--") {
        loc = "1Y";
    }
    else {
        int x = (int)loc[0];
        x += 1;
        loc[0] = (char)x;
    }
    return loc;
}

string subtractor(string loc) {
  
    int x = (int)loc[0];
    x -= 1;
    if (x == 48) {
        loc = "--";
    }
    else {
        loc[0] = (char)x;
    }
    
    return loc;
}

bool degistici(int firstLoc, int dice) {
    int a = 0;
    if (turn == false && xDobla == false) {
        a = 24;
    }
    else if (turn == false && xDobla == true) {
        a = 30;
    }
    else if (turn == true && yDobla == false) {
        a = 1;
    }
    else if (turn == true && yDobla == true) {
        a = -5;
    }
    if(firstLoc + dice <= a && ((board[firstLoc][1] == 'X' || firstLoc == 0 ) && turn == false)){
        if (a == 30 && firstLoc + dice >= 25) {
            board[firstLoc] = subtractor(board[firstLoc]);
            board[25] = adderX(board[25]);
            appendLogFile(to_string(firstLoc) + " konumundan bir tane X taşı alındı");
            appendLogFile(to_string(dice) + " zarı oynandı");
            appendLogFile("Alınan taş kenara konuldu");
            return false;
        }
        else if (board[firstLoc + dice][1] != 'Y' || board[firstLoc + dice] == "1Y") {
            if (firstLoc != 0) {
                board[firstLoc] = subtractor(board[firstLoc]);
                appendLogFile(to_string(firstLoc) + " konumundan bir tane X taşı alındı");
            }
            else {
                broken[0] = subtractor(broken[0]);
                appendLogFile("Kırık bir tane X taşı alındı");
            }

            int asd = firstLoc + dice;
            appendLogFile(to_string(dice) + " zarı oynandı");

            if (board[firstLoc + dice] == "1Y") {
                board[firstLoc + dice] = subtractor(board[firstLoc + dice]);
                broken[1] = adderY(broken[1]);
                appendLogFile(to_string(asd) + " konumundaki Y taşı kırıldı");
            }
            board[firstLoc + dice] = adderX(board[firstLoc + dice]);
            
            appendLogFile(to_string(asd) + " konumuna bir tane X taşı yerleştirildi");
            return false;
        }
        else
        {
            cout << "Gecersiz hamle" << endl;
            return true;
        }
    }
    else if (firstLoc - dice >= a && ((board[firstLoc][1] == 'Y' || firstLoc == 25) && turn == true)) {
        if (a == -5 && firstLoc - dice <= 0) {
            board[firstLoc] = subtractor(board[firstLoc]);
            board[0] = adderY(board[0]);
            appendLogFile(to_string(firstLoc) + " konumundan bir tane Y taşı alındı");
            appendLogFile(to_string(dice) + " zarı oynandı");
            appendLogFile("Alınan taş kenara konuldu");
            return false;
        }
        else if (board[firstLoc - dice][1] != 'X' || board[firstLoc - dice] == "1X") {
            if (firstLoc != 25) {
                board[firstLoc] = subtractor(board[firstLoc]);
                appendLogFile(to_string(firstLoc) + " konumundan bir tane Y taşı alındı");
            }
            else
            {
                broken[1] = subtractor(broken[1]);
                appendLogFile("Kırık bir tane Y taşı alındı");
            }

            int asd = firstLoc - dice;
            appendLogFile(to_string(dice) + " zarı oynandı");

            if (board[firstLoc - dice] == "1X") {
                board[firstLoc - dice] = subtractor(board[firstLoc - dice]);
                broken[0] = adderX(broken[0]);
                appendLogFile(to_string(asd) + " konumundaki X taşı kırıldı");
            }

            board[firstLoc - dice] = adderY(board[firstLoc - dice]);
            
            appendLogFile(to_string(asd) + " konumuna bir tane Y taşı yerleştirildi");
            return false;
        }
        else
        {
            cout << "Gecersiz hamle" << endl;
            return true;
        }
        
    }
    else {
        cout << "Gecersiz hamle" << endl;
        return true;
    }
    
}

bool Move() {
    Exit = false;
    int loc,dice,a;

    bool kont = true;
    while (kont == true)
    {
        cout << "Cikis yapmak icin 0 tuslayiniz " << endl;
        cout << "Pas gecmek icin 99 tuslayiniz " << endl;
        cout << "Hangi konumdaki tasinizi oynamak istersiniz : ";
        cin >> loc;
        if (loc == 99) {
            appendLogFile("Tur pas geçildi");
            dices.clear();
            return false;
        }
        else if (loc > 0 && loc < 25 && ((board[loc][1] == 'X' && turn == false) || (board[loc][1] == 'Y' && turn == true)) ) {
            kont = false;
        }
        else if (loc == 0) {
            Exit = true;
            return false;
        }
        else {
            cout << "Belirtilen konumda tasiniz bulunmamaktadir" << endl;
        }
    }
    
    cout << endl;

    kont = true;
    while (kont == true) {
        cout << "Hangi zarinizi oynamak istersiniz? " << endl;
        for (int i = 0; i < dices.size();i++) {
            cout << i + 1 << " - " << dices[i] << endl;
        }
        cout << endl << "Seciminiz :";
        cin >> a;
        if (a > dices.size() || a < 1) {
            cout << "Zar mecvut degil" << endl;
        }
        else {
            dice = dices[a - 1];
            kont = false;
        }
    }
    bool kontrol = degistici(loc, dice);
    if (kontrol == false) {
        dices.erase(dices.begin() + a - 1);
    }
    return kontrol;
}


int brokenCheck() {

    bool kontrol = false;
    if (turn == false && broken[0] != "--") {
        Exit = false;
        cout << "Kirik Pulunuz Var" << endl;
        for (int i = 0;i < dices.size();i++) {
            if ((board[dices[i]][1] != 'Y') || board[dices[i]] == "1Y") {
                kontrol = true;
            }
        }
        if (kontrol == true) {
            bool kontrol2 = true;
            int a, dice;
            while (kontrol2 == true){
                bool kont = true;
                while (kont == true) {
                    cout << "Hangi zarinizi oynamak istersiniz? " << endl;
                    cout << "0 - Exit" << endl;
                    for (int i = 0; i < dices.size();i++) {
                        cout << i + 1 << " - " << dices[i] << endl;
                    }
                    cout << endl << "Seciminiz :";
                    cin >> a;
                    if (a == 0) {
                        system("CLS");
                        Exit = true;
                        return 4;
                    }
                    if (a > dices.size() || a < 1) {
                        cout << "Zar mevcut degil" << endl;
                    }
                    else {
                        dice = dices[a - 1];
                        kont = false;
                    }
                }
                kontrol2 = degistici(0, dice);
                if (kontrol2 == false) {
                    dices.erase(dices.begin() + a - 1);
                    xDobla = false;
                    return 1;
                }
            }
        }
        else
        {
            cout << "Gecerli hamle yok turu bitirmek icin 1 i tuslayiniz ";
            string x;
            cin >> x;
            return 3;
        }
    }
    else if (turn == true && broken[1] != "--") {
        Exit = false;
        cout << "Kirik Pulunuz Var" << endl;
        for (int i = 0;i < dices.size();i++) {
            if ((board[25 - dices[i]][1] != 'X') || board[25 - dices[i]] == "1X") {
                kontrol = true;
            }
        }
        if (kontrol == true) {
            bool kontrol2 = true;
            int a, dice;
            while (kontrol2 == true) {
                bool kont = true;
                while (kont == true) {
                    cout << "Hangi zarinizi oynamak istersiniz? " << endl;
                    cout << "0 - Exit" << endl;
                    for (int i = 0; i < dices.size();i++) {
                        cout << i + 1 << " - " << dices[i] << endl;
                    }
                    cout << endl << "Seciminiz :";
                    cin >> a;
                    if (a == 0) {
                        system("CLS");
                        Exit = true;
                        return 4;
                    }
                    if (a > dices.size() || a < 1) {
                        cout << "Zar mevcut degil" << endl;
                    }
                    else {
                        dice = dices[a - 1];
                        kont = false;
                    }
                }
                kontrol2 = degistici(25, dice);
                if (kontrol2 == false) {
                    dices.erase(dices.begin() + a - 1);
                    yDobla = false;
                    return 1;
                }
            }
        }
        else
        {
            cout << "Gecerli hamle yok turu bitirmek icin 1 i tuslayiniz ";
            string x;
            cin >> x;
            return 3;
        }
    }
    else {
        return 2;
    }
}
void turnChange() {
    if (turn == true) {
        turn = false;
        system("CLS");
        cout << " X'in turu" << endl;
        appendLogFile("Tur sona erdi");
        appendLogFile("X'in turu");
    }
    else {
        turn = true;
        system("CLS");
        cout << " Y'nin turu" << endl;
        appendLogFile("Tur sona erdi");
        appendLogFile("Y'nin turu");
    }
}

void openCheck() {
    int toplam = 0;
    for (int i = 1;i <= 6; i++) {
        if (turn == true && board[i][1] == 'Y') {
            toplam += (int)board[i][0] - 48;
        }
        else if (turn == false && board[25 - i][1] == 'X') {
            toplam += (int)board[25 - i][0] - 48;
        }
    }
    if (turn == false) {
        if (board[25][0] == '-' && toplam == 15) {
            xDobla = true;
            appendLogFile("X toplamaya başladı");
        }
        else if (toplam == (15 - ((int)board[25][0] - 48))) {
            xDobla = true;
            appendLogFile("X toplamaya başladı");
        }        
    }
    else if (turn == true)
    {
        if (board[0][0] == '-' && toplam == 15) {
            yDobla = true;
            appendLogFile("Y toplamaya başladı");
        }
        else if (toplam == (15 - ((int)board[0][0] - 48))) {
            yDobla = true;
            appendLogFile("Y toplamaya başladı");
        }
    }

}
bool finishCheck() {
    int toplam = 0;
    for (int i = 1;i <= 24; i++) {
        if (turn == true && board[i][1] == 'Y') {
            toplam += (int)board[i][0] - 48;
        }
        else if (turn == false && board[25 - i][1] == 'X') {
            toplam += (int)board[i][0] - 48;
        }
    }
    if (toplam == 0 && turn == false && (int)board[25][0] == 63){
        system("CLS");
        cout << "X kazandi " << endl;
        appendLogFile("X kazandı");
        ofstream saveFile("Save.txt");
        saveFile << "OyunBitti";
        return true;
    }
    else if (toplam == 0 && turn == true && (int)board[0][0] == 63) {
        system("CLS");
        cout << "Y kazandi " << endl;
        appendLogFile("Y kazandı");
        ofstream saveFile("Save.txt");
        saveFile << "OyunBitti";
        return true;
    }
    else {
        return false;
    }
}

void printBoard() {
    cout << "  1    2    3    4    5    6      7    8    9    10   11   12  " << endl;
    cout << "---------------------------------------------------------------" << endl << "| ";
    for (int i = 1; i < 13;i++) {
        cout << board[i] << " | ";
        if (i == 6) {
            cout << "| ";
        }
    }
    cout << endl << "|";
    for (int i = 1; i < 13;i++) {
        cout << "    |";
        if (i == 6) {
            cout << " |";
        }
    }
    cout << endl << "|";
    cout << "-------------------------------------------------------------| ";
    cout << endl << "|     Kirik X Pullari    | " << broken[0] << " | | " << broken[1] << " |     Kirik Y Pullari    |" << endl << "|";
    cout << "-------------------------------------------------------------| ";
    cout << endl << "|";
    for (int i = 1; i < 13;i++) {
        cout << "    |";
        if (i == 6) {
            cout << " |";
        }
    }
    cout << endl << "| ";
    for (int i = 24;i > 12;i--) {
        cout << board[i] << " | ";
        if (i == 19) {
            cout << "| ";
        }
    }
    cout << endl << "---------------------------------------------------------------" << endl;
    cout << "  24   23   22   21   20   19     18   17   16   15   14   13  " << endl;
 }
void printBoardFile() {
    ofstream boardFile("Table.txt");
    boardFile << "  1    2    3    4    5    6      7    8    9    10   11   12  " << endl;
    boardFile << "---------------------------------------------------------------" << endl << "| ";
    for (int i = 1; i < 13;i++) {
        boardFile << board[i] << " | ";
        if (i == 6) {
            boardFile << "| ";
        }
    }
    boardFile << endl << "|";
    for (int i = 1; i < 13;i++) {
        boardFile << "    |";
        if (i == 6) {
            boardFile << " |";
        }
    }
    boardFile << endl << "|";
    boardFile << "-------------------------------------------------------------| ";
    boardFile << endl << "|     Kirik X Pullari    | " << broken[0] << " | | " << broken[1] << " |     Kirik Y Pullari    |" << endl << "|";
    boardFile << "-------------------------------------------------------------| ";
    boardFile << endl << "|";
    for (int i = 1; i < 13;i++) {
        boardFile << "    |";
        if (i == 6) {
            boardFile << " |";
        }
    }
    boardFile << endl << "| ";
    for (int i = 24;i > 12;i--) {
        boardFile << board[i] << " | ";
        if (i == 19) {
            boardFile << "| ";
        }
    }
    boardFile << endl << "---------------------------------------------------------------" << endl;
    boardFile << "  24   23   22   21   20   19     18   17   16   15   14   13  " << endl << endl;
    boardFile << "Mevcut zarlar : ";
    for (int i = 0; i < dices.size();i++) {
        boardFile << dices[i] << " , ";
    }
    boardFile.close();
}
void printSaveFile() {
    ofstream saveFile("Save.txt");

    saveFile << "Top|";
    for (int i = 0; i < 13;i++) {
        saveFile << board[i];
        if (i != 12) {
            saveFile << "|";
        }
    }
    saveFile << endl << "Broken|" << broken[0] << "|" << broken[1] << endl;
    saveFile << "Bottom|";
    for (int i = 25;i > 12;i--) {
        saveFile << board[i];
        if (i != 13) {
            saveFile << "|";
        }
    }
    saveFile << endl;
    saveFile << "Dices|";
    for (int i = 0; i < dices.size();i++) {
        saveFile << dices[i];
        if (i != dices.size() - 1) {
            saveFile << "|";
        }
    }
    saveFile << endl;
    if (turn == false) {
        saveFile << "Turn|X" << endl;
    }
    else
    {
        saveFile << "Turn|Y" << endl;
    }
    if (xDobla == true) {
        saveFile << "xDobla|1" << endl;
    }
    else
    {
        saveFile << "xDobla|0" << endl;
    }
    if (yDobla == true) {
        saveFile << "yDobla|1" << endl;
    }
    else
    {
        saveFile << "yDobla|0" << endl;
    }
    saveFile.close();
}
vector<string> split(string line) {
    vector<string> words;
    string s="";
    for (int i = 0;i < line.size();i++) {
        if(line[i] != '|'){
            s += line[i];
            if (i == line.size()-1) {
                words.push_back(s);
            }
        }
        else
        {
            words.push_back(s);
            s = "";
        }
    }
    return words;
}
void newGame() {
    for (int i = 0; i < 26;i++) {
        board[i] = "--"; 
    }
    board[1] = "2X";
    board[6] = "5Y";
    board[8] = "3Y";
    board[12] = "5X";
    board[13] = "5Y";
    board[17] = "3X";
    board[19] = "5X";
    board[24] = "2Y";
    broken[0] = "--";
    broken[1] = "--";

    bool starting = true;
    while (starting == true) {
        starting = startingDice();
    }
    printBoardFile();
    printSaveFile();
    ofstream logFile("Log.txt");
    logFile << "Yeni Oyun oluşturuldu" << endl;
    logFile.close();
 }

bool Continue() {
    ifstream saveFile("Save.txt");
    string line = "";
    if (saveFile.is_open()) {
        while (getline(saveFile, line)) {
            if (line == "OyunBitti") {
                saveFile.close();
                return false;
            }
            else {
                vector<string> words = split(line);
                if (words[0] == "Top") {
                    for (int i = 0;i < 13;i++) {
                        board[i] = words[i + 1];
                    }
                }
                else if (words[0] == "Broken") {
                    for (int i = 0;i < 2;i++) {
                        broken[i] = words[i + 1];
                    }
                }
                else if (words[0] == "Bottom") {
                    for (int i = 25;i > 12;i--) {
                        board[i] = words[25 - i + 1];
                    }
                }
                else if (words[0] == "Dices") {
                    words.erase(words.begin());
                    int a = words.size();
                    vector<int> z(a);
                    for (int i = 0; i < words.size();i++) {
                        z[i] = stoi(words[i]);
                    }
                    dices = z;
                }
                else if (words[0] == "Turn") {
                    if (words[1] == "X") {
                        turn = false;
                    }
                    else if (words[1] == "Y") {
                        turn = true;
                    }
                }
                else if (words[0] == "xDobla") {
                    if (words[1] == "1") {
                        xDobla = true;
                    }
                }
                else if (words[0] == "yDobla") {
                    if (words[1] == "1") {
                        yDobla = true;
                    }
                }
            } 
        }
        saveFile.close();
    }
    return true;
}
bool play() {
    printBoardFile();
    printSaveFile();

    cout << endl;

    while (dices.size() != 0) {
        cout << endl << "Zarlariniz ";
        for (int i = 0; i < dices.size();i++) {
            cout << dices[i];
            if (i != dices.size() - 1) {
                cout << " , ";
            }
        }
        cout << endl;
        int knt = brokenCheck();
        if (knt == 1) {
            printBoard();
            printBoardFile();
            printSaveFile();
        }
        else if (knt == 2) {
            break;
        }
        else if (knt == 3) {
            dices.clear();
            break;
        }
        else if (knt == 4 && Exit == true) {
            return false;
        }
    }

    while (dices.size() != 0)
    {
        system("CLS");
        if (turn == true) {
            cout << " Y'nin turu" << endl;
        }
        else {
            cout << " X'in turu" << endl;
        }
        printBoard();
        cout << endl << "Zarlariniz ";
        for (int i = 0; i < dices.size();i++) {
            cout << dices[i];
            if (i != dices.size() - 1) {
                cout << " , ";
            }
        }
        cout << endl;
        openCheck();

        if ((xDobla == true && turn == false) || (yDobla == true && turn == true)) {
            bool kontrol = true;
            while (kontrol == true) {
                kontrol = Move();
            }
            cout << endl;
            printBoardFile();
            printSaveFile();
            printBoard();
            cout << endl;
        }
        else
        {
            bool kontrol = true;
            while (kontrol == true) {
                kontrol = Move();
            }
            cout << endl;
            printBoardFile();
            printSaveFile();
            printBoard();
            cout << endl;
        }
        bool check = false;
        check = finishCheck();
        if (check == true) {
            return false;
        }
        if (Exit == true) { 
            system("CLS");
            return false;
        }
    }

    turnChange();
    printBoard();
    return true;
}
int main()
{
    while (true)
    {
        int a;
        cout << "Tavla Oyunu" << endl << "1 - Kayitli Oyun" << endl << "2 - Yeni Oyun" << endl << "3 - Cikis" << endl << "Seciminiz :";
        cin >> a;
        if (a == 1) {
            system("CLS");
            bool durum = Continue();
            if (durum) {
                if (turn == true) {

                    cout << " Y'nin turu" << endl;
                }
                else {

                    cout << " X'in turu" << endl;
                }
                printBoard();
                bool kontrol = true;
                while (kontrol == true) {
                    kontrol = play();
                    if (kontrol == true) {
                        dices = toDice();
                    }
                }
            }
            else {
                cout << "Kayitli oyun bulunmamaktadir." << endl;
            }
        }
        else if (a == 2) {

            system("CLS");

            newGame();


            printBoard();

            bool kontrol = true;
            while (kontrol == true) {
                dices = toDice();
                kontrol = play();
            }
        }
        else if (a == 3) {
            return 0;
        }
    }
 }