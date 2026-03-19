//
// Created by pat on 12/03/2026.
//

#include "labV2_3D.h"

#include <chrono>
#include <thread>
#include <unistd.h>

#include "testNewLab.h"
int vitesse=100;
int pos=0;
int angleVu=1;
int tailleLaby=5;
labV2_3D newLab=labV2_3D();

void rotate(){
    angleVu=(((angleVu-1)%4  )+4 )%4 ;
    for (int i = 0; i < 12; ++i) {
        newLab.affichageAnim(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(vitesse));
    }
    bool old0=newLab.options[0];
    newLab.options[0]=newLab.options[1];
    newLab.options[1]=newLab.options[2];
    newLab.options[2]=newLab.options[3];
    newLab.options[3]=old0;
    newLab.affichageAnim(0);
}


int main(int argc, char *argv[]) {
    laby leLab =laby(tailleLaby, 3);
    newLab.options[0]=leLab.checkFlag(pos,(angleVu+1)%4);
    newLab.options[1]=leLab.checkFlag(pos,(angleVu)%4);
    newLab.options[2]=leLab.checkFlag(pos,(angleVu+3)%4);
    newLab.options[3]=leLab.checkFlag(pos,(angleVu+2)%4);
    newLab.affichageAnim(0);
    while (true) {
        std::string input;
        std::getline(std::cin, input);
        std::cout << "Tu as tape : " << input << std::endl;
        std::cout << newLab.options[0]<< newLab.options[1] << newLab.options[2] << newLab.options[3] << std::endl;
        if (input=="r") {//faudrait mettre un ptit switch
            rotate();
            std::cout<<" nouvel etat "<< newLab.options[0]<< newLab.options[1] << newLab.options[2] << newLab.options[3] << std::endl;
        }
        else if (input=="z") {
            if (newLab.options[1]) {
                std::cout<<" ancienne position "<<std::endl;
                switch (angleVu) {
                    case 3:
                        pos-=1;
                        break;
                    case 2:
                        pos-=tailleLaby;
                        break;
                    case 1:
                        pos+=1;
                        break;
                    case 0:
                        pos+=tailleLaby;
                        break;
                }
                newLab.options[0]=leLab.checkFlag(pos,(angleVu+1)%4);
                newLab.options[1]=leLab.checkFlag(pos,(angleVu)%4);
                newLab.options[2]=leLab.checkFlag(pos,(angleVu+3)%4);
                newLab.options[3]=leLab.checkFlag(pos,(angleVu+2)%4);
                newLab.affichageAnim(0);
                std::cout<<" nouvelle position "<<pos<<std::endl;
                std::cout<<" nouvel etat "<< newLab.options[0]<< newLab.options[1] << newLab.options[2] << newLab.options[3] << std::endl;
            }
        }

        if (((tailleLaby*tailleLaby)-1)==pos) {
           break;
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

