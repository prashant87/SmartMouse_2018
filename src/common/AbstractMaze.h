/** maze.h
 * \brief Contains functions for creating and using the AbstractMaze and Node structs
 */
#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "SensorReading.h"
#include "Node.h"
#include "Direction.h"

/**
 * \brief the maze is graph of nodes, stored internally as an matrix.
 * don't forget to call free_maze(maze) after a maze is done being used
 */
class AbstractMaze {
  public:

    const static int MAZE_SIZE = 16;
    const static int PATH_SIZE = 100;
    bool solved; //boolean for if we know the fastest route
    char *fastest_route; //a char array like NSEWNENNSNE, which means North, South, East...

    /** \brief allocates and initializes a node
     * allocates a maze of the given size and sets all links in graph to be null. Naturally, it's column major.
     */
    AbstractMaze();

    /** \brief get node by its position
     * \return 0 on success, OUT_OF_BOUNDS, or -1 on NULL
     */
    int get_node(Node **out, int r, int c);

    /** \brief get neighbor node in a direction from a position
     * \param the adress of the node to set
     * \param row starting row
     * \param col starting col
     * \param dir the direction of the neighbor you want
     * \return 0 on success, OUT_OF_BOUNDS, or -1 on NULL
     */
    int get_node_in_direction(Node **out, int row, int col, const Direction dir);

    /** \brief output a maze that has the fewest walls
     * actually I have no idea how this works
     */
    Node *maze_diff(AbstractMaze *maze2);

    /** \brief get the node that the mouse is currently on
     */
    Node *get_mouse_node();

    Node *center_node();

    /** \brief is the mouse blocked in from by a wall?
     */
    bool is_mouse_blocked();

    /** \brief connect all neighbors in the whole maze
     * \param i row
     * \param j col
     */
    void connect_all_neighbors_in_maze();

    /** \brief add the neighbor in the given direction
     * \param dir direction connect in
     */
    void connect_neighbor(int row, int col, const Direction dir);

    /** \brief add all the neighbors
     */
    void connect_all_neighbors(int row, int col);

    /** \brief remove any neighbor in the given direction
     * \param dir direction connect in
     */
    void remove_neighbor(int row, int col, const Direction dir);

    void mark_origin_known();

    void mark_mouse_position_visited();

    //This method will take a maze and perform a traditional flood fill
    //the fill starts from r0, c0 and ends at r1, c1
    bool flood_fill_from_mouse(char *path, int r1,  int c1);
    bool flood_fill_from_origin(char *path, int r1,  int c1);

    void reset();

    /**
     * \brief uses the information from a sensor read and correctly adds or removes walls from nodes
     * \param row row
     * \param col col
     * \param walls the array of walls
     * \param n the node to update the neighbors of
     */
    void update(SensorReading sr);

    bool is_mouse_blocked(Direction dir);

    /** prints a maze
    * @param maze the maze
    */
    void print_maze();

    /** prints a maze with a mouse in it
    * @param mouse the mouse
    * @param maze the maze
    */
    void print_maze_mouse();

    /** duh*/
    void print_pointer_maze();

    /** prints each node as a list of booleans
    EX)  0010 would mean on wall South
         1011 would mean walls to the North, South, and West

    */
    void print_neighbor_maze();

    /** duh*/
    void print_weight_maze();

    /** duh*/
    void print_dist_maze();

  private:
    bool flood_fill(char *path, int r0, int c0, int r1,  int c1);

  protected:
    Node *nodes[AbstractMaze::MAZE_SIZE][AbstractMaze::MAZE_SIZE]; // array of node pointers
};
