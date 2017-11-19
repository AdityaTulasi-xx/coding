#include <stdio.h>
#include <math.h>

// checks whether the piece is obstructing
// the line of visibility
int is_obstructing(int r,
    int c,
    int x_dir,
    int y_dir,
    int obs_r,
    int obs_c)
{
    int delta_x = obs_r - r;
    int delta_y = obs_c - c;

    int x_valid = 0;
    int y_valid = 0;

    if ((delta_x == 0 && x_dir == 0)
        || (delta_x < 0 && x_dir < 0)
        || (delta_x > 0 && x_dir > 0))
    {
        x_valid = 1;
    }

    if ((delta_y == 0 && y_dir == 0)
        || (delta_y > 0 && y_dir > 0)
        || (delta_y < 0 && y_dir < 0))
    {
        y_valid = 1;
    }

    if (x_valid == 1 && y_valid == 1)
    {
        // validate the distances and slopes
        if (x_dir != 0 && y_dir != 0)
        {
            if (abs(delta_x) != abs(delta_y))
            {
                // not a valid point
                return 0;
            }
        }

        return 1;
    }

    // if one of them isn't valid then return
    return 0;
}

// gets the distance (in number of squares)
// between the original piece and this piece
int get_distance(int r,
    int c,
    int obs_r,
    int obs_c)
{
    int delta_x = abs(obs_r - r);
    int delta_y = abs(obs_c - c);

    return delta_x == 0 ? delta_y - 1 : delta_x - 1;
}

int get_max_distance(int r,
    int c,
    int x_dir,
    int y_dir,
    int n)
{
    int x_dist = 0;
    int y_dist = 0;

    if (x_dir < 0)
    {
        x_dist = r - 1;
    }
    else if (x_dir > 0)
    {
        x_dist = n - r;
    }

    if (y_dir < 0)
    {
        y_dist = c - 1;
    }
    else if (y_dir > 0)
    {
        y_dist = n - c;
    }

    // return no of cols if it's horizontal or vertical
    if (x_dir == 0)
    {
        return y_dist;
    }
    else if (y_dir == 0)
    {
        return x_dist;
    }

    // return min of both if it's oblique
    return x_dist > y_dist ? y_dist : x_dist;
}

int pos_count(int r,
    int c,
    int x_dir,
    int y_dir,
    int obs_r[],
    int obs_c[],
    int k,
    int n)
{
    int max_distance = get_max_distance(r, c, x_dir, y_dir, n);;

    for (int i = 0; i < k; i++)
    {
        if (is_obstructing(r, c, x_dir, y_dir, obs_r[i], obs_c[i]))
        {
            // printf("Yes obstructing x_dir: %d y_dir: %d obs_r: %d obs_c: %d\n", x_dir, y_dir, obs_r[i], obs_c[i]);
            if (get_distance(r, c, obs_r[i], obs_c[i]) < max_distance)
            {
                max_distance = get_distance(r, c, obs_r[i], obs_c[i]);
            }
        }
    }

    // printf("Max distance is x_dir: %d y_dir: %d dist: %d\n", x_dir, y_dir, max_distance);
    return max_distance;
}

int main()
{
    int n;
    int k;
    int r, c;

    scanf("%d %d", &n, &k);
    scanf("%d %d", &r, &c);

    // reading positions of obstacles
    int obs_r[k];
    int obs_c[k];

    for (int i = 0; i < k; i++)
    {
        scanf("%d %d", &(obs_r[i]), &(obs_c[i]));
    }

    int total_positions = 0;

    // if we aren't on top row
    if (r < n && c > 1)
    {
        total_positions += pos_count(r, c, 1, -1, obs_r, obs_c, k, n);
    }
    if (r <= n && c > 1)
    {
        total_positions += pos_count(r, c, 0, -1, obs_r, obs_c, k, n);
    }
    if (r < n && c <= n)
    {
        total_positions += pos_count(r, c, 1, 0, obs_r, obs_c, k, n);
    }
    if (r < n && c < n)
    {
        total_positions += pos_count(r, c, 1, 1, obs_r, obs_c, k, n);
    }
    if (r <= n && c < n)
    {
        total_positions += pos_count(r, c, 0, 1, obs_r, obs_c, k, n);
    }
    if (r > 1 && c < n)
    {
        total_positions += pos_count(r, c, -1, 1, obs_r, obs_c, k, n);
    }
    if (r > 1 && c <= n)
    {
        total_positions += pos_count(r, c, -1, 0, obs_r, obs_c, k, n);
    }
    if (r > 1 && c > 1)
    {
        total_positions += pos_count(r, c, -1, -1, obs_r, obs_c, k, n);
    }

    printf("%d\n", total_positions);

    return 0;
}