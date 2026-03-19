#include <iostream>
#include <random>
#include <string>
#include <pstl/unseq_backend_simd.h>

struct Index {
    int y;
    int x;
};

#define TAILLE 7
#define TAILLE_G 5
#define ORIGIN {0,0}
#define END Index{TAILLE-1,TAILLE-1}

Index posRotate = {0,0};
Index posOrigin = {TAILLE-1,TAILLE-1};
Index lab[TAILLE][TAILLE] = {0};
int schemaLab[TAILLE][TAILLE][TAILLE_G][TAILLE_G] = {0};


bool inTab(int size,Index tab[],Index toFind) {
    for (int i = 0; i < size; ++i) {
        if (toFind.x==tab[i].x and tab[i].y==toFind.y) {
            return true;
        }
    }
    return false;
}

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
    float centerY = (posRotate.y+0.5)*TAILLE_G;
    float centerX = (posRotate.x+0.5)*TAILLE_G;
    for (int y = 0; y < TAILLE; y++) {
        for (int i = 0; i < TAILLE_G; i++) {
            for (int x = 0; x < TAILLE; x++) {
                for (int j = 0; j < TAILLE_G; j++) {
                    int rX=(x*TAILLE_G)+j;
                    int rY=(y*TAILLE_G)+i;
                    if (sqrt(pow(rX-centerX,2)+pow(rY-centerY,2))<=7){

                        if (schemaLab[y][x][i][j] == 0) {
                            if (x==END.x and y==END.y)  {
                                std::cout << "\033[34m██\033[0m"<< "";
                            }else {
                                std::cout << "██"<< "";
                            }

                        }else {
                            if (x==posRotate.x and y==posRotate.y) {
                                std::cout << "\033[31m██\033[0m"<< "";
                            }else {
                                std::cout << "  " << "";
                            }
                        }
                    }else {
                        std::cout << "  " << "";
                    }
                }
            }
            std::cout << std::endl;
        }
    }
}

/**
 * fonction transformant mon petit labyrinthe de taille (nombre de col * 3) en (nombre de col * TAILLE_G)
 * cela permet de transformer par exemple mon labyrinthe simple de 15 pixel en un labyrinthe
 * remplissant la matrice et ne laissant pas d'espace vide
 */
void newDimLab() {
    int epaisseur_mur=1;
    if (TAILLE_G>5) {
        epaisseur_mur=2;
    }
    if (TAILLE_G>10) {
        epaisseur_mur=3;
    }
    for (int y = 0; y < TAILLE; y++){
        for (int x = 0; x < TAILLE; x++) {
            for (int j = epaisseur_mur; j < TAILLE_G-(epaisseur_mur); j++){
              for (int k = epaisseur_mur; k < TAILLE_G-(epaisseur_mur); k++) {
                schemaLab[y][x][j][k]=1;
              }
            }
            if (x-1 >= 0 and ( lab[y][x-1].x == x or lab[y][x].x == x-1 )) {
                for (int ep1 = 0; ep1 < epaisseur_mur; ep1++) {
                    for (int ep2 = epaisseur_mur; ep2 < TAILLE_G-epaisseur_mur ; ep2++) {
                        schemaLab[y][x][ep2][ep1]=1;
                    }
                }

            }if (y-1 >= 0 and ( lab[y-1][x].y == y or lab[y][x].y == y-1 )) {
                for (int ep1 = 0; ep1 < epaisseur_mur; ep1++) {//x
                    for (int ep2 = epaisseur_mur; ep2 < TAILLE_G-epaisseur_mur ; ep2++) {
                        schemaLab[y][x][ep1][ep2]=1;
                    }
                }

            }if (x+1 < TAILLE and ( lab[y][x+1].x == x or lab[y][x].x == x+1 )) {
                for (int ep1 = TAILLE_G-epaisseur_mur   ; ep1 < TAILLE_G; ep1++) {
                    for (int ep2 = epaisseur_mur; ep2 < TAILLE_G-epaisseur_mur ; ep2++) {
                        schemaLab[y][x][ep2][ep1]=1;
                    }
                }
            }if (y+1 <TAILLE  and ( lab[y+1][x].y == y or lab[y][x].y == y+1 )) {
                for (int ep1 = TAILLE_G-epaisseur_mur   ; ep1 < TAILLE_G; ep1++) {
                    for (int ep2 = epaisseur_mur; ep2 < TAILLE_G-epaisseur_mur ; ep2++) {
                        schemaLab[y][x][ep1][ep2]=1;
                    }
                }
            }
        }
    }
}

/**
 * Créée la matrice originelle pour créer le labyrinthe
 * technique issu de cette video : https://www.youtube.com/watch?v=zbXKcDVV4G0
 */
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

int main() {
    tabCreation();//initialisation du laby
    for (int tour = 0; tour <= ((TAILLE*TAILLE)*10); tour++) {
        calculVoisin();
    }//shift de l'origine pour créer un labyrinthe aléatoire

    newDimLab();//s

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
        if (input=="z") {
            if (posRotate.y-1>=0
                and !(posRotate.y-1==END.y and posRotate.x==END.x)) {
                posRotate={posRotate.y-1,posRotate.x};
                showLab();
            }
        }
        else if (input=="q") {
            if (posRotate.x-1>=0
                and !(posRotate.y==END.y and posRotate.x-1==END.x)) {
                posRotate={posRotate.y,posRotate.x-1};
                showLab();
            }
        }
        else if (input=="s") {
            if (posRotate.y+1<TAILLE
                and !(posRotate.y+1==END.y and posRotate.x==END.x)) {
                posRotate  ={posRotate.y+1,posRotate.x};
                showLab();
            }
        }
        else if (input=="d") {
            if (posRotate.x+1<TAILLE
                and !(posRotate.y==END.y and posRotate.x+1==END.x))  {
                posRotate={posRotate.y,posRotate.x+1};
                showLab();
            }
        }
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
