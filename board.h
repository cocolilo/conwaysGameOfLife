#ifndef BOARD_H
    #define BOARD_H

    #include <stdio.h>
    #include <stdint.h>
    #include <ctype.h>
    #include <time.h>
    #include <string.h>
    #include <math.h>
    #include <assert.h>
    #include <stdlib.h>
    #include <limits.h>

    #include <SDL2/SDL.h>

    #define FALSE 0
    #define TRUE 1

    #define LIVING_CELL_R 255
    #define LIVING_CELL_G 255
    #define LIVING_CELL_B 255
    #define DEAD_CELL_R 20
    #define DEAD_CELL_G 20
    #define DEAD_CELL_B 20

    typedef Uint8 bool;

    #if defined(_M_IX86) || defined(__i386__) //32 bits

        typedef struct
        {
            uint32_t rows;
            uint32_t columns;
            bool grid[ 0 ];
        } board;
    #elif defined(__x86_64__) //64 bits
        typedef struct
        {
            uint64_t rows;
            uint64_t columns;
            bool grid[ 0 ];
        } board;
    #else //unknown architecture
            typedef struct
        {
            int rows;
            int columns;
            bool grid[ 0 ];
        } board;
    #endif

    typedef struct
    {
        int camera_x;
        int camera_y;
        int cell_size;
        int height_in_cells;
        int width_in_cells;
        int window_height;
        int window_width;
        // The movement speed in cell depends on the movement speed in pixels but is never less then 1
        int movement_speed_in_cells;
        int min_movement_speed_in_pixels;
    } view;


    /**
    * Initialize a board with a given size and a given number of
    * living cells.
    */
    board* init_board( int rows, int columns, int living_cell_count );

    /**
    * Update the board's state and return the number of living cells.
    */
    int update_board( board* b );

    /**
    * Return the state of the cell at location x, y in the given board
    */
    static inline bool cell_state( int x, int y, board* b );

    /**
    * Return the updated state of the cell at location x, y in the given board
    */
    static inline bool updated_cell_state( int x, int y, board* b );

    /**
    * Invert the state of the given cell ( alive -> dead and dead -> alive )
    */
    void toggle_cell_state( int x, int y, board *b );

    /** 
    * Draw the given board to the window.
    */
    void draw_board( board* b, view *player_view, SDL_Renderer* renderer );

    /**
    * Kill all cells in the given board.
    */
    void kill_all_cells( board* b );

    /**
    * Resizes the view. Adds the zoom factor the cell_size. 
    * ( i.e a negative zoom factor zooms out and a positive zoom factor zooms in)
    */
    void resize_board_view( int zoom, view* player_view, board* world );


    /**
    * Moves the camera in the given direction by a given amount.
    * If it's not possbile to move by x and y it moves as far in the direction as possible.
    * And if the camera position is out of bounds it doesn't move the camera at all.
    */
    void move_camera_by( int x, int y, view* player_view, board* game_board, SDL_Window* window );

#endif
