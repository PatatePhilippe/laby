
 
#include <DFRobot_RGBMatrix.h>

#define OE   	9
#define LAT 	10
#define CLK 	11
#define A   	A0
#define B   	A1
#define C   	A2
#define D   	A3
#define E   	A4
#define WIDTH 64
#define _HIGH	64

DFRobot_RGBMatrix matrix(A, B, C, D, E, CLK, LAT, OE, false, WIDTH, _HIGH);



#define TAILLE 5
#define TAILLE_G 5

struct Index {
    int y;
    int x;
};
Index posOrigin = {4,4};

// 0 = gauche, 1 = haut, 2 = droite, 3 = bas
void calculVoisin(Index lab[TAILLE][TAILLE]){
    bool voisin[4]={false,false,false,false};
    int cptVoisinValide=0;
    if (posOrigin.x-1 >= 0) {
        cptVoisinValide++;
        voisin[0] = true;
    }if (posOrigin.y-1 >= 0) {
        cptVoisinValide++;
        voisin[1] = true;
    }if (posOrigin.x+1 < 5) {
        cptVoisinValide++;
        voisin[2] = true;
    }if (posOrigin.y+1 < 5) {
        cptVoisinValide++;
        voisin[3] = true;
    }

    
    int randomNum = random(1,cptVoisinValide+1);;
    //std::cout << randomNum << std::endl;
    int cptVTrue = 0;
    for(int i = 0; i < 4; i++) {
        if (voisin[i]) {
            cptVTrue++;
        }
        if (cptVTrue == randomNum) {
            Index newOrigin = {-1,-1};
            //std::cout << posOrigin.x << posOrigin.y << std::endl;
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
            // i = direction


            return;
        }
    }
    return ;
}

void affichageLab(Index lab[TAILLE][TAILLE]) {
    int schemaLab[TAILLE][TAILLE][TAILLE_G][TAILLE_G] = {};
    bool voisin[5][5][4]={};
    int epaisseur_mur=1;
    if TAILLE_G>5:
      epaisseur_mur=2
    for (int y = 0; y < TAILLE; y++){
        for (int x = 0; x < TAILLE; x++) {
            for (int j = 0; j < TAILLE_G-2; j++){
              for (int k = 0; k < TAILLE_G-2; k++) {
                schemaLab[y][x][1+j][1+k]=1;
              }
            }
            if (x-1 >= 0 and ( lab[y][x-1].x == x or lab[y][x].x == x-1 )) {// si je suis lié le sommet de gauche
                schemaLab[y][x][(TAILLE_G-1)/2][0]=1;

            }if (y-1 >= 0 and ( lab[y-1][x].y == y or lab[y][x].y == y-1 )) {
                schemaLab[y][x][0][(TAILLE_G-1)/2]=1;

            }if (x+1 < 5 and ( lab[y][x+1].x == x or lab[y][x].x == x+1 )) {
                schemaLab[y][x][(TAILLE_G-1)/2][TAILLE_G-1]=1;

            }if (y+1 <5  and ( lab[y+1][x].y == y or lab[y][x].y == y+1 )){
                schemaLab[y][x][TAILLE_G-1][(TAILLE_G-1)/2]=1;
            }
        }
    }
                      for (int ep1 = 0; ep1 < epaisseur_mur; ep1++) {
                        for (int ep2 = 0; ep2 < TAILLE_G-(epaisseur_mur*2) ; ep2++) {
    for (int y = 0; y < TAILLE; y++) {
        for (int i = 0; i < TAILLE_G; i++) {
            for (int x = 0; x < TAILLE; x++) {
                for (int j = 0; j < TAILLE_G; j++) {
                    if (schemaLab[y][x][i][j] == 0) {
                        matrix.drawPixel((y*TAILLE_G)+i, (x*TAILLE_G)+j, matrix.Color333(7, 7, 7)); 
                        //std::cout << "■ " << " ";
                    }else {
                        matrix.drawPixel((y*TAILLE_G)+i, (x*TAILLE_G)+j, matrix.Color333(0, 0, 0)); 
                        //std::cout << "  " << " ";
                    }
                }
                //std::cout << "  ";
            }
            //std::cout << std::endl;
        }
        //std::cout << std::endl;
    }
}


int indexToInt(int x,int y) {
    return x + (y*TAILLE) +1;
}
Index intToIndex(int index) {
    return { ((index-1)%TAILLE), ((index-1)/TAILLE)};
}







Index lab[TAILLE][TAILLE] = {
    {{0,1},{0,2},{0,3},{0,4},{1,4}},
    {{1,1},{1,2},{1,3},{1,4},{2,4}},
    {{2,1},{2,2},{2,3},{2,4},{3,4}},
    {{3,1},{3,2},{3,3},{3,4},{4,4}},
    {{4,1},{4,2},{4,3},{4,4},{-1,-1}}
};


void setup() {

  matrix.begin();
  
  // draw a pixel in solid white
  matrix.drawPixel(0, 0, matrix.Color333(7, 7, 7)); 
  delay(500);

  // fix the screen with green
  matrix.fillRect(0, 0, matrix.width(), matrix.height(), matrix.Color333(3, 3, 3));
  delay(500);

  // draw a box in yellow
  matrix.drawRect(0, 0, matrix.width(), matrix.height(), matrix.Color333(2, 2, 2));
  delay(500);
  
  // draw an 'X' in red
  matrix.drawLine(0, 0, matrix.width()-1, matrix.height()-1, matrix.Color333(7, 0, 0));
  matrix.drawLine(matrix.width()-1, 0, 0, matrix.height()-1, matrix.Color333(7, 0, 0));
  delay(500);
  
  // draw a blue circle
  //matrix.drawCircle(10, 10, 10, matrix.Color333(0, 0, 7));
  delay(500);
  
  // fill a violet circle
  //matrix.fillCircle(40, 21, 10, matrix.Color333(7, 0, 7));
  delay(500);
  
  // fill the screen with 'black'
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  int shiftPoint=25;
  for (int tour = 0; tour <= ((TAILLE*TAILLE)*10); tour++) {
      calculVoisin(lab);
  }

  affichageLab(lab);
  
}

void loop() {
  // do nothing
}


// Input a value 0 to 24 to get a color value.
// The colours are a transition r - g - b - back to r.