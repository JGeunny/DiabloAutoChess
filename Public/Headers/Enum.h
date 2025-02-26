#pragma once

//Struct.h
namespace MATRIX {
	enum ID {
		NONE = OPTION_NONE, SCALE = OPTION_1, ROTATE = OPTION_2, TRANS = OPTION_3
		, REVOLVE = OPTION_4, PARENT = OPTION_5
		, ALL = OPTION_1 | OPTION_2 | OPTION_3 | OPTION_4 | OPTION_5
		, EXCEPT_ROTATE = ALL - ROTATE
	};
}
class ENUM
{
public:
	enum class OrderBy {
		ASC, DESC
	};
	enum class DrawRect {
		IMAGE, COLLISION, LAND
	};
	enum class Team {
		NONE, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT
	};
	enum class Job {
		NONE, KNIGHT, SCOUT, WIZARD, ASSASSIN, END
	};
	enum class Event { //2의 배수로 쓸꺼임
		NOEVENT, DEAD, CLICK
	};
	enum class Target {
		PARENT, FOCUS, ENEMY, END
	};
	enum class LiveTime {
		BASE, LIVE, DEAD, FSM_INIT_ASTAR, MOVE, SKILL, STUN, SLOW, BUFF, END
	};
	enum class ButtonState {
		NONE, NORMAL, DOWN, SELECTED
	};
	enum class MouseState {
		NONE, NORMAL, CLICK, DRAG, 
		SCROLL_D, SCROLL_DL, SCROLL_DR, SCROLL_L, SCROLL_R, 
		SCROLL_U, SCROLL_UL, SCROLL_UR, 
		MAG_ALLY, MAG_ENEMY, TARGET_ALLY, TARGET_ENEMY
	};
	enum class State {
		NONE, IDLE, WALK, ATTACK, DEAD
	};
	enum class Scene {
		NONE, LOADING, TITLE, WORLDMAP, BATTLEFIELD,STAGE1, STAGE2, EDIT, ENDING
	};
	enum class Tile {
		BLANK, BLOCK, ALLY_STACK, ALLY_FIELD, ENEMY_FIELD, END
	};
	enum class MapType {
		TERRAIN, TILE, END
	};
	enum class ObjType{
		PLAYER, UNIT, ITEM, SKILL, EFFECT, END
	};
	enum class UIType {
		EFFECT, TRAIT, INFO, BUTTON, MOUSE, SCENE, END
	};
	enum class Building {
		BASE, BUILDING, FURNITURE, ART, JOY, POWER, LINKED, END
	};
	enum class Unit {
		BASE, PLAYER, MONSTER, ANIMAL, END
	};
	enum class Item {
		BASE, POTION, FOOD, TOOL, CLOTH, RESOURCE, END
	};
	enum class Craft {
		BASE, BUILDING, UNIT, ITEM, END
	};
	enum class FONT {
		NORMAL, FONT16, FONT24, FONT32, FONT40, FONT48, FONT56, END
	};
	enum class BattleState {
		NONE, NORMAL, READY
	};
	enum class ControlState {
		NONE, NOATTACK
	};
};
//TextureMgr
namespace RZIMAGE {
	enum ID { BASE, BACKGROUND, MAP, TILE, AMAZONE, DURIEL, BAVARIAN, ANDARIEL, DIA, IZUAL, 
		BARLOG, COW, SKILL, ICEBOLT, LASER, BONE, EFFECT, STUN, TRAITBUFF, BASEBUTTON, BASEMOUSE, END };
}