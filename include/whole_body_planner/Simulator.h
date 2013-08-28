/*!
 * \author Janno Lunenburg
 * \date August 2013
 * \version 0.1
 */

#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <WholeBodyController.h>
#include <amigo_whole_body_controller/ArmTaskGoal.h>
#include <nav_msgs/Path.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>

class Simulator
{

public:

    /**
      * Default constructor
      */
    Simulator();

    /**
      * Constructor
      */
    Simulator(const double Ts);

    /**
      * Deconstructor
      */
    virtual ~Simulator();

    /**
      * Initialize function
      */
    void initialize(const double Ts);

    /**
      * Simulates the whole body controller forward to check feasibility
      * @param constraints: Vector of constraints that subsequently have to be satisfied
      * @param max_iter: maximum number of iterations per constraint
      * @param error_index: In case of failure, this indicates which constraint cannot be satisfied. Will become -1 if all constraints are feasible
      */
    bool checkFeasibility(const std::vector<amigo_whole_body_controller::ArmTaskGoal>& constraints, const unsigned int &max_iter, int &error_index);

    /**
      * Updates the current joint positions with the last measured positions
      * @param joint_positions: map with joint names and corresponding joint positions
      */
    bool setInitialJointConfiguration(const std::map<std::string,double>& joint_positions, const geometry_msgs::PoseWithCovarianceStamped& amcl_pose);

    /**
      * Returns the current path
      */
    nav_msgs::Path getPath();

protected:

    /**
      * Whole body controller object for forward simulation
      */
    WholeBodyController* wbc_;

    /**
      * Desired joint positions
      */
    Eigen::VectorXd q_ref_;

    /**
      * Desired joint velocities
      */
    Eigen::VectorXd qdot_ref_;

    /**
      * Map mapping joint names to joint index in vectors
      */
    std::map<std::string, unsigned int> joint_name_to_index_;

    /**
      * Path message containing trajectory
      */
    nav_msgs::Path path_;

};

#endif // SIMULATOR_H