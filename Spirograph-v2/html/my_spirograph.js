function sleep(ms) {
    return new Promise((resolve) => setTimeout(resolve, ms));
}

window.onload = function () {
    // prepare the canvas
    var paper = new Raphael(document.getElementById('container'), 1200, 900);
    var top_x = 200,
        top_y = 200,
        length = 300,
        height = 300,
        radius = 35,
        from_center = 40;

    // call the function to draw rectangle and circle around it
    move_around_rect(top_x, top_y, length, height, radius, from_center, paper);
}

function move_around_rect(top_x,
    top_y,
    length,
    height,
    radius,
    from_center,
    paper) {
    var cur_x = top_x;
    var cur_y = top_y - radius;
    //var cur_circle = paper.circle(top_x, top_y, radius);
    var dist_so_far = 0;

    // just draw the rectangle first
    paper.rect(top_x, top_y, length, height);

    var recur_draw = function () {
        // remove the previously drawn circle
        //cur_circle.remove();

        // re-evaluate the new position of the circle
        var new_pos = get_new_position_for_rect(top_x,
            top_y,
            length,
            height,
            cur_x,
            cur_y,
            radius);

        cur_x = new_pos.x;
        cur_y = new_pos.y;

        if (false === new_pos.is_jump) {
            dist_so_far += new_pos.d;
        }

        draw_cur_dot(cur_x, cur_y, radius, dist_so_far, from_center, paper);

        // draw the circle
        //cur_circle = paper.circle(cur_x, cur_y, radius);

        setTimeout(recur_draw);
    };

    setTimeout(recur_draw);
}

function draw_cur_dot(cur_x,
    cur_y,
    radius,
    dist_so_far,
    from_center,
    paper) {
    // compute angle
    var angle = (dist_so_far / radius);

    var pi_prod = (angle / (2 * Math.PI));
    angle -= ((pi_prod | 0) * (2 * Math.PI));

    // find position of the red dot
    // assumption: it begins at top
    var dot_x = cur_x + (Math.sin(angle) * from_center);
    var dot_y = cur_y - (Math.cos(angle) * from_center);

    // draw a small dot there
    paper.circle(dot_x, dot_y, 1);
}

function get_new_position_for_rect(top_x,
    top_y,
    length,
    height,
    cur_x,
    cur_y,
    radius) {
    to_return = {};
    var is_jump = false;

    if (cur_x < top_x) {
        if (cur_y > top_y) {
            cur_y -= 1;
        }
        else {
            // move it to top
            cur_x = top_x;
            cur_y = top_y - radius;
            is_jump = true;
        }
    }
    else if (cur_x == top_x) {
        if (cur_y < top_y) {
            // at start, so add 1
            cur_x += 1;
        }
        else if (cur_y > (top_y + height)) {
            // on bottom at left end
            cur_x = top_x - radius;
            cur_y = top_y + height;
            is_jump = true;
        }
    }
    else if (cur_x < (top_x + length)) {
        if (cur_y < top_y) {
            // on top, rolling right
            cur_x += 1;
            if (cur_x > (top_x + length)) {
                cur_x = top_x + length;
            }
        }
        else if (cur_y > (top_y + height)) {
            // on bottom rolling left
            cur_x -= 1;
            if (cur_x < (top_x)) {
                cur_x = top_x;
            }
        }
    }
    else if (cur_x == (top_x + length)) {
        if (cur_y < top_y) {
            cur_y = top_y;
            cur_x = top_x + length + radius;
            is_jump = true;
        }
        else if (cur_y > (top_y + height)) {
            cur_x -= 1;
        }
    }
    else if (cur_x > (top_x + length)) {
        if (cur_y == (top_y + height)) {
            cur_y = top_y + height + radius;
            cur_x = top_x + length;
            is_jump = true;
        }
        else {
            cur_y += 1;
        }
    }

    to_return.x = cur_x;
    to_return.y = cur_y;
    to_return.is_jump = is_jump;
    // currently constant
    // to be ignored if it is a jump
    to_return.d = 1;

    return to_return;
}