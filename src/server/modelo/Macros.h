#ifndef TP4_MACROS_H
#define TP4_MACROS_H

#define GRAVITY 15.81
#define ZERO 0.0
#define MAX_LIM 1000.0
#define DELTA_WALLS 1.0
#define FRICTION 0.3
#define DENSITY 1.0
#define GROUND_HIGH 1.0
#define BLOCK_SIZES 1.0
#define ENERGY_BALL_RESITUTION 1.0
#define DELTA_POSITION 0.02
#define FOOT_SENSOR_SIZE 0.04
#define CHELL_HIGH 1.6
#define CHELL_WIDTH 0.5
#define CHELL_JUMP_FORCE 300.0
#define CHELL_MOVE_FORCE 10.0
#define CHELL_QUIET 0
#define CHELL_RUNNING 2
#define CHELL_DANCING 3
#define CHELL_DYING 4
#define CHELL_JUMPING 7
#define CHELL_FALLING 8
#define CHELL_VELOCITY 5.0
#define CHELL_Y_DELTA 1.0
#define CHELL_X_DELTA 0.7
#define ENERGY_BALL 0.5
#define ENERGY_BALL_FORCE 100
#define DELTA_ENERGY_BALL_X 0.5
#define DELTA_ENERGY_BALL_Y 1
#define ROCK_RADIUS 0.5
#define BOTTOM_LARGE 1.0
#define BOTTOM_HIGH 0.25
#define GATE_LARGE 2.0
#define GATE_WIDTH 1.0
#define ENERGY_BARRIER_WIDTH 0.03
#define PORTAL_HIGH 1.0
#define PORTAL_WIDTH 0.3
#define OTHER_BITS 1
#define CHELL_BITS 2
#define BARRIER_BITS 4
#define ROCK_PORTAL_BITS 8
#define BALL_BITS 16

#define UNUSEDBODY(x) (void*)(x)
#define UNUSEDB2VEC2(x) (void)(x)

#endif
