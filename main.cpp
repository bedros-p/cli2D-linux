#include <iostream>
#include <bits/stdc++.h> //for clamp, although i can take the clamp function from old renderwow
#include <map>
#include <vector>
#include <list>
#include <iterator>  
#include <string>
#include <ncurses.h>

#define xSize 20
#define ySize 20

void hideCursor(){printf("\e[?25l");}
void showCursor(){printf("\e[?25h");} //I could just directly print it but its more understandable this way

std::string toColor(int R, int G, int B) { return "\x1B[38;2;" + std::to_string(R) + ";" + std::to_string(G) + ";" + std::to_string(B) + "m"; }
std::string toBG(int R, int G, int B) { return "\x1B[48;2;" + std::to_string(R) + ";" + std::to_string(G) + ";" + std::to_string(B) + "m"; }

std::map<int, std::string> depthMap = {
    {0, toBG(10,10,10) + toColor(100,100,100)},
    {1, toBG(50,50,50) + toColor(50, 50, 50)},
    {2, toBG(100,100,100) + toColor(100, 100, 100)},
    {3, toBG(150,150,150) + toColor(150, 150, 150)},
    {4, toBG(200,200,200) + toColor(200, 200, 200)},
    {5, toBG(250,250,250) + toColor(250, 250, 250)}
};

class vec3 { //totally not inspired by glsl (real)
    public:
        int x,y,z;
        //.begin is a simple cheat for getting subscript capabilities on initializer_list
        //I'm only using initializer_list because its the easy way to initialize a vector, it looks just like std::vector
        vec3 (std::initializer_list<int> list){this->x = list.begin()[0];this->y = list.begin()[1];this->z = list.begin()[2];};
        vec3 (std::vector<int> list){this->x=list[0];this->y=list[1];this->z=list[2];}//vec3(std::vector<int>{1,2,3});
        vec3 (){this->x=0;this->y=0;this->z=0;} //default constructor
        vec3 (int x, int y, int z){this->x=x;this->y=y;this->z=z;} //vec3(1,2,3)
}; //a small price to pay for readability with var.x, var.y, var.z
//I squeezed it to a few lines because i dont want it hogging up the rest of my code

vec3 cameraPos = {0,0,0};
char screen[xSize+1][ySize];

vec3 screenSpace(vec3 object) { //legacy code from old renderwow, but hey it works fine!
    vec3 screenSpaceObj;
    screenSpaceObj.x = (cameraPos.x - object.x) + (int)(xSize / 2);
    screenSpaceObj.y = (cameraPos.y - object.y) + (int)(ySize / 2);
    screenSpaceObj.z = std::clamp((cameraPos.z - object.z),1,5);
    return screenSpaceObj;
}

typedef std::list<vec3*> vecList;
vecList ptrList;

vec3* createPixel(vec3* coords){
    ptrList.push_back(coords);
    return &(*coords);
}

void fillMap(){
    for (int i = 0; i < xSize; i++) {
        for (int j = 0; j < ySize; j++) {
            screen[i][j] = '0';
        }
    }
}

std::string render(){
    fillMap();
    for (vecList::const_iterator itr = ptrList.cbegin(); itr!=ptrList.end();itr++){
        vec3 vec = screenSpace(vec3(*(*itr)));

        if (!(vec.x<0 || vec.x>=xSize || vec.y<0 || vec.y>=ySize)) { //if in screen
            if ((screen[vec.x][vec.y]-'0') < vec.x){ //overlap fix
                screen[vec.x][vec.y] = (vec.z+48); //48 is the ascii value of 0, and 1+48 would give ascii for 1, 2+48 would give ascii for 2, etc.
            }
            //dont handle the else since its not getting rendered if its behind a pixel anyways
        } 
        //dont handle the else since its not getting rendered if its out of bounds anyways
    }


    std::string output = "";
    for(int yIter = 0; yIter < ySize; yIter++){
        for(int xIter=0; xIter < xSize; xIter++){
            output+=depthMap[screen[xIter][yIter]-'0']+"  ";
        }
        output+= "\033[0m\n";
    }
    std::cout << output;
    return output;
}

int main(){
    initscr();
    hideCursor();
    vec3 pixel = {2,0,3};
    pixel = *createPixel(&pixel); //XYZ COORDINATES!!! NO MORE X,DEPTH,Y!!!!!!!!!
    pixel.y+=9;
    
    while(true){ //cursed code incoming
        endwin();
        system("clear");
        render();
        cbreak();
        noecho();
        char keypress = getchar();
        if (keypress == 'q'){
            system("stty sane");
            break;
        }
        if (keypress == 'w'){
            pixel.y++;
        }
        if (keypress == 's'){
            pixel.y--;
        }
        if (keypress == 'a'){
            pixel.x++;
        }
        if (keypress == 'd'){
            pixel.x--;
        }
        
        echo();
        nocbreak();
    }
    showCursor();
    exit_curses(0);

    return 0;
} //you can probably shape this code to be a donut
