//
//  Game.hpp
//  SFML Game
//
//  Created by Joseph Herkness on 7/4/16.
//  Copyright © 2016 Joseph Herkness. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

class Grid {
public:
    bool* cells;
    bool* newCells;
    bool paused;
    int width;
    int height;
    
    Grid(int width, int height);
    void update();
    void randomize();
    
private:
    int neighbors(int x, int y);
    bool shouldLive(bool alive, int neighbors);
    bool isAlive(int x, int y);
    void toggleState(int x, int y);
};

#endif /* Game_hpp */
