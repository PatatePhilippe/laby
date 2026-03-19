#include <iostream>
#include <random>
#include <string>
#include <pstl/unseq_backend_simd.h>

struct Index {
    int y;
    int x;
};

#define TAILLE 7
#define ORIGIN {0,0}
#define END Index{TAILLE-1,TAILLE-1}

int rotate = 2;
Index posOrigin = {TAILLE-1,TAILLE-1};
Index lab[TAILLE][TAILLE] = {0};






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
    std::cout << "\033[34m██\033[0m"<< "";
    std::cout << "██"<< "";
    std::cout << "\033[31m██\033[0m"<< "";
    std::cout << "  " << "";

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
    }
    showLab();
    bool fin = false;
    while (!fin) {
        std::string input;
        std::getline(std::cin, input);
        std::cout << "Tu as tape : " << input << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
        if (posRotate.y-1>=0 and !posRotate.y-1==END.y ) {
            if (input=="z") {
                //avance
                showLab();
            }
            else if (input=="q") {
                //tourne gauche
                showLab();
            }
            else if (input=="d") {
                //tourne droite
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
