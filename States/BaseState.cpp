#include"BaseState.h"
#include<string>
using namespace std;

BaseState::BaseState(){};
BaseState::~BaseState(){};
void BaseState::enter(string enterParams){};
void BaseState::enter(){};
void BaseState::exit(){};
void BaseState::bgrender(){};
void BaseState::render(){};
void BaseState::update(){};