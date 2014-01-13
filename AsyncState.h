/* 
 * File:   AsyncState.h
 * Author: monchi
 *
 * Created on December 26, 2013, 6:17 PM
 */

#ifndef ASYNCSTATE_H
#define	ASYNCSTATE_H
enum TypeToDo { Thrust=0, Pitch, Roll, Yaw};

class AsyncState {
public:
    AsyncState();
    AsyncState(const AsyncState& orig);
    AsyncState(TypeToDo toDo, double value, int ticks);
    virtual ~AsyncState();
    int GetTicks() const;

    void SetTicks(int ticks);

    TypeToDo GetType() const;

    double GetValue() const;

    void SetValue(double value) ;
    
    void DecreaseTicks();

private:
    TypeToDo type;
    double value;
    int ticks;
};

#endif	/* ASYNCSTATE_H */

