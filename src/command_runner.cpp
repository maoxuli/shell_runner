#include "command_runner.h"
#include "ros_parameter.hpp"

#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;


CommandRunner::CommandRunner(const ros::NodeHandle& nh, const ros::NodeHandle& private_nh)
: _nh(nh)
{   
    std::string command_service = "run_command"; 
    _command_svr = _nh.advertiseService(command_service, &CommandRunner::CommandService, this);
    ROS_INFO_STREAM("Advertised command service: " << command_service); 
}

// shell command service 
bool CommandRunner::CommandService(shell_runner::RunCommand::Request &request,
                                   shell_runner::RunCommand::Response &response)
{
    std::string command = request.command;
    ROS_INFO_STREAM("command service request: " << command);

    if (command.empty())
    {
        ROS_WARN_STREAM("No command in request!"); 
        response.success = false;  
        response.message = "No command in request!"; 
        return false;
    }

    ROS_INFO_STREAM("Shell command line: " << command);
    system(command.c_str());
    response.success = true;  
    return true; 
}
