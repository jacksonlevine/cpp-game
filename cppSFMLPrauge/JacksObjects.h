#pragma once
#include <string>
#include <unordered_map>
#include "SFML/Graphics.hpp"

namespace objs {

  int clamp(int val, int min, int max);

	class ColorBrick {
	public:
		sf::Color col;
		float elevation;
    ColorBrick(sf::Color c, float elev) {
      col = c;
      elevation = elev;
    };
	};
  
  class ObjectBrick {
  public:
    sf::Color col;
    int obx = 0;
    int oby = 0;
    ObjectBrick() {

    };
    ObjectBrick(sf::Color c, int ox, int oy) {
      obx = ox;
      oby = oy;
      col = c;
    };
  };

  class FixedObject {
  public:
    int width = 0;
    int height = 0;
    int x = 0;
    int y = 0;
    std::string thing;
  };

  class PlayerPixel {
  public:
    sf::Color col;
    int px = 0;
    int py = 0;
    PlayerPixel() {

    };
    PlayerPixel(sf::Color c, int x, int y) {
      col = c;
      px = x;
      py = y;
    };
  };

	class Tree {
	public:
		static std::string makeTree() {
      std::vector<int> intString;
      int width = 26;
      int height = 25;
      int amplitudeX = 3;
      for (int j = 0; j < width; j++) {
        for (int i = 0; i < height; i++) {
          intString.push_back(0);
        }
      }
      sf::Vector2f initialSpot((int)(width / 2), height - 1);

      sf::Vector2f initialDirection(((float)std::rand() / RAND_MAX) - 0.5, 1);

      int trunkheight = std::min(((float)std::rand() / RAND_MAX) * 10, (float)5);
      
      sf::Vector2f nextSpot(0.0, 0.0);
      for (int i = 0; i < trunkheight; i++) {
        intString[clamp(((int)(initialSpot.y) * width) + (int)(initialSpot.x), 0, intString.size()-1)] = 1;
        initialSpot.x += initialDirection.x;
        initialSpot.y -= initialDirection.y;
        nextSpot.x = initialSpot.x;
        nextSpot.y = initialSpot.y;
      }
      
      std::vector<sf::Vector2f> nextSpots;
      for (int i = 0; i < 3; i++) {
        int branchlength = std::max(((float)std::rand() / RAND_MAX) * 5, (float)3);
        sf::Vector2f nextSpot2(0.0, 0.0);
        sf::Vector2f newDirection((((float)std::rand() / RAND_MAX)-0.5)*amplitudeX, 1);
        for (int b = 0; b < branchlength; b++) {
          if (((int)(nextSpot.y) * width) + (int)(nextSpot.x) > 0 && ((int)(nextSpot.y) * width) + (int)(nextSpot.x) < (width * height) - 1) {
            intString[clamp(((int)(nextSpot.y) * width) + (int)(nextSpot.x), 0, intString.size() - 1)] = 1;
          }
          nextSpot.x += newDirection.x;
          nextSpot.y -= newDirection.y;
          nextSpot2.x = initialSpot.x;
          nextSpot2.y = initialSpot.y;
        }
        nextSpots.push_back(nextSpot2);
      }
      
      std::vector<sf::Vector2f> nextSpotsClone = nextSpots;
      std::vector<sf::Vector2f> leafspots;
      
      for (int i = 0; i < 3; i++) {
        for (int t = 0; t < 3; t++) {
          int finlength = std::max(((float)std::rand() / RAND_MAX) * 5, (float)3);
          sf::Vector2f newDirection((((float)std::rand() / RAND_MAX)-0.5)*(float)amplitudeX, 1);
          sf::Vector2f endOfThisBranch(0, 0);
          for (int b = 0; b < finlength; b++) {
            if (((int)std::floor(nextSpots[i].y) * width) + (int)std::floor(nextSpots[i].x) > 0 && ((int)std::floor(nextSpots[i].y) * width) + (int)std::floor(nextSpots[i].x) < (width * height) - 1) {
              intString[clamp(((int)std::floor(nextSpots[i].y) * width) + (int)std::floor(nextSpots[i].x), 0, intString.size() - 1)] = 1;
            
            nextSpots[i].x += newDirection.x;
            nextSpots[i].y -= newDirection.y;
            endOfThisBranch.x = nextSpots[i].x;
            endOfThisBranch.y = nextSpots[i].y;
            }
          }
          if ((endOfThisBranch.y * width) + endOfThisBranch.x > 0 && (endOfThisBranch.y * width) + endOfThisBranch.x < (width * height) - 1) {
            leafspots.push_back(endOfThisBranch);
          }
        }
        for (int n = 0; n < nextSpots.size(); n++) {
          nextSpots[n] = nextSpotsClone[n];
        }
      }
      
      for (sf::Vector2f i : leafspots) {
          intString[clamp(((int)(i.y + 1) * width) + (int)(i.x), 0, intString.size() - 1)] = 3;
          intString[clamp(((int)(i.y + 1) * width) + (int)(i.x - 1), 0, intString.size() - 1)] = 3;
          intString[clamp(((int)(i.y + 1) * width) + (int)(i.x + 1), 0, intString.size() - 1)] = 3;
          intString[clamp(((int)(i.y) * width) + (int)(i.x - 1), 0, intString.size() - 1)] = 3;
          intString[clamp(((int)(i.y) * width) + (int)(i.x + 1), 0, intString.size() - 1)] = 3;
          intString[clamp(((int)(i.y) * width) + (int)(i.x), 0, intString.size() - 1)] = 3;
          intString[clamp(((int)(i.y) * width) + (int)(i.x - 2), 0, intString.size() - 1)] = 3;
          intString[clamp(((int)(i.y) * width) + (int)(i.x + 2), 0, intString.size() - 1)] = 3;
          intString[clamp(((int)(i.y-1) * width) + (int)(i.x - 1), 0, intString.size() - 1)] = 3;
          intString[clamp(((int)(i.y-1) * width) + (int)(i.x + 1), 0, intString.size() - 1)] = 3;
          intString[clamp(((int)(i.y-1) * width) + (int)(i.x), 0, intString.size() - 1)] = 3;
          intString[clamp(((int)(i.y-2) * width) + (int)(i.x - 1), 0, intString.size() - 1)] = 2;
          intString[clamp(((int)(i.y-2) * width) + (int)(i.x + 1), 0, intString.size() - 1)] = 2;
          intString[clamp(((int)(i.y - 2) * width) + (int)(i.x), 0, intString.size() - 1)] = 2;
          intString[clamp(((int)(i.y-1) * width) + (int)(i.x - 2), 0, intString.size() - 1)] = 2;
          intString[clamp(((int)(i.y-1) * width) + (int)(i.x + 2), 0, intString.size() - 1)] = 2;
      }

      std::string string = "";

      for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
          if (intString[clamp((j * width) + i, 0, intString.size()-1)] == 0) {
            string = string + '0';
          }
          if (intString[clamp((j * width) + i, 0, intString.size()-1)] == 1) {
            string = string + 't';
          }
          if (intString[clamp((j * width) + i, 0, intString.size()-1)] == 2) {
            string = string + 'l';
          }
          if (intString[clamp((j * width) + i, 0, intString.size()-1)] == 3) {
            string = string+ 'b';
          }
        }
      }
      return string;
		}
	};

  int clamp(int val, int min, int max) {
    return std::min(std::max(val, min), max);
  }

	class Player{
		std::string name = "";
		public: 
			float x = 0;
			float y = 0;
			int width = 3;
			int height = 5;
			bool jump = false;
			float elevation = 0;
			float gravityForce = 0;
			int jumpForce = 10;

		Player(std::string pname, int px, int py) {
			name = pname;
			x = px;
			y = py;
		};

		Player(std::string pname, int px, int py, int wid, int hei) {
			name = pname;
			x = px;
			y = py;
			width = wid;
			height = hei;
		};

		std::string posKey() {
			return "" + std::to_string((int)(x)) + ',' + std::to_string((int)(y));
		}

		void move(float mx, float my, std::unordered_map<std::string, Player*>* pmap) {
			pmap->erase(posKey());
			x += mx;
			y += my;
			pmap->insert_or_assign(posKey(), this);
		}

		void stepJump() {
			if (jump == true) {
				if (elevation >= 0) {
					elevation += (jumpForce - gravityForce)/2;
					gravityForce+=.4;
				}
				else {
					jump = false;
					gravityForce = 0;
					elevation = 0;
				}
			}
		}
	};
}