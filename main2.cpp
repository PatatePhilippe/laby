#include <iostream>
#include <random>
#include <string>

struct Index {
    int y;
    int x;
};

#define TAILLE 12
#define TAILLE_G 3
#define ORIGIN {0,0}
#define END Index{TAILLE-1,TAILLE-1}

Index posPlayer = {0,0};
Index posRotate = {0,0};
Index posOrigin = {TAILLE-1,TAILLE-1};
Index lab[TAILLE][TAILLE] = {0};
int schemaLab[TAILLE][TAILLE][TAILLE_G][TAILLE_G] = {0};

// 0 = gauche, 1 = haut, 2 = droite, 3 = bas
void calculVoisin(){
    bool voisin[4]={false,false,false,false};
    int cptVoisinValide=0;
    if (posOrigin.x-1 >= 0) {
        cptVoisinValide++;
        voisin[0] = true;
    }if (posOrigin.y-1 >= 0) {
        cptVoisinValide++;
        voisin[1] = true;
    }if (posOrigin.x+1 < TAILLE) {
        cptVoisinValide++;
        voisin[2] = true;
    }if (posOrigin.y+1 < TAILLE) {
        cptVoisinValide++;
        voisin[3] = true;
    }

    std::random_device rd;              // graine aléatoire
    std::mt19937 gen(rd());             // générateur Mersenne Twister
    std::uniform_int_distribution<> dis(1, cptVoisinValide); // intervalle [1,10]

    int randomNum = dis(gen);;

    //int randomNum = random(1,cptVoisinValide+1);;
    //std::cout << randomNum << std::endl;
    int cptVTrue = 0;
    for(int i = 0; i < 4; i++) {
        if (voisin[i]) {
            cptVTrue++;
        }
        if (cptVTrue == randomNum) {
            Index newOrigin = {-1,-1};
            switch (i) {

                case 0:
                    newOrigin = {posOrigin.y, posOrigin.x-1};
                    break;
                case 1:
                    newOrigin = {posOrigin.y-1, posOrigin.x};
                    break;
                case 2:
                    newOrigin = {posOrigin.y, posOrigin.x+1};
                    break;
                case 3:
                    newOrigin = {posOrigin.y+1, posOrigin.x};
                    break;
            }
            lab[posOrigin.y][posOrigin.x]={newOrigin.y,newOrigin.x};//je fais que mon ancienne origine pointe vers la nouvelle
            posOrigin = {newOrigin.y,newOrigin.x}; // et je passe mon pointer sur le nouveau sommet
            lab[posOrigin.y][posOrigin.x]={-1,-1};
            break;
        }

    }
}


