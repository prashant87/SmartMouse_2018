#pragma once

#ifdef SIM
  #include <gazebo/msgs/msgs.hh>
  #include <gazebo/transport/transport.hh>
  #include <ignition/math.hh>
  #include <mutex>
  #include <condition_variable>
#endif

#include "Direction.h"
#include <stdlib.h>

/** \brief depresents a mouse
 * don't ever change the row/col of a mouse directly. This prevents it from working on the real robot
 * use forward and turn_to_face to move the mouse around. Once those functions work on the real robot it will port over fluidly
 */
class Mouse {

  public:
    /** \brief return the current column.
     * Guaranteed to be between 0 and MAZE_SIZE
     * \return current column
     */
    static int getCol();

    /** \brief return the current row.
     * Guaranteed to be between 0 and MAZE_SIZE
     * \return current row
     */
    static int getRow();

    /** \brief return the current direction.
     * \return current direction
     */
    static Direction getDir();

    /** base functions the emulate mouse movement calls
     * returns -1 if you ran into a wall
     * returns -2 if the mouses's direction is messed up
    */
    static int forward();

    /** check if we're in bounds */
    static bool inBounds();

    /** \brief is the mouse at the center of the maze? */
    static bool atCenter();

    /** literally just sets mouse position. pretty useless, but eventually will cause physical mouse to turn */
    static void turn_to_face(Direction d);
    static void turn_to_face(char c);

  private:

    static void internalTurnToFace(Direction dir);
    static void internalForward();

#ifdef SIM

  private: static float rotation(ignition::math::Pose3d p0,
              ignition::math::Pose3d p1);
  private: static float forwardDisplacement(ignition::math::Pose3d p0,
              ignition::math::Pose3d p1);
  private: static float absYawDiff(float y1, float y2);
  public: static void pose_callback(ConstPosePtr &msg);
  public: static gazebo::transport::PublisherPtr control_pub;
  public: static void simInit();
  private: static ignition::math::Pose3d pose;
  private: static std::mutex pose_mutex;
  private: static std::condition_variable pose_cond;
#endif

    static int row, col;
    static Direction dir;
    static constexpr float ROT_TOLERANCE = 0.04;
};
