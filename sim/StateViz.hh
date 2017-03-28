#pragma once

#ifndef Q_MOC_RUN  // See: https://bugreports.qt-project.org/browse/QTBUG-22829

#include <gazebo/transport/transport.hh>
#include <gazebo/gui/gui.hh>

#endif

#include <QtGui/QPainter>
#include "msgs/msgs.h"

namespace gazebo {
  class GAZEBO_VISIBLE StateViz : public GUIPlugin {
  Q_OBJECT

  public:
    StateViz();

    virtual ~StateViz();

  signals:

    void SetLeftVelocity(QString str);

    void SetRightVelocity(QString str);

    void SetRow(QString str);

    void SetCol(QString str);

    void SetDir(QString str);

  protected slots:

    void ClearRobotTrace();

  private:
    gazebo::msgs::Pose last_pose;

    std::string topic;

    transport::NodePtr node;
    transport::SubscriberPtr state_sub;
    transport::SubscriberPtr maze_loc_sub;
    ignition::transport::Node ign_node;
    ignition::transport::Node::Publisher pub;

    QLabel *left_wheel_velocity_label;
    QLabel *right_wheel_velocity_label;
    QLabel *col_label;
    QLabel *row_label;
    QLabel *dir_label;

    QLineEdit *left_wheel_velocity_edit;
    QLineEdit *right_wheel_velocity_edit;
    QLineEdit *col_edit;
    QLineEdit *row_edit;
    QLineEdit *dir_edit;

    void StateCallback(ConstRobotStatePtr &msg);

    void MazeLocationCallback(ConstMazeLocationPtr &msg);
  };
}