void showLab() {
    for (int y = 0; y < TAILLE; y++) {
        for (int i = 0; i < TAILLE_G; i++) {
            for (int x = 0; x < TAILLE; x++) {
                for (int j = 0; j < TAILLE_G; j++) {
                    if (schemaLab[y][x][i][j] == 0) {
                        if (x==END.x and y==END.y)  {
                            std::cout << "\033[34m██\033[0m"<< "";
                        }else if (x==posRotate.x and y==posRotate.y) {
                            std::cout << "\033[31m██\033[0m"<< "";
                        }else {
                            std::cout << "██"<< "";
                        }
                        //matrix.drawPixel((y*TAILLE_G)+i, (x*TAILLE_G)+j, matrix.Color333(7, 7, 7));
                    }else {
                        if (x==posPlayer.x and y==posPlayer.y and i!=0 and i!=TAILLE_G-1 and j!=0 and j!=TAILLE_G-1 ) {
                            std::cout << "\033[36m██\033[0m" << "";
                        }else {
                            //matrix.drawPixel((y*TAILLE_G)+i, (x*TAILLE_G)+j, matrix.Color333(0, 0, 0));
                            std::cout << "  " << "";
                        }
                    }
                }
                std::cout << "  ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}

void newDimLab() {
    int epaisseur_mur=1;
    if (TAILLE_G>5) {
        epaisseur_mur=2;
    }
    if (TAILLE_G>10) {
        epaisseur_mur=3;
    }
    showLab();
    for (int y = 0; y < TAILLE; y++){
        for (int x = 0; x < TAILLE; x++) {
            for (int j = epaisseur_mur; j < TAILLE_G-(epaisseur_mur); j++){
              for (int k = epaisseur_mur; k < TAILLE_G-(epaisseur_mur); k++) {
                schemaLab[y][x][j][k]=1;
              }
            }
            if (x-1 >= 0 and ( lab[y][x-1].x == x or lab[y][x].x == x-1 )) {// si je suis lié le sommet de gauche
                for (int ep1 = 0; ep1 < epaisseur_mur; ep1++) {//x
                    for (int ep2 = epaisseur_mur; ep2 < TAILLE_G-epaisseur_mur ; ep2++) {//y
                        schemaLab[y][x][ep2][ep1]=1;
                    }
                }

            }if (y-1 >= 0 and ( lab[y-1][x].y == y or lab[y][x].y == y-1 )) {
                for (int ep1 = 0; ep1 < epaisseur_mur; ep1++) {//x
                    for (int ep2 = epaisseur_mur; ep2 < TAILLE_G-epaisseur_mur ; ep2++) {//y
                        schemaLab[y][x][ep1][ep2]=1;
                    }
                }

            }if (x+1 < TAILLE and ( lab[y][x+1].x == x or lab[y][x].x == x+1 )) {
                for (int ep1 = TAILLE_G-epaisseur_mur   ; ep1 < TAILLE_G; ep1++) {//x
                    for (int ep2 = epaisseur_mur; ep2 < TAILLE_G-epaisseur_mur ; ep2++) {//y
                        schemaLab[y][x][ep2][ep1]=1;
                    }
                }
            }if (y+1 <TAILLE  and ( lab[y+1][x].y == y or lab[y][x].y == y+1 )) {
                for (int ep1 = TAILLE_G-epaisseur_mur   ; ep1 < TAILLE_G; ep1++) {//x
                    for (int ep2 = epaisseur_mur; ep2 < TAILLE_G-epaisseur_mur ; ep2++) {//y
                        schemaLab[y][x][ep1][ep2]=1;
                    }
                }
            }
        }
    }
}



void rotateMatrix(int x,int y) {
    int nLab[TAILLE_G][TAILLE_G]={0};
    for (int y2 = 0; y2 < TAILLE_G; y2++) {
        for (int x2 = 0; x2 < TAILLE_G; x2++) {
            nLab[x2][y2]=schemaLab[y][x][TAILLE_G-1-y2][x2];
        }
    }
    for (int y2 = 0; y2 < TAILLE_G; y2++) {
        for (int x2 = 0; x2 < TAILLE_G; x2++) {
            schemaLab[y][x][y2][x2]=nLab[y2][x2];
        }
    }
}

void tabCreation() {
    lab[TAILLE-1][TAILLE-1]={-1,-1};
    for (int y = 0; y < TAILLE; y++) {
        for (int x = 0; x < TAILLE-1; x++) {
            lab[y][x]={y,x+1};
        }
    }
    for (int y = 0; y < TAILLE-1; y++) {
        lab[y][TAILLE-1]={y+1,TAILLE-1};
    }
}

void rotateAllPieces(){
    std::random_device rd;              // graine aléatoire
    std::mt19937 gen(rd());             // générateur Mersenne Twister
    std::uniform_int_distribution<> dis(0, 3);
    for (int y = 0; y < TAILLE; y++) {
        for (int x = 0; x < TAILLE; x++) {
            int randomNum = dis(gen);
            for (int r = 0; r < randomNum ; r++) {
                rotateMatrix(x,y);
            }
        }
    }
}
    //int randomNum = random(1,cptVoisinValide+1);;
    //std::cout << randomNum << std::endl;




int main() {
    tabCreation();
    for (int tour = 0; tour <= ((TAILLE*TAILLE)*10); tour++) {
        calculVoisin();
    }
    newDimLab();
    rotateAllPieces();
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    showLab();
    bool fin = false;
    while (!fin) {
        std::string input;
        std::getline(std::cin, input);
        std::cout << "Tu as tape : " << input << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
        if (input=="r") {//faudrait mettre un ptit switch
            rotateMatrix(posRotate.x,posRotate.y);
            showLab();
        }
        else if (input=="z") {
            if (posRotate.y-1>=0) {
                posRotate={posRotate.y-1,posRotate.x};
                showLab();
            }
        }
        else if (input=="q") {
            if (posRotate.x-1>=0) {
                posRotate={posRotate.y,posRotate.x-1};
                showLab();
            }
        }
        else if (input=="s") {
            if (posRotate.y+1<TAILLE) {
                posRotate  ={posRotate.y+1,posRotate.x};
                showLab();
            }
        }
        else if (input=="d") {
            if (posRotate.x+1<TAILLE) {
                posRotate={posRotate.y,posRotate.x+1};
                showLab();
            }
        }



        else if (input=="u") {
            if (posPlayer.y-1>=0) {
                posPlayer={posPlayer.y-1,posPlayer.x};
                showLab();
            }
        }
        else if (input=="h") {
            if (posPlayer.x-1>=0) {
                posPlayer={posPlayer.y,posPlayer.x-1};
                showLab();
            }
        }
        else if (input=="j") {
            if (posPlayer.y+1<TAILLE) {
                posPlayer={posPlayer.y+1,posPlayer.x};
                showLab();
            }
        }
        else if (input=="k") {
            if (posPlayer.x+1<TAILLE) {
                posPlayer={posPlayer.y,posPlayer.x+1};
                showLab();
            }
        }
        if (END.x==posPlayer.x and END.y==posPlayer.y) {
            fin=true;
        }
        //if pour Z,D,Q,S et U,H,J,K
    }
    std::cout << "---------------------------------" << std::endl;
    std::cout << "---███████----██-----███----██---" << std::endl;
    std::cout << "---██----------------████---██---" << std::endl;
    std::cout << "---██████-----██-----██-██--██---" << std::endl;
    std::cout << "---██---------██-----██--██-██---" << std::endl;
    std::cout << "---██---------██-----██---████---" << std::endl;
    std::cout << "---██---------██-----██----███---" << std::endl;
    std::cout << "---------------------------------" << std::endl;
}
