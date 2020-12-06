#ifndef __COMMAND_RUNNER_H
#define __COMMAND_RUNNER_H

#include <ros/ros.h>
#include <shell_runner/RunCommand.h>

class CommandRunner 
{
public: 
    CommandRunner(const ros::NodeHandle& nh = ros::NodeHandle(), 
                  const ros::NodeHandle& private_nh = ros::NodeHandle("~"));

private: 
    // run command service 
    bool CommandService(shell_runner::RunCommand::Request &request,
                        shell_runner::RunCommand::Response &response);

private: 
    ros::NodeHandle _nh;

    // shell command server 
    ros::ServiceServer _command_svr; 
};

#endif // ifndef __COMMAND_RUNNER_H
