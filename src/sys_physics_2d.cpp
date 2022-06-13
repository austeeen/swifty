#include "sys_physics_2d.hpp"
#include "components.hpp"

void Physics2DSystem::update(std::shared_ptr<RigidBody> obj_body, const float dt)
{
    const int in_x_motion = obj_body->moving_right - obj_body->moving_left;
    // ACCELERATION -- X
    obj_body->acl.x = in_x_motion * obj_body->f_move;

    /*
    if (obj_body->vel.x > 0.f) {
        obj_body->acl.x -= obj_body->f_fric;
    } else if (obj_body->vel.x < 0) {
        obj_body->acl.x += obj_body->f_fric;
    }
    */

    // ACCELERATION -- Y
    obj_body->acl.y = obj_body->f_grav;
    if (obj_body->wants_to_jump) {
        obj_body->wants_to_jump = false;
        if (obj_body->grounded) {
            obj_body->setGrounded(false);
            obj_body->vel.y -= obj_body->f_jump;
        }
    }

    // VELOCITY
    obj_body->vel.x += obj_body->acl.x * dt;
    obj_body->vel.y += obj_body->acl.y * dt;

    if (obj_body->vel.x != 0.f) {
        if (fabs(obj_body->vel.x) > obj_body->max_x_vel) {
            if (obj_body->vel.x < 0) {
                obj_body->vel.x = -obj_body->max_x_vel;
            } else {
                obj_body->vel.x = obj_body->max_x_vel;
            }
        } else if (fabs(obj_body->vel.x) < close_to_zero) {
            obj_body->vel.x = 0.f;
        } else {
            // should ignore damping horizontally when in air
            obj_body->vel.x = obj_body->vel.x / (1 + obj_body->f_damp * dt);
        }
    }

    // POSITION
    obj_body->updatePosition(obj_body->vel.x * dt, obj_body->vel.y * dt);

    // DEBUGGING STUFF
    /*
    if (obj_body->vel.y < 0) {
        // printf("ay: %f |  vy: %f\n", obj_body->acl.y, obj_body->vel.y);
    }
    if ((obj_body->vel.x > 0 && obj_body->acl.x < 0) || (obj_body->vel.x < 0 && obj_body->acl.x > 0)) {
        slide_time += dt;
        still_moving = true;
        printf("SLIDING: a: %f |  v: %f\n", obj_body->acl.x, obj_body->vel.x);
        end = true;
    } else if (still_moving && obj_body->vel.x == 0 && obj_body->acl.x == 0) {
        still_moving = false;
        printf("slide time: %f\n", slide_time);
        end = true;
        slide_time = 0.0f;
    }

    if (end) {
        printf("--- \n");
    }
    */
}
