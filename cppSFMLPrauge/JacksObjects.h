#pragma once
#include <string>
#include <unordered_map>
#include "SFML/Graphics.hpp"
#include <chrono>

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

	class FixedObject {
	public:
		int width = 0;
		int height = 0;
		int type = 0;
		int x = 0;
		int y = 0;
		int strength = 10;
		std::string thing;

		void clickEvent() {
			strength -= 1;
		}
	};

	class DroppedItem {
	public:
		float x = 0;
		float y = 0;
		int width = 0;
		int height = 0;
		float elevation = 0;
		float PI = 3.1415926535f;
		float angle = 0;
		float x1 = 0;
		float y1 = 0;
		float r = 5;
		float timeStarted = 0;
		std::string thing = "";
		DroppedItem(float ax, float ay) {
			x = ax;
			y = ay;
		};

		void update()
		{
			std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
			angle = (int)((t1.time_since_epoch().count()+timeStarted)/1500000) % 360;
			x1 = r * std::cos(angle * PI / 180);
			y1 = r * std::sin(angle * PI / 180);
			elevation = y1/3;
		} 
	};

	class Particle {
	public:
		int life = 35;
		int timer = 0;
		float x = 0;
		float y = 0;
		sf::Color col = sf::Color(0,0,0);
		float speedX = ((float)std::rand() / RAND_MAX) * 5 - 2;
		float speedY = ((float)std::rand() / RAND_MAX) * 5 - 2;
		float yTravel = 0;
		float maxYTravel = ((float)std::rand() / RAND_MAX) * 7;

		Particle() {

		};

		void update() {
			x += speedX/4;
			speedX *= .95;
			if (yTravel < maxYTravel) {
				y += speedY / 4;
				yTravel += speedY / 4;
			}
			speedY += .1;
			timer += 1;
		}
	};

	bool operator==(const Particle& x, const Particle& y)
	{
		if (x.x == y.x && x.y == y.y) {
			return true;
		}
		else {
			return false;
		}
	}
  
  class ObjectBrick {
  public:
    sf::Color col;
    int obx = 0;
    int oby = 0;
		objs::FixedObject* point;
    ObjectBrick() {

    };
    ObjectBrick(sf::Color c, int ox, int oy) {
      obx = ox;
      oby = oy;
      col = c;
    };
  };



	float getRandom() {
		return (float)std::rand() / RAND_MAX;
	}

  class Rock {
	public:

		static std::string makeRock() {
			int width = 23;
			int height = 15;

			std::vector<int> xVariations;
			xVariations.push_back(0);
			xVariations.push_back(-1);
			xVariations.push_back(-2);
			xVariations.push_back(0);
			xVariations.push_back(-1);
			xVariations.push_back(-2);
			xVariations.push_back(0);
			xVariations.push_back(-1);
			std::vector<int> yVariations;
			yVariations.push_back(0);
			yVariations.push_back(0);
			yVariations.push_back(0);
			yVariations.push_back(-1);
			yVariations.push_back(-1);
			yVariations.push_back(-1);
			yVariations.push_back(-2);
			yVariations.push_back(-2);
			std::vector<int> lightVariations;
			lightVariations.push_back(2);
			lightVariations.push_back(2);
			lightVariations.push_back(3);
			lightVariations.push_back(2);
			lightVariations.push_back(3);
			lightVariations.push_back(3);
			lightVariations.push_back(2);
			lightVariations.push_back(3);

			std::vector<int> intString;

			for (int i = 0; i < width; i++) {
				for (int j = 0; j < height; j++) {
					intString.push_back(0);
				}
			}

			int size = (int)(3 + getRandom() * 6);

			float orx = (int)(width / 2 + (getRandom()));
			float ory = (int)(height - 1);

			for (int i = 0; i < size; i++) {
				float dist = getRandom() * i;
				float brushX = orx + (dist - (getRandom() * i));
				float brushY = ory - dist;
				for (int j = 0; j < xVariations.size(); j++) {
					int index = (int)std::floor(brushX + xVariations[j]) + ((int)std::floor(brushY + yVariations[j]) * width);
					if (index > 0 && index < width * height) {
						intString[index] = lightVariations[j];
					}
				}
			}
			orx = (int)(width / 3) * 2 - getRandom();
			ory = (int)(height - 1);

			for (int i = 0; i < size; i++) {
				float dist = getRandom() * i;
				float brushX = orx + (dist - (getRandom() * i));
				float brushY = ory - dist;
				for (int j = 0; j < xVariations.size(); j++) {
					int index = (int)std::floor(brushX + xVariations[j]) + ((int)std::floor(brushY + yVariations[j]) * width);
					if (index > 0 && index < width * height) {
						intString[index] = lightVariations[j];
					}
				}
			}

			orx = (int)(width / 2.5) + getRandom();
			ory = (int)(height - 1);

			for (int i = 0; i < size; i++) {
				float dist = getRandom() * i;
				float brushX = orx + (dist - (getRandom() * i));
				float brushY = ory - dist;
				for (int j = 0; j < xVariations.size(); j++) {
					int index = (int)std::floor(brushX + xVariations[j]) + ((int)std::floor(brushY + yVariations[j]) * width);
					if (index > 0 && index < width * height) {
						intString[index] = lightVariations[j];
					}
				}
			}

			for (int j = 0; j < height; j++) {
				for (int i = 0; i < width; i++) {
					if (intString[(j * width) + i] == 0) {
						if ((j * width) + i - 1 < width * height && (j * width) + i - 1 > 0) {
							if (intString[(j * width) + i - 1] == 2 || intString[(j * width) + i - 1] == 3) {
								intString[(j * width) + i] = 1;
							}
						}
						if ((j * width) + i + 1 < width * height && (j * width) + i + 1 > 0) {
							if (intString[(j * width) + i + 1] == 2 || intString[(j * width) + i + 1] == 3) {
								intString[(j * width) + i] = 1;
							}
						}
						if ((j * width) + i - width < width * height && (j * width) + i - width > 0) {
							if (intString[(j * width) + i - width] == 2 || intString[(j * width) + i - width] == 3) {
								intString[(j * width) + i] = 1;
							}
						}
						if ((j * width) + i + width < width * height && (j * width) + i + width > 0) {
							if (intString[(j * width) + i + width] == 2 || intString[(j * width) + i + width] == 3) {
								intString[(j * width) + i] = 1;
							}
						}
						if (j == height - 1) {
							if (intString[(j * width) + i] == 2 || intString[(j * width) + i] == 3) {
								intString[(j * width) + i] = 1;
							}
						}
					}
				}
			}

			std::string str = "";
			for (int j = 0; j < height; j++) {
				for (int i = 0; i < width; i++) {
					int index = (j * width) + i;
					if (intString[index] == 0) {
						str = str + '0';
					}
					else
						if (intString[index] == 2) {
							str = str + 'n';
						}
						else
							if (intString[index] == 3) {
								str = str + 's';
							}
							else
								if (intString[index] == 1) {
									str = str + 'a';
								}
				}
			}
			return str;
		}
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