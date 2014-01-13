/* 
 * File:   AsyncState.cpp
 * Author: monchi
 * 
 * Created on December 26, 2013, 6:17 PM
 */

#include "AsyncState.h"

AsyncState::AsyncState() {
}

AsyncState::AsyncState(const AsyncState& orig) {
    ticks = orig.ticks;
    value = orig.value;
    type = orig.type;
}

AsyncState::~AsyncState() {
}

int AsyncState::GetTicks() const {
    return ticks;
}

TypeToDo AsyncState::GetType() const {
    return type;
}

double AsyncState::GetValue() const {
    return value;
}

void AsyncState::SetTicks(int ticks) {
    this->ticks = ticks;
}

void AsyncState::SetValue(double value) {
    this->value = value;
}

void AsyncState::DecreaseTicks() {
    this->ticks--;
}

AsyncState::AsyncState(TypeToDo toDo, double value, int ticks) {
    this->type = toDo;
    this->value = value;
    this->ticks = ticks;
}